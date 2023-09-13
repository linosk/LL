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

        template <template T>
        static D2D1_POINT_2F PixelsToDips(T x, T y);
};

#endif