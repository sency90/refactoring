#pragma once
class HairStyle;
class IHairStyleBuilder;

class HairDesigner {  // Director
   private:
    IHairStyleBuilder &builder;

   public:
    explicit HairDesigner(IHairStyleBuilder &builder);
    [[nodiscard]] HairStyle CutSoldierHairStyle(int front, int back, int side);
};
