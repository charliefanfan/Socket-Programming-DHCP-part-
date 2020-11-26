// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include<string>
#include<cstring>
#include <iostream>
#include <algorithm>
#include <memory.h>
#include<functional>
#define PORT 4334

using namespace std;

void RemoveSpace(char *s, char m)
{ int w=0, r=0;
while(s[r]){
if(s[r]!=m)
{s[w++]=s[r];}
r++;
}
s[w]=0;
}

int TraID(){
int a;
srand(time(NULL));
a=(rand()%255)+1;
return a;
}
char local_adrress;

int main(int argc, char const *argv[])
{
int sock = 0, valread,valread1;
struct sockaddr_in serv_addr;
char buffer[1024] = {0};
char buffer2[1024]= {0};
char buffer3[1024]={0};
if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
{
printf("\n Socket creation error \n");
return -1;
}


serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(PORT);

// Convert IPv4 and IPv6 addresses from text to binary form
if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
{
printf("\nInvalid address/ Address not supported \n");
return -1;
}

if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
{
printf("\nConnection Failed \n");
return -1;
}
char *some_addr;
inet_aton(  *argv ,&serv_addr.sin_addr);
some_addr=inet_ntoa(serv_addr.sin_addr);


printf("client: connecting to %s \n",some_addr);
//discover
int reminder= 334%255;
sprintf(buffer,"%d",reminder);
strcat(buffer," ");
strcat(buffer,some_addr);
printf("Sending the following Transaction ID to server: %d\n",reminder);
send(sock,buffer,strlen(buffer),0);
sleep(1);


string IP;
string ID2;
string sub;


 if (valread = read(sock, buffer, 1024) > 0) {
 	printf("Received the following:\n");
    	string msg = string(buffer);
    	int idx = msg.find(' ');
    	IP = msg.substr(0, idx);
    	char *ID2=strstr(buffer," ");
    	RemoveSpace(ID2,' ');
	cout<<"IP address: "<<IP<<endl;
	printf("Transaction ID: %s\n",ID2);
	//cout<<"Transaction ID: "<<ID2<<endl;

}
int id;
id=TraID();
strcpy(buffer3,IP.c_str());
sprintf(buffer2,"%d",id);
strcat(buffer3," ");
strcat(buffer3,buffer2);
printf("Formally requesting the following server:\n");
send(sock,buffer3,1024,0);
cout<<"IP address: "<<IP<<endl;
printf("Transaction ID: %d\n", id);

if (valread1 = read(sock, buffer, 1024) > 0) {
	string msg2 = string(buffer);
    	int idx1 = msg2.find(' ');
    	string IP2 = msg2.substr(0, idx1);
	char *ptr=strstr(buffer," ");
 	cout<<"Officially connected tto IP Address: "<<IP2<<endl;
 	RemoveSpace(ptr,' ');
 	printf("client: received'%s'\n",ptr);
 	}

close(sock);

return 0;
}
