#include "FirestoreIoT.h"
#define PORT 443

int FirestoreIoT::requestToGoogle(char request[1024]){
    int sock = 0; 
    struct sockaddr_in serv_addr; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){ 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "172.217.29.42", &serv_addr.sin_addr)<=0){ 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){ 
        printf("\nConnection Failed \n"); 
        return -1; 
    }
    send(sock, request, strlen(request), 0);
    char response[2048];
    read(sock, response, 2048);
    printf("%s\n", response);
}

char* FirestoreIoT::makeGetRequest(char* path){
  char* method = "GET ";
  char* protocol = " HTTP/1.1\n";
  char* hostHeader = "Host: ";
  char* end = "\n\n";
  static char request[1024];
  char* parts[] = {method, path, protocol, hostHeader, googleHost, end};
  for(int i = 0; i < 6; i++){
    strcat(request, parts[i]);
  }
  return request;
  
}

char* FirestoreIoT::makePostRequest(char* path, char* requestBody){
  char* method = "POST ";
  char* protocol = " HTTP/1.1";
  char* hostHeader = "\nHost: ";
  char* end = "\n\n";
  char* contentLength = "\nContent-Length: ";
  static char request[1024];
  int length = strlen(requestBody);
  printf("%d\n", length);
  char lengthStr[5];
  itoa(length, lengthStr, 10);
  char* parts[] = {method, path, protocol, hostHeader, googleHost, contentLength, lengthStr, end, requestBody};
  for(int i = 0; i < 9; i++){
    strcat(request, parts[i]);
  }
  printf("Request: %d\n%s\n", sizeof(request), request);
  return request;
  
}

void FirestoreIoT::addNewDocument(char* path/*to new document*/, char* fields){
  requestToGoogle(makePostRequest(path, "{\"fields\":{\"teste\":{\"integerValue\":\"0\"}}}"));
}