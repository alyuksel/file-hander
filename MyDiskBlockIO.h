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

int createBlock(char* blockName);
int writeBlock(int fd, short data [],int offset, int size);
void readBlock(char* blockName);
#endif /* MyDiskBlockIO_h */
