//-----------------------------------------------------------------------------

#include "init.h"

//-----------------------------------------------------------------------------

void runTradeSystem() {
    cout << ">> ���뽻��ϵͳ" << endl;
    initTradeSystem();
}

void initTradeSystem() {
    cout << ">> ��ʼ������ϵͳ" << endl;
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
    cout << "ѡ��ģʽ:\n1. ��ʷ�ز�\n2.ʵ��ģ��\n3.ʵ�̽���" << endl;
    int mode;
    cin >> mode;
    while (mode != 1 && mode != 2 && mode != 3) {
        cout << "�����������������" << endl;
        // ��ֹ cin ��������������ѭ��
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
        }
        cin >> mode;
    }
    return mode;
}

//-----------------------------------------------------------------------------
