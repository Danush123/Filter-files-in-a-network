#include<netdb.h> 
#include<netinet/in.h> 
#include<stdlib.h> 
#include<string.h> 
#include<sys/socket.h> 
#include<sys/types.h> 
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<arpa/inet.h>

int main(int argc,char** argv)
{
char buffer[200];
struct sockaddr_in s;

int sd=socket(AF_INET,SOCK_STREAM,0);

bzero(&s,sizeof(s));
s.sin_family=AF_INET;
s.sin_port=htons(8787);
s.sin_addr.s_addr=inet_addr("127.0.0.1");

connect(sd,(struct sockaddr*)&s,sizeof(s));

while(1)
{
int n=0;
char c;

bzero(buffer,sizeof(buffer));
while((c=getchar())!='\n')
buffer[n++]=c;
buffer[n]='\0';

write(sd,buffer,sizeof(buffer));
if(strcmp(buffer,"close")==0)
break;

bzero(buffer,sizeof(buffer));

read(sd,buffer,sizeof(buffer));

printf("Received: %s\n",buffer);
}
return 0;
}
