#pragma once

#include<iostream>
#include<string>

class TimeStamp{
public:
    TimeStamp();
    explicit TimeStamp(int64_t microSecondsSinceEpoch); 
    std::string toString() const;
    // 静态方法 获取当前时间 
    static TimeStamp now();
private:
    int64_t microSecondsSinceEpoch_; // 微秒  
};
