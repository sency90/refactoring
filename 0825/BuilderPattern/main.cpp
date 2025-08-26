#include <cstdio>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <memory>
using namespace std;
struct HairStyleSpec {
	int front=0;
	int back=0;
	int side=0;
};

class HairStyle {
private:
	HairStyleSpec spec_{};
	int price_{ 0 };

public:
	int Front() const noexcept { return spec_.front; }
	int Back() const noexcept { return spec_.back; }
	int Side() const noexcept { return spec_.side; }
	int Price() const noexcept { return price_; }

private:
	friend class SoldierHairStyleBuilder; //Builder만 생성 가능
	explicit HairStyle(const HairStyleSpec &spec):spec_(spec), price_(ComputePrice()) {}

	int ComputePrice() const {
		ValidateBeforeComputePrice();
		return spec_.front * 1'000 + spec_.back * 2'000 + spec_.side * 10'000;
	}

	void ValidateBeforeComputePrice() const {
		if(spec_.front<0 || spec_.back<0 || spec_.side<0) {
			throw std::logic_error("You need to set hair_style");
		}
	}
};

class IHairStyleBuilder {
public:
	virtual ~IHairStyleBuilder() {}
	virtual void Reset()=0;
	virtual IHairStyleBuilder &Front(int front)=0;
	virtual IHairStyleBuilder &Back(int back)=0;
	virtual IHairStyleBuilder &Side(int side)=0;
	[[nodiscard]] virtual HairStyle Build()=0;
	//Interface 역할을 하기 위해 멤버변수는 선언하지 않는다.
};

class SoldierHairStyleBuilder: public IHairStyleBuilder {
private:
	HairStyleSpec spec_{};

public:
	void Reset() override {
		spec_={};
	}

	IHairStyleBuilder &Front(int front) override {
		spec_.front = front;
		return *this;
	}

	IHairStyleBuilder &Back(int back) override {
		spec_.back = back;
		return *this;
	}

	IHairStyleBuilder &Side(int side) override {
		spec_.side = side;
		return *this;
	}

	[[nodiscard]] HairStyle Build() override {
		HairStyle hair_style{ spec_ };
		Reset();
		return hair_style;
	}
};

class HairDesigner { //Director
private:
	IHairStyleBuilder &builder;
public:
	explicit HairDesigner(IHairStyleBuilder &builder):builder(builder) {}
	[[nodiscard]] HairStyle CutSoldierHairStyle(int front, int back, int side) {
		builder.Reset();
		return builder.Front(front).Back(back).Side(side).Build();
	}
};

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