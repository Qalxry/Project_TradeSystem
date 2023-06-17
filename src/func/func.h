#pragma once
#ifndef FUNC_H
#define FUNC_H
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string getSystemTime(const char* timeFormat);
void getSystemTime(string& timeString, const char* timeFormat);

// Function: convert Timestamp To TimeString
string convertTimestampToTimeString(const time_t& timestamp,
                                    const char* timeFormat);
char* convertTimestampToTimeString(const time_t& timestamp,
                                   const char* timeFormat,
                                   char* timeString);

// Function: convert TimeString To Timestamp                    
bool convertTimeStringToTimestamp(const char* timeString,
                                  const char* timeFormat,
                                  time_t& timestamp);
bool convertTimeStringToTimestamp(const char** timeString,
                                  const char* timeFormat,
                                  const int num_timeString,
                                  time_t* timestamp);
                                  
// Function: convert TimeString To Timestamp (vector)                                  
bool convertTimeStringToTimestamp(vector<char*> timeString,
                                  const char* timeFormat,
                                  const int num_timeString,
                                  vector<time_t>& timestamp);
bool convertTimeStringToTimestamp(vector<string> timeString, 
                                    const char* timeFormat, 
                                    const int num_timeString,
                                    vector<time_t>& timestamp);                               
#endif  // !FUNC_H