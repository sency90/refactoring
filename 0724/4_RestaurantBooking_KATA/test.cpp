#include "gmock/gmock.h"
#include "booking_scheduler.cpp"

//STEP1: �׽�Ʈ ���̽� �ۼ�(with Mocking)
TEST(BookingSchedulerTest, t1) {//������_���ÿ���_�����ϴ�_���ð�_�ƴѰ��_����Ұ�) {
	//arrange
	tm notOnTheHour = {0};
	notOnTheHour.tm_year = 2021 - 1900; //tm����ü�� 1900�⵵���� ������ ���
	notOnTheHour.tm_mon = 03-1; //tm����ü�� month�� 0���� ����
	notOnTheHour.tm_mday = 26;
	notOnTheHour.tm_hour = 9; //9��
	notOnTheHour.tm_min = 5; //5��, ������ �ƴ�
	notOnTheHour.tm_isdst = -1;  //-1: daylight�� �ڵ� �������� �ñ�
	mktime(&notOnTheHour); //������ tm����ü ��� ���� ���� �ڵ����� ����Ͽ� ä��

	Customer customer{"Fake name", "010-1234-5678"};
	Schedule* schedule = new Schedule{ notOnTheHour, 1, customer };
	BookingScheduler bookingScheduler{3};

	//act
	EXPECT_THROW({bookingScheduler.addSchedule(schedule);}, std::runtime_error);
}

TEST(BookingSchedulerTest, t2) {//������_���ÿ���_�����ϴ�_������_���_���డ��) {
	//arrange
	tm onTheHour = {0};
	onTheHour.tm_year = 2021 - 1900; //tm����ü�� 1900�⵵���� ������ ���
	onTheHour.tm_mon = 03-1; //tm����ü�� month�� 0���� ����
	onTheHour.tm_mday = 26;
	onTheHour.tm_hour = 9; //9��
	onTheHour.tm_min = 0; //5��, ������ �ƴ�
	onTheHour.tm_isdst = -1;  //-1: daylight�� �ڵ� �������� �ñ�
	mktime(&onTheHour); //������ tm����ü ��� ���� ���� �ڵ����� ����Ͽ� ä��

	Customer customer{"Fake name", "010-1234-5678"};
	Schedule* schedule = new Schedule{ onTheHour, 1, customer };
	BookingScheduler bookingScheduler{3};

	//act
	bookingScheduler.addSchedule(schedule);

	//assert
	EXPECT_EQ(true, bookingScheduler.hasSchedule(schedule));
}

TEST(BookingSchedulerTest, t3) {//�ð��뺰_�ο�������_�ִ�_����_�ð��뿡_Capacity_�ʰ���_���_���ܹ߻�) {

}

TEST(BookingSchedulerTest, t4) {//�ð��뺰_�ο�������_�ִ�_����_�ð��밡_�ٸ���_Capacity_���־_������_�߰�_����) {

}

TEST(BookingSchedulerTest, t5) {//����Ϸ��_SMS��_������_�߼�) {

}

TEST(BookingSchedulerTest, t6) {//�̸�����_����_��쿡��_�̸���_�̹߼�) {

}

TEST(BookingSchedulerTest, t7) {//�̸�����_�ִ�_��쿡��_�̸���_�߼�) {

}

TEST(BookingSchedulerTest, t8) {//���糯¥��_�Ͽ�����_���_����Ұ�_����ó��) {

}

TEST(BookingSchedulerTest, t9) {//���糯¥��_�Ͽ�����_�ƴѰ��_���డ��) {

}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}