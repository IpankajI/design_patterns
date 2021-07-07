#include<bits/stdc++.h>

using namespace std;


class CHTTPRequest{

    public:
    class CHTTPRequestBuilder{
        public:
            string method;
            string url;
            map<string, string> params;
            CHTTPRequestBuilder setURL(string url){
                this->url=url;
                return *this;
            }
            CHTTPRequestBuilder setMethod(string method){
                this->method=method;
                return *this;
            }
            CHTTPRequestBuilder setParam(string key, string value){
                this->params[key]=value;
                return *this;
            }

            CHTTPRequest build(){
                return CHTTPRequest(this);
            }

    };

    private:
    string method;
    string url;
    map<string, string> params;

    public:
    CHTTPRequest(CHTTPRequestBuilder* builder){
        url=builder->url;
        method=builder->method;
        params=builder->params;
    }

    static CHTTPRequestBuilder httpRequestBuilder(){
        return CHTTPRequestBuilder();
    }

    void Do(){
        cout<<"making request with method: "<<method<<", url: "<<url<<endl;
        cout<<"params-"<<endl;
        for(auto e: params){
            cout<<e.first<<" "<<e.second<<endl;
        }
    }

};


int main(){
    
    CHTTPRequest req=CHTTPRequest::httpRequestBuilder().setMethod("post").setURL("example.com").setParam("key", "value").build();
    req.Do();

}
