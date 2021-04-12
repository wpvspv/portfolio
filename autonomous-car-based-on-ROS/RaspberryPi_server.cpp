#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
 
 
#define BUF_SIZE 512
#define MAX_BUF 32
 
using namespace std;

int main(int argc, char*argv[])
{
    int server_fd, client_fd;
    char buffer[1];
    struct sockaddr_in server_addr, client_addr;
    char temp[20];
    int msg_size;
    socklen_t len;
    int speed=80;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {// 
        cout << "Server : Can't open stream socket\n";
        exit(0);
    }
    //server_Addr 을 NULL로 초기화
    memset(&server_addr, 0x00, sizeof(server_addr));
 
    //server_addr 셋팅
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(9999);
 
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <0)
    {//bind() 호출
        cout << "Server : Can't bind local address.\n";
        exit(0);
    }
 
    if (listen(server_fd, 5) < 0)
    {//소켓을 수동 대기모드로 설정
        cout << "Server : Can't listening connect.\n";
        exit(0);
    }

    //reset address
    memset(buffer, 0x00, sizeof(buffer));

    len = sizeof(client_addr);
    cout << "Server : wating connection request.\n";

    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &len);
    inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, temp, sizeof(temp));
    cout << "Server : " << temp << " client connected.\n";
    while (1)
    {
	cout << "waiting" <<endl;
	client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &len);
  	inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, temp, sizeof(temp));
	recv(client_fd,buffer,BUF_SIZE,0);
	while(1)
	{
		//front
		if(buffer[0]=='W'){
			cout << "buffer : " <<  buffer <<endl;		
			break;
		}

		//back
		if(buffer[0]=='X'){
			cout << "buffer : " <<  buffer <<endl;
			
			break;
		}

		//stop
		if(buffer[0]=='S'){
			cout << "buffer : " <<  buffer <<endl;
			break;
		}

		//front left
		if(buffer[0]=='Q'){
			cout << "buffer : " <<  buffer <<endl;
			break;
		}

		//front right
		if(buffer[0]=='E'){
			cout << "buffer : " <<  buffer <<endl;
			break;
		}

		//back left
		if(buffer[0]=='Z'){
			cout << "buffer : " <<  buffer <<endl;
			break;
		}

		//back right
		if(buffer[0]=='C'){
			cout << "buffer : " <<  buffer <<endl;
			break;
		}

		//speed up
		if(buffer[0]=='U'){
			cout << "buffer : " <<  buffer <<endl;
			if(speed>=170) speed=170;			
			else speed+=5;
			cout << "speed : " << speed <<endl; 
			break;
		}

		//speed down
		if(buffer[0]=='J'){
			cout << "buffer : " <<  buffer <<endl;
			if(speed<=80) speed=80;			
			else speed-=5;
			cout << "speed : " << speed <<endl; 
			break;
		}
	}

	//reset address
        memset(buffer, 0x00, sizeof(buffer));


    }
    close(server_fd);
    return 0;
}
