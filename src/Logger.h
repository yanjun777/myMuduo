#pragma once 
#include<string> 
#include "noncopyable.h"
enum LogLevel{
    INFO,
    ERROR,
    FATAL,
    DEBUG
};
#define LOG_INFO(logmsgformat, ...) \
    do{ \
        Logger &logger = Logger::instance();\
        logger.setLogLevel(INFO);\
        char buffer[1024] = {0};\
        snprintf(buffer,1024,logmsgformat,##__VA_ARGS__);\
        logger.log(buffer);\
    }while(0)

#define LOG_ERROR(logmsgformat, ...) \
    do{ \
        Logger &logger = Logger::instance();\
        logger.setLogLevel(ERROR);\
        char buffer[1024] = {0};\
        snprintf(buffer,1024,logmsgformat,##__VA_ARGS__);\
        logger.log(buffer);\
    }while(0)
#define LOG_FATAL(logmsgformat, ...) \
    do{ \
        Logger &logger = Logger::instance();\
        logger.setLogLevel(FATAL);\
        char buffer[1024] = {0};\
        snprintf(buffer,1024,logmsgformat,##__VA_ARGS__);\
        logger.log(buffer);\
    }while(0)
#ifdef MYMUDUO_DEBUG
    #define LOG_DEBUG(logmsgformat, ...) \
        do{ \
            Logger &logger = Logger::instance();\
            logger.setLogLevel(DEBUG);\
            char buffer[1024] = {0};\
            snprintf(buffer,1024,logmsgformat,##__VA_ARGS__);\
            logger.log(buffer);\
        }while(0)
#else
    #define LOG_DEBUG(logmsgformat, ...)
#endif

class Logger:noncopyable{
// 单例模式
public:
    // 静态方法
    static Logger& instance();
    // 设置日志级别
    void setLogLevel(int level);
    // 写日志
    void log(std::string msg); 
private:
    Logger(){   
    }
    ~Logger(){
    }
    int logLevel_; 
};