#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>

// set address struct
void setAddressStruc(struct sockaddr_in* address, int portNumber){

  //clear the address struct
  memset((char*) address, '\0', sizeof(*address));

  //set network to ipv4
  address->sin_family = AF_INET;
  //store the port number 
  address->sin_port = htons(portNumber);

  // get the DNS entry to this host name
  struct hostent* hostInfo = gethostbyname("localhost");
  if (hostInfo == NULL){
    fprintf(stderr, "CLIENT: ERROR, no such host\n");
    exit(1);
  }
  // copy the first IP address from the DNS entry to sin_addr.s_addr
  memcpy((char*) &address->sin_addr.s_addr, hostInfo->h_addr_list[0], hostInfo->h_length);
}

int main(int argc, char* argv[]){
  int socketFD, charsWritten, charsRead;
  struct sockaddr_in serverAddress;

  // check usage and args
  if (argc < 3){
    fprintf(stderr, "USAGE: %s hostname port\n", argv[0]);
    exit(1);
  }

  char plaintext_buffer[200000];
  char keygen_buffer[200000];
  char data_buffer[200000];
  int plaint_char_count = 0;
  int key_char_count = 0;

  char good_characters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
    'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' '};

  // open files to read
  FILE *input = stdin;
  char *input_fn = ("stdin");
  input_fn = argv[1];
  input = fopen(input_fn, "r");
  if (!input){
    fprintf(stderr, "Open error decipher file");
  }
  int i = 0;
  int k = 0;
  int l = 0;
  char c = fgetc(input);
  while (c != EOF){
    for (k = 0; k < 27; k++){
      if (good_characters[k] == c){
        plaintext_buffer[i] = c;
        i += 1;
        plaint_char_count += 1;
        break;
      }
      if (c == '\n'){
        break;
      }
      if (k == 26){
        fprintf(stderr, "Bad character in dicipher file");
        exit(1);
      }
    }
    c = fgetc(input);
  }
  fclose(input);

  FILE *key_input = stdin;
  char *key_input_fn = ("stdin");
  key_input_fn = argv[2];
  key_input = fopen(key_input_fn, "r");
  if (!key_input){
    fprintf(stderr, "Open error keygen");
  }

  int j = 0;
  char b = fgetc(key_input);
  while (key_char_count != plaint_char_count){
    for (l = 0; l < 27; l++){
      if (good_characters[l] == b){
          keygen_buffer[j] = b;
          j += 1;
          key_char_count += 1;
          break;
      }
      if (b == '\n'){
        break;
      }
      if (l == 26){
        fprintf(stderr, "Keygen file too short");
        exit(1);
      }
    }
    b = fgetc(key_input);
  }
  fclose(key_input);

  // if check key file is shorter than plaintext file
  if (key_char_count < plaint_char_count){
    fprintf(stderr, "Key file is shorter than decipher file");
    exit(1);
  }

  // create a buffer packet mixed with keygen data and encrypted data to send to server
  int m = 0;
  int n = 0;
  char d = plaintext_buffer[m];
  while (m < strlen(plaintext_buffer)){
    data_buffer[n] = d;
    data_buffer[n+1] = keygen_buffer[m];
    m += 1;
    n += 2;
    d = plaintext_buffer[m];
  }
  
  // create a socket
  socketFD = socket(AF_INET, SOCK_STREAM, 0);
  if(socketFD < 0){
    fprintf(stderr, "CLIENT: ERROR opening socket");
  }
  
  // set up the server address struct
  setAddressStruc(&serverAddress, atoi(argv[3]));

  //connect to server
  if (connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0){
    fprintf(stderr, "CLIENT: ERROR connecting");
  }

  int data_length = strlen(data_buffer);
  char str_data_length[1024];
  sprintf(str_data_length, "%d", data_length);
  int total_length = strlen(str_data_length) + data_length;
  char str_total_len[1024];
  sprintf(str_total_len, "%d", total_length);

  // send length header to server first
  charsWritten = send(socketFD, str_total_len, strlen(str_total_len), 0);

  // send decipher text to server
  while (charsWritten < strlen(data_buffer)){
    charsWritten = send(socketFD, data_buffer, strlen(data_buffer), 0);
  }
  shutdown(socketFD, SHUT_WR);

  char receive_buffer[200000];
  memset(receive_buffer, '\0', sizeof(receive_buffer));

  charsRead = recv(socketFD, receive_buffer, 200000, 0);

  // write to file
  int fd = open(argv[4], O_WRONLY, 0600);
  dup2(fd, 1);
  for (int i = 0; i < strlen(receive_buffer); i++){
    printf("%c", receive_buffer[i]);
  }
  printf("%c", '\n');
}

