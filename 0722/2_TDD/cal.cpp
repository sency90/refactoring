#pragma once
class Cal{
public:
	int getMinus(int num1, int num2) {
		if(num1>num2) return num1-num2;
		return -1;
	}
};