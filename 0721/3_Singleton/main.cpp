#include <iostream>
#include <string>
#define interface struct


//��ü�� ������ 1���� �����Ҽ��ֵ��� ����
class Single {
public:
    static Single *getInstance() {
        if (instance == nullptr) {
            instance = new Single();
        }
        return instance;
    }

    void run() {
        std::cout << "RUN\n";
    }

private:
    static Single* instance;
    Single() {}
};

Single* Single::instance = nullptr;

int main() {
    //Single t;
    //Single* t = new Single();

    Single* t1 = Single::getInstance();
    t1->run();

    Single* t2 = Single::getInstance();
    t2->run();

    return 0;
}