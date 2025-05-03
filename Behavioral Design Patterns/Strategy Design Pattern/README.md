
- Flexibility
- Maintainability
- Extensibility
- Take care of LSP and Open Close Principle 
- Each statedy is a way to do stuff (SRP) Seperation of concern
- Take our things that will be changing from a class

## Example 1: Payment processing
```java
interface PaymentStrategy{
    public void processPayment();
}

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

public class Main{
    public static void main(String args[]){
        PaymentStrategy card = new CreditCardPayment();
        PaymentStrategy wallet = new WAlletPayment();
        PaymentProcessor pp = new PaymentProcessor(card);
        pp.process();
        pp.setPaymentStategy(wallet);
        pp.process();
    }
}
```
