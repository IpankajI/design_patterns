#include<iostream>

using namespace std;

class CShape{
public:
    virtual ~CShape()=0;
    virtual void draw()=0;
};
CShape::~CShape(){}

class CCircle:public CShape{
public:
    void draw(){
        cout<<"drawing circle..."<<endl;
    }
    ~CCircle(){
        // cout<<"CCircle: delete"<<endl;
    }
};

class CShapeDecorator:public CShape{
public:
    CShape* shape;
    CShapeDecorator(CShape* shape):shape(shape){

    }
    ~CShapeDecorator(){
        // cout<<"CShapeDecorator: delete"<<endl;
        delete shape;
        shape=0;
    }
};

class CShapeDecoratorRed:public CShapeDecorator{
public:
    CShapeDecoratorRed(CShape* shape):CShapeDecorator(shape){
        cout<<"coloring shape with red..."<<endl;
    }
    void draw(){
        shape->draw();
    }
    ~CShapeDecoratorRed(){
        // cout<<"CShapeDecoratorRed: delete"<<endl;
    }
};

class CShapeDecoratorBlur:public CShapeDecorator{
public:
    CShapeDecoratorBlur(CShape* shape):CShapeDecorator(shape){
        cout<<"bluring shape..."<<endl;
    }
    void draw(){
        shape->draw();
    }
    ~CShapeDecoratorBlur(){
        // cout<<"CShapeDecoratorBlur: delete"<<endl;
    }
};

int main(){
    CShape* circle=new CCircle();

    circle->draw();
    delete circle;

    CShape* circleRed=new CShapeDecoratorBlur(new CShapeDecoratorRed(new CCircle()));
    circleRed->draw();
    delete circleRed;
}