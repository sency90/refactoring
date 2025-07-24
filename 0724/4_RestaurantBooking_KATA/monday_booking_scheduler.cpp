#include "booking_scheduler.cpp"

class MondayBookingScheduler: public BookingScheduler {
public:
	MondayBookingScheduler(int capacityPerHour):
		BookingScheduler{capacityPerHour} {}

	time_t getNow() override { //This function always returns Monday.
		return getTime(2021, 3, 29, 17, 0);
	}

private:
	time_t getTime(int year, int mon, int day, int hour, int min) {
		tm result = {0, min, hour, day, mon-1, year-1990, 0, 0, -1};
		return mktime(&result);
	}
};
