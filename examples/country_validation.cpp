// SRP, OCP, LSP ,ISP,DI (SOLID)
// Factory Design Pattern
#include <iostream>
#include<map>
using namespace std;

enum Country{
    US,
    INDIA,
    JAPAN
};
class User{
    string email;
    Country country;
    int age;
public:
    User(const string& email,const Country country,const int age){
        this->email=email;
        this->country=country;
        this->age = age;
    }
    int getAge() const{
        return age;
    }
    Country getCountry() const{
        return country;
    }
    string getEmail()const{
         return email;
    }
    // getter and setters
};
class UserValidator{
public:
    virtual ~UserValidator() = default;
    virtual bool validator(const User& user) =0;
};

class AdultUserValidator:public UserValidator{
    map<Country,int> adultAgeDefinition;
public:
    bool validator(const User& user)override{
        Country country = user.getCountry();
        int legalAge = adultAgeDefinition[country];
        if(user.getAge()<legalAge){
            // invalid age
            return false;
        }
        return true;
    }
};

class EmailIdUserValidator:public UserValidator{
public:
    bool validator(const User& user)override{
        string email = user.getEmail();
        // logic
        // return false;
        return true;
    }
};


class CountryUserValidation{
    vector<shared_ptr<UserValidator>> validators;
public:
    explicit CountryUserValidation(const vector<shared_ptr<UserValidator>>& countryValidators):
    validators(countryValidators) {}

    bool validateUser(const User& user) const {
        for(auto& validator:validators){
            if(!validator->validator(user)){
                return false;
            }
        }
        return true;
    }
};

class CountryUserValidationFactory{
public:
    static CountryUserValidation getValidatorsForCountry(const Country& country){
        if(Country::US==country){
            return CountryUserValidation({
                make_shared<AdultUserValidator>(),
            });
        }
        else if(Country::INDIA==country){
            return CountryUserValidation({
                make_shared<AdultUserValidator>(),
                make_shared<EmailIdUserValidator>()
            });
        }
        return CountryUserValidation({});
    }
};

// for different countries there will be different validation
class UserService{
    vector<User> userList;
    bool userValidation(const User& user){
        CountryUserValidation countryUserValidation = CountryUserValidationFactory::getValidatorsForCountry(user.getCountry());
        if(!countryUserValidation.validateUser(user)){
            return 0;
        }
        return 1;
    }
public:
    void createUser(const User& user){
        if(!userValidation(user)){

        }
        userList.push_back(user);
    }
};
