#include<memory>

#include<XSystem\XSystem.h>
#include<XSystem.kernel\ini.h>

#include "ini_parser\api\ini_parser_api.h"

#include "kernel\kernel.h"

#include "general.h"

pfn_xsKernelMessageCallback g_KernelMessage;

XS_KERNEL_API uint32_t xsKernelSDKVersion = XS_SDK_VERSION;

xsIniParserAPI m_pIniParserAPI{
	xsAPI_ParseIniFile,
	xsAPI_GetSection,
	xsAPI_GetSectionParameter,
	xsAPI_FreeFile,

	xsAPI_GetIniFileSectionsCount,
	xsAPI_GetSectionParametersCount,

	xsAPI_GetSectionByInx,
	xsAPI_GetParameterByInx,

	xsAPI_GetSectionName,
	xsAPI_GetParameterName,

	xsAPI_GetArrayParameterArgument
};

void* xsGetKernelIniParserApi() {
	return &m_pIniParserAPI;
}

xsAPI m_pAPI{
	xsKernelInit,

	xsKernelLoadExtension,
	xsKernelLoadExtensionFromIni,
	xsGetKernelLoadedExtensionsCount,

	xsGetKernelLoadedExtensionInfo,
	xsGetKernelLoadedExtensionInfo,

	xsGetKernelLoadedExtensionHandle,
	xsGetKernelLoadedExtensionHandle,
	
	xsGetKernelLoadedExtensionProcAddr,
	xsGetKernelLoadedExtensionProcAddr,
	
	xsGetKernelIniParserApi,

	xsKernelShutdown
};

XS_KERNEL_API void xsKernelEntry(pfn_xsKernelMessageCallback Callback) {
	g_KernelMessage = Callback;
}

XS_KERNEL_API xsAPI* xsGetKernelApi(const uint32_t m_nVersion) {
	return &m_pAPI;
}