//
//  MyStdIO.c
//  fileHandler
//
//  Created by Alparslan Yuksel on 20/03/2018.
//  Copyright © 2018 Alparslan Yuksel. All rights reserved.
//

#include "MyStdIO.h"
#include "MyDiskBlockIO.h"

char* create(char* fileName){
    return createFile(fileName);
}

void writ(char* file, short data[]){
    writFile(file, data);
}

void readd(char* file){
    readFile(file);
}
