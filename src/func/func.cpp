#include "func.h"

string getSystemTime(const char* timeFormat) {
    time_t t = time(0);
    tm* localTime = localtime(&t);
    char buf[80];
    strftime(buf, 80, timeFormat, localTime);
    return buf;
}

void getSystemTime(string& timeString, const char* timeFormat) {
    time_t t = time(0);
    tm* localTime = localtime(&t);
    char buf[80];
    strftime(buf, 80, timeFormat, localTime);
    timeString = buf;
}

string convertTimestampToTimeString(const time_t& timestamp, 
                                    const char* timeFormat) {
    char timeString[32] = {0};
    struct tm t;
    memset(&t, 0, sizeof(t));
    localtime_s(&t, &timestamp);
    strftime(timeString, sizeof(timeString), timeFormat, &t);
    return timeString;
}

char* convertTimestampToTimeString(const time_t& timestamp, 
                                   const char* timeFormat, 
                                   char* timeString) {
    struct tm t;
    memset(&t, 0, sizeof(t));
    localtime_s(&t, &timestamp);
    strftime(timeString, sizeof(timeString), timeFormat, &t);
    return timeString;
}

bool convertTimeStringToTimestamp(const char* timeString,
                                  const char* timeFormat,
                                  time_t& timestamp) {
    char timeFormatCovt[32] = {0};
    char order[7] = {0};
    int num = 0;
    const char *p = timeFormat;
    char *q = timeFormatCovt;
    int ts[6];
    struct tm t;
    memset(&t, 0, sizeof(t));

    while(*p) 
    {
        *q++ = *p;
        if(*p == '%')
        {
            *q++ = 'd';
            p++;
            order[num++] = *p++;
        }
        else p++;
    }

    switch(num)
    {
        case 1: sscanf(timeString, timeFormatCovt, &ts[0]); break;
        case 2: sscanf(timeString, timeFormatCovt, &ts[0], &ts[1]); break;
        case 3: sscanf(timeString, timeFormatCovt, &ts[0], &ts[1], &ts[2]); break;
        case 4: sscanf(timeString, timeFormatCovt, &ts[0], &ts[1], &ts[2], &ts[3]); break;
        case 5: sscanf(timeString, timeFormatCovt, &ts[0], &ts[1], &ts[2], &ts[3], &ts[4]); break;
        case 6: sscanf(timeString, timeFormatCovt, &ts[0], &ts[1], &ts[2], &ts[3], &ts[4], &ts[5]); break;
        default: return false;
    }

    while(num)
    {
        num--;
        switch(order[num])
        {
            case 'Y': t.tm_year = ts[num] - 1900; break;
            case 'm': t.tm_mon = ts[num] - 1; break;
            case 'd': t.tm_mday = ts[num]; break;
            case 'H': t.tm_hour = ts[num]; break;
            case 'M': t.tm_min = ts[num]; break;
            case 'S': t.tm_sec = ts[num]; break;
            default: return false;
        }
    }

    timestamp = mktime(&t);
    return true;
}

bool convertTimeStringToTimestamp(const char** timeString, 
                                    const char* timeFormat, 
                                    const int num_timeString,
                                    time_t* timestamp) {
    char timeFormatCovt[32] = {0}, order[7] = {0};
    const char *p = timeFormat;
    char *q = timeFormatCovt;
    int num = 0;
    int* ts[6];
    struct tm t;
    memset(&t, 0, sizeof(t));

    while(*p) 
    {
        *q++ = *p;
        if(*p == '%')
        {
            *q++ = 'd';
            p++;
            order[num++] = *p++;
        }
        else p++;
    }

    for(int i = 0; i < num; i++)
    {
        switch(order[num])
        {
            case 'Y': ts[num] = &t.tm_year; break;
            case 'm': ts[num] = &t.tm_mon; break;
            case 'd': ts[num] = &t.tm_mday; break;
            case 'H': ts[num] = &t.tm_hour; break;
            case 'M': ts[num] = &t.tm_min; break;
            case 'S': ts[num] = &t.tm_sec; break;
            default: return false;
        }
    }

    switch(num)
    {
        case 1:
            for (int i = 0; i < num_timeString; i++) {
                sscanf(timeString[i], timeFormatCovt, ts[0]);
                timestamp[i] = mktime(&t);
            }
            break;
        case 2:
            for (int i = 0; i < num_timeString; i++) {
                sscanf(timeString[i], timeFormatCovt, ts[0], ts[1]);
                timestamp[i] = mktime(&t);
            }
            break;
        case 3:
            for (int i = 0; i < num_timeString; i++) {
                sscanf(timeString[i], timeFormatCovt, ts[0], ts[1], ts[2]);
                timestamp[i] = mktime(&t);
            }
            break;
        case 4:
            for (int i = 0; i < num_timeString; i++) {
                sscanf(timeString[i], timeFormatCovt, ts[0], ts[1], ts[2], ts[3]);
                timestamp[i] = mktime(&t);
            }
            break;
        case 5:
            for (int i = 0; i < num_timeString; i++) {
                sscanf(timeString[i], timeFormatCovt, ts[0], ts[1], ts[2], ts[3], ts[4]);
                timestamp[i] = mktime(&t);
            }
            break;
        case 6:
            for (int i = 0; i < num_timeString; i++) {
                sscanf(timeString[i], timeFormatCovt, ts[0], ts[1], ts[2], ts[3], ts[4], ts[5]);
                timestamp[i] = mktime(&t);
            }
            break;
        default: return false;
    }
    return true;
}

