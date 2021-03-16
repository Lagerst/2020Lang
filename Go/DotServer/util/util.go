package util

/*
#cgo  CFLAGS:  -I  ./include
#cgo  LDFLAGS:  -L ./lib  -lopencv_core -lopencv_highgui -lopencv_imgproc
#include <stdlib.h>
#include "util.h"
*/
import "C"

import (
	"errors"
	"runtime"
	"strings"
	"unsafe"
)

func Substr(s string, pos, length int) string {
	runes := []rune(s)
	l := pos + length
	if l > len(runes) {
		l = len(runes)
	}
	return string(runes[pos:l])
}

func GetParentDirectory(dirctory string) string {
	return Substr(dirctory, 0, strings.LastIndex(dirctory, "/"))
}

func CurrentFile() string {
	_, file, _, ok := runtime.Caller(1)
	if !ok {
		panic(errors.New("Can not get current file info"))
	}
	return file
}

func GetDotValue(file_name string) string {
	cstr := C.CString(file_name)
	res := C.GetDotValue(cstr)
	C.free(unsafe.Pointer(cstr))
	return C.GoString(res)
}
