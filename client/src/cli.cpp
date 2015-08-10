#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define SOCKET_ERROR   ((int)-1)
#define INPSIZE 100

//write len bytes on the given socket
int writen(int sock, char *buf, int len) {
	int nsent = 0, ris;
	while (nsent < len) {
		ris = send(sock, buf+nsent, len-nsent, MSG_NOSIGNAL);
		if (ris == -1 && errno == EINTR)
			continue;
		else if (ris <= 0)
			return ris;
		nsent += ris;
	}
	return nsent;
}

//here I can improve by sending few packages
//read len bytes from the given socket
int readn(int sock, char *buf, int len) {
	int nread = 0, ris;
	while (nread < len) {
		ris = read(sock, buf+nread, len-nread);
		if (ris == -1 && errno == EINTR)
			continue;
		else if (ris <= 0)
			return ris;
		nread += ris;
	}
	return nread;
}

void * retrieveData(int sock, uint32_t sector) {
	uint32_t l, l_comm, ack, sect;
	int len, ack_int;
	char * ris;
	l = htonl(sizeof(uint32_t));
	l_comm = htonl(2);
	sect =  htonl(sector);
	//here I send that I want to read
	if (writen(sock, (char*)"re", 3)<=0) {
		perror("command");
		return NULL;
	}
	//I have to send the number of the sector of the data to be retrieved
	if (writen(sock, (char*)sect, 4)<=0) {
		perror("number of the sector");
		return NULL;
	}
	//here I receive the length of te record
	if (readn(sock, (char*)&l, 4)<=0) {
		perror("receiving length");
		return NULL;
	}
	len = ntohl(l);
	ris = (char*)malloc(len+1);
	/* here I receive the answer */
	if (readn(sock, ris, len)<=0) {
		perror("record not retrieved");
		free(ris);
		return NULL;
	}
/*	//this is the acknowledgment for the server
	if (writen(sock, (char*)sect, 4)<=0) {
		perror("ack client send");
		return NULL;
	}
	//this is the acknowledgment of the server
	if (readn(sock, (char*)&ack, 4)<=0) {
		perror("receiving length");
		return NULL;
	}*/
	if (ntohl(ack) != sector){
		return NULL;
	}
	return (void*) ris;
}

int serverConnectionFinish(int socket_fd) {
	if (writen(sock, (char*)"xx", 2)<=0) {
		perror("command");
		return -1;
	}
	if (readn(sock, (char*)&ack, 4)<=0) {
		perror("receiving length");
		return -1;
	}
	close(socketfd);
	return 1;
}

//here I need the socket file descriptor only
int serverConnectionInit(char *ip_addr, char *port, int *socket_main) {
	struct sockaddr_in Local, Serv;
	char *string_remote_ip_address;
	short int remote_port_number;
	int ris, socketfd;
	char inp[INPSIZE];
	string_remote_ip_address = ip_addr;
	remote_port_number = atoi(port);

	/* get a datagram socket */
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketfd == SOCKET_ERROR) {
		printf ("socket() failed, Err: %d \"%s\"\n", errno,strerror(errno));
		return 1;
	}

	/* name the socket */
	memset ( &Local, 0, sizeof(Local) );
	Local.sin_family		=	AF_INET;
	Local.sin_addr.s_addr	=	htonl(INADDR_ANY);         /* wildcard */
	Local.sin_port	=	htons(0);
	ris = bind(socketfd, (struct sockaddr*) &Local, sizeof(Local));
	if (ris == SOCKET_ERROR)  {
		printf ("bind() failed, Err: %d \"%s\"\n",errno,strerror(errno));
		return 1;
	}

	/* assign our destination address */
	memset ( &Serv, 0, sizeof(Serv) );
	Serv.sin_family	 =	AF_INET;
	Serv.sin_addr.s_addr  =	inet_addr(string_remote_ip_address);
	Serv.sin_port		 =	htons(remote_port_number);

	/* connection request */
	printf ("connect()\n");
	ris = connect(socketfd, (struct sockaddr*) &Serv, sizeof(Serv));
	if (ris == SOCKET_ERROR)  {
		printf ("connect() failed, Err: %d \"%s\"\n",errno,strerror(errno));
		//in case of error must handle it and send an error message
		return 1;
	}
	*socket_main = socketfd;
	return 0;
}

int main() {
	return 0;
}
/*	
	while (1) {
		int i=0;
		printf("inserisci comando: ");
		while ((inp[i++] = getchar()) != '\n' && i<INPSIZE-1);
		inp[i] = '\0';
		if (getresult(socketfd, inp, i) == -1) {
			if (strcmp(inp, "exit\n") != 0)
				printf("errore connessione\n");
			else 
				printf("bye bye\n");

		}
	}
*/
