class Bank{
public:
	bool verify() {
		//�α����� �� �Ǹ�... true
		return false;
	}
};

class Cal{ //SUT
public:
	int getSum(int a, int b) {
		Bank bank;

		if(bank.verify()) {
			return a+b;
		}

		return -1;
	}
};