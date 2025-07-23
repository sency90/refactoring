#include <vector>
using std::vector;

class PrimeFactors {
public:
	vector<int> of(int number) {
		vector<int> result = {};
		for(int divisor=2; number>1; divisor++) {
			while(number % divisor == 0) {
				result.push_back(divisor);
				number/=divisor;
			}
		}
		return result;
	}
};