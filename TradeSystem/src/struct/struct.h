#pragma once
#ifndef STRUCT_H
#define STRUCT_H
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../func/func.h"
using namespace std;

class Snapshot {
  public:
    size_t dataSize;
    time_t startTime;
    string code;
    vector<string> date;
    vector<time_t> time;
    vector<double> high;
    vector<double> low;
    vector<double> open;
    vector<double> close;
    vector<double> volume;

  public:
    Snapshot();
    Snapshot(string filename, size_t size = 0);
    ~Snapshot();
    size_t size();
    void readCSV(string filename);
};

class Order {
  public:
    int time;
    string code;
    string type;
    double price;
    double money;
    double amount;
    double fee;
    double stopLoss;
    double stopProfit;
    double profit;

  public:
    Order(int time,
          string code,
          string type,
          double price,
          double money,
          double fee,
          double stopLoss,
          double stopProfit);
    ~Order();
};

class TradeRecord {
  public:
    int id;             // 交易编号
    int time;           // 交易时间
    string strTime;     // 用于输出
    string type;        // buy or sell
    string code;        // 交易的股票代码
    double price;       // 交易价格
    double amount;      // 交易数量
    double fee;         // 交易费用
    double profit;      // 交易盈亏
    double stopLoss;    // 止损
    double stopProfit;  // 止盈
    double cash;        // 现金结余
    double netValue;    // 净值
    double cashChange;  // 现金结余变化
    TradeRecord(int id,
                int time,
                string type,
                string code,
                double price,
                double amount,
                double fee,
                double profit,
                double stopLoss,
                double stopProfit,
                double cash,
                double netValue,
                double cashChange);
    ~TradeRecord();
    string& toString() const;
};

class TradeSystem {
  public:
    vector<Snapshot> snapshots;
    vector<Order> orders;
    vector<TradeRecord> tradeRecords;
    double cash;
    double netValue;
    double cashChange;
    double fee;
    double stopLoss;
    double stopProfit;
    double maxLoss;
    double maxProfit;
    double maxDrawdownRate;

    void outputTradeRecord_CSV(const string& filename = "TradeRecord_") const;
};
#endif  // !STRUCT_H