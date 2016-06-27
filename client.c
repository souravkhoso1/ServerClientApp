#include<stdio.h>
#include<errno.h>
#include<strings.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>



#define ERROR -1
#define MAX_CLIENT 10
#define MAX_DATA 1024


int main(int argc, char **argv){
	struct sockaddr_in server;
	int sock, len=sizeof(struct sockaddr_in), data_len;
	char string1[MAX_DATA], string2[2], string3[MAX_DATA];
	
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) == ERROR){
		perror("Socket:");
		exit(-1);
	}
	
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[2]));
	server.sin_addr.s_addr = inet_addr(argv[1]);
	bzero(&server.sin_zero, 8);
	
	if(connect(sock, (struct sockaddr *)&server, len) == ERROR){
		perror("Connect:");
		exit(-1);
	}
	
	{
		data_len = recv(sock, string1, MAX_DATA, 0);
		string1[data_len] = 0;
		printf("%s", string1);
		/*while(string1 != 0){
			printf("%c", string1);
			string1++;
		}*/
		scanf("%s", string2);
		send(sock, string2, strlen(string2), 0);
		data_len = recv(sock, string3, MAX_DATA, 0);
		string3[data_len] = 0;
		/*while(string3 != 0){
			printf("%c", string3);
			string3++;
		}*/
		printf("%s", string3);
	
	}
	printf("Connect once more to play this game. Thanks!!");
	close(sock);
	return 0;
}
