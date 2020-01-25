
#include<iostream>

using namespace std;

enum EVehicleType{
    VT_Bus, VT_Train, VT_Flight 
};

class CVehical{
public:
    virtual bool Book()=0;
    virtual ~CVehical()=0;
    static CVehical* createVehical(EVehicleType vehicleType);
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

class CFlight:public CVehical{
public:
    bool Book(){
        cout<<"Flight is booked!"<<endl;
        return true;
    }
};

CVehical* CVehical::createVehical(EVehicleType vehicleType){
    
    if(VT_Bus == vehicleType){
        return new CBus();
    }
    else if(VT_Train == vehicleType){
        return new CTrain();
    }
    else if(VT_Flight == vehicleType){
        return new CFlight();
    }
    else{
        return NULL;
    }
}


class CVehicalBookingHandler{
private:
    CVehical* vehicle;
    EVehicleType eVehicleType;

public:
    CVehicalBookingHandler(EVehicleType eVehicleType):eVehicleType(eVehicleType){
        vehicle=CVehical::createVehical(eVehicleType);
    }
    ~CVehicalBookingHandler(){
        if(vehicle){
            delete vehicle;
            vehicle=NULL  ;
        }
    }
    CVehical* getVehicle(){
        return vehicle;
    }

    EVehicleType getVehicleType(){
        return eVehicleType;
    }
};


int main(){
    CVehicalBookingHandler busBookingHandler(VT_Bus);
    CVehical* vehicle=busBookingHandler.getVehicle();
    vehicle->Book();

    CVehicalBookingHandler trainBookingHandler(VT_Train);
    vehicle=trainBookingHandler.getVehicle();
    vehicle->Book();

    CVehicalBookingHandler flightBookingHandler(VT_Flight);
    vehicle=flightBookingHandler.getVehicle();
    vehicle->Book();
}