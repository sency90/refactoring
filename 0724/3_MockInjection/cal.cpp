class Bank{
public:
	bool verify() {
		//로그인이 잘 되면... true
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