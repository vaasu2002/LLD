#include <iostream>
using namespace std;

class Vehicle{
public:
    string number_plate;
    explicit Vehicle(const string& number_plate){
        this->number_plate=number_plate;
    }
    virtual ~Vehicle() = default;
    virtual void start()=0;
    virtual void stop()=0;
};

class Car:public Vehicle{
public:
    explicit Car(const string& number_plate):Vehicle(number_plate){}
    ~Car() override = default;
    void start() override{
        cout<<"Starting the car...."<<endl;
    }
    void stop() override{
        cout<<"Stopping the car...."<<endl;
    }
};

class Bus:public Vehicle{
public:
    explicit Bus(const string& number_plate):Vehicle(number_plate){}
    ~Bus() override = default;
    void start() override{
        cout<<"Starting the bus...."<<endl;
    }
    void stop() override{
        cout<<"Stopping the bus...."<<endl;
    }
};

enum VehicleType{
    CAR,
    TRUCK,
    BUS
};

class VehicleFactory{
public:
    static Vehicle* getVehicle(VehicleType vehicle_type,const string& number_plate){
        Vehicle* vehicle = nullptr;
        if(vehicle_type==VehicleType::CAR){
            vehicle = new Car(number_plate);
        }
        else if(vehicle_type==VehicleType::BUS){
            vehicle = new Bus(number_plate);
        }
        return vehicle;
    }
};

int main(){
    Vehicle* vehicle1 = VehicleFactory::getVehicle(VehicleType::CAR,"DL5454");
    vehicle1->start();
    Vehicle* vehicle2 = VehicleFactory::getVehicle(VehicleType::BUS,"DL5454");
    vehicle2->start();
    return 0;
}
