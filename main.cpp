#ifndef UNICODE
#define UNICODE
#endif

#include <tchar.h>
#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow){

  //There is a mismatch between LPCSTR type and const wchar_t... for some reason?
  //RESOLUTION: UNICODE needs to be defined in macro-way
  const wchar_t CLASS_NAME[] = L"Window Class";
  WNDCLASS wc = {};

  //wc.lpfnWndProc = WindowProc; &THIS HAS TO BE DEFINED NEXT ALONG WITH THE MESSAGE DECODING&
  //https://learn.microsoft.com/en-us/windows/win32/learnwin32/window-messages
  //https://learn.microsoft.com/en-us/windows/win32/learnwin32/writing-the-window-procedure

  wc.hInstance = hInstance;
  wc.lpszClassName = CLASS_NAME;

  RegisterClass(&wc);

  HWND hwnd = CreateWindowEx(
    0,
    CLASS_NAME,
    L"Window text",
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    NULL,
    NULL,
    hInstance,
    NULL
  );

  if (hwnd == NULL){
    return 0;
  }

  ShowWindow(hwnd, nCmdShow);

  return 0;
}