#include <iostream>
#include <string>

//수정불가
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

//수정불가
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

//수정불가
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

//Client Code
int main() {
    ImportantModule im;

    Azure azure;
    im.run(azure);
}