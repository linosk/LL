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

    //Constructor may be createad by deafult, following line may be pointless
    BaseWindow();
    //Destructor can be overridden, is it good?
    virtual ~BaseWindow() {}

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    //Some values are assigned to make it easier for possible calls
    BOOL Create(
        PCWSTR lpWindowName,
        DWORD dwStyle,
        DWORD dwExStyle = 0,
        int x = CW_USEDEFAULT,
        int y = CW_USEDEFAULT,
        int nWidth = CW_USEDEFAULT,
        int nHeight = CW_USEDEFAULT,
        HWND hWndParent = 0,
        HMENU hMenu = 0
    );

    //public vs protected vs private
    //public can be accesed outside of class
    //private can not be accesed outside of class
    //protected can not be accesed outside of class, but can be accesed in inherited classes

    //BaseWindow() : m_hwnd(NULL);

    //This function cannot modify class members
    //HWND Window () const {return m_hwnd};
    HWND Window() const { return m_hwnd; }
    //Should this retunrn be in cpp file?

protected:
    //Why is 0 assigned to those variables?
    virtual PCWSTR ClassName() const = 0;
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

    HWND m_hwnd;
};

#endif // BASE_WINDOW_H