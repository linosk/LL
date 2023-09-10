#include "basewindow.h"

#include <iostream>

template <class DERIVED_TYPE>

//Apperently it is enough to define that funciont is static in header file
LRESULT CALLBACK BaseWindow<DERIVED_TYPE>::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

    // 
    DERIVED_TYPE *pThis = NULL;

    if (uMsg == WM_NCCREATE){
        //reinterpret_cast?
        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        pThis = (DERIVED_TYPE*)pCreate->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

        pThis->m_hwnd = hwnd;
    }
    else{
        //reinterpret_cast?
        pThis = (DERIVED_TYPE*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }

    if(pThis){
        return pThis->HandleMessage(uMsg,wParam,lParam);
    }
    else{
        //Specifing Unicode characters is neccesary
        return DefWindowProcW(hwnd, uMsg, wParam, lParam);
    }

}

template <class DERIVED_TYPE>
BaseWindow<DERIVED_TYPE>::BaseWindow() : m_hwnd(nullptr) {}

template <class DERIVED_TYPE>
BOOL BaseWindow<DERIVED_TYPE>::Create(
        PCWSTR lpWindowName,
        DWORD dwStyle,
        DWORD dwExStyle ,
        int x,
        int y,
        int nWidth,
        int nHeight,
        HWND hWndParent,
        HMENU hMenu
){
    WNDCLASS wc = {0};

    wc.lpfnWndProc = BaseWindow<DERIVED_TYPE>::WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = ClassName();

    RegisterClass(&wc);

    m_hwnd = CreateWindowEx(dwExStyle, ClassName(), lpWindowName, dwStyle, x, y,
            nWidth, nHeight, hWndParent, hMenu, GetModuleHandle(NULL), this
    );

    //Checking if m_hwnd is not NULL, if so return TRUE, otherwise FALSE
    return (m_hwnd ? TRUE : FALSE);  
}