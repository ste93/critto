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

int retrieveData(int sock, char *inp, int len) {
	uint32_t l;
	char *ris;
	l = htonl(len);
	//I have to send the length of the data
	if (writen(sock, (char*)&l, 4)<=0) {
		perror("command not sent");
		return -1;
	}
	//here I send the number of the record to be retrieved, it is always a 32/64 bit
	if (writen(sock, (char*)&l, 4)<=0) {
		perror("command not sent");
		return -1;
	}
	//I have to manage the ack
	//wait for the record
	while (1) {
		//here I receive the record, it is always 8 + 512 byte (number of record + data)
		if (readn(sock, (char*)&l, 4)<=0) {
			perror("ricezione len risp");
			return -1;
		}
		len = ntohl(l);
		if (len == 0) /* EOF */
			break;
		ris = (char*)malloc(len+1);
		/* here I receive the answer */
		if (readn(sock, ris, len)<=0) {
			perror("ricezione risp");
			free(ris);
			return -1;
		}
		ris[len] = '\t';
		write(1, ris, len+1);
	}
	printf("\n");
	
	return 1;
}

int retrieveDataInit(char *ip_addr, char *port, int *socket_main) {
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
	//here I need the socket file descriptor only
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
			close(socketfd);
			return 1;
		}
	}
*/
