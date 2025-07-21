#include <iostream>
#include <string>
#define interface struct


class Single {
public:
    static Single &getInstance() {
        static Single instance;
        return instance;
    }

    void run() {
        std::cout << "RUN\n";
    }

private:    
    Single() {}
};

int main() {
    Single t = Single::getInstance();
    t.run();

    //Single t;
    //Single* t = new Single();

    //Single* t1 = Single::getInstance();
    //t1->run();

    //Single* t2 = Single::getInstance();
    //t2->run();
}