#include<muduo/net/TcpServer.h>
#include<muduo/net/EventLoop.h>
#include<iostream>
using namespace std; 
using namespace muduo;
using namespace muduo::net;


class chatServer{
public:
    chatServer(
        EventLoop *loop,
        const InetAddress &listenAddr,
        const string &nameArg
    ):_server(loop,listenAddr,nameArg),_loop(loop){
        _server.setMessageCallback(std::bind(&chatServer::onMessage,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));
        _server.setConnectionCallback(std::bind(&chatServer::onConnection,this,std::placeholders::_1));
    }
    void start(){
        _server.start();
    }
private:
    void onMessage(const TcpConnectionPtr &conn,Buffer *buf,Timestamp time){
        string msg = buf->retrieveAllAsString();
        cout << "recv data:" << msg << "time:" << time.toString() << endl;
        conn->send(msg);
    }
    void onConnection(const TcpConnectionPtr &conn){
        if(conn->connected()){
            // 客户端连接成功
            cout<<"new client connected"<<endl;
            cout<<"peer address and port:"<<conn->peerAddress().toIpPort()<<endl;
        }else{
            cout<<"client disconnected"<<endl;
            cout<<"peer address and port:"<<conn->peerAddress().toIpPort()<<endl;
            conn->shutdown(); // 释放socket资源 
        }
    }
    TcpServer _server;
    EventLoop *_loop; 
};

int main(){
    EventLoop loop;
    InetAddress addr("127.0.0.1",6666);
    chatServer server(&loop,addr,"chatServer");
    server.start();
    loop.loop();
    return 0;
}