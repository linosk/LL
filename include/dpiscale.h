#ifndef DPI_SCALE_H
#define DPI_SCALE_H

//Is it good idea to declare it second time?
//Make hader with all includes?
#include <Windows.h>

#include <d2d1.h>
#pragma comment(lib, "d2d1")
#include <algorithm>

class DPI_Scale{
        static float scale;

    public:
        static void Initialize(HWND hwnd);

        //Can template be replced with class
        template <class T>
        static D2D1_POINT_2F PixelsToDips(T x, T y);
};

#endif