#include "backtest.h"

int runBackTest() {
    // 1. ׼������
    Snapshot* data = new Snapshot("HistoricalData\\data.csv", 5000);
    // 2. �������ݸ�����


    // 8. ���潻�׼�¼
    outputTradeRecord(records);
    cout << "AutoSave: tradeRecord.csv" << endl;

    return 0;
}