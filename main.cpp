#include <Windows.h>

//Apparently all the strings should be ASCII code based
//g++ .\main.cpp -o main.exe -lgdi32
LRESULT Wndproc(
  HWND hWindow,
  UINT uMessage,
  WPARAM wParam,
  LPARAM lParam
)
{

  LRESULT Result = 0;

  //No debug messages
  //Issue is here
  switch(uMessage){
    case WM_SIZE:
    {
      OutputDebugStringA("WM_SIZE");
    }break;
    case WM_DESTROY:
    {
      OutputDebugStringA("WM_DESTROY");
    }break;
    case WM_CLOSE:
    {
      OutputDebugStringA("WM_CLOSE");
    }break;
    case WM_ACTIVATEAPP:
    {
      OutputDebugStringA("WM_ACTIVATEAPP");
    }break;
    case WM_PAINT:
    {
      PAINTSTRUCT Paint;
      HDC DeviceContext = BeginPaint(hWindow,&Paint);
      LONG Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
      LONG Width = Paint.rcPaint.right - Paint.rcPaint.left;
      PatBlt(DeviceContext,Paint.rcPaint.left, Paint.rcPaint.right,Width,Height,BLACKNESS);
      EndPaint(hWindow,&Paint);
    }break;
    default:
    {
      OutputDebugStringA("default");
      Result = DefWindowProc(hWindow,uMessage,wParam,lParam);
    }break;
    
  }

  return Result;
}

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

    //MessageBoxA(0,"Hello world!","Title",MB_OK|MB_ICONINFORMATION);

    //Is a struct, = {} initializes all members to "0 value"
    WNDCLASSA Window = {};

    //Recheck later
    Window.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
    Window.lpfnWndProc = Wndproc;
    //Window.cbClsExtra = 0;
    //Window.cbWndExtra = 0;
    Window.hInstance = hInstance;
    //Window.hIcon = 0; //Icon of an app
    //Window.hCursor = 0; //Important for later, mouse cursor
    //Window.hbrBackground = 0; //Background color?
    //Window.lpszMenuName = 0;
    Window.lpszClassName = "idk";

    if (RegisterClassA(&Window)){
   
    HWND WindowHandle = CreateWindowExA(
          0,
          Window.lpszClassName,
          "LL",
          WS_OVERLAPPEDWINDOW|WS_VISIBLE,
          CW_USEDEFAULT,
          CW_USEDEFAULT,
          CW_USEDEFAULT,
          CW_USEDEFAULT,
          0,
          0,
          hInstance,
          0);
          //Check if not NULL
          if(WindowHandle){
            MSG Message;
            for(;;){
              BOOL MSGRES = GetMessageA(&Message,0,0,0);
              if (MSGRES>0){
                TranslateMessage(&Message);
                DispatchMessage(&Message);
              }
              else{
                break;
              }
            }
          }
          else{
            //TODO
          }
    }
    else{
      //TODO
    }
    return 0;
  }