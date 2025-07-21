#include <iostream>
#include <string>

//�����Ұ�
class Azure {
public:
    virtual void ms_connect() {
        std::cout << "[Azure] Connected\n";
    }
    virtual void ms_login(const std::string& id, const std::string& pass) {
        std::cout << "[Azure] Login : " << id << " pass : " << pass << "\n";
    }
    virtual void ms_sendData() {
        std::cout << "[Azure] Data sent\n";
    }
    virtual void ms_receiveData() {
        std::cout << "[Azure] Data received\n";
    }
    virtual void ms_disconnect() {
        std::cout << "[Azure] Disconnected\n";
    }
};

//�����Ұ�
class AWS {
public:
    virtual void aws_conn(const std::string& id, const std::string& pass) {
        std::cout << "[AWS] Connected as " << id << "(" << pass << ")\n";
    }
    virtual void aws_setData() {
        std::cout << "[AWS] Data sent\n";
    }
    virtual void aws_getData() {
        std::cout << "[AWS] Data received\n";
    }
    virtual void aws_bye() {
        std::cout << "[AWS] Disconnected\n";
    }
};

//�����Ұ�
class ImportantModule {
public:
    void run(Azure& az) {
        az.ms_connect();
        az.ms_login("KFC", "1234");
        az.ms_sendData();
        az.ms_receiveData();
        az.ms_disconnect();
    }
};

class Adapter : public Azure {
public:
    virtual void ms_connect() {
        //std::cout << "[Azure] Connected\n";
    }
    virtual void ms_login(const std::string& id, const std::string& pass) {
        //std::cout << "[Azure] Login : " << id << " pass : " << pass << "\n";
        aws.aws_conn(id, pass);
    }
    virtual void ms_sendData() {
        //std::cout << "[Azure] Data sent\n";
        aws.aws_setData();
    }
    virtual void ms_receiveData() {
        //std::cout << "[Azure] Data received\n";
        aws.aws_getData();
    }
    virtual void ms_disconnect() {
        //std::cout << "[Azure] Disconnected\n";
        aws.aws_bye();
    }
private:
    AWS aws;
};

//Client Code
int main() {
    ImportantModule im;

#if 0
    Azure azure;
    im.run(azure);
#else
    Adapter adapter;
    im.run(adapter);
#endif
}