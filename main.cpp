#include <iostream> //cout
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <json.hpp>
#include <sstream>
#include <string>



using namespace std;
using json = nlohmann::json;


string str;
json clientInfo;
json accepted;
int client;
int portNum = 6666; // NOTE that the port number is same for both client and server
bool isExit = false;
const int bufsize = 1024;
char buffer[bufsize];
char* ip = "127.0.0.1";

int main() {


std::cout << "Hello, World!" << std::endl;


    struct sockaddr_in server_addr;
    server_addr.sin_port = htons(portNum);
    inet_pton(AF_INET, ip, &server_addr.sin_addr);


    client = socket(AF_INET, SOCK_STREAM, 0);

    if (client < 0)
    {
        cout << "\nError establishing socket..." << endl;
        exit(1);
    }

    if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0)
    {
        cout << "=> Connection to the server " << inet_ntoa(server_addr.sin_addr) << " with port number: "  << portNum << endl;
        char port[]= "9090";
        char carType[] = "true";
        char model[] = "F1";
        clientInfo["port"] = port;
        clientInfo["robot"] = carType;
        clientInfo["model"] = model;

        std::string s =  clientInfo.dump();
        const char *test1 = s.c_str();

        send(client,test1,strlen(test1),0);
        send(client,"\n",strlen("\n"),0);

        send(client, carType,strlen(carType),0);
        recv(client, buffer, bufsize - 1, 0);
        std::string str (buffer);
        auto j3 = json::parse(str);


        std::cout << j3.at("id") << '\n';
        do {
            sleep(5000);
        } while (isExit);

    }
    else
        cout << "could nog connect" << endl;




    cout << "\n=> Connection terminated.\nGoodbye...\n";
    close(client);
    return 0;
}