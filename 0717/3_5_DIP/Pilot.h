#pragma once
#include "Vehicle.h"
#include "RacingCar.h"

class Pilot {
public:
    Pilot() {}

    void IncreaseSpeed() {
        vehicle_->Accelerate();
    }

    void SetVehicle(Vehicle *vehicle) {
        this->vehicle_ = vehicle;
    }

private:
    Vehicle *vehicle_;
};
