#include<iostream>

using namespace std;

class CLoan{
public:
    virtual ~CLoan()=0;
    virtual void calculateEMI()=0;
};

CLoan::~CLoan(){}

class CBussinessLoanHDFC:public CLoan{
    void calculateEMI(){
        cout<<"HDFC: calculating EMI for bussiness loan..."<<endl;
    }
    ~CBussinessLoanHDFC(){
        cout<<"Destructor: CBussinessLoanHDFC"<<endl;
    }
};

class CHomeLoanHDFC:public CLoan{
    void calculateEMI(){
        cout<<"HDFC: calculating EMI for home loan..."<<endl;
    }
    ~CHomeLoanHDFC(){
        cout<<"Destructor: CHomeLoanHDFC"<<endl;
    }
};

class CEducationLoanHDFC:public CLoan{
    void calculateEMI(){
        cout<<"HDFC: calculating EMI for education loan..."<<endl;
    }
    ~CEducationLoanHDFC(){
        cout<<"Destructor: CEducationLoanHDFC"<<endl;
    }
};


class CBussinessLoanICICI:public CLoan{
    void calculateEMI(){
        cout<<"ICICI: calculating EMI for bussiness loan..."<<endl;
    }
    ~CBussinessLoanICICI(){
        cout<<"Destructor: CBussinessLoanICICI"<<endl;
    }
};

class CHomeLoanICICI:public CLoan{
    void calculateEMI(){
        cout<<"ICICI: calculating EMI for home loan..."<<endl;
    }
    ~CHomeLoanICICI(){
        cout<<"Destructor: CHomeLoanICICI"<<endl;
    }
};

class CEducationLoanICICI:public CLoan{
    void calculateEMI(){
        cout<<"ICICI: calculating EMI for education loan..."<<endl;
    }
    ~CEducationLoanICICI(){
        cout<<"Destructor: CEducationLoanICICI"<<endl;
    }
};



class CBank{
public:
    virtual CLoan* getBussinessLoan()=0;
    virtual CLoan* getHomeLoan()=0;
    virtual CLoan* getEducationLoan()=0;
    virtual ~CBank()=0;
};

CBank::~CBank(){}

class CHDFCBank:public CBank{
    CLoan* getBussinessLoan(){
        return new CBussinessLoanHDFC();
    }
    CLoan* getHomeLoan(){
        return new CHomeLoanHDFC();
    }
    CLoan* getEducationLoan(){
        return new CEducationLoanHDFC();
    }
    ~CHDFCBank(){
        cout<<"Destructor: CHDFCBank"<<endl;
    }
};

class CICICIBank:public CBank{
    CLoan* getBussinessLoan(){
        return new CBussinessLoanICICI();
    }
    CLoan* getHomeLoan(){
        return new CHomeLoanICICI();
    }
    CLoan* getEducationLoan(){
        return new CEducationLoanICICI();
    }
    ~CICICIBank(){
        cout<<"Destructor: CICICIBank"<<endl;
    }
};

class CClient{
private:
    CBank* bank;
    CLoan* bussinessLoan;
    CLoan* homeLoan;
    CLoan* educationLoan;
public:
    CClient(CBank* bank):bank(bank){
        if(bank==NULL){
            cout<<"Client can't initialize without bank"<<endl;
            throw 0;
        }
        bussinessLoan=NULL;
        homeLoan=NULL;
        educationLoan=NULL;       
    }
    void calculateEMIHomeLoan(){
        if(!homeLoan){
            homeLoan=bank->getHomeLoan();
        }
        homeLoan->calculateEMI();
    }

    void calculateEMIBussinessLoan(){
        if(!bussinessLoan){
            bussinessLoan=bank->getBussinessLoan();
        }
        bussinessLoan->calculateEMI();
    }

    void calculateEMIEducationLoan(){
        if(!educationLoan){
            educationLoan=bank->getEducationLoan();
        }
        educationLoan->calculateEMI();
    }

    ~CClient(){
        if(bussinessLoan){
            delete bussinessLoan;
            bussinessLoan=NULL;
        }
        if(homeLoan){
            delete homeLoan;
            homeLoan=NULL;
        }
        if(educationLoan){
            delete educationLoan;
            educationLoan=NULL;
        }
        cout<<"Destructor: CClient"<<endl;
    }
};

int main(){
    CBank* bankHDFC=new CHDFCBank();
    CClient* hdfcClient=new CClient(bankHDFC);
    hdfcClient->calculateEMIHomeLoan();
    hdfcClient->calculateEMIBussinessLoan();
    hdfcClient->calculateEMIEducationLoan();
    delete hdfcClient;
    delete bankHDFC;

    CBank* bankICICI=new CICICIBank();
    CClient* iciciClient=new CClient(bankICICI);
    iciciClient->calculateEMIHomeLoan();
    iciciClient->calculateEMIBussinessLoan();
    iciciClient->calculateEMIEducationLoan();
    
    delete iciciClient;
    delete bankICICI;
}

