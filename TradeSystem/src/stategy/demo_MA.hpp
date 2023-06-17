#pragma once
#ifndef DEMO_MA_HPP
#define DEMO_MA_HPP
namespace demo_MA {
    void strategy()
    {
        vector<double>* ma20 = new vector<double>(data->size(), 0);
        vector<double>* ma60 = new vector<double>(data->size(), 0);
        int out_beg_idx, out_nb_element;
        // 3. 调用函数
        TA_RetCode ret_code = TA_MA(0,
            data->size() - 1,
            data->close.data(),
            20,
            TA_MAType_SMA, &out_beg_idx, &out_nb_element, ma20->data() + 19);
        // 4. 检查返回值
        if (ret_code != TA_SUCCESS) {
            cout << "error" << endl;
            return 0;
        }
        ret_code = TA_MA(0,
            data->size() - 1,
            data->close.data(),
            60,
            TA_MAType_SMA, &out_beg_idx, &out_nb_element, ma60->data() + 59);
        if (ret_code != TA_SUCCESS) {
            cout << "error" << endl;
            return 0;
        }
        // 5. 回测策略
        /*
            交易类型：期货
            交易多空：多
            初始资金：10000
            入场策略：ma20[i]>ma60[i] && ma20[i-2]<ma60[i-2] && ma60[i]>max(open, close)
            出场策略：ma20[i]<ma60[i] && ma20[i-2]>ma60[i-2] && ma60[i]<min(open, close)
            每单交易金额：1000
            最大持仓数：1
            止损：-10%
            止盈：20%
        */
        data->code = "rb2101";
        double cash = 10000;
        double netValue = cash;
        const double stopLoss = 0.1;
        const double stopProfit = 0.2;
        const double amountPerTrade = 1000;
        const double feeRate = 0.0003;
        const string tradeType = "buy";
        int hold = 0;

        vector<Order> orders;
        vector<TradeRecord> records;

        double orderFee = 0;
        double orderProfit = 0;
        double orderAmount = 0;
        double profitRate = 0;

        // 6. 开始回测
        for (int i = 59; i < data->size(); i++) {
            double nowPrice = data->open[i];
            //  检查止盈止损
            if (hold == 1 && (orders[0].price - nowPrice) / orders[0].price >= stopLoss) {
                // 止损
                double fee = nowPrice * orders[0].amount * feeRate;
                double getMoney = -(fee + (orders[0].price - nowPrice) * orders[0].amount);
                records.push_back(TradeRecord(records.size() + 1, data->time[i], "sell", data->code,
                    nowPrice, orders[0].amount, fee, getMoney, stopLoss, stopProfit,
                    cash + getMoney, cash + getMoney, getMoney / cash));
                cash += getMoney;
                hold--;
                orders.erase(orders.begin());
            }
            else if (hold == 1 && (nowPrice - orders[0].price) / nowPrice >= stopProfit) {
                // 止盈
                double fee = nowPrice * orders[0].amount * 0.0003;
                double getMoney = fee + (nowPrice - orders[0].price) * orders[0].amount;
                records.push_back(TradeRecord(records.size() + 1, data->time[i], "sell", data->code,
                    nowPrice, orders[0].amount, fee, getMoney, stopLoss, stopProfit,
                    cash + getMoney, cash + getMoney, getMoney / cash));
                cash += getMoney;
                hold--;
                orders.erase(orders.begin());
            }
            else if (hold == 0 && (*ma20)[i] > (*ma60)[i] &&
                (*ma20)[i - 2] < (*ma60)[i - 2] &&
                (*ma60)[i] > max(data->open[i], data->close[i])) {
                // 买入
                orderFee = amountPerTrade * feeRate;
                orderProfit = -orderFee;
                netValue = cash - orderFee;
                cash -= amountPerTrade + orderFee;

                hold++;
                orders.push_back(Order(data->time[i], data->code, "buy", nowPrice, amountPerTrade, orderFee, stopLoss, stopProfit));
                records.push_back(TradeRecord(records.size() + 1, data->time[i], "sell", data->code, nowPrice, orderAmount,
                    orderFee, orderProfit, stopLoss, stopProfit, cash, netValue, profitRate);
                orders.clear();
            }

            else if (hold == 1 && (*ma20)[i] < (*ma60)[i] &&
                (*ma20)[i - 2] > (*ma60)[i - 2] &&
                (*ma60)[i] < min(data->open[i], data->close[i])) {
                // 卖出
                orderAmount = orders[0].amount;
                orderProfit = (nowPrice - orders[0].price) * orderAmount;
                orderFee = nowPrice * orderAmount * feeRate;
                cash -= nowPrice * orderAmount;
                netValue = cash;
                profitRate = (orders[0].profit + orderProfit) / orders[0].money;
                hold--;
                // 记录交易记录
                records.push_back(TradeRecord(records.size() + 1, data->time[i], "sell", data->code, nowPrice, orderAmount,
                    orderFee, orderProfit, stopLoss, stopProfit, cash, netValue, profitRate);
                orders.clear();
            }
        }
        // 7. 输出结果
        cout << "BackTest Trade Result: " << endl;
        cout << "\ttrade times: " << records.size() << endl;
        cout << "\tbeginning cash: " << 10000 << endl;
        cout << "\tfinal cash: " << cash << endl;
        cout << "\tprofit %: " << (cash - 10000) / 10000 << endl;
        cout << "\twin %: ";
        int win = 0, sells = 0;
        for (int i = 0; i < records.size(); i++) {
            if (records[i].type == "sell") {
                sells++;
                if (records[i].profit > 0)
                    win++;
            }
        }
        cout << win * 1.0 / sells << endl;
    }
}
#endif // !DEMO_MA_HPP
