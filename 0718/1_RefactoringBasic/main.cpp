#include <iostream>
using namespace std;

//ex1. �������� �� �ǹ̿� �µ��� �и���.
int main() {

	//�б� ���� ������ const�� �� �ٿ�����. �׷��� �������� ��������.

	const double temp_celcius = 24; // ���� 
	const double temp_fahrenheit = (temp_celcius * 9 / 5) + 32; // ȭ���� ��ȯ
	cout << "���� �µ��� ȭ���� ��ȯ: " << temp_fahrenheit << endl;

	const double meter = 10.0; // ����(����)
	const double area = meter * meter;// ���� ��� 
	cout << "���簢�� ����: " << area << endl;

	return 0;
}