#include <iostream>
using namespace std;

//ex1. 변수들을 각 의미에 맞도록 분리함.
int main() {

	//읽기 전용 변수는 const를 꼭 붙여주자. 그래야 가독성이 좋아진다.

	const double temp_celcius = 24; // 섭씨 
	const double temp_fahrenheit = (temp_celcius * 9 / 5) + 32; // 화씨로 변환
	cout << "섭씨 온도를 화씨로 변환: " << temp_fahrenheit << endl;

	const double meter = 10.0; // 길이(미터)
	const double area = meter * meter;// 면적 계산 
	cout << "정사각형 면적: " << area << endl;

	return 0;
}