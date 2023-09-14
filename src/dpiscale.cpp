#include "dpiscale.h"

float DPI_Scale::scale = 1.0f;

void DPI_Scale::Initialize(HWND hwnd){
    float dpi = GetDpirWindow(hwnd);
}