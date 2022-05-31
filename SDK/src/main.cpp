#include <XSystem/XSystem.h>
#include <XSystem/Loader.h>

#include "general.h"

pfn_xsKernelMessageCallback g_KernelMessage = NULL;
xsExtensionModuleHandle m_pKernelHandle = NULL;

xsAPI* xsLoadKernel(const xsExtensionInfo* KernelExtensionInfo, pfn_xsKernelMessageCallback Callback){
	g_KernelMessage = Callback;

	m_pKernelHandle = xsLoadLibrary(KernelExtensionInfo->m_sPath.c_str());
	if (m_pKernelHandle == XS_NULL_HANDLE) {
		return XS_NULL_HANDLE;
	}

	xsAddress m_pAddr = xsGetProcAddr(m_pKernelHandle, XS_API_SDK_VERSION);
	if (m_pAddr == NULL) {
		xsUnloadLibrary(m_pKernelHandle);

		g_KernelMessage("XSystem.SDK", 0, "check kernel library version failed to find xsKernelSDKVersion!", __FILE__, __LINE__ ,XS_RESULT_FAILED);
		return XS_NULL_HANDLE;
	}

	if (XS_SDK_VERSION != *(uint32_t*)m_pAddr) {
		xsUnloadLibrary(m_pKernelHandle);

		g_KernelMessage("XSystem.SDK", 0, "check kernel library sdk version matches application sdk version!", __FILE__, __LINE__, XS_RESULT_FAILED);
		return XS_NULL_HANDLE;
	}

	m_pAddr = xsGetProcAddr(m_pKernelHandle, "xsKernelEntry");
	if (m_pAddr == NULL) {
		xsUnloadLibrary(m_pKernelHandle);

		g_KernelMessage("XSystem.SDK", 0, "check kernel library version failed to find xsKernelEntry!", __FILE__, __LINE__, XS_RESULT_FAILED);
		return XS_NULL_HANDLE;
	}

	void(*xsKernelEntry)(pfn_xsKernelMessageCallback) =
		reinterpret_cast
		<void(*)(pfn_xsKernelMessageCallback)>(m_pAddr);

	xsKernelEntry(g_KernelMessage);

	m_pAddr = xsGetProcAddr(m_pKernelHandle, XS_API_FUNCTION);
	if (m_pAddr == NULL) {
		xsUnloadLibrary(m_pKernelHandle);

		g_KernelMessage("XSystem.SDK", 0, "check kernel library version failed to find xsGetKernelApi!", __FILE__, __LINE__, XS_RESULT_FAILED);
		return XS_NULL_HANDLE;
	}

	xsAPI*(*xsGetKernelApi)(const uint32_t m_nVersion) = (xsAPI*(*)(const uint32_t m_nVersion))m_pAddr;

	return xsGetKernelApi(KernelExtensionInfo->m_nVersion);
}

void xsUnloadKernel(void) {
	xsUnloadLibrary(m_pKernelHandle);
}