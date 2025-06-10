#include <iostream>
#include <vector>
#include <string>
using namespace std;

// builder pattern --> Subway
// select bread(compulsory), select size(compulsory),
// select list of sauces(optional), select list of toppings(optional)
// hasCheese(optional), hasGrilled(optional)

enum BreadType{
    WhiteItalian,
    Multigrain
};
enum BreadSize{
    Inch_15,
    Inch_30
};
enum Sauces{
    BBQ,
    Mustard,
    Mayo
};
enum Toppings{
    Tomato,
    Pickle,
    Onion,
};

class SubwaySub{
private:
    BreadSize size=BreadSize::Inch_15;
    BreadType bread=BreadType::WhiteItalian;
    SubwaySub()= default;
    string getSizeString(const BreadSize& size) const {
        switch(size) {
            case Inch_15: return "15 cm";
            default: return "30 cm";
        }
    }
    string getBreadString(const BreadType& bread) const {
        switch(bread) {
            case WhiteItalian: return "White Italian Bread";
            case Multigrain: return "Multi grain bread";
            default: return "Unknown";
        }
    }
public:
    class SubBuilder{
    public:
        BreadSize breadSize;
        BreadType breadType;
        vector<Sauces> saucesList;
        vector<Toppings> toppingsList;

        SubBuilder* chooseBreadType(const BreadType& bread){
            this->breadType = bread;
            return this;
        }
        SubBuilder* chooseBreadSize(const BreadSize& size){
            this->breadSize = size;
            return this;
        }

        SubwaySub build() const{
            return SubwaySub(*this);
        }
    };
    explicit SubwaySub(const SubBuilder& subBuilder){
        this->bread = subBuilder.breadType;
        this->size = subBuilder.breadSize;
    }
    
    void display() const {
        cout<<"Bread Type: "<<getBreadString(bread)<<" of size: "<<getSizeString(size)<<endl;
    }
};

int main(){
    const SubwaySub sub = SubwaySub::SubBuilder().chooseBreadType(BreadType::Multigrain)
                                                 ->chooseBreadSize(BreadSize::Inch_30)->build();
    sub.display();
}
