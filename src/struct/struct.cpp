
#include "struct.h"

Snapshot::Snapshot() {}

Snapshot::Snapshot(string filename, size_t size) {
    if (size != 0) {
        date.reserve(size);
        time.reserve(size);
        high.reserve(size);
        low.reserve(size);
        open.reserve(size);
        close.reserve(size);
        volume.reserve(size);
    }
    readCSV(filename);
}

Snapshot::~Snapshot() {}

size_t Snapshot::size() {
    return dataSize;
}

void Snapshot::readCSV(string filename) {
    ifstream file(filename);
    // 检查文件是否打开成功
    if (!file.is_open()) {
        cout << "History CSV file open failed" << endl;
        return;
    }
    string line;
    // 由于time是按分钟递增的，所以只需要读取第一行的time即可
    while (getline(file, line)) {
        stringstream ss(line);
        string field;
        getline(ss, field, ',');
        date.emplace_back(field);
        getline(ss, field, ',');
        open.emplace_back(stod(field));
        getline(ss, field, ',');
        high.emplace_back(stod(field));
        getline(ss, field, ',');
        low.emplace_back(stod(field));
        getline(ss, field, ',');
        close.emplace_back(stod(field));
        getline(ss, field, ',');
        volume.emplace_back(stod(field));
    }
    file.close();
    time_t time;
    // dateConvertToTime(date[0], time);
    convertTimeStringToTimestamp(date[0].c_str(), "%Y-%m-%d", time);
    for (int i = 0; i < date.size(); i++) {
        this->time.emplace_back(time + i);
    }
    dataSize = date.size();
    startTime = this->time[0];
    return;
}


Order::Order(int time,
             string code,
             string type,
             double price,
             double money,
             double fee,
             double stopLoss,
             double stopProfit) {
    this->time = time;
    this->code = code;
    this->type = type;
    this->price = price;
    this->money = money;
    this->fee = fee;
    this->stopLoss = stopLoss;
    this->stopProfit = stopProfit;
    this->amount = money / price;
    this->profit = -fee;
}
Order::~Order() {}


TradeRecord::TradeRecord(int id,
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
                         double cashChange) {
    this->id = id;
    this->time = time;
    this->type = type;
    this->code = code;
    this->price = price;
    this->amount = amount;
    this->fee = fee;
    this->profit = profit;
    this->stopLoss = stopLoss;
    this->stopProfit = stopProfit;
    this->cash = cash;
    this->netValue = netValue;
    this->cashChange = cashChange;
    time_t t = time;
    tm* localTime = localtime(&t);
    char buf[80];
    strftime(buf, 80, "%Y-%m-%d %H:%M:%S", localTime);
    strTime = buf;
}
TradeRecord::~TradeRecord() {
}
string& TradeRecord::toString() const {
    string str = to_string(id) + ',' +
                 strTime + ',' +
                 type + ',' +
                 code + ',' +
                 to_string(price) + ',' +
                 to_string(amount) + ',' +
                 to_string(fee) + ',' +
                 to_string(profit) + ',' +
                 to_string(stopLoss) + ',' +
                 to_string(stopProfit) + ',' +
                 to_string(cash) + ',' +
                 to_string(netValue) + ',' +
                 to_string(cashChange);
    return str;
}

void TradeSystem::outputTradeRecord_CSV(const string& filename) const {
      ofstream file(filename + getSystemTime("%Y%m%d%H%M%S") + ".csv", ios::out);
      if (!file.is_open()) {
          cout << "TradeRecord CSV file open failed" << endl;
          return;
      }
      file << "id,time,type,code,price,amount,fee,profit,stopLoss,stopProfit,cash,netValue,cashChange" << endl;
      for (int i = 0; i < tradeRecords.size(); i++) {
          file << tradeRecords[i].toString() << endl;
      }
      file.close();
  }
