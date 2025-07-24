class BankInterface {
public:
	virtual bool verify() = 0;
};
class Bank : public BankInterface{
public:
	bool verify() {
		//로그인이 잘 되면... true
		return false;
	}
};

class Cal{ //SUT(= System Under Test: Test 대상이 되는 Class나 Module을 말함)
public:
	Cal(BankInterface *bank) : bank(bank) {}
	int getSum(int a, int b) {
		if(bank->verify()) {
			return a+b;
		}

		return -1;
	}

private:
	BankInterface *bank;
};