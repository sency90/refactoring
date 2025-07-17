#include "racing_car.cpp"

class Pilot {
public:
    Pilot() {
        //Pilot�� Racing Car�� ���� �¾��. 
        //�̷��� ���Ϸ��� ó������ � ������ ���ӵ� �� �ۿ� ����. 
        //�ٸ� ������ �̿��� �� �ֵ��� �Ϸ��� �������踦 ������� �Ѵ�. 
        //-> DIP: Dependency Inversion Principle
        vehicle_ = new RacingCar(100); 
    }

    void IncreaseSpeed() {
        vehicle_->Accelerate();
    }

private:
    RacingCar *vehicle_;
};
