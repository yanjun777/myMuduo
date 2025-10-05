#pragma once 

class noncopyable{
public:
    // 禁止拷贝构造和赋值 派生类禁止拷贝：因为基类不能拷贝 
    noncopyable(const noncopyable&) = delete;
    noncopyable& operator=(const noncopyable&) = delete;
protected:
    noncopyable() = default;
    ~noncopyable() = default; 
};