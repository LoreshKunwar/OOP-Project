#include<iostream>
#include<cstring>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
using namespace std;

int main()
{
    //creating socket
    int clientSocket=socket(AF_INET,SOCK_STREAM,0);

    //specifying address
    sockaddr_in serverAddress;
    serverAddress.sin_family=AF_INET;
    serverAddress.sin_port=htons(8080);
    serverAddress.sin_addr.s_addr=INADDR_ANY;

    //sending connection request
    //connect is for ready to send
    connect(clientSocket,(struct sockaddr*)&serverAddress,sizeof(serverAddress));

    //sending data
    char data[1024] ;
    while(true)
    {
        cout<<"Enter Messege: ";
        cin.getline(data,sizeof(data));

        ssize_t bytesSent = send(clientSocket,data,strlen(data),0);
        if (bytesSent < 0) {
            cerr << "Send failed" << endl;
            break;
        } 
        else if (bytesSent == 0) {
            cerr << "Connection closed by server" << endl;
            break;
        }
    }
    close(clientSocket);

    return 0;
}
