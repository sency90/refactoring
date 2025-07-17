#include "racing_car.cpp"

class Pilot {
public:
    Pilot() {
        //Pilot이 Racing Car와 같이 태어난다. 
        //이러면 파일럿은 처음부터 어떤 차량에 종속될 수 밖에 없다. 
        //다른 차량도 이용할 수 있도록 하려면 의존관계를 뒤집어야 한다. 
        //-> DIP: Dependency Inversion Principle
        vehicle_ = new RacingCar(100); 
    }

    void IncreaseSpeed() {
        vehicle_->Accelerate();
    }

private:
    RacingCar *vehicle_;
};
