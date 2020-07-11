#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
//#include <iostream>

int main()
 {
     wchar_t words[2];
     setlocale(LC_CTYPE, "chs");
     //std::wcout.imbue(std::locale("chs"));
     /*wchar_t zi =L'你';*/
     //wprintf(L"%c\n",zi);
     words[0]=L'你';
     words[1] =L'\0';
     wprintf(L"%s\n",words);
     return 0;
 } //wrong