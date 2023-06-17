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
    int id;             // ���ױ��
    int time;           // ����ʱ��
    string strTime;     // �������
    string type;        // buy or sell
    string code;        // ���׵Ĺ�Ʊ����
    double price;       // ���׼۸�
    double amount;      // ��������
    double fee;         // ���׷���
    double profit;      // ����ӯ��
    double stopLoss;    // ֹ��
    double stopProfit;  // ֹӯ
    double cash;        // �ֽ����
    double netValue;    // ��ֵ
    double cashChange;  // �ֽ����仯
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