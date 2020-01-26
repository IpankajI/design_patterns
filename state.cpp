#include<iostream>

using namespace std;

class CMachine;

class CState{
public:
    virtual ~CState()=0;
    virtual void On(CMachine* machine)=0;
    virtual void Off(CMachine* machine)=0;

    virtual bool isOn(){
        return false;
    }
    virtual bool isOff(){
        return false;
    }
};

CState::~CState(){}

class COn:public CState{
public:
    void On(CMachine* machine){
        cout<<"Already on"<<endl;
    }
    void Off(CMachine* machine){
        cout<<"Going Off from On"<<endl;
    }
    bool isOn(){
        return true;
    }

    ~COn(){
        cout<<"COn: delete"<<endl;
    }
};


class COff:public CState{
public:
    void On(CMachine* machine){
        cout<<"Going On from Off"<<endl;
    }
    void Off(CMachine* machine){
        cout<<"Already Off"<<endl;
    }
    bool isOff(){
        return true;
    }
    ~COff(){
        cout<<"COff: delete"<<endl;
    }
};

class CMachine{
private:
    CState* state;

public:

    void turnOn(){
        if(state->isOn()){
            return;
        }
        state->On(this);
        delete state;
        state=new COn();
    }
    
    void turnOff(){
        if(state->isOff()){
            return;
        }
        state->Off(this);
        delete state;
        state=new COff();
    }
    
    CMachine(){
        state=new COff();
    }

    ~CMachine(){
        if(state){
            delete state;
        }
    }
};

int main(){
    CMachine* machine=new CMachine();
    machine->turnOff();
    machine->turnOn();
    machine->turnOff();
    machine->turnOff();
    machine->turnOn();

    delete machine;
}