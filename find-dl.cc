#include <dlfcn.h>
#include <stdio.h>

typedef int (*func_ptr_t)(int);

int main() {
    auto handle = dlopen("./plugin/build/ExamplePlugin.dll", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error loading library: %s", dlerror());        
    }
    auto fun = dlsym(handle, "l_Example_funA___boxed");
    if (fun == NULL) {
        fprintf(stderr, "Error finding funcion: %s", dlerror());
        return 1;
    }

    auto funA = reinterpret_cast<func_ptr_t>(dlsym(handle, "funA"));
    if (fun == NULL) {
        fprintf(stderr, "Error finding funcion: %s", dlerror());
        return 1;
    }
    printf("f(%d) = %d\n", 2, funA(2));
    return 0;
}