#include <vector>
using std::vector;

class PrimeFactors{
public:
	vector<int> of(int number) {
		vector<int> result = {};
		if(number==2) {
			result.push_back(number);
		}
		if(number==3) {
			result.push_back(number);
		}
		return result;
	}
};