#ifndef DIRECT_WINDOW_H
#define DIRECT_WINDOW_H

#include <d2d1.h>
#pragma comment(lib, "d2d1")
#include <algorithm>

#include "basewindow.h"

template <class T> void SafeRelease(T **ppt);

class DirectWindow : public BaseWindow<DirectWindow>{
    //private by default
    ID2D1Factory            *pFactory;
    ID2D1HwndRenderTarget   *pRenderTarget;
    ID2D1SolidColorBrush    *pBrush;
    D2D1_ELLIPSE            ellipse;

    void    CalculateLayout();
    HRESULT CreateGraphicsResources();
    void    DiscardGraphicsResources();
    void    OnPaint();
    void    Resize();

public:
    //What does it mean? - it initiliazs the class members of DirectWindow
    DirectWindow() : pFactory(NULL), pRenderTarget(NULL), pBrush(NULL)
    {
    }

    PCWSTR  ClassName() const { return L"Circle Window Class"; }
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif