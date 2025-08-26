#include "SoldierHairStyleBuilder.h"

#include "HairStyle.h"

void SoldierHairStyleBuilder::Reset() { spec_ = {}; }

IHairStyleBuilder &SoldierHairStyleBuilder::Front(int front) {
    spec_.front = front;
    return *this;
}

IHairStyleBuilder &SoldierHairStyleBuilder::Back(int back) {
    spec_.back = back;
    return *this;
}

IHairStyleBuilder &SoldierHairStyleBuilder::Side(int side) {
    spec_.side = side;
    return *this;
}

[[nodiscard]] HairStyle SoldierHairStyleBuilder::Build() {
    HairStyle hair_style{spec_};
    Reset();
    return hair_style;
}
