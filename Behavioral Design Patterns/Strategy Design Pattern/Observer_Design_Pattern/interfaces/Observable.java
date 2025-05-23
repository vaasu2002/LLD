package Observer_Design_Pattern.interfaces;

public interface Observable<T>{
    void addObserver(Observer<T> observer);
    void removeObserver(Observer<T> observer);
    void setData(T latestData);
    void notifyObservers(T latestData);
}