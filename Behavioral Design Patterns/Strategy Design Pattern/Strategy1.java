interface PaymentStrategy{
    public void processPayment();
}

// public class should be declared only with their sepearete file
class CreditCardPayment implements PaymentStrategy{
    public void processPayment(){
        System.out.println("Processing payment using credit card!!");
    }
}

class WAlletPayment implements PaymentStrategy{
    public void processPayment(){
        System.out.println("Processing payment using wallet!!");
    }
}

class PaymentProcessor{
    private PaymentStrategy paymentStrategy;
    PaymentProcessor(PaymentStrategy paymentStrategy){
        this.paymentStrategy = paymentStrategy;
    }
    public void process(){
        this.paymentStrategy.processPayment();
    }
    public void setPaymentStategy(PaymentStrategy paymentStrategy){
        this.paymentStrategy = paymentStrategy;
    }
}

public class Strategy1{
    public static void main(String args[]){
        PaymentStrategy card = new CreditCardPayment();
        PaymentStrategy wallet = new WAlletPayment();
        PaymentProcessor pp = new PaymentProcessor(card);
        pp.process();
        pp.setPaymentStategy(wallet);
        pp.process();
    }
}
