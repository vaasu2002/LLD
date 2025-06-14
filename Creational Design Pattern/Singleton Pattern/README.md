# Singleton Pattern
Ensures that the class has only one instance and not multiple instances **throughout the application/services**
- Single Source of truth (A global instance) for different services
- Example-> Database, Logger, Queue, Analytics

##### NOTE->
- Make the default constructor private
- Delete copy constructor
- Delete assignment operator(=)
- **Database& db = Database::getInstance()** USE REFERENCE BIND ELSE IT WILL INVOKE COPY CONSTRUCTOR
Eager Loading (Thread Safe)
- **Eager loading is not memory efficient, as the instance will be there in memory even if we don't need it.**
    - Using mutex, we can use a thread-safe lazy loading, but >= C++ 1,1, local static itself is thread safe
```cpp
class Database{
public:
    // only tells the compiler that such a static variable exists.
    // It does not allocate storage or construct it yet.
    static Database db;
    int cnt=0;
    static Database& getInstance(){
        return db;
    }

    // Deleting copy constructor and assignment operator
    Database(const Database& db) = delete;
    Database& operator=(const Database&) = delete; 
private:
    Database() = default;
};
//Actual definition and construction of the static member happen here.
Database Database::db; // Initialization outside the class
```

Lazy Loading
```cpp
class Database{
public:
    int cnt=0;
    static Database& getInstance(){
        static Database db;
        return db;
    }

    // Deleting copy constructor and assignment operator
    Database(const Database& db) = delete;
    Database& operator=(const Database&) = delete; 
private:
    Database() = default;
};
```

```cpp
int main(){
    Database& db = Database::getInstance();
    db.cnt++;
    Database& db2 = Database::getInstance();
    cout<<db2.cnt++<<endl;
}
```
