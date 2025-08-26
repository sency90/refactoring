#include "HairDesigner.h"

#include "HairStyle.h"
#include "IHairStyleBuilder.h"

HairDesigner::HairDesigner(IHairStyleBuilder &builder) : builder(builder) {}

[[nodiscard]]
HairStyle HairDesigner::CutSoldierHairStyle(int front, int back, int side) {
    builder.Reset();
    return builder.Front(front).Back(back).Side(side).Build();
}
