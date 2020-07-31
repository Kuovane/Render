#pragma once

#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>

class VxFile
{
public:
	static FILE* open(const char* pFileName, int nMode = 1 << 1);
	static void close(FILE* pFileHandle);
	static bool createDir(const char* pDir);
	static bool createDirEx(const char* pDir);			// do not use it.
	static bool isDirExist(const char* pDir);
	static bool isFileExist(const char* pFile);

	static bool write(FILE* pFile, const char* pBuffer, int nSize);
	static bool write(FILE* pFile, int nFilePos, const char* pBuffer, int nSize);
	static bool read(FILE* pFile, char* pBuffer, int nSize);
	static bool read(FILE* pFile, int nFilePos, char* pBuffer, int nSize);
	static int getFileSize(const char* pFileName);
	static bool removeFile(const char* pFileName);
	static bool rename(const char* pSrcName, const char* pDstName);

	static unsigned char* createFileData(const char* pFullFileName, const char* pszMode, unsigned long * pSize);
};

