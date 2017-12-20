#pragma once

#include "SendLog.h"

#ifndef __FILE_API__
#define __FILE_API__


NTSTATUS MyZwSetInformationFile(
	_In_  HANDLE                 FileHandle,
	_Out_ PIO_STATUS_BLOCK       IoStatusBlock,
	_In_  PVOID                  FileInformation,
	_In_  ULONG                  Length,
	_In_  FILE_INFORMATION_CLASS FileInformationClass
);

typedef NTSTATUS(*ptrZwSetInformationFile)(
	_In_  HANDLE                 FileHandle,
	_Out_ PIO_STATUS_BLOCK       IoStatusBlock,
	_In_  PVOID                  FileInformation,
	_In_  ULONG                  Length,
	_In_  FILE_INFORMATION_CLASS FileInformationClass
	);

extern ptrZwSetInformationFile realZwSetInformationFile;


#endif // !__FILE_API__


