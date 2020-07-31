
#include "VxFile.h"

#define __VX_FILE_ENCRYPTION__

#define VXFILE_COPY_FILE_BUFFER_SIZE			(100 * 1024)

#define VXFILE_OPEN_FLAG_CREATE							(1 << 1)
#define VXFILE_OPEN_FLAG_CREATE_ALWAYS					(1 << 2)
#define VXFILE_OPEN_FLAG_APPEND							(1 << 3)

#define VXFILE_OPEN_MODE_CREATE_ALWAYS					"wb+"
#define VXFILE_OPEN_MODE_CREATE							"rb+"
#define VXFILE_OPEN_MODE_APPEND							"ab+"


#define VX_PLATFORM_WIN32 1

#define  VX_TARGET_PLATFORM  VX_PLATFORM_WIN32

#include <sys/stat.h>
#if VX_TARGET_PLATFORM == VX_PLATFORM_WIN32
	#include <regex>
	#include <direct.h>
	#include <io.h>
#else
	#include <unistd.h>
#endif



/************************************************************************/
/* VxFile
/************************************************************************/
FILE* VxFile::open(const char* pFileName, int nMode)
{
	FILE* pRet = NULL;
	if(VXFILE_OPEN_FLAG_CREATE_ALWAYS & nMode)
	{
		pRet = fopen(pFileName, VXFILE_OPEN_MODE_CREATE_ALWAYS);
	}
	else if(VXFILE_OPEN_FLAG_CREATE & nMode)
	{
		pRet = fopen(pFileName, VXFILE_OPEN_MODE_CREATE);
		if(NULL == pRet)
		{
			pRet = fopen(pFileName, VXFILE_OPEN_MODE_CREATE_ALWAYS);
		}
	}
	else if(VXFILE_OPEN_FLAG_APPEND & nMode)
	{
		pRet = fopen(pFileName, VXFILE_OPEN_MODE_APPEND);
	}
	return pRet;
}

void VxFile::close(FILE* pFileHandle)
{
	fclose(pFileHandle);
}

bool VxFile::createDirEx(const char* pDir)
{
/*	char* t;
	//VxLocalString sLocalT(&t, pDir);

	while (t = strchr(++t, '\\'))
	{
		*t = 0;
		if (VxFile::isDirExist(pDir))
		{
			*t = '\\';
			continue;
		}
		if(!VxFile::createDir(pDir))
		{
			return false;
		}
		*t = '\\';
	}
	*/
	return true;
}

bool VxFile::createDir(const char* pDir)
{
#if VX_TARGET_PLATFORM == VX_PLATFORM_WIN32
	return 0 == _mkdir(pDir);
#else
	return 0 == mkdir(pDir, 0777);
#endif
}

bool VxFile::isDirExist(const char* pDir)
{
#if VX_TARGET_PLATFORM == VX_PLATFORM_WIN32
	return 0 == _access(pDir, 0);
#else
	return 0 == access(pDir, 0);
#endif
}

bool VxFile::isFileExist(const char* pFile)
{
#if VX_TARGET_PLATFORM == VX_PLATFORM_WIN32
	return 0 == _access(pFile, 0);
#else
	return 0 == access(pFile, 0);
#endif
}

bool VxFile::write(FILE* pFile, const char* pBuffer, int nSize)
{
	return nSize == fwrite(pBuffer, 1, nSize, pFile);
}

bool VxFile::write(FILE* pFile, int nFilePos, const char* pBuffer, int nSize)
{
	if(0 > fseek(pFile, nFilePos, SEEK_SET))
	{
		return false;
	}
	return write(pFile, pBuffer, nSize);
}

bool VxFile::read(FILE* pFile, char* pBuffer, int nSize)
{
	return nSize == fread(pBuffer, 1, nSize, pFile);
}

bool VxFile::read(FILE* pFile, int nFilePos, char* pBuffer, int nSize)
{
	if(0 > fseek(pFile, nFilePos, SEEK_SET))
	{
		return false;
	}
	return read(pFile, pBuffer, nSize);
}

int VxFile::getFileSize(const char* pFileName)
{
	struct stat file_info;

	if(stat(pFileName, &file_info) == 0) 
	{
		return file_info.st_size;
	}

	return -1;
}

bool VxFile::removeFile(const char* pFileName)
{
#if VX_PLATFORM_WIN32 == VX_TARGET_PLATFORM
	return 0 == _unlink(pFileName);
#else
	return 0 == unlink(pFileName);
#endif
}

bool VxFile::rename(const char* pSrcName, const char* pDstName)
{
	return 0 == std::rename(pSrcName, pDstName);
}



unsigned char* VxFile::createFileData(const char* pFullFileName, const char* pszMode, unsigned long * pSize)
{
	unsigned char* pBuffer = NULL;

	{
		//assert(pFullFileName != NULL && pSize != NULL && pszMode != NULL, "Invaild parameters.");
		*pSize = 0;
		do
		{
			// read the file from hardware
			FILE *fp = fopen(pFullFileName, pszMode);
			if (!fp) break;

			fseek(fp, 0, SEEK_END);
			*pSize = ftell(fp);
			fseek(fp, 0, SEEK_SET);
			pBuffer = new unsigned char[*pSize];
			*pSize = fread(pBuffer, sizeof(unsigned char), *pSize, fp);
			fclose(fp);
		} while (0);
	}

	return pBuffer;
}

