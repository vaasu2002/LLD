package Observer_Design_Pattern.conc_observer;

import Observer_Design_Pattern.interfaces.Observer;
public class SmsObserver implements Observer<String>{
    String phoneNum;
    public SmsObserver(String phoneNum){
        this.phoneNum = phoneNum;
    }
    @Override
    public void update(String latestData){
        System.out.println("Sending notification to phone number: "+this.phoneNum);
    }
}