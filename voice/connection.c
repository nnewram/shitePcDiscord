#include "../common/common.c"

int remvc(char* ip, int port) {
  int clientSocket;
  struct sockaddr_in serverAddr;
  
  if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    logError("Could not create socket");
  }
  
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(port);
  
  if (inet_pton(AF_INET, ip, &serverAddr.sin_addr) <= 0) {
    logError("Invalid IP address: %s", ip);
    return ERROR;
  }
  
  if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof serverAddr) >= 0) {
    logInfo("Accepted connection to ip %s with port %d", ip, port);
  }
  else {
    logError("Could not accept connection to ip %s with port %d", ip, port);
    return ERROR;
  }
  return clientSocket;
}