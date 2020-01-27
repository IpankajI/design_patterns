
#include<iostream>
#include<unordered_map>
#include<mutex>

using namespace std;

enum EPenType{
    PT_Thin, PT_Medium, PT_Thick
};

class CPen{
public:
    virtual ~CPen()=0;
    virtual void setColor(string color)=0;
    virtual void draw()=0;
};
CPen::~CPen(){}

class CThinPen:public CPen{
private:
    static const EPenType penType=PT_Thin;
    string color;
public:
    void setColor(string color){
        this->color=color;
    }
    void draw(){
        cout<<"CThinPen: drawing with color "<<color<<endl;
    }
};


class CThickPen:public CPen{
private:
    static const EPenType penType=PT_Thick;
    string color;
public:
    void setColor(string color){
        this->color=color;
    }
    void draw(){
        cout<<"CThickPen: drawing with color "<<color<<endl;
    }
};


class CMediumPen:public CPen{
private:
    static const EPenType penType=PT_Medium;
    string color;
public:
    void setColor(string color){
        this->color=color;
    }
    void draw(){
        cout<<"CMediumPen: drawing with color "<<color<<endl;
    }
};

class CPenFactory{
private:
    static unordered_map<string, CPen*> m;
    static mutex mtxThick;
     static mutex mtxThin;
      static mutex mtxMedium;
public:
    static CPen* getThinPen(string color){
        string key=color+to_string(PT_Thin);
        lock_guard<mutex> lck(mtxThin);
        if(m.count(key)==0){
            m[key]=new CThinPen();
            m[key]->setColor(color);
        }
        return m[key];
    }
    static CPen* getThickPen(string color){
        string key=color+to_string(PT_Thick);
        lock_guard<mutex> lck(mtxThick);
        if(m.count(key)==0){
            m[key]=new CThickPen();
            m[key]->setColor(color);
        }
        return m[key];
    }
    static CPen* getMediumPen(string color){
        string key=color+to_string(PT_Medium);
        lock_guard<mutex> lck(mtxMedium);
        if(m.count(key)==0){
            m[key]=new CMediumPen();
            m[key]->setColor(color);
        }
        return m[key];
    }
};
unordered_map<string, CPen*> CPenFactory::m;
mutex CPenFactory::mtxThick;
mutex CPenFactory::mtxThin;
mutex CPenFactory::mtxMedium;

int main(){
    CPen* thickPenRed=CPenFactory::getThickPen("red");
    thickPenRed->draw();

    CPen* thickPenRed2=CPenFactory::getThickPen("red");
    thickPenRed2->draw();

    delete thickPenRed;
}