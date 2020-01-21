//A singelton class in C++ (thread safe)

#include <iostream>
using namespace std;

class Config{
    private:

    Config() = default;
    ~Config() = default;
    Config(const Config&)=delete;
    Config& operator = (const Config&)=delete;

    public: //config variables
    string serverIP;
    int serverPort;

    public: // get and object of Config type
    static Config& getInstance(){
        // Mayer Singleton (static variable with block scope)
        static Config config;
        return config; 
    }
};

void useConfig(Config& cfg){
    cout<<"Server IP: "<<cfg.serverIP<<endl;
    cout<<"Server Port: "<<cfg.serverPort<<endl;
}

int main() {
    Config& config=Config::getInstance();
    config.serverIP="27.0.0.1";
    config.serverPort=8997;

    useConfig(config);
}