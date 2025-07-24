#include "gmock/gmock.h"
#include "booking_scheduler.cpp"
#include "testable_sms_sender.cpp"
#include "testable_mail_sender.cpp"
#include "testable_booking_scheduler.cpp"

using namespace testing;

class MockCustomer: public Customer {
public:
	MOCK_METHOD(string, getEmail, (), (override));
};

class BookingItem: public Test {
protected:
	void SetUp() override {
		NOT_ON_THE_HOUR = getTime(2021, 3, 26, 9, 5);
		ON_THE_HOUR = getTime(2021, 3, 26, 9, 0);
		SUNDAY_TIME = getTime(2021, 3, 28, 17, 0);
		MONDAY_TIME = getTime(2021, 3, 29, 17, 0);

		bookingScheduler.setSmsSender(&testableSmsSender);
		bookingScheduler.setMailSender(&testableMailSender);

		EXPECT_CALL(CUSTOMER, getEmail)
			.WillRepeatedly(testing::Return(""));

		EXPECT_CALL(CUSTOMER_WITH_MAIL, getEmail)
			.WillRepeatedly(testing::Return("test@test.com"));
	}
public:
	tm getTime(int year, int mon, int day, int hour, int min) {
		tm result = {0, min, hour, day, mon-1, year-1990, 0, 0, -1};
		mktime(&result);
		return result;
	}

	tm plusHour(tm base, int hour) {
		base.tm_hour += hour;
		mktime(&base);
		return base;
	}

	tm NOT_ON_THE_HOUR;
	tm ON_THE_HOUR;
	tm SUNDAY_TIME;
	tm MONDAY_TIME;
	MockCustomer CUSTOMER;
	MockCustomer CUSTOMER_WITH_MAIL;
	//Customer CUSTOMER{"Fake name", "010-1234-5678"};
	//Customer CUSTOMER_WITH_MAIL{"Fake Name", "010-1234-5678", "test@test.com"};
	const int UNDER_CAPACITY = 1;
	const int CAPACITY_PER_HOUR = 3;

	BookingScheduler bookingScheduler{CAPACITY_PER_HOUR};
	NiceMock<TestableSmsSender> testableSmsSender;
	NiceMock<TestableMailSender> testableMailSender;
};

//STEP1: �׽�Ʈ ���̽� �ۼ�(with Mocking)
TEST_F(BookingItem, t1) {//������_���÷θ�_�����ϴ�_���ð�_�ƴѰ��_����Ұ�) {
	//arrange
	Schedule* schedule = new Schedule{NOT_ON_THE_HOUR, UNDER_CAPACITY, CUSTOMER};

	//act
	EXPECT_THROW({bookingScheduler.addSchedule(schedule); }, std::runtime_error);
}

TEST_F(BookingItem, t2) {//������_���÷θ�_�����ϴ�_������_���_���డ��) {
	//arrange
	Schedule* schedule = new Schedule{ON_THE_HOUR, UNDER_CAPACITY, CUSTOMER};

	//act
	bookingScheduler.addSchedule(schedule);

	//assert
	EXPECT_EQ(true, bookingScheduler.hasSchedule(schedule));
}

TEST_F(BookingItem, t3) {//�ð��뺰_�ο�������_�ִ�_����_�ð��뿡_Capacity_�ʰ���_���_���ܹ߻�) {
	//arrange
	Schedule* schedule = new Schedule{ON_THE_HOUR, CAPACITY_PER_HOUR, CUSTOMER};
	bookingScheduler.addSchedule(schedule);

	try {
		//act
		Schedule* newSchedule = new Schedule{ON_THE_HOUR, UNDER_CAPACITY, CUSTOMER};
		bookingScheduler.addSchedule(newSchedule);
		FAIL();
	} catch(std::runtime_error& ex) {
		//assert
		EXPECT_EQ(string{ex.what()}, string{"Number of people is over restaurant capacity per hour"});
	}

}

TEST_F(BookingItem, t4) {//�ð��뺰_�ο�������_�ִ�_����_�ð��밡_�ٸ���_Capacity_���־_������_�߰�_����) {
	//arrange
	Schedule* schedule = new Schedule{ON_THE_HOUR, CAPACITY_PER_HOUR, CUSTOMER};
	bookingScheduler.addSchedule(schedule);

	//act
	tm differentHour = plusHour(ON_THE_HOUR, 1);
	Schedule* newSchedule = new Schedule{differentHour, UNDER_CAPACITY, CUSTOMER};
	bookingScheduler.addSchedule(newSchedule);

	//assert
	EXPECT_EQ(true, bookingScheduler.hasSchedule(schedule));
}

TEST_F(BookingItem, t5) {//����Ϸ��_SMS��_������_�߼�) {
	//arrange
	Schedule* schedule = new Schedule{ON_THE_HOUR, CAPACITY_PER_HOUR, CUSTOMER};

	//act, assert
	EXPECT_CALL(testableSmsSender, send(schedule)).Times(1);
	bookingScheduler.addSchedule(schedule);
}

TEST_F(BookingItem, t6) {//�̸�����_����_��쿡��_�̸���_�̹߼�) {
	//arrange
	Schedule* schedule = new Schedule{ON_THE_HOUR, UNDER_CAPACITY, CUSTOMER};

	//act, assert
	EXPECT_CALL(testableMailSender, sendMail(schedule)).Times(0);
	bookingScheduler.addSchedule(schedule);
}

TEST_F(BookingItem, t7) {//�̸�����_�ִ�_��쿡��_�̸���_�߼�) {
	//arrange
	Schedule* schedule = new Schedule{ON_THE_HOUR, UNDER_CAPACITY, CUSTOMER_WITH_MAIL};

	//act
	EXPECT_CALL(testableMailSender, sendMail(schedule)).Times(1);
	bookingScheduler.addSchedule(schedule);
}


TEST_F(BookingItem, t8) {//���糯¥��_�Ͽ�����_���_����Ұ�_����ó��) {
	//arrange
	BookingScheduler* bookingScheduler = new TestableBookingScheduler{CAPACITY_PER_HOUR, SUNDAY_TIME};

	try {
		//act
		Schedule* schedule = new Schedule{ON_THE_HOUR, UNDER_CAPACITY, CUSTOMER_WITH_MAIL};
		bookingScheduler->addSchedule(schedule);
		FAIL();
	} catch(std::runtime_error& ex) {
		//assert
		EXPECT_EQ(string{ex.what()}, string{"Booking system is not available on Sunday."});
	}
}

TEST_F(BookingItem, t9) {//���糯¥��_�Ͽ�����_�ƴѰ��_���డ��) {
	//arrange
	BookingScheduler* bookingScheduler = new TestableBookingScheduler{CAPACITY_PER_HOUR, MONDAY_TIME};

	//act
	Schedule* schedule = new Schedule{ON_THE_HOUR, UNDER_CAPACITY, CUSTOMER_WITH_MAIL};
	bookingScheduler->addSchedule(schedule);

	//assert
	EXPECT_EQ(true, bookingScheduler->hasSchedule(schedule));

}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}