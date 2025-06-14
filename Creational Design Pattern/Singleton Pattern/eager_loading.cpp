#include <iostream>
using namespace std;

class Database{
public:
    int cnt=0;
    static Database db;
    static Database& getInstance(){
        return db;
    }
    Database(const Database& db) = delete;
    Database& operator=(const Database&) = delete;
private:
    Database() = default;
};
Database Database::db;
int main(){
    Database& db = Database::getInstance();
    db.cnt++;
    Database& db2 = Database::getInstance();
    cout<<db2.cnt++<<endl;
}
