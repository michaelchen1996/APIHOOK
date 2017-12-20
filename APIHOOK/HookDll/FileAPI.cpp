#include "stdafx.h"
#include "FileAPI.h"


NTSTATUS MyZwSetInformationFile(
	_In_  HANDLE                 FileHandle,
	_Out_ PIO_STATUS_BLOCK       IoStatusBlock,
	_In_  PVOID                  FileInformation,
	_In_  ULONG                  Length,
	_In_  FILE_INFORMATION_CLASS FileInformationClass
)
{
	NTSTATUS status = -1;
	if (NULL == realZwSetInformationFile)
	{
		OutputDebugString(TEXT("realZwSetInformationFile NOT FOUND\n"));
		return status;
	}
	else
	{
		if (10 == FileInformationClass)
		{
			SendLog(TEXT("MyZwSetInformationFile\r\n"));
		}

		status = realZwSetInformationFile(
			FileHandle,
			IoStatusBlock,
			FileInformation,
			Length,
			FileInformationClass
		);

	}

	return status;
}