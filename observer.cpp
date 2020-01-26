#include<iostream>
#include<unordered_set>

using namespace std;

class CObserver{
public:
    virtual ~CObserver()=0;
    virtual void update(string msg)=0;
};

CObserver::~CObserver(){}

class CSubject{
private:
    string msg;
    unordered_set<CObserver*> observers;
    void notifySubsribers(){
        for(auto it=observers.begin(); it!=observers.end();++it){
            (*it)->update(msg);
        }
    }
public:
    void subscribe(CObserver* observer){
        observers.insert(observer);
    }
    void unSubscribe(CObserver* observer){
        observers.erase(observer);
    }
    void update(string msg){
        this->msg=msg;
        notifySubsribers();
    }
};

class CHuman:public CObserver{
public:
    void update(string msg){
        cout<<"CHuman: got msg- "<<msg<<endl;
    }
};


class CRobot:public CObserver{
public:
    void update(string msg){
        cout<<"CRobot: got msg- "<<msg<<endl;
    }
};

int main(){

    CSubject* subject=new CSubject();

    CObserver* human=new CHuman();
    CObserver* robot=new CRobot();

    
    subject->subscribe(human);
    subject->subscribe(robot);

    subject->update("Hello everyone");

    subject->unSubscribe(robot);

    subject->update("Hello everyone, except robot");

    delete human;
    delete robot;
    delete subject;
}