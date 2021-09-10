# A minimal Lean4 plugin example

The build code is based on the excellent [lean4-papyrus](https://github.com/tydeu/lean4-papyrus/tree/master) stripped to a minimal example.

To test it run
```
make test
```
Unfortunately this fails at the moment with 
```
could not find native implementation of external declaration 'Example.funA' (symbols 'l_Example_funA___boxed' or 'l_Example_funA')
```
however 
```
nm -D -C plugin/build/ExamplePlugin.dll | grep l_Example_funA___boxed
```
finds the symbol successfully.