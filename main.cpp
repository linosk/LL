#ifndef UNICODE
#define UNICODE
#endif

#include <tchar.h>
#include <Windows.h>
#include <new>

struct StateInfo{

};

void OnSize(HWND hwnd, UINT flag, int width, int height){
  //TODO
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

  switch(uMsg){
    /*
    case WM_SIZE:{
      int width = LOWORD(lParam);
      int height= HIWORD(lParam);

      OnSize(hwnd, (UINT)wParam, width, height);    
    }break;
    return 0;
    */

    case WM_PAINT:{
      PAINTSTRUCT ps;

      HDC hdc = BeginPaint(hwnd, &ps);

      FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW+1));

      EndPaint(hwnd, &ps);
    }break;
    return 0;

    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;

    /*
    case WM_CLOSE:{
      if (MessageBox(hwnd,L"Really quit?",L"My application",MB_OKCANCEL) == IDOK){
        DestroyWindow(hwnd);
      }
    }
    return 0;
    */
  }

  return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow){

  //There is a mismatch between LPCSTR type and const wchar_t... for some reason?
  //RESOLUTION: UNICODE needs to be defined in macro-way
  const wchar_t CLASS_NAME[] = L"Window Class";
  WNDCLASS wc = {};

  //wc.lpfnWndProc = WindowProc; &THIS HAS TO BE DEFINED NEXT ALONG WITH THE MESSAGE DECODING&
  //https://learn.microsoft.com/en-us/windows/win32/learnwin32/window-messages
  //https://learn.microsoft.com/en-us/windows/win32/learnwin32/writing-the-window-procedure

  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = CLASS_NAME;

  RegisterClass(&wc);

  //Is using new good idea?
  //StateInfo *pState = new (std::nothrow) StateInfo;

  //CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT>

  //Remember reinterpret_cast
  //CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
  //pState = reinterpret_cast<StateInfo*>(pCreate->lpCreateParams);
  //SetWindowsLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pState);

  //if(pState == NULL){
  //  return 0;
  //}

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
    //pState
    NULL
  );

  if (hwnd == NULL){
    return 0;
  }

  ShowWindow(hwnd, nCmdShow);

  MSG msg = {};
  //Msg arriving to a procees in queue
  //GetMessage(&msg,NULL,0,0);

  //Then only case in which GetMessage can return nonzero value is when WM_QUIT message is placed in message queue. Calling PostQuitMessage causes this. 
  while (GetMessage(&msg, NULL, 0, 0) > 0)
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  //delete(pState);

  return 0;
}