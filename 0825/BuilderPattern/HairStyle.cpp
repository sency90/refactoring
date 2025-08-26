#include "HairStyle.h"

#include <stdexcept>

int HairStyle::Front() const noexcept { return spec_.front; }
int HairStyle::Back() const noexcept { return spec_.back; }
int HairStyle::Side() const noexcept { return spec_.side; }
int HairStyle::Price() const noexcept { return price_; }

// Builder만 생성 가능
HairStyle::HairStyle(const HairStyleSpec &spec)
    : spec_(spec), price_(ComputePrice()) {}

int HairStyle::ComputePrice() const {
    ValidateBeforeComputePrice();
    return spec_.front * 1'000 + spec_.back * 2'000 + spec_.side * 10'000;
}

void HairStyle::ValidateBeforeComputePrice() const {
    if (spec_.front < 0 || spec_.back < 0 || spec_.side < 0) {
        throw std::logic_error("You need to set hair_style");
    }
}
