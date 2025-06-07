#include <iostream>
using namespace std;

class Logistic{
public:
    string message;
    explicit Logistic(const string& message){
        this->message=message;
    }
    virtual ~Logistic() = default;
    virtual void send()=0;
};

class AirPlaneLogistic:public Logistic{
public:
    explicit AirPlaneLogistic(const string& message):Logistic(message){}
    ~AirPlaneLogistic() override = default;
    void send() override{
        cout<<"Starting parcel by air...."<<endl;
    }
};

class TruckLogistic:public Logistic{
    public:
    explicit TruckLogistic(const string& message):Logistic(message){}
    ~TruckLogistic() override = default;
    void send() override{
        cout<<"Starting parcel by truck...."<<endl;
    }
};

enum LogisticMode{
    AIRPLANE,
    TRUCK,
};

// Dealing with logic of object creation
// open of extension
class LogisticFactory{
public:
    static Logistic* getLogistic(LogisticMode mode,const string& message){
        Logistic* logistic = nullptr;
        if(mode==LogisticMode::AIRPLANE){
            logistic = new AirPlaneLogistic(message);
        }
        else if(mode==LogisticMode::TRUCK){
            logistic = new TruckLogistic(message);
        }
        return logistic;
    }
};

// just handling the sending logic not dealing with logic on object creation (SRP)
// decoupling
class LogisticService{
public:
    void send(LogisticMode mode,const string& message){
        Logistic* logistic = LogisticFactory::getLogistic(mode,message);
        if(!logistic){
            cout<<"Failed to send.."<<endl;
            return;
        }
        logistic->send();
    }
};

int main(){
    LogisticService logisticService;
    logisticService.send(LogisticMode::TRUCK,"This is a message");
    logisticService.send(LogisticMode::AIRPLANE,"This is a message");
}
