#ifndef ___UTIL___
#define ___UTIL___
// #define _GLIBCXX_USE_CXX11_ABI 0

// __cplusplus gets defined when a C++ compiler processes the file
#ifdef __cplusplus
// extern "C" is needed so the C++ compiler exports the symbols without name
// manging.
extern "C" {
#endif

const char* GetDotValue(const char* file_name);

#ifdef __cplusplus
}
#endif

#endif
