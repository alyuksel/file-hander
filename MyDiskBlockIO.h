//
//  MyDiskBlockIO.h
//  fileHandler
//
//  Created by Alparslan Yuksel on 20/03/2018.
//  Copyright © 2018 Alparslan Yuksel. All rights reserved.
//

#ifndef MyDiskBlockIO_h
#define MyDiskBlockIO_h

#include <stdio.h>
#include <sys/stat.h>
#include <stdio.h>

char* createFile(char * fileName);
void writFile(char* file, short data[]);
void readFile(char* file);

#endif /* MyDiskBlockIO_h */
