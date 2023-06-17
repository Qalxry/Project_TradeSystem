//-----------------------------------------------------------------------------

#include "init.h"

//-----------------------------------------------------------------------------

void runTradeSystem() {
    cout << ">> 进入交易系统" << endl;
    initTradeSystem();
}

void initTradeSystem() {
    cout << ">> 初始化交易系统" << endl;
    int mode = modeSelect();
    switch (mode) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            break;
    }
}

int modeSelect() {
    cout << "选择模式:\n1. 历史回测\n2.实盘模拟\n3.实盘交易" << endl;
    int mode;
    cin >> mode;
    while (mode != 1 && mode != 2 && mode != 3) {
        cout << "输入错误，请重新输入" << endl;
        // 防止 cin 输入错误后陷入死循环
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
        }
        cin >> mode;
    }
    return mode;
}

//-----------------------------------------------------------------------------
