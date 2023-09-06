#ifndef BASE_WINDOW_H
#define BASE_WINDOW_H

#ifndef UNICODE
#define UNICODE
#endif

#include <tchar.h>
#include <Windows.h>
#include <new>

template <class DERIVED_TYPE>
class BaseWindow{
public:
    BaseWindow();
    //Destructor can be overridden, is it good?
    virtual ~BaseWindow() {}

    //For what?
    BOOL Create{
        PCWSTR lpWindowName,
        DWORD dwStExStyle = 0,
        int x = CW_USEDEFAULT,
        int y = CW_USEDEFAULT,
        int nWidth = CW_USEDEFAULT,
        int nHeigth = CW_USEDEFAULT,
        HWND hWndParent = 0,
        HMENU hMenu = 0
    };

    HWND Window() const {return m_hwnd; }
//public vs protected

protected:
    virtual PCWSTR ClassName() const = 0;
    virtual LRESULT HndleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

    HWND m_hwnd;
};

#endif // BASE_WINDOW_H