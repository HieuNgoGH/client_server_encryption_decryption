#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

void setupAddressStruct(struct sockaddr_in* address, int portNumber){

  // clear out the address struct
  memset((char*) address, '\0', sizeof(*address));

  // address network ipv4 capable
  address->sin_family = AF_INET;
  //store the port number
  address->sin_port = htons(portNumber);
  //allow a client at any address to connect to this server
  address->sin_addr.s_addr = INADDR_ANY;
}

int main(int argc, char *argv[]){

  int connectionSocket, charsRead, charsWritten;
  char plain_buffer[200000];
  int plain_int_buffer[200000];
  char key_buffer[200000];
  int dec_int_buffer[200000];
  char dec_buffer[200000];
  char header_buffer[1024];
  int int_header_buffer[1024];
  int header_int;
  char len_str[10] = "";

  struct sockaddr_in serverAddress, clientAddress;
  socklen_t sizeOfClientInfo = sizeof(clientAddress);

  if (argc < 2) {
    fprintf(stderr, "Not enough arguments");
  }

  //set up the address struct for the server socket
  setupAddressStruct(&serverAddress, atoi(argv[1]));

  // create a socket that will listen for connections
  int listenSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (listenSocket < 0){
    fprintf(stderr, "Error opening socket");
  }

  // associate the socket to the port
  if (bind(listenSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0){
    fprintf(stderr, "Error on decipher server binding");
  }

  // start listening for connections. Allow up to 5 connections to queue up
  listen(listenSocket, 5);

  // accept a connection, blocking if one is not available until one connects
  while(1){
    connectionSocket = accept(listenSocket, (struct sockaddr *)&clientAddress, &sizeOfClientInfo);
    if(connectionSocket < 0){
      fprintf(stderr, "Error on accept");
    }

    // fork a new process to handle the rest of client requests
    int childStatus;
    pid_t spawnChild = fork();
    switch(spawnChild){
      case -1:
        fprintf(stderr, "Fork error");
        break;

      case 0:
        // get message from the client and display it
        memset(plain_buffer, '\0', 200000);
        memset(key_buffer, '\0', 200000);
        memset(plain_int_buffer, '\0', 200000);
        memset(dec_buffer, '\0', 200000);
        memset(dec_int_buffer, '\0', 200000);
        memset(header_buffer, '\0', 1024);
        memset(int_header_buffer, '\0', 1024);

        charsRead = recv(connectionSocket, plain_buffer, 200000, 0);

        int i = 0;
        int x = 0;
        while (x == 1){
          char header_str = plain_buffer[i];
          switch(header_str){
            case '1':
              strcat(len_str, "1");
              i += 1;
              break;
            case '2':
              strcat(len_str, "2");
              i += 1;
              break;
            case '3':
              strcat(len_str, "3");
              i += 1;
              break;
            case '4':
              strcat(len_str, "4");
              i += 1;
              break;
            case '5':
              strcat(len_str, "5");
              i += 1;
              break;
            case '6':
              strcat(len_str, "6");
              i += 1;
              break;
            case '7':
              strcat(len_str, "7");
              i += 1;
              break;
            case '8':
              strcat(len_str, "8");
              i += 1;
              break;
            case '9':
              strcat(len_str, "9");
              i += 1;
              break;
            case '0':
              strcat(len_str, "0");
              i += 1;
              break;
            default:
              x = 0;
              break;
          }
        }

        int length = atoi(len_str);

        // read the client's message from the socket
        while (charsRead < 0){

        charsRead = recv(connectionSocket, plain_buffer, 200000, 0);
          if (charsRead < 0){
            fprintf(stderr, "Error reading from socket");
          }
        }

        int plain_int_len = 0;
        int j = 0;
        memset(dec_buffer, '\0', 200000);
        for (int i = 0; i < strlen(plain_buffer); i++){
          char en_c = plain_buffer[i];
          switch(en_c){
            case 'A':
              plain_int_buffer[j] = 0;
              plain_int_len += 1;
              j += 1;
              break;
            case 'B':
              plain_int_buffer[j] = 1;
              plain_int_len += 1;
              j += 1;
              break;
            case 'C':
              plain_int_buffer[j] = 2;
              plain_int_len += 1;
              j += 1;
              break;
            case 'D':
              plain_int_buffer[j] = 3;
              plain_int_len += 1;
              j += 1;
              break;
            case 'E':
              plain_int_buffer[j] = 4;
              plain_int_len += 1;
              j += 1;
              break;
            case 'F':
              plain_int_buffer[j] = 5;
              plain_int_len += 1;
              j += 1;
              break;
            case 'G':
              plain_int_buffer[j] = 6;
              plain_int_len += 1;
              j += 1;
              break;
            case 'H':
              plain_int_buffer[j] = 7;
              plain_int_len += 1;
              j += 1;
              break;
            case 'I':
              plain_int_buffer[j] = 8;
              plain_int_len += 1;
              j += 1;
              break;
            case 'J':
              plain_int_buffer[j] = 9;
              plain_int_len += 1;
              j += 1;
              break;
            case 'K':
              plain_int_buffer[j] = 10;
              plain_int_len += 1;
              j += 1;
              break;
            case 'L':
              plain_int_buffer[j] = 11;
              plain_int_len += 1;
              j += 1;
              break;
            case 'M':
              plain_int_buffer[j] = 12;
              plain_int_len += 1;
              j += 1;
              break;
            case 'N':
              plain_int_buffer[j] = 13;
              plain_int_len += 1;
              j += 1;
              break;
            case 'O':
              plain_int_buffer[j] = 14;
              plain_int_len += 1;
              j += 1;
              break;
            case 'P':
              plain_int_buffer[j] = 15;
              plain_int_len += 1;
              j += 1;
              break;
            case 'Q':
              plain_int_buffer[j] = 16;
              plain_int_len += 1;
              j += 1;
              break;
            case 'R':
              plain_int_buffer[j] = 17;
              plain_int_len += 1;
              j += 1;
              break;
            case 'S':
              plain_int_buffer[j] = 18;
              plain_int_len += 1;
              j += 1;
              break;
            case 'T':
              plain_int_buffer[j] = 19;
              plain_int_len += 1;
              j += 1;
              break;
            case 'U':
              plain_int_buffer[j] = 20;
              plain_int_len += 1;
              j += 1;
              break;
            case 'V':
              plain_int_buffer[j] = 21;
              plain_int_len += 1;
              j += 1;
              break;
            case 'W':
              plain_int_buffer[j] = 22;
              plain_int_len += 1;
              j += 1;
              break;
            case 'X':
              plain_int_buffer[j] = 23;
              plain_int_len += 1;
              j += 1;
              break;
            case 'Y':
              plain_int_buffer[j] = 24;
              plain_int_len += 1;
              j += 1;
              break;
            case 'Z':
              plain_int_buffer[j] = 25;
              plain_int_len += 1;
              j += 1;
              break;
            case ' ':
              plain_int_buffer[j] = 26;
              plain_int_len += 1;
              j += 1;
              break;
            default:
              break;
          }
        }
        
        // encyption math
        j = 0;
        int k = 0;
        int l = 1;
        int dec_num;
        int dec_array_length = 0;
        while (l < plain_int_len){
          dec_num = (plain_int_buffer[k] - plain_int_buffer[l]);
          if (dec_num < 0){
            dec_num = dec_num + 27;
            dec_int_buffer[j] = dec_num;
            dec_array_length += 1;
            j += 1;
            k += 2;
            l += 2;
          }
          else{
            dec_int_buffer[j] = dec_num;
            dec_array_length += 1;
            j += 1;
            k += 2;
            l += 2;
          }
        }

        for (int i = 0; i < dec_array_length; i++){
          int dec_num = dec_int_buffer[i];
          switch (dec_num){
            case 0:
              dec_buffer[i] = 'A';
              break;
            case 1:
              dec_buffer[i] = 'B';
              break;
            case 2:
              dec_buffer[i] = 'C';
              break;
            case 3:
              dec_buffer[i] = 'D';
              break;
            case 4:
              dec_buffer[i] = 'E';
              break;
            case 5:
              dec_buffer[i] = 'F';
              break;
            case 6:
              dec_buffer[i] = 'G';
              break;
            case 7:
              dec_buffer[i] = 'H';
              break;
            case 8:
              dec_buffer[i] = 'I';
              break;
            case 9:
              dec_buffer[i] = 'J';
              break;
            case 10:
              dec_buffer[i] = 'K';
              break;
            case 11:
              dec_buffer[i] = 'L';
              break;
            case 12:
              dec_buffer[i] = 'M';
              break;
            case 13:
              dec_buffer[i] = 'N';
              break;
            case 14:
              dec_buffer[i] = 'O';
              break;
            case 15:
              dec_buffer[i] = 'P';
              break;
            case 16:
              dec_buffer[i] = 'Q';
              break;
            case 17:
              dec_buffer[i] = 'R';
              break;
            case 18:
              dec_buffer[i] = 'S';
              break;
            case 19:
              dec_buffer[i] = 'T';
              break;
            case 20:
              dec_buffer[i] = 'U';
              break;
            case 21:
              dec_buffer[i] = 'V';
              break;
            case 22:
              dec_buffer[i] = 'W';
              break;
            case 23:
              dec_buffer[i] = 'X';
              break;
            case 24:
              dec_buffer[i] = 'Y';
              break;
            case 25:
              dec_buffer[i] = 'Z';
              break;
            case 26:
              dec_buffer[i] = ' ';
              break;
          }
        }
        charsWritten = 0;
        while (charsWritten < strlen(dec_buffer)){
          charsWritten = send(connectionSocket, dec_buffer, strlen(dec_buffer), 0);
        }
        exit(0);
      default:
        waitpid(spawnChild, &childStatus, 0);
        break;
  }
    close(connectionSocket);
}
close(listenSocket);
return 0;
}
