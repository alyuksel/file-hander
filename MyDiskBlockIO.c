//
//  MyDiskBlockIO.c
//  fileHandler
//
//  Created by Alparslan Yuksel on 20/03/2018.
//  Copyright © 2018 Alparslan Yuksel. All rights reserved.
//

#include <dirent.h>
#include "MyDiskBlockIO.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>


char* createFile(char * fileName){
    char* root ="./";
    char* path;
    path = malloc(strlen(fileName)+strlen(root));
    strcpy(path, root);
    strcat(path, fileName);
    if (mkdir(path, 0777)<0){
        printf("error lors de la creation du fichier");
    }
    return path;
}

void writFile(char* file, short data[]){
  //calcul du nombre de block de 10 + reste
  int offset = 0;
  int fullBlockNbr = ((sizeof(data)*12) / 10);
  int remaining = ((sizeof(data)*12) % 10);
  int i;
  char * blockChar = malloc(sizeof(int));
  int block = 0;
  char* blockName = malloc(strlen(file)+2+4);
  for(i = 0; i < fullBlockNbr ; i++){
    strcpy(blockName, file);
    strcat(blockName, "/");
    sprintf(blockChar, "%d", block);
    strcat(blockName, blockChar);
    strcat(blockName, ".txt");
    //createBlock
    int fd = createBlock(blockName);

    //writeBlock
    writeBlock(fd, data, offset, 10);
    blockChar = realloc(blockChar, sizeof(int));

    block = block + 1;
    offset = offset + 10;
  }
  strcpy(blockName, file);
  strcat(blockName, "/");
  sprintf(blockChar, "%d", block);
  strcat(blockName, blockChar);
  strcat(blockName, ".txt");
  //createBlock
  int fd = createBlock(blockName);
  //writeBlock
  writeBlock(fd, data, offset, remaining);

  free(blockChar);
  free(blockName);
}

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

void readFile(char* file){
    DIR* rep = NULL;
    struct dirent* fichierLu = NULL; /* Déclaration d'un pointeur vers la structure dirent. */
    rep = opendir(file);
    if (rep == NULL)
        printf("erreur d'ouverture de fichier");
    int nbrBlocks = -2;
    while ((fichierLu = readdir(rep) )!= NULL) {
      nbrBlocks ++;
    };
    char* blockName = malloc(strlen(file)+2+4);
    char * blockChar = malloc(sizeof(int));

    int i =0;
    printf("\n");
    for(i = 0 ; i<nbrBlocks ; i++){
      strcpy(blockName, file);
      strcat(blockName, "/");
      sprintf(blockChar, "%d", i);
      strcat(blockName, blockChar);
      strcat(blockName, ".txt");

      struct stat statFile;
      stat(blockName, &statFile);
      //utile pour connaitre la taille du fichier afin de creer des tableau de la bonne taille
      int blockSize = statFile.st_size/4;

      int c;
      FILE *block;
      block = fopen(blockName, "r");
      if (block) {
          printf("block -> %d\n", i);
          while ((c = getc(block)) != EOF){
            if(isdigit(c))
                printf("%c", c);
          }
          printf("\n");
          fclose(block);

      }
      blockChar = realloc(blockChar, sizeof(int));
    }

}
