#include <iostream>
#include <typeinfo>
using namespace std;

// credit card
// visa and mastercard cannot do upi payment
// rupay card cannot do international payment
enum PaymentType{
    INTERNATION,
    DOMESTIC,
    UPI
};
class Payment{
public:
    int senderId;
    int receiverId;
    long long amount;
    PaymentType type;
};
class CreditCard{
public:
    string num;
    explicit CreditCard(const string& carNum):num(carNum){}
    virtual ~CreditCard() =default;
    virtual void performInternationalPayment(Payment payment);
    virtual void performDomesticPayment(Payment payment);
    virtual void performUpiPayment(Payment payment);
};
// Violates LSP(we are forced to implement a method that we don't need in class MastercardCreditCard,RupayCreditCard
// Violates OCP(not closed for modification) PaymentGateway (we need many if else and have to change if rupay one
// day can do performInternationalPayment

class MastercardCreditCard:public CreditCard{
public:
    explicit MastercardCreditCard(const string& carNum): CreditCard(carNum){}
    void performInternationalPayment(Payment payment) override{
        // logic
    }
    void performDomesticPayment(Payment payment) override{
        // logic
    }
    void performUpiPayment(Payment payment) override{
        // cannot do
    }
};

class RupayCreditCard:public CreditCard{
public:
    explicit RupayCreditCard(const string& carNum): CreditCard(carNum){}
    void performInternationalPayment(Payment payment) override{
        // cannot do
    }
    void performDomesticPayment(Payment payment) override{
        // logic
    }
    void performUpiPayment(Payment payment) override{
        // logic
    }
};
class PaymentGateway{
public:
    void processPayment(const Payment& payment,CreditCard* card){
        if(typeid(*card)!=typeid(RupayCreditCard) && payment.type==PaymentType::INTERNATION){
            card->performInternationalPayment(payment);
        }
        else if(typeid(*card)==typeid(RupayCreditCard) && payment.type==PaymentType::UPI){
            card->performUpiPayment(payment);
        }
        else if(payment.type==PaymentType::DOMESTIC){
            card->performDomesticPayment(payment);
        }
    }
};
int main(){
    return 0;
}
