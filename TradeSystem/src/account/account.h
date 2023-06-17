#pragma once
#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "..\struct\struct.h"

class Account {
public:
public:
    string accountName;     // 账户名称
    string accountID;       // 账户ID
    double cash;            // 现金
    double netValue;        // 净值
    
    
    
    int hold;
    vector<Order> orders;
    vector<TradeRecord> records;
    double orderFee;
    double orderProfit;
    double orderAmount;
    double profitRate;
    Account() {};
    Account(double cash, double stopLoss, double stopProfit, double amountPerTrade, double feeRate, string tradeType);
    void update(double price);
    void buy(double price, double amount);
    void sell(double price, double amount);
    void close(double price);
    void print();
    void printRecords();
    void printOrders();
    void printProfit();
    void printProfitRate();
    void printMaxDrawdown();
    void printMaxDrawdownRate();
    void printAnnualizedReturnRate();
    void printAnnualizedVolatility();
    void printAnnualizedSharpRate();
    void printWinRate();
    void printLossRate();
    void printProfitFactor();
    void printMaxProfit();
    void printMaxLoss();
    void printProfitLossRatio();
    void printAverageProfit();
    void printAverageLoss();
    void printAverageProfitLossRatio();
};

#endif // !ACCOUNT_H