bool convertTimeStringToTimestamp(vector<char*> timeString, 
                                    const char* timeFormat, 
                                    const int num_timeString,
                                    vector<time_t>& timestamp) {
    char timeFormatCovt[32] = {0}, order[7] = {0};
    const char *p = timeFormat;
    char *q = timeFormatCovt;
    int num = 0;
    int* ts[6];
    struct tm t;
    if (timestamp.size() < num_timeString)
        timestamp.resize(num_timeString);
    memset(&t, 0, sizeof(t));

    while(*p) 
    {
        *q++ = *p;
        if(*p == '%')
        {
            *q++ = 'd';
            p++;
            order[num++] = *p++;
        }
        else p++;
    }

    for(int i = 0; i < num; i++)
    {
        switch(order[num])
        {
            case 'Y': ts[num] = &t.tm_year; break;
            case 'm': ts[num] = &t.tm_mon; break;
            case 'd': ts[num] = &t.tm_mday; break;
            case 'H': ts[num] = &t.tm_hour; break;
            case 'M': ts[num] = &t.tm_min; break;
            case 'S': ts[num] = &t.tm_sec; break;
            default: return false;
        }
    }

    switch(num)
    {
        case 1:
            for (int i = 0; i < num_timeString; i++) {
                sscanf(timeString[i], timeFormatCovt, ts[0]);
                timestamp[i] = mktime(&t);
            }
            break;
        case 2:
            for (int i = 0; i < num_timeString; i++) {
                sscanf(timeString[i], timeFormatCovt, ts[0], ts[1]);
                timestamp[i] = mktime(&t);
            }
            break;
        case 3:
            for (int i = 0; i < num_timeString; i++) {
                sscanf(timeString[i], timeFormatCovt, ts[0], ts[1], ts[2]);
                timestamp[i] = mktime(&t);
            }
            break;
        case 4:
            for (int i = 0; i < num_timeString; i++) {
                sscanf(timeString[i], timeFormatCovt, ts[0], ts[1], ts[2], ts[3]);
                timestamp[i] = mktime(&t);
            }
            break;
        case 5:
            for (int i = 0; i < num_timeString; i++) {
                sscanf(timeString[i], timeFormatCovt, ts[0], ts[1], ts[2], ts[3], ts[4]);
                timestamp[i] = mktime(&t);
            }
            break;
        case 6:
            for (int i = 0; i < num_timeString; i++) {
                sscanf(timeString[i], timeFormatCovt, ts[0], ts[1], ts[2], ts[3], ts[4], ts[5]);
                timestamp[i] = mktime(&t);
            }
            break;
        default: return false;
    }
    return true;
}

bool convertTimeStringToTimestamp(vector<string> timeString, 
                                    const char* timeFormat, 
                                    const int num_timeString,
                                    vector<time_t>& timestamp) {
    char timeFormatCovt[32] = {0}, order[7] = {0};
    const char *p = timeFormat;
    char *q = timeFormatCovt;
    int num = 0;
    int* ts[6];
    struct tm t;
    if (timestamp.size() < num_timeString)
        timestamp.resize(num_timeString);
    memset(&t, 0, sizeof(t));

    while(*p) {
        *q++ = *p;
        if(*p == '%') {
            *q++ = 'd';
            p++;
            order[num++] = *p++;
        }
        else p++;
    }

    for(int i = 0; i < num; i++) {
        switch(order[num]) {
            case 'Y': ts[num] = &t.tm_year; break;
            case 'm': ts[num] = &t.tm_mon; break;
            case 'd': ts[num] = &t.tm_mday; break;
            case 'H': ts[num] = &t.tm_hour; break;
            case 'M': ts[num] = &t.tm_min; break;
            case 'S': ts[num] = &t.tm_sec; break;
            default: return false;
        }
    }

    switch(num) {
        case 1:
            for (int i = 0; i < num_timeString; i++) {
                sscanf(timeString[i].c_str(), timeFormatCovt, ts[0]);
                timestamp[i] = mktime(&t);
            }
            break;
        case 2:
            for (int i = 0; i < num_timeString; i++) {
                sscanf(timeString[i].c_str(), timeFormatCovt, ts[0], ts[1]);
                timestamp[i] = mktime(&t);
            }
            break;
        case 3:
            for (int i = 0; i < num_timeString; i++) {
                sscanf(timeString[i].c_str(), timeFormatCovt, ts[0], ts[1], ts[2]);
                timestamp[i] = mktime(&t);
            }
            break;
        case 4:
            for (int i = 0; i < num_timeString; i++) {
                sscanf(timeString[i].c_str(), timeFormatCovt, ts[0], ts[1], ts[2], ts[3]);
                timestamp[i] = mktime(&t);
            }
            break;
        case 5:
            for (int i = 0; i < num_timeString; i++) {
                sscanf(timeString[i].c_str(), timeFormatCovt, ts[0], ts[1], ts[2], ts[3], ts[4]);
                timestamp[i] = mktime(&t);
            }
            break;
        case 6:
            for (int i = 0; i < num_timeString; i++) {
                sscanf(timeString[i].c_str(), timeFormatCovt, ts[0], ts[1], ts[2], ts[3], ts[4], ts[5]);
                timestamp[i] = mktime(&t);
            }
            break;
        default: return false;
    }
    return true;
}
