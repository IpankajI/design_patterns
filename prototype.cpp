#include<iostream>
#include<unordered_map>
#include<mutex>
using namespace std;

enum EPeripheralType{
    PT_Printer,
    PT_Mouse,
    PT_Keyboard
};

class CPeripheral{
public:
    virtual CPeripheral* clone()=0;
    virtual ~CPeripheral()=0;
    static CPeripheral* createPeripheral(EPeripheralType peripheralType);
};
CPeripheral::~CPeripheral(){}

class CPrinter:public CPeripheral{
public:
    CPeripheral* clone(){
        return new CPrinter();
    }
    CPrinter(){

    }
    ~CPrinter(){
        cout<<"CPrinter deleted"<<endl;
    }
};


class CMouse:public CPeripheral{
public:
    CPeripheral* clone(){
        return new CMouse();
    }
    CMouse(){

    }
    ~CMouse(){
        cout<<"CMouse deleted"<<endl;
    }
};



class CKeyboard:public CPeripheral{
public:
    CPeripheral* clone(){
        return new CKeyboard();
    }
    CKeyboard(){

    }
    ~CKeyboard(){
        cout<<"CKeyboard deleted"<<endl;
    }
};

CPeripheral* CPeripheral::createPeripheral(EPeripheralType peripheralType){
    if(PT_Keyboard==peripheralType){
        return new CKeyboard();
    }
    else if(PT_Mouse==peripheralType){
        return new CMouse();
    }
    else if(PT_Printer==peripheralType){
        return new CPrinter();
    }
    else{
        return NULL;
    }
};

class Client{
private:
    static unordered_map<EPeripheralType, CPeripheral*> mapPeripheralPrototype;
    static mutex mtx;
public:
    CPeripheral* clonePeripheral(EPeripheralType peripheralType){
        lock_guard<mutex> lck(mtx);
        if(mapPeripheralPrototype.count(peripheralType) ==0 ){
            mapPeripheralPrototype[peripheralType]= CPeripheral::createPeripheral(peripheralType);
        }
        return mapPeripheralPrototype[peripheralType]->clone();
    }
    ~Client(){
        for(auto it=mapPeripheralPrototype.begin(); it!=mapPeripheralPrototype.end();++it){
            delete it->second;
        }
        mapPeripheralPrototype.clear();
    }
};
unordered_map<EPeripheralType, CPeripheral*> Client::mapPeripheralPrototype;
mutex Client::mtx;


int main(){
    Client* peripheralClient=new Client();
    CPeripheral* printer=peripheralClient->clonePeripheral(PT_Printer);
    // CPeripheral* keyboard=peripheralClient->clonePeripheral(PT_Keyboard);
    CPeripheral* mouse=peripheralClient->clonePeripheral(PT_Mouse);
    delete printer;
    // delete keyboard;
    delete mouse;
    delete peripheralClient;
}