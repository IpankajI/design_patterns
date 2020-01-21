//A singelton class in C++ (thread safe)

#include <iostream>
#include <future>
#include <cassert>

using namespace std;

/*****************************************************************************************************/

class MayerSingleton{
    private:
    MayerSingleton() = default;
    ~MayerSingleton() = default;
    MayerSingleton(const MayerSingleton&)=delete;
    MayerSingleton& operator = (const MayerSingleton&)=delete;

    public:
    static MayerSingleton* getInstance(){
        //static variable with block scope
        static MayerSingleton* singleton=new MayerSingleton();
        return singleton; 
    }
};


/*****************************************************************************************************/

class Singleton_by_call_once{
    private:

    Singleton_by_call_once() = default;
    ~Singleton_by_call_once() = default;
    Singleton_by_call_once(const Singleton_by_call_once&)=delete;
    Singleton_by_call_once& operator = (const Singleton_by_call_once&)=delete;


    static once_flag initOnceFlag;
    static Singleton_by_call_once* singleton;

    static void initConfig(){
        singleton=new Singleton_by_call_once();
    }

    public:
    static Singleton_by_call_once* getInstance(){
        call_once(initOnceFlag, initConfig);
        return singleton;
    }

};
once_flag Singleton_by_call_once::initOnceFlag;
Singleton_by_call_once* Singleton_by_call_once::singleton=NULL;

/*****************************************************************************************************/

class SingletonByLock{
    private:

    SingletonByLock() = default;
    ~SingletonByLock() = default;
    SingletonByLock(const SingletonByLock&)=delete;
    SingletonByLock& operator = (const SingletonByLock&)=delete;

    static SingletonByLock* singleton;
    static mutex mtx;
    public:
    static SingletonByLock* getInstance(){
        lock_guard<mutex> lckGuard(mtx);
        if(singleton==NULL){
            singleton=new SingletonByLock();
        }
        return singleton;
    }

};

SingletonByLock* SingletonByLock::singleton=NULL;
mutex SingletonByLock::mtx;

/*****************************************************************************************************/

int main() {

    MayerSingleton* configMayerSingleton1=MayerSingleton::getInstance();
    MayerSingleton* configMayerSingleton2=MayerSingleton::getInstance();
    assert(configMayerSingleton1==configMayerSingleton2 && configMayerSingleton1!=NULL && configMayerSingleton2!=NULL);

    Singleton_by_call_once* configSingleton_by_call_once1=Singleton_by_call_once::getInstance();
    Singleton_by_call_once* configSingleton_by_call_once2=Singleton_by_call_once::getInstance();
    assert(configSingleton_by_call_once1==configSingleton_by_call_once2  && configSingleton_by_call_once1!=NULL && configSingleton_by_call_once2!=NULL);

    const int N=100000;
    SingletonByLock* a[N];
    for(int i=0;i<N;++i){
        a[i]=SingletonByLock::getInstance();
    }
    for(int i=1;i<N;++i){
        assert(a[i-1]==a[i] && a[i]!=NULL);
    }

}