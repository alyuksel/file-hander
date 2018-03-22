//
//  main.c
//  fileHandler
//
//  Created by Alparslan Yuksel on 20/03/2018.
//  Copyright © 2018 Alparslan Yuksel. All rights reserved.
//

#include <stdio.h>
#include <fcntl.h>
#include "MyStdIO.h"

int main(int argc, char * argv[]) {
    //creation du fichier
    char * filePath = create("myfile");

    //préparation de la data a ecrire
    short data [96];
    int i;
    for(i = 0; i < (sizeof(data) / sizeof(data[0])) ; i++){
      data[i] = i;
    }

    //Ecriture data -> file
    writ(filePath, data);

    //Lecture des blocks
    readd(filePath);

    return 0;
}
