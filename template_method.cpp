#include<iostream>

using namespace std;

class CTicket{
private:
    virtual void selectSeats()=0;
    virtual void calculatePrice()=0;
    virtual void makePayment()=0;
    virtual void sendConfirmation()=0;
public:
    virtual void bookTickets(){
        selectSeats();
        calculatePrice();
        makePayment();
        sendConfirmation();
    }

    virtual ~CTicket()=0;
};
CTicket::~CTicket(){}


class CMovieTicket:public CTicket{
private:
    void selectSeats(){
        cout<<"CMovieTicket: seats selected"<<endl;
    }
    void calculatePrice(){
        cout<<"CMovieTicket: price calculated"<<endl;
    }
    void makePayment(){
        cout<<"CMovieTicket: payment received"<<endl;
    }
    void sendConfirmation(){
        cout<<"CMovieTicket: confirmation message sent"<<endl;
    }
};

class CFlightTicket:public CTicket{
private:
    void selectSeats(){
        cout<<"CFlightTicket: seats selected"<<endl;
    }
    void calculatePrice(){
        cout<<"CFlightTicket: price calculated"<<endl;
    }
    void makePayment(){
        cout<<"CFlightTicket: payment received"<<endl;
    }
    void sendConfirmation(){
        cout<<"CFlightTicket: confirmation message sent"<<endl;
    }
};

int main(){
    CTicket* movieTicket=new CMovieTicket();
    movieTicket->bookTickets();

    CTicket* flightTicket=new CFlightTicket();
    flightTicket->bookTickets();

    delete movieTicket;
    delete flightTicket;
}