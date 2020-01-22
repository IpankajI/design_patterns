#include<thread>
#include<iostream>
#include <mutex>

using namespace std;

class Thread{
    private:
    
    public:
    thread::id threadId;
    int threadPriority;
    virtual void run();
    void start();
};

void Thread::start(){
    thread t=thread(run, this);
    t.detach();
}

void Thread::run(){

}

mutex mtx;
class Client:public Thread{
    public:
    void run(){
        threadId=this_thread::get_id();
        this_thread::sleep_for(chrono::seconds(1));
        lock_guard<mutex> lckGuard(mtx);
        cout<<"thread with id-"<<threadId<<" is started"<<endl;   
    }
};

int main(){
    const int N=100;
    Client c[N];
    for(int i=0;i<N;++i){
        c[i]=Client();
        c[i].start();
    }

    this_thread::sleep_for(chrono::seconds(5));
}