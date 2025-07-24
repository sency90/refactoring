class BankInterface {
public:
	virtual bool verify() = 0;
};
class Bank : public BankInterface{
public:
	bool verify() {
		//�α����� �� �Ǹ�... true
		return false;
	}
};

class Cal{ //SUT(= System Under Test: Test ����� �Ǵ� Class�� Module�� ����)
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