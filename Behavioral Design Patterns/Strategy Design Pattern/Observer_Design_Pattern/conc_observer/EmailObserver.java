package Observer_Design_Pattern.conc_observer;

import Observer_Design_Pattern.interfaces.*;

public class EmailObserver implements Observer<String> {
    String emailID;
    public EmailObserver(String emailID){
        this.emailID = emailID;
    }
    @Override
    public void update(String latestData){
        System.out.println("Sending notification to emailId: "+this.emailID);
    }
}