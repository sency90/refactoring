#include <cstdio>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <memory>
#include "HairStyleSpec.h"
#include "HairStyle.h"
#include "IHairStyleBuilder.h"
#include "SoldierHairStyleBuilder.h"
#include "HairDesigner.h"
using namespace std;

int main() {
	try {
		std::unique_ptr<IHairStyleBuilder> builder = std::make_unique<SoldierHairStyleBuilder>();
		HairDesigner hair_designer(*builder); //Director가 ConcreteBuilder를 인자로 받아서 
		HairStyle hair_style = hair_designer.CutSoldierHairStyle(1, 2, 3);
		printf("Soldier Hair Style Price: %d\n", hair_style.Price());
	}
	catch(std::exception &ex) {
		printf("[EXCEPTION] %s\n", ex.what());
	}
	return 0;
}