#ifndef OS_WIN
#define OS_WIN

#include <Windows.h>

void write_file(const char* name, void* buffer, int size, int offset);
char* read_file(const char* name, void* buffer, int size, int offset);

#endif
