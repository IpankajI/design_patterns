#include<bits/stdc++.h>

using namespace std;

class CVehical{
    
public:
    virtual bool Book()=0;
    virtual ~CVehical();
};

CVehical::~CVehical(){}

class CBus:public CVehical{
public:
    bool Book(){
        cout<<"Bus is booked!"<<endl;
        return true;
    }
};


class CTrain:public CVehical{
public:
    bool Book(){
        cout<<"Train is booked!"<<endl;
        return true;
    }
};


class FactoryMethod{

public:
    virtual ~FactoryMethod()=0;
    virtual CVehical* createVehicle()=0;

};

FactoryMethod::~FactoryMethod(){}

class FactoryBus: public FactoryMethod{
    CVehical* createVehicle(){
        return new CBus();
    }
};

class FactoryTrain: public FactoryMethod{

    CVehical* createVehicle(){
        return new CTrain();
    }
};



int main(){
    
    FactoryMethod *busFactory, *trainFactory;
    busFactory= new FactoryBus();
    trainFactory= new FactoryTrain();

    CVehical* bus= busFactory->createVehicle();
    CVehical* train= trainFactory->createVehicle();

    bus->Book();
    train->Book();

    delete busFactory;
    delete trainFactory;
    delete bus;
    delete train;

}
