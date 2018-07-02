#include "os_win.h"

void write_file(const char* name, void* buffer, int size, int offset) {

	HANDLE hfile = CreateFileA(name, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	SetFilePointer(hfile, offset, NULL, FILE_BEGIN);

	BOOL bErrorFlag = FALSE;
	DWORD dwBytesWritten = 0;

	bErrorFlag = WriteFile(hfile, (LPCVOID)buffer, size, &dwBytesWritten, 0);
	CloseHandle(hfile);

	return;
}

char* read_file(const char* name, void* buffer, int size, int offset) {
	char* res = new char[size];
	
	HANDLE hfile = CreateFileA(name, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	SetFilePointer(hfile, offset, NULL, FILE_BEGIN);

	BOOL bErrorFlag = FALSE;
	DWORD dwBytesRead = 0;

	ReadFile(hfile, res, size, &dwBytesRead, 0);

	return res;
}
