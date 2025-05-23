package Observer_Design_Pattern;

import java.util.List;
import java.util.ArrayList;
import Observer_Design_Pattern.interfaces.Observable;
import Observer_Design_Pattern.interfaces.Observer;

public class ObservableImpl implements Observable<String>{
    List<String> data;
    List<Observer<String>> observers;
    public ObservableImpl(){
        this.data = new ArrayList<>();
        this.observers = new ArrayList<>();
    }
    @Override
    public void addObserver(Observer<String> observer){
        this.observers.add(observer);
    }
    @Override
    public void removeObserver(Observer<String> observer){
        this.observers.remove(observer);
    }
    @Override
    public void notifyObservers(String latestData){
        for(Observer<String> observer:observers){
            observer.update(latestData);
        }
    }
    @Override
    public void setData(String latestData){
        this.data.add(latestData);
        this.notifyObservers(latestData);
    }
}
