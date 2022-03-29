#ifndef _X_SYSTEM_H
#define _X_SYSTEM_H
#include<stddef.h>
#include<string>

#include <stdint.h>

#define XS_SDK_VERSION 0x01

#ifdef WIN32
#define XS_API_EXPORT __declspec(dllexport)

#define XS_API_IMPORT __declspec(dllimport)
#else
#define XS_API_EXPORT __attribute__((dllexport))

#define XS_API_IMPORT __attribute__((dllimport))
#endif

#ifdef WIN32

#else
#endif

#define XS_API_FUNCTION "xsGetKernelApi"
#define XS_API_SDK_VERSION "xsKernelSDKVersion"



#define XS_NULL_HANDLE 0x0

// Basic functional!
#define XS_VERSION_0_1 0x01

#define XS_MAX_C_STRING_SIZE 256

enum xsResult : bool {
	XS_RESULT_SUCCESS = true,
	XS_RESULT_FAILED = false
};

typedef struct {
	std::string m_sName;
	std::string m_sPath;
	uint32_t m_nVersion;
}xsExtensionInfo;

typedef struct {
	xsResult(*xsKernelInit)(xsExtensionInfo* KernelExtInfo);

	xsResult(*xsKernelLoadExtension)(xsExtensionInfo* m_pExtInfo);
	xsResult(*xsKernelLoadExtensionFromIni)(const char* m_sPath, xsExtensionInfo* m_pExtInfo);

	uint32_t(*xsGetKernelLoadedExtensionsCount)();

	xsExtensionInfo* (*xsGetKernelLoadedExtensionInfo)(uint32_t m_nInx);
	xsExtensionInfo* (*xsGetKernelLoadedExtensionInfoFromName)(const char* m_sName);

	void* (*xsGetKernelLoadedExtensionHandle)(uint32_t m_nInx);
	void* (*xsGetKernelLoadedExtensionHandleFromName)(const char* m_sName);

	void* (*xsGetKernelLoadedExtensionProc)(uint32_t m_nInx, const char* m_sProcName);
	void* (*xsGetKernelLoadedExtensionProcFromName)(const char* m_sName, const char* m_sProcName);

	void* (*xsGetKernelIniParserApi)();

	void (*xsKernelShutdown)();
}xsAPI;

typedef void(*pfn_xsKernelMessageCallback)(const char* m_sMsg, const uint32_t m_nResult);

xsAPI* xsLoadKernel(const xsExtensionInfo* KernelExtensionInfo, pfn_xsKernelMessageCallback Callback);
void xsUnloadKernel(void);

#endif