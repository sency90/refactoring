#pragma once
#include "HairStyleSpec.h"

class SoldierHairStyleBuilder;

class HairStyle {
   private:
    HairStyleSpec spec_{};
    int price_{0};

   public:
    int Front() const noexcept;
    int Back() const noexcept;
    int Side() const noexcept;
    int Price() const noexcept;

   private:
    friend class SoldierHairStyleBuilder;  // Builder만 생성 가능
    explicit HairStyle(const HairStyleSpec &spec);

   private:
    int ComputePrice() const;
    void ValidateBeforeComputePrice() const;
};
