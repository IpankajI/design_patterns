#include<iostream>

using namespace std;



class CImplemention{
public:
    virtual ~CImplemention()=0;
    virtual void switchOff()=0;
};
CImplemention::~CImplemention(){}

class CRemote{
public:
    CImplemention* implementation;
    virtual ~CRemote()=0;
    virtual void switchOff()=0;
};
CRemote::~CRemote(){}

class CTVImplementation:public CImplemention{
public:
    void switchOff(){
        cout<<"turning TV off"<<endl;
    }
};

class CRemoteImplimentation:public CRemote{
public:
    void switchOff(){
        implementation->switchOff();
    }
    CRemoteImplimentation(CImplemention* implementation){
        this->implementation=implementation;
    }
    ~CRemoteImplimentation(){
        if(implementation==NULL){
            return;
        }
        cout<<"CRemoteImplimentation: deleting pointer implementation"<<endl;
        delete implementation;
        implementation=NULL;
    }
};


int main(){
    CRemote* remote=new CRemoteImplimentation(new CTVImplementation());
    remote->switchOff();
    delete remote;
}