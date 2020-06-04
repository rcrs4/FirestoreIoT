#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
class FirestoreIoT{
private:
	char* googleHost = "firestore.googleapis.com";
public:
	int requestToGoogle(char*);
	char * makeGetRequest(char*);
	char * makePostRequest(char*, char*);
	void addNewDocument(char*, char*);
};