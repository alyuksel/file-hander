//
//  MyStdIO.c
//  fileHandler
//
//  Created by Alparslan Yuksel on 20/03/2018.
//  Copyright © 2018 Alparslan Yuksel. All rights reserved.
//

#include "MyStdIO.h"
#include "MyDiskBlockIO.h"

#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>

#define BLOCK_SIZE 20

char* create(char* fileName){
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

void writ(char* file, short data[]){
  //calcul du nombre de block de 10 + reste
  int offset = 0;
  int fullBlockNbr = ((sizeof(data)*12) / BLOCK_SIZE);
  int remaining = ((sizeof(data)*12) % BLOCK_SIZE);
  int i;
  char * blockChar = malloc(sizeof(int));
  int blockNbr = 0;
  char* blockName = malloc(strlen(file)+2+4);
  for(i = 0; i < fullBlockNbr ; i++){
    strcpy(blockName, file);
    strcat(blockName, "/");
    sprintf(blockChar, "%d", blockNbr);
    strcat(blockName, blockChar);
    strcat(blockName, ".txt");
    //createBlock
    int fd = createBlock(blockName);

    //writeBlock
    writeBlock(fd, data, offset, BLOCK_SIZE);
    blockChar = realloc(blockChar, sizeof(int));

    blockNbr = blockNbr + 1;
    offset = offset + BLOCK_SIZE;
  }
  strcpy(blockName, file);
  strcat(blockName, "/");
  sprintf(blockChar, "%d", blockNbr);
  strcat(blockName, blockChar);
  strcat(blockName, ".txt");
  //createBlock
  int fd = createBlock(blockName);
  //writeBlock
  writeBlock(fd, data, offset, remaining);

  free(blockChar);
  free(blockName);
}

void readd(char* file){
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

    readBlock(blockName);
    blockChar = realloc(blockChar, sizeof(int));
  }
}
