#include<iostream>

using namespace std;

class CSortingStrategy{
public:
    virtual ~CSortingStrategy()=0;
    virtual void sort()=0;
};
CSortingStrategy::~CSortingStrategy(){}


class CQuickSort:public CSortingStrategy{
public:
    void sort(){
        cout<<"CQuickSort: sorting..."<<endl;
    }
};


class CHeapSort:public CSortingStrategy{
public:
    void sort(){
        cout<<"CHeapSort: sorting..."<<endl;
    }
};

class CMergeSort:public CSortingStrategy{
public:
    void sort(){
        cout<<"CMergeSort: sorting..."<<endl;
    }
};

class CMySort{
private:
    CSortingStrategy* sortingStrategy;
public:
    void setStrategy(CSortingStrategy* strategy){
        if(sortingStrategy){
            delete sortingStrategy;
        }
        sortingStrategy=strategy;
    }
    void sort(){
        sortingStrategy->sort();
    }
    CMySort(){
        sortingStrategy=NULL;
    }
    ~CMySort(){
        if(sortingStrategy){
            delete sortingStrategy;
        }
    }
};

int main(){
    CMySort* mySort=new CMySort();

    mySort->setStrategy(new CHeapSort());
    mySort->sort();

    mySort->setStrategy(new CMergeSort());
    mySort->sort();

    delete mySort;
}