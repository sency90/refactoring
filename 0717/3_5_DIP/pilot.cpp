#include "Pilot.h"
void Pilot::IncreaseSpeed() {
	vehicle_->Accelerate();
}

void Pilot::SetVehicle(Vehicle *vehicle) {
	this->vehicle_ = vehicle;
}
