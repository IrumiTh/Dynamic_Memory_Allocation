#ifndef MYALLOC_H
#define MYALLOC_H

#include<stddef.h>
void initialize_memory();
void *MyMalloc(size_t size);
void MyFree(void *ptr);

#endif
