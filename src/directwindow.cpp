#include "directwindow.h"

template <class T> void SafeRelease(T **ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}

void DirectWindow::CalculateLayout(){
    if (pRenderTarget != NULL){
        D2D1_SIZE_F size = pRenderTarget->GetSize();
        const float x = size.width/2;
        const float y = size.height/2;
        const float radius = std::min(x,y);
        ellipse = D2D1::Ellipse(D2D1::Point2F(x,y), radius, radius);
    }
}
    //Creates two resources, pRenderTarget and pBrush 
    HRESULT DirectWindow::CreateGraphicsResources(){
        HRESULT hr = S_OK;
        if(pRenderTarget == NULL){
            RECT rc;
            GetClientRect(m_hwnd, &rc);

            //Size calculated in UINT32, I guess
            D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

            hr = pFactory->CreateHwndRenderTarget(
                D2D1::RenderTargetProperties(),
                D2D1::HwndRenderTargetProperties(m_hwnd, size),
                &pRenderTarget);

            if(SUCCEEDED(hr)){
                const D2D1_COLOR_F color = D2D1::ColorF(1.0f,1.0f,0);
                hr = pRenderTarget->CreateSolidColorBrush(color, &pBrush);

                if(SUCCEEDED(hr)){
                    CalculateLayout();
                }
            }
        }

        return hr;
    }

void DirectWindow::DiscardGraphicsResources(){
    SafeRelease(&pRenderTarget);
    SafeRelease(&pBrush);
}

void DirectWindow::OnPaint(){
    HRESULT hr = CreateGraphicsResources();
    if (SUCCEEDED(hr)){
        PAINTSTRUCT ps;
        BeginPaint(m_hwnd, &ps);

        pRenderTarget->BeginDraw();

        pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));
        pRenderTarget->FillEllipse(ellipse, pBrush);

        hr = pRenderTarget->EndDraw();
        if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET){
            DiscardGraphicsResources();
        }
        EndPaint(m_hwnd, &ps);
    }
}

//Remember about DPI
void DirectWindow::Resize(){
    if (pRenderTarget !=NULL){
        RECT rc;
        GetClientRect(m_hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        pRenderTarget->Resize(size);
        CalculateLayout();
        InvalidateRect(m_hwnd,NULL,FALSE);
    }
}

LRESULT DirectWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    //No default
    switch (uMsg)
    {
    case WM_CREATE:
        //D2D1CreateFactory requires adding d2d1 library while compiling
        if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
        {
            return -1;  // Fail CreateWindowEx.
        }
        return 0;

    case WM_DESTROY:
        DiscardGraphicsResources();
        SafeRelease(&pFactory);
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        OnPaint();
        return 0;

    //case WM_LBUTTONDOWN:{
    case WM_LBUTTONUP:{ // UP when the button goes UP after being pressed (being DOWN)
        exit(0);
        //return 0;
    }

    case WM_SIZE:
        Resize();
        return 0;
    }
    //Specifing Unicode characters is neccesary
    return DefWindowProcW(m_hwnd, uMsg, wParam, lParam);
}