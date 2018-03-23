//
//  MyDiskBlockIO.c
//  fileHandler
//
//  Created by Alparslan Yuksel on 20/03/2018.
//  Copyright © 2018 Alparslan Yuksel. All rights reserved.
//

#include "MyDiskBlockIO.h"
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>


int createBlock(char* blockName){
  creat(blockName, O_CREAT|S_IRWXU);
  return open(blockName, O_WRONLY);
}

int writeBlock(int fd, short data [],int offset, int size){

  int i;
  for(i = 0 ; i< size ; i++){
    char* dataChar = malloc(sizeof(int));
    short tamp = data[offset+i];
    sprintf(dataChar, "%d", tamp);
    //printf("%s\n", dataChar);
    write(fd, dataChar, 2);
    write(fd, "\n", 2);
    free(dataChar);
  }
}

void readBlock(char* blockName){
  int c;
  FILE *block;
  block = fopen(blockName, "r");
  if (block) {
      printf("block -> \n");
      while ((c = getc(block)) != EOF){
        if(isdigit(c))
            printf("%c", c);
      }
      printf("\n");
      fclose(block);
  }
}
