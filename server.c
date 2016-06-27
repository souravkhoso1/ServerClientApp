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
#define MAX_SIZE 1024

int main(int argc, char **argv){
	struct sockaddr_in server, client;
	int sock, len=sizeof(struct sockaddr_in), newclient, data_len=1, number, pid;
	char string1[] = "Welcome!!\nEnter a number from 1 to 10: ", string2[MAX_SIZE], string3[MAX_SIZE];
	
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) == ERROR){
		perror("Socket:");
		exit(-1);
	}
	
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[1]));
	server.sin_addr.s_addr = INADDR_ANY;
	bzero(&server.sin_zero, 8);
	
	if(bind(sock, (struct sockaddr *)&server, len) == ERROR){
		perror("Bind:");
		exit(-1);
	}
	
	if(listen(sock, MAX_CLIENT) == ERROR){
		perror("Listen:");
		exit(-1);
	}
	
	while(1){
	
		if((newclient = accept(sock, (struct sockaddr *)&client, &len)) == ERROR){
			perror("Accept");
			exit(-1);
		}
		
		pid = fork();
		
		if(pid < 0){
			perror("Fork: ");
			exit(-1);
		}
		if(pid == 0){
			close(sock);
			
			printf("Client connected from %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
		
			send(newclient, string1, strlen(string1), 0);
		
		
			data_len = recv(newclient, string2, MAX_SIZE, 0);
			string2[data_len] = '\0';
			number = (rand()%10)+1;
			sprintf(string3, "You guessed %s and the right answer was %d \n", string2, number);
			send(newclient, string3, strlen(string3), 0);
			printf("Client %s:%d guessed %s and actual number was %d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port), string2, number);
			
			printf("Client %s:%d Disconnected\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
			close(newclient);
			
			exit(-1);
		} else {
			
		}
	}
	
	return 0;
}
