#include "RacingCar.h"
RacingCar::RacingCar(int max_fuel) {
	max_fuel_ = max_fuel;
	remaining_fuel_ = max_fuel;
}

void RacingCar::Accelerate() override {
	power_++;
	remaining_fuel_--;
}
