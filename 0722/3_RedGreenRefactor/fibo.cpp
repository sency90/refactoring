#pragma once
class Fibo{
public:
	int fibo(int n) {
		if(n==0) return 0;
		if(n<=2) return 1;
		return fibo(n-2) + fibo(n-1);
	}
};