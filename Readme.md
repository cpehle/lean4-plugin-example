# A minimal Lean4 plugin example

The build code is based on the excellent [lean4-papyrus](https://github.com/tydeu/lean4-papyrus/tree/master) stripped to a minimal example. A plugin is a way of extending Lean with native code that can be used by the
interpreter, thereby enabling interactive use in Visual Studio Code and other editors supporting the Language Server protocol. 

This example consists of four parts: 
- A very simple c++ library implemented in the ```cc/``` containing one
    function 
    ```c++ 
    int funA(uint64_t a) {
        return a * a;
    }
    ```
- A Lean package ```Example```, which declares the extern constant funA in ```Example/Basic.lean```
    ```lean
    namespace Example

    @[extern "funA"] constant funA (a : UInt64) : UInt64
    ```
- A plugin in ```ExamplePlugin/```, which is compiled into a dynamic library to be loaded as a plugin by ```lean```
- Infrastructure for defining tests in the test/ subdirectory


To test this example you can run
```
make test
```
There are differences in how Lean resolved symbols on Windows / Linux at the moment. For this reason it
is not sufficient to just pass in the compiled dynamic library as a plugin to lean. This fails in Unix systems at the moment with 
```
could not find native implementation of external declaration 'Example.funA' (symbols 'l_Example_funA___boxed' or 'l_Example_funA')
```
however 
```
nm -D -C plugin/build/ExamplePlugin.dll | grep l_Example_funA___boxed
```
finds the symbol successfully. The solution is to also instruct the dynamic linker to preload the
symbols from the generated dynamic library by using ```LD_PRELOAD=$(PWD)/plugin/build/ExamplePlugin.dll```.


## Using the Plugin in VSCode

If you navigate to the ```test/out/ex/ex0.lean``` file, you will hopefully see that evaluation
of the function defined in the plugin just works. This is due to workspace setting in ```.vscode/settings.json```. It tells the language server to use the ```./leanWithPlugin.sh``` script instead of the vanilla
```lean``` executable. Otherwise one would get the error

```
terminate called after throwing an instance of 'lean::exception'
  what():  could not find native implementation of external declaration 'Example.funA' (symbols 'l_Example_funA___boxed' or 'l_Example_funA')
[Error - 12:49:17 PM] Request textDocument/semanticTokens/range failed.
  Message: Server process for file:///home/cpehle/work/lean4-plugin-example/test/run/ex/ex0.lean crashed, likely due to a stack overflow in user code.
  Code: -32603 
[Error - 12:49:17 PM] Request textDocument/semanticTokens/full failed.
  Message: Server process for file:///home/cpehle/work/lean4-plugin-example/test/run/ex/ex0.lean crashed, likely due to a stack overflow in user code.
  Code: -32603 
terminate called after throwing an instance of 'lean::exception'
  what():  could not find native implementation of external declaration 'Example.funA' (symbols 'l_Example_funA___boxed' or 'l_Example_funA')
[Error - 1:10:20 PM] Request textDocument/semanticTokens/full failed.
  Message: Server process for file:///home/cpehle/work/lean4-plugin-example/test/out/ex/ex0.lean crashed, likely due to a stack overflow in user code.
  Code: -32603 
```