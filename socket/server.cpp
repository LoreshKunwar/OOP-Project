#include<iostream>
#include<cstring>
//defines various IP protocal , and sock_stream for socket
#include<netinet/in.h>
//for socket programming
#include<sys/socket.h>
//for os APi , with file write and read
#include<unistd.h>

using namespace std;

int main()
{
    cout<<"Server on"<<endl;
    //creating socket
    int serverSocket = socket(AF_INET, SOCK_STREAM,0);
    //AF_INET specifies IPv4 protocol family
    //SOCK STREAM defines TCP(telecommunication protocal for messeging) type socket 
    //0 for default protocol 


    //specifying the address
    //sockadrr_in
    sockaddr_in serverAddress;
    serverAddress.sin_family =AF_INET;
    //specifies port number to which socket should be bound
    serverAddress.sin_port=htons(8080);
    //htons: host to network short , is a funstion that converts a port number from host byte order to network byte order
    //8080 is port number , used for the socket
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    //accepts any incomming address


    //binding the socket address
    bind(serverSocket,(struct sockaddr*)&serverAddress,sizeof(serverAddress));


    //listening to the assigned socket
    //used to accept incoming connection requests
    //5 rquest will be queued before rejecting
    listen(serverSocket,5);


    //its like accepting an incoming call from sender
    int clientSocket= accept(serverSocket,nullptr,nullptr);


    //0 represent '\0' for all the element of the array;
    char buffer[1024];

    while(true)
    {
        //clear buffer
        memset(buffer,0,sizeof(buffer));

        //recieve data from connected socket
        recv(clientSocket,buffer,sizeof(buffer),0);
        cout<<"Messege from client: "<<buffer<<endl;
    }

    close(clientSocket);
    close(serverSocket);
    
    return 0;
}