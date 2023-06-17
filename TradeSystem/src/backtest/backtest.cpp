#include "backtest.h"

int runBackTest() {
    // 1. 准备数据
    Snapshot* data = new Snapshot("HistoricalData\\data.csv", 5000);
    // 2. 输入数据给策略


    // 8. 保存交易记录
    outputTradeRecord(records);
    cout << "AutoSave: tradeRecord.csv" << endl;

    return 0;
}