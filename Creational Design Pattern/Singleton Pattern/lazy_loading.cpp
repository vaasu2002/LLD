#include <iostream>
using namespace std;

class Database{
public:
    int cnt=0;
    static Database& getInstance(){
        static Database db;
        return db;
    }

    // Deleting copy constructor and assignment opeator
    Database(const Database& db) = delete;
    Database& operator=(const Database&) = delete;
private:
    Database() = default;
};

int main(){
    Database& db = Database::getInstance();
    db.cnt++;
    Database& db2 = Database::getInstance();
    cout<<db2.cnt++<<endl;
}
