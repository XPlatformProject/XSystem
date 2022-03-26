#ifndef _X_SYSTEM_SDK_LOADER_H
#define _X_SYSTEM_SDK_LOADER_H

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include<Windows.h>

typedef HINSTANCE xsExtensionModuleHandle;
#else
#include <dlfcn.h>

typedef void* xsExtensionModuleHandle;
#endif

typedef void* xsAddress;

xsExtensionModuleHandle xsLoadLibrary(const char* path);

xsAddress xsGetProcAddr(xsExtensionModuleHandle m_pHandle, const char* m_sName);

void xsUnloadLibrary(xsExtensionModuleHandle& m_pHandle);


#endif