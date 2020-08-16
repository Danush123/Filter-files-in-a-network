#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/time.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<dirent.h> 
#include<sys/stat.h>
#include<time.h>


int sd,a,year,minutes,n,i,arr[30],max,val=0;
socklen_t l;
struct sockaddr_in s,c;
char buffer[1000];
struct dirent *de;
struct tm *foo;
struct stat attrib;
fd_set f;

int flag,flag2;
int yi1,yi2,mi1,mi2,di1,di2,hi1,hi2,mini1,mini2,mm1,mm2;
char yc1[50],yc2[50],mc1[50],mc2[50],dc1[50],dc2[50],hc1[50],hc2[50],minc1[50],minc2[50];

void tokenise();

int compare(int,int,int,int);
int crtdate(int,int,int,int,int);

int main()
{
for(i=0;i<30;i++)
arr[i]=0;

sd=socket(AF_INET,SOCK_STREAM,0);
s.sin_family=AF_INET;
s.sin_port=htons(8004);
s.sin_addr.s_addr=htonl(INADDR_ANY);
bind(sd,(struct sockaddr* )&s,sizeof(s));
listen(sd,10);

while(1)
{
FD_ZERO(&f);
FD_SET(sd,&f);
max=sd;
for(i=0;i<30;i++)
{
if(arr[i]>0)
FD_SET(arr[i],&f);
if(arr[i]>max)
max=arr[i];
}

a=select(max+1,&f,NULL,NULL,NULL);
l=sizeof(s);

if(FD_ISSET(sd,&f))
{
n=accept(sd,(struct sockaddr*)&s,&l);
for(i=0;i<30;i++)
{
if(arr[i]==0)
{
arr[i]=n;
break;
}
}
}

for(i=0;i<30;i++)
{
if(FD_ISSET(arr[i],&f))
{
bzero(buffer,sizeof(buffer));
if((val=read(arr[i],buffer,sizeof(buffer)))==0)
{
printf("Host terminated\n");
arr[i]=0;
}
else
{
printf("Received: %s\n",buffer);

tokenise();

bzero(buffer,sizeof(buffer));
if(flag2==0)
{
	printf("Not a date!");
	strcat(buffer,"Invalid date");
	strcat(buffer,"\n");
}
else
{
DIR *dr = opendir("."); 
	if (dr == NULL)
        { 
		printf("Could not open current directory" ); 
		return 0; 
	} 

	while ((de = readdir(dr)) != NULL) 
	{		printf("%s\n", de->d_name);
            stat(de->d_name, &attrib);
    foo = localtime(&(attrib.st_mtime));
    year=foo->tm_year-100+2000;
    minutes=(foo->tm_hour*60)+foo->tm_min;
    printf("Y, M, D, minutes = %d %d %d %d",year,foo->tm_mon,foo->tm_mday,minutes);
    if((strcmp(de->d_name,"..")==0)||(strcmp(de->d_name,".")==0))
    continue;
    if(compare(year,foo->tm_mon,foo->tm_mday,minutes)==1)
	{
        printf("Success\n");
        strcat(buffer,de->d_name);
    	strcat(buffer,"\n");
	}
    }
    closedir(dr);
}
printf("Buffer = %s",buffer);
write(arr[i],buffer,sizeof(buffer));
}
}
}

}

return 0;
}


int crtdate(int yy,int mm,int dd,int h,int min)
{
	if(h>=0 && h<=23)
	{
		if(min>=0 && min<=59)
		{
			if(yy>=1900 && yy<=9999)
			{
				if(mm>=1 && mm<=12)
				{
				    if((dd>=1 && dd<=31) && (mm==1 || mm==3 || mm==5 || mm==7 || mm==8 || mm==10 || mm==12))
				        return 1;
				    else if((dd>=1 && dd<=30) && (mm==4 || mm==6 || mm==9 || mm==11))
				        return 1;
				    else if((dd>=1 && dd<=28) && (mm==2))
				        return 1;
				    else if(dd==29 && mm==2 && (yy%400==0 ||(yy%4==0 && yy%100!=0)))
				        return 1;
				    else
				        return 0;
				}
				else
				    return 0;
			}
			else
				return 0;
		}
		else
			return 0;
	}
	else
		return 0;
}

int compare(int y,int m,int d,int min)
{
    int xe=(y*10000000)+(m*100000)+(d*1000)+min;
    if((xe>=mm1)&&(xe<=mm2))
    return 1;
    return 0;
}

void tokenise()
{
    int k=0,i=0;
    while(buffer[k]!=':')
    {
        yc1[k]=buffer[k];
        k++;
    }
    yc1[k]='\0';
    k++;

    while(buffer[k]!=':')
    {
        mc1[i++]=buffer[k];
        k++;
    }
    mc1[i]='\0';
    k++;
    i=0;

    while(buffer[k]!=':')
    {
        dc1[i++]=buffer[k];
        k++;
    }
    dc1[i]='\0';
    k++;i=0;

    while(buffer[k]!=':')
    {
        hc1[i++]=buffer[k];
        k++;
    }
    hc1[i]='\0';
    k++;i=0;

    while(buffer[k]!=' ')
    {
        minc1[i++]=buffer[k];
        k++;
    }
    minc1[i]='\0';
    k++;i=0;

while(buffer[k]!=':')
    {
        yc2[i++]=buffer[k];
        k++;
    }
    yc2[i]='\0';
    k++;i=0;

    while(buffer[k]!=':')
    {
        mc2[i++]=buffer[k];
        k++;
    }
    mc2[i]='\0';
    k++;i=0;

    while(buffer[k]!=':')
    {
        dc2[i++]=buffer[k];
        k++;
    }
    dc2[i]='\0';
    k++;i=0;

    while(buffer[k]!=':')
    {
        hc2[i++]=buffer[k];
        k++;
    }
    hc2[i]='\0';
    k++;i=0;

    while(buffer[k]!='\0')
    {
        minc2[i++]=buffer[k];
        k++;
    }
    minc2[i]='\0';
    k++;i=0;

    printf("%s:%s:%s:%s:%s %s:%s:%s:%s:%s\n",yc1,mc1,dc1,hc1,minc1,yc2,mc2,dc2,hc2,minc2);

    yi1=atoi(yc1);
    yi2=atoi(yc2);
    mi1=atoi(mc1);
    mi2=atoi(mc2);
    di1=atoi(dc1);
    di2=atoi(dc2);
    hi1=atoi(hc1);
    hi2=atoi(hc2);
    mini1=atoi(minc1);
    mini2=atoi(minc2);
    mm1=(yi1*10000000)+(mi1*100000)+(di1*1000)+(hi1*60)+mini1;
    mm2=(yi2*10000000)+(mi2*100000)+(di2*1000)+(hi2*60)+mini2;
    
	if(crtdate(yi1,mi1,di1,hi1,mini1)&&crtdate(yi2,mi2,di2,hi2,mini2))
	{
		flag2=1;
	}
	else
		flag2=0;
    printf("%d %d %d %d %d %d %d %d %d %d\n",yi1,yi2,mi1,mi2,di1,di2,hi1,hi2,mini1,mini2);

}
