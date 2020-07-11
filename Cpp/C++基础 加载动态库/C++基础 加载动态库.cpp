//main.cpp
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#define LIB_LIBRARY_PATH_1 "./libcal.so"

typedef int (*CAC_FUNC)(int ,int);

int main() {
	void* handler = NULL;
	char* error = NULL;
	CAC_FUNC cac_func = NULL;

	handler = dlopen(LIB_LIBRARY_PATH_1, RTLD_LAZY);
	if (!handler) {
		fprintf(stderr, "err:%s\n", dlerror());
		exit(1);
	}

	dlerror();

  //此处取对应函数地址,
	*(void **) (&cac_func) = dlsym(handler, "add");
	if ((error = dlerror()) != NULL) {
		fprintf(stderr, "err:%s", error);
		exit(1);
	}

	printf("add:%d\n", cac_func(1,2));

	cac_func = (CAC_FUNC)dlsym(handler, "sub");
	printf("sub:%d\n", cac_func(1,2));

	cac_func = (CAC_FUNC)dlsym(handler, "mul");
	printf("mul:%d\n", cac_func(1,2));

	cac_func = (CAC_FUNC)dlsym(handler, "div");
	printf("div:%d\n", cac_func(1,2));

	dlclose(handler);
	return 0;
}