#pragma once

class HairStyle;

class IHairStyleBuilder {
   public:
    virtual ~IHairStyleBuilder() noexcept = default;
    virtual void Reset() = 0;
    virtual IHairStyleBuilder &Front(int front) = 0;
    virtual IHairStyleBuilder &Back(int back) = 0;
    virtual IHairStyleBuilder &Side(int side) = 0;
    [[nodiscard]] virtual HairStyle Build() = 0;
    // Interface 역할을 하기 위해 멤버변수는 선언하지 않는다.
};
