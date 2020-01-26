#include<iostream>

using namespace std;

class CVisitor;

class CRouter{
public:
    virtual void accept(CVisitor* visitor)=0;
    virtual ~CRouter()=0;
};
CRouter::~CRouter(){}

class CDLinkRouter:public CRouter{
public:
    void accept(CVisitor* visitor);
};

class CTPLinkRouter:public CRouter{
public:
    void accept(CVisitor* visitor);
};

class CVisitor{
public:
    virtual ~CVisitor()=0;
    virtual void visite(CDLinkRouter* router)=0;
    virtual void visite(CTPLinkRouter* router)=0;
};
CVisitor::~CVisitor(){}

class CMacConfigurator:public CVisitor{
public:
    void visite(CDLinkRouter* router){
        cout<<"CMacConfigurator: configuring for DLinkRouter..."<<endl;
    }
    void visite(CTPLinkRouter* router){
        cout<<"CMacConfigurator: configuring for TPLinkRouter..."<<endl;
    }
};

class CWindowsConfigurator:public CVisitor{
public:
    void visite(CDLinkRouter* router){
        cout<<"CWindowsConfigurator: configuring for DLinkRouter..."<<endl;
    }
    void visite(CTPLinkRouter* router){
        cout<<"CWindowsConfigurator: configuring for TPLinkRouter..."<<endl;
    }
};

void CDLinkRouter::accept(CVisitor* visitor){
    visitor->visite(this);
}

void CTPLinkRouter::accept(CVisitor* visitor){
    visitor->visite(this);
}

int main(){
    CVisitor* visitorWindows=new CWindowsConfigurator();
    CRouter* routerDLink=new CDLinkRouter();
    routerDLink->accept(visitorWindows);

    delete visitorWindows;
    delete routerDLink;

    CVisitor* visitorMac=new CMacConfigurator();
    CRouter* routerTPLink=new CTPLinkRouter();
    routerTPLink->accept(visitorMac);

    delete visitorMac;
    delete routerTPLink;
}