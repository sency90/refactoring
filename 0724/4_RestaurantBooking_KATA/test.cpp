#include "gmock/gmock.h"
#include "booking_scheduler.cpp"

using namespace testing;

class BookingItem: public Test{
public:
	tm getTime(int year, int mon, int day, int hour, int min) {
		tm result = {0, min, hour, day, mon-1, year-1990, 0, 0, -1};
		mktime(&result);
		return result;
	}
};

//STEP1: �׽�Ʈ ���̽� �ۼ�(with Mocking)
TEST_F(BookingItem, t1) {//������_���ÿ���_�����ϴ�_���ð�_�ƴѰ��_����Ұ�) {
	//arrange
	tm notOnTheHour = getTime(2021,3,26,9,5);
	Customer customer{"Fake name", "010-1234-5678"};
	Schedule* schedule = new Schedule{ notOnTheHour, 1, customer };
	BookingScheduler bookingScheduler{3};

	//act
	EXPECT_THROW({bookingScheduler.addSchedule(schedule);}, std::runtime_error);
}

TEST_F(BookingItem, t2) {//������_���ÿ���_�����ϴ�_������_���_���డ��) {
	//arrange
	tm onTheHour = getTime(2021,3,26,9,0);
	Customer customer{"Fake name", "010-1234-5678"};
	Schedule* schedule = new Schedule{ onTheHour, 1, customer };
	BookingScheduler bookingScheduler{3};

	//act
	bookingScheduler.addSchedule(schedule);

	//assert
	EXPECT_EQ(true, bookingScheduler.hasSchedule(schedule));
}

TEST_F(BookingItem, t3) {//�ð��뺰_�ο�������_�ִ�_����_�ð��뿡_Capacity_�ʰ���_���_���ܹ߻�) {

}

TEST_F(BookingItem, t4) {//�ð��뺰_�ο�������_�ִ�_����_�ð��밡_�ٸ���_Capacity_���־_������_�߰�_����) {

}

TEST_F(BookingItem, t5) {//����Ϸ��_SMS��_������_�߼�) {

}

TEST_F(BookingItem, t6) {//�̸�����_����_��쿡��_�̸���_�̹߼�) {

}

TEST_F(BookingItem, t7) {//�̸�����_�ִ�_��쿡��_�̸���_�߼�) {

}

TEST_F(BookingItem, t8) {//���糯¥��_�Ͽ�����_���_����Ұ�_����ó��) {

}

TEST_F(BookingItem, t9) {//���糯¥��_�Ͽ�����_�ƴѰ��_���డ��) {

}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}