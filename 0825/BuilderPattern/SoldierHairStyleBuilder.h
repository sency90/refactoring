#pragma once
#include "HairStyleSpec.h"
#include "IHairStyleBuilder.h"

class HairStyle;

class SoldierHairStyleBuilder : public IHairStyleBuilder {
   private:
    HairStyleSpec spec_{};

   public:
    virtual ~SoldierHairStyleBuilder() noexcept = default;

   public:
    void Reset() override;

    IHairStyleBuilder &Front(int front) override;
    IHairStyleBuilder &Back(int back) override;
    IHairStyleBuilder &Side(int side) override;

    [[nodiscard]] HairStyle Build() override;
};
