#include <iostream>
using namespace std;

class Payment{};

class RefundStrategy{
public:
    virtual ~RefundStrategy(){
        cout<<"calling RefundStrategy destructor"<<endl;
    }
    virtual void doRefund()=0;
};

class WalletRefundStrategy final:public RefundStrategy{
public:
    void doRefund() override{
        cout<<"Refunding money on wallet...."<<endl;
    }
};

class BankRefundStrategy final:public RefundStrategy{
public:
    void doRefund() override{
        cout<<"Refunding money on wallet...."<<endl;
    }
};

class ThirdPartyRefundStrategy final:public RefundStrategy{
public:
    ~ThirdPartyRefundStrategy() override{
        cout<<"calling ThirdPartyRefundStrategy destructor"<<endl;
    }
    void doRefund() override{
        cout<<"Refunding money via 3rd Party ...."<<endl;
    }
};
enum RefundType{
    WALLET,
    THIRD_PARTY,
    BANK
};

class RefundFactory{
public:
    virtual ~RefundFactory(){
        cout<<"calling generic refund factory destructor"<<endl;
    }
    virtual RefundStrategy* getRefundStrategy(RefundType type) = 0;
};
class RupayRefundFactory final :public RefundFactory{
public:
    RefundStrategy* getRefundStrategy(RefundType type) override{
        RefundStrategy* refundStrategy = nullptr;
        if(type==RefundType::BANK){
            refundStrategy =  new BankRefundStrategy();
        }
        else if(type==RefundType::WALLET){
            refundStrategy =  new BankRefundStrategy();
        }
        return refundStrategy;
    }
};
class VisaRefundFactory final :public RefundFactory{
public:
    ~VisaRefundFactory() override{
        cout<<"calling visa refund factory destructor"<<endl;
    }
    RefundStrategy* getRefundStrategy(RefundType type) override{
        RefundStrategy* refundStrategy = nullptr;
        if(type==RefundType::BANK){
            refundStrategy =  new BankRefundStrategy(); // no one owns this object???
        }
        else if(type==RefundType::THIRD_PARTY){
            refundStrategy =  new ThirdPartyRefundStrategy();
        }
        return refundStrategy;
    }
};

class CreditCard{
public:
    virtual ~CreditCard(){
        cout<<"CreditCard destructor called"<<endl;
    }
    virtual void processDomesticPayment()=0;
};
class RefundCapableCreditCard{
public:
    RefundFactory* refundFactory;
    explicit RefundCapableCreditCard(RefundFactory* refundFactory){
        this->refundFactory = refundFactory;
    }

    virtual ~RefundCapableCreditCard(){
        cout<<"RefundCapableCreditCard destructor called"<<endl;
    }
    void processRefund(const RefundType type) const{
        RefundStrategy* RefundStrategy = this->refundFactory->getRefundStrategy(type);
        RefundStrategy->doRefund();
    }

};
class VisaCreditCard final :public CreditCard,public RefundCapableCreditCard{
public:
    ~VisaCreditCard() override{
        cout<<"calling VisaCreditCard destructor"<<endl;
    }
    explicit VisaCreditCard(RefundFactory* refundFactory)
        :CreditCard(),RefundCapableCreditCard(refundFactory){}
    void processDomesticPayment() override{
        // visa domestic payment logic
        cout<<"processing domestic payment"<<endl;
    }
};
int main(){
    RefundFactory* refundFactory = new VisaRefundFactory();
    RefundCapableCreditCard* card = new VisaCreditCard(refundFactory);
    card->processRefund(RefundType::BANK);
    card->processRefund(RefundType::THIRD_PARTY);
    delete card;
    delete refundFactory;
}
