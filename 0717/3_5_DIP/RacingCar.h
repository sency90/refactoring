#pragma once

#include "Vehicle.h"
#include "Pilot.h"
class RacingCar : public Vehicle{
public:
    RacingCar(int max_fuel);
    void Accelerate() override;

private:
    int max_fuel_;
    int remaining_fuel_;
    int power_;
};
