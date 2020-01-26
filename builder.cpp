#include<iostream>
#include<unordered_map>
#include<mutex>

using namespace std;

class CHttpRequest{
    string url;
    string method;
    unordered_map<string, string> params;
    
public:

    class CHttpRequestBuilder{
        string url;
        string method;
        unordered_map<string, string> params;
    public:
        CHttpRequestBuilder* setUrl(string url){
            this->url=url;
            return this;
        }
        CHttpRequestBuilder* setMethod(string method){
            this->method=method;
            return this;
        }
        CHttpRequestBuilder* addParam(string key, string value){
            this->params[key]=value;
            return this;
        }
        CHttpRequest* build(CHttpRequest* httpRequest){
            httpRequest->url=url;
            httpRequest->method=method;
            httpRequest->params=params;
            return httpRequest;
        }
    };

    
    static mutex mtx;
    CHttpRequestBuilder* HttpRequestBuilder(){
        lock_guard<mutex> lck(mtx);
        if(httpRequestBuilder==NULL){
            httpRequestBuilder= new CHttpRequestBuilder();
        }
        return httpRequestBuilder;
    }

    bool Do(){  
        
        cout<<"url: "<<url<<endl;
        cout<<"method: "<<method<<endl;

        for(auto it=params.begin(); it!=params.end(); ++it){
            cout<<it->first<<": "<<it->second<<endl;
        }
        cout<<"Sending HttpRequest..."<<endl;
        return true;
    }

    CHttpRequest(){
        httpRequestBuilder=NULL;
    }
    ~CHttpRequest(){
        if(httpRequestBuilder){
            delete httpRequestBuilder;
            httpRequestBuilder=NULL;
        }
    }
private:
    CHttpRequestBuilder* httpRequestBuilder;
};

mutex CHttpRequest::mtx;

int main(){

    CHttpRequest* httpRequest=new CHttpRequest();
    httpRequest->HttpRequestBuilder()
        ->setUrl("example.com")
        ->setMethod("get")
        ->addParam("page", "1")
        ->addParam("user", "pankaj kumar")
        ->build(httpRequest)
        ->Do();

    delete httpRequest;
}