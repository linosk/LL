#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "basewindow.h"

class MainWindow : public BaseWindow<MainWindow>{
    public:
        PCWSTR ClassName() const {return L"Sample Window Class";}
        LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif