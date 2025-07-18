#include <iostream>
using namespace std;

int main() {

	double temp = 24; // ¼·¾¾ 
	temp = (temp * 9 / 5) + 32; // È­¾¾·Î º¯È¯
	cout << "¼·¾¾ ¿Âµµ¸¦ È­¾¾·Î º¯È¯: " << temp << endl;
	temp = 10.0; // ±æÀÌ(¹ÌÅÍ)
	double area = temp * temp; // ¸éÀû °è»ê 
	cout << "Á¤»ç°¢Çü ¸éÀû: " << area << endl;

	return 0;
}