//
//  MyStdIO.h
//  fileHandler
//
//  Created by Alparslan Yuksel on 20/03/2018.
//  Copyright © 2018 Alparslan Yuksel. All rights reserved.
//

#ifndef MyStdIO_h
#define MyStdIO_h

#include <stdio.h>
#include <sys/stat.h>

char* create(char* fileName);
void writ(char* file, short data[]);
void readd(char* file);

#endif /* MyStdIO_h */
