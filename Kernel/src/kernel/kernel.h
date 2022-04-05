#ifndef _X_SYSTEM_KERNEL_H
#define _X_SYSTEM_KERNEL_H

#include<XSystem/XSystem.h>
#include<XSystem/Loader.h>

#define XS_KERNEL_API extern "C" XS_API_EXPORT

#define XS_LIBRARY_SHUTDOWN_FUNCTION "xsModuleShutdown"

xsResult xsKernelInit(xsExtensionInfo* KernelExtInfo);
void xsKernelShutdown();
xsResult xsKernelLoadExtension(xsExtensionInfo* m_pExtInfo);
xsResult xsKernelLoadExtensionFromIni(const char*, xsExtensionInfo* m_pExtInfo);

uint32_t xsGetKernelLoadedExtensionsCount();
xsExtensionInfo* xsGetKernelLoadedExtensionInfo(uint32_t m_nInx);
xsExtensionInfo* xsGetKernelLoadedExtensionInfo(const char* m_sName);

void* xsGetKernelLoadedExtensionProcAddr(uint32_t m_nInx, const char* m_sProcName);
void* xsGetKernelLoadedExtensionProcAddr(const char* m_sName, const char* m_sProcName);

void* xsGetKernelLoadedExtensionHandle(uint32_t m_nInx);
void* xsGetKernelLoadedExtensionHandle(const char* m_sName);

XS_KERNEL_API xsAPI* xsGetKernelApi(const uint32_t m_nVersion);

#endif