#include <stdexcept>
using namespace std;
class Baseball {
public:
	void guess(const string& s) {
		if(s.length() != 3) {
			throw length_error("Must be three letters.");
		}
	}
};