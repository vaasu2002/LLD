#include <iostream>
using namespace std;
class Database {
private:
    static Database* instance;
    static mutex mtx;

    Database() = default;
public:
    int cnt=0;
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;
    static Database& getInstance() {
        lock_guard lock(mtx); // aquiring lock
        if (!instance) {
            instance = new Database();
        }
        return *instance;
    }
};

// Initialization outside the class
Database* Database::instance = nullptr;
mutex Database::mtx;

int main(){
    Database& db = Database::getInstance();
    db.cnt++;
    Database& db2 = Database::getInstance();
    cout<<db2.cnt<<endl;
}
