// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <string>
#include <cstring>
#include<sstream>
#include <time.h>
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

string Convert (int r) {
    ostringstream str1;
    str1 << r;
    return str1.str();
}

string randomAddr (int b,int c,int d) {
    
    string addr = "";

        addr = Convert(c) + "." + addr;
        addr = Convert(b) + "." + addr;
        addr = Convert(d) + "." + addr;

    return addr;
}




int main(int argc, char const *argv[])
{
printf("server:waiting for connections...\n");
int server_fd, new_socket, valread;
struct sockaddr_in address;
int opt = 1;
int addrlen = sizeof(address);
char buffer[1024] = {0};
char buffer1[1024] = {0};
char buffer0[1024]={0};
string buff;
string trans_id;

// Creating socket file descriptor
if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
{
perror("socket failed");
exit(EXIT_FAILURE);
}

// Forcefully attaching socket to the port 8080
if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
&opt, sizeof(opt)))
{
perror("setsockopt");
exit(EXIT_FAILURE);
}
address.sin_family = AF_INET;
address.sin_addr.s_addr = INADDR_ANY;
address.sin_port = htons( PORT );

// Forcefully attaching socket to the port 8080
if (bind(server_fd, (struct sockaddr *)&address,
sizeof(address))<0)
{
perror("bind failed");
exit(EXIT_FAILURE);
}
if (listen(server_fd, 3) < 0)
{
perror("listen");
exit(EXIT_FAILURE);
}
if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
(socklen_t*)&addrlen))<0)
{
perror("accept");
exit(EXIT_FAILURE);
}

if(valread = read( new_socket , buffer, 1024)>0){
string f = string(buffer);
int id0 = f.find(' ');
buff = f.substr(0, id0);
char *ptr1=strstr(buffer," ");
RemoveSpace(ptr1,' ');
printf("server:got connection from %s \n",ptr1);
cout<<"Received the following Transaction ID from client: "<<buff<<endl;
}
strcpy(buffer0, buff.c_str());
// OFFer
printf("Sending the following to Client:\n");
int id;
char str[10];
char str1[10];
int a=0;
int b=0;
int c=0;
int d=0;
int e=0;
time_t num=time(NULL);
srand(num);
a=(rand()%255)+1;
b=(rand()%255)+1;
c=(rand()%255)+1;
d=(rand()%255)+1;
e=(rand()%255)+1;

id=a;
sprintf(str,"%d",id);
string addr;
addr=randomAddr(b,c,d);
addr=addr+buffer0;
string msg = addr +" "+ str;
strcpy(buffer1, addr.c_str());
strcpy(buffer0, msg.c_str());
send(new_socket, buffer0,1024, 0);
printf("IP address: %s\n", buffer1);					
printf("Transaction ID: %s\n",str);

//Acknowledge
char last[1024];
char *ptr1;
if(valread = read( new_socket , buffer0, 1024)>0){
printf("Received the following request:\n");
char *ptr=strstr(buffer0," ");
const int c=strlen(ptr);
const int d=strlen(buffer0);
RemoveSpace(ptr,' ');
printf("Transaction ID: %s\n",ptr);
//ptr1= RemoveString(buffer,ptr,d,c);
}
printf("Sending following acknowledgment:\n");
int lastid=e;
sprintf(str1,"%d",lastid);
string msg1 = addr +" "+ str1;
strcpy(buffer0, msg1.c_str());
send(new_socket , buffer0 , 1024, 0 );
printf("IP address: %s\n",buffer1);
printf("Transaction ID: %s\n",str1);
close(new_socket);
return 0;
}
