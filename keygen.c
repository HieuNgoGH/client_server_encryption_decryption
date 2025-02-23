#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){


  // extract the argument and convert it into an integer
  char* arg = argv[1];
  int num = atoi(arg);
  int num_array[num+1];

  // place random integers 0-27 into integer array
  for (int i = 0; i < num; i++){
    int rand_num = rand() % 27;
    num_array[i] = rand_num;
  }

  // convert integers into characters and place into new array
  char key_array[num];
  for (int i = 0; i < num; i++){
    int before_key = num_array[i];
    switch(before_key){
      case 0:
        key_array[i] = 'A';
        break;
      case 1:
        key_array[i] = 'B';
        break;
      case 2:
        key_array[i] = 'C';
        break;
      case 3:
        key_array[i] = 'D';
        break;
      case 4:
        key_array[i] = 'E';
        break;
      case 5:
        key_array[i] = 'F';
        break;
      case 6:
        key_array[i] = 'G';
        break;
      case 7:
        key_array[i] = 'H';
        break;
      case 8:
        key_array[i] = 'I';
        break;
      case 9:
        key_array[i] = 'J';
        break;
      case 10:
        key_array[i] = 'K';
        break;
      case 11:
        key_array[i] = 'L';
        break;
      case 12:
        key_array[i] = 'M';
        break;
      case 13:
        key_array[i] = 'N';
        break;
      case 14:
        key_array[i] = 'O';
        break;
      case 15:
        key_array[i] = 'P';
        break;
      case 16:
        key_array[i] = 'Q';
        break;
      case 17:
        key_array[i] = 'R';
        break;
      case 18:
        key_array[i] = 'S';
        break;
      case 19:
        key_array[i] = 'T';
        break;
      case 20:
        key_array[i] = 'U';
        break;
      case 21:
        key_array[i] = 'V';
        break;
      case 22:
        key_array[i] = 'W';
        break;
      case 23:
        key_array[i] = 'X';
        break;
      case 24:
        key_array[i] = 'Y';
        break;
      case 25:
        key_array[i] = 'Z';
        break;
      case 26:
        key_array[i] = ' ';
        break;
    }
   }

  // add newline to the end of array then do redirection to file
  key_array[num+1] = '\n';

  int fd = open(argv[1], O_WRONLY, 0600);
  dup2(fd, 1);
  for (int j = 0; j<num; j++){
    printf("%c", key_array[j]);
  }
  printf("%c", '\n');

return 0;
}
