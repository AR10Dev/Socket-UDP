// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT	 8080 
#define MAXLINE 1024 

// Driver code 
int main() { 
	int sockfd; 
	char buffer[MAXLINE]; 
	char *hello = "Benvenuto, Le temperature dei sensori sono:\n- Sensore 1: 20°C,\n- Sensore 2: 18°C,\n- Sensore 3: 17°C\n"; 
	struct sockaddr_in servaddr, cliaddr; 
	
	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("\033[1;31m[-] Creazione socket fallita\033[0m"); 
		exit(EXIT_FAILURE); 
	} 

    printf("\033[0;32m[+] Socket creata con successo\033[0m\n");
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(PORT); 
	
	// Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
			sizeof(servaddr)) < 0 ) 
	{ 
		perror("\033[1;31m[-] Bind fallito\033[0m"); 
		exit(EXIT_FAILURE); 
	} 
	printf("\033[0;32m[+] Bind effettuato con successo\033[0m\n");
	int len, n; 

	for (;;)
	{
		len = sizeof(cliaddr); //len is value/resuslt 
		n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len); 
		buffer[n] = '\0'; 
		printf("\033[0;32m\u2705 Connessione con il client\n\033[0m"); 
		sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len); 
		printf("\033[0;32m\u2705 Messagio inviato.\n\033[0m"); 
	}

	return 0; 
} 
