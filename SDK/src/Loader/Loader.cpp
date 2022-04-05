#include <XSystem/Loader.h>
#include <XSystem/XSystem.h>

#include "..//general.h"

#include<memory>
#include<string.h>

void xsPrintLibraryError(const char* path) {
#ifdef WIN32
	char* m_pSystemMessageBuffer = NULL;

	{
		DWORD ErrorMsgId = GetLastError();

		FormatMessageA(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			ErrorMsgId,
			MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT),
			(LPSTR)&m_pSystemMessageBuffer, 0, NULL
		);
	}
#else
	
	const char* m_pSystemMessageBuffer = dlerror();

#endif

	uint32_t m_PathLength = strlen(path);
	uint32_t m_SystemMsgLength = strlen(m_pSystemMessageBuffer);
	uint32_t m_MsgLength = 31 + m_PathLength + 4 + m_SystemMsgLength + 1;

	char* m_pMessage = (char*)malloc(m_MsgLength);
	if (m_pMessage == NULL) {
		g_KernelMessage("[xs]: not enogh memory for print error!", XS_RESULT_FAILED);
		exit(-101);
	}
	memset(m_pMessage, 0x0, m_MsgLength);

	strcat(m_pMessage, "[xs]: failed to load library '");
	strcat(m_pMessage, path);
	strcat(m_pMessage, "':\n");
	strcat(m_pMessage, m_pSystemMessageBuffer);

	g_KernelMessage(m_pMessage, XS_RESULT_FAILED);
}

xsExtensionModuleHandle xsLoadLibrary(const char* path){
	xsExtensionModuleHandle m_Handle = XS_NULL_HANDLE;

#ifdef WIN32
	m_Handle = LoadLibraryA(path);
#else
	m_Handle = dlopen(path, RTLD_LAZY);
#endif

	if (m_Handle == NULL) {
		xsPrintLibraryError(path);

		return XS_NULL_HANDLE;
	}

	return m_Handle;
}

xsAddress xsGetProcAddr(xsExtensionModuleHandle m_pHandle, const char* m_sName){
#ifdef WIN32
	return GetProcAddress((HMODULE)m_pHandle, m_sName);
#else
	return dlsym(m_pHandle, m_sName);
#endif
}

void xsUnloadLibrary(xsExtensionModuleHandle& m_pHandle){
#ifdef WIN32
	FreeLibrary(m_pHandle);
#else
	dlclose(m_pHandle);
#endif

	m_pHandle = XS_NULL_HANDLE;
}

