#include <iostream>
#include <Windows.h>

//CONSIDER WHAT IS GOING ON UP THE CALLSTACK

//an entry point windows graphical application
//called by C runtime library(CRT)
int CALLBACK 
WinMain(
  HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPSTR     lpCmdLine,
  int       nShowCmd)
  {

    MessageBoxA(0,"Hello world!","Title",MB_OK|MB_ICONINFORMATION);

    return 0;
  }