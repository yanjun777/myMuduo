#include "Logger.h"
#include <iostream>

// 静态方法 cpp实现不需要加static 
Logger& Logger::instance(){
    static Logger instance;
    return instance; // 返回单例对象 
}
// 设置日志级别
void Logger::setLogLevel(int level){
    logLevel_ = level; 
}
// 写日志
void Logger::log(std::string msg){
    switch(logLevel_){
        case INFO:
            std::cout<<"[INFO]";
            break;
        case ERROR:
            std::cout<<"[ERROR]";
            break;
        case DEBUG:
            std::cout<<"[DEBUG]";
            break;
        case FATAL:
            std::cout<<"[FATAL]";
            break;
        default:
            break;
    }
    std::cout<<"print time"<<":"<<msg<<std::endl; 

}