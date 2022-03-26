#include<memory>

#include<XSystem\XSystem.h>


#include "kernel\kernel.h"

#include "general.h"

pfn_xsKernelMessageCallback g_KernelMessage;

XS_KERNEL_API uint32_t xsKernelSDKVersion = XS_SDK_VERSION;

xsAPI m_pAPI{
	xsKernelInit,
	xsKernelLoadExtension,
	xsKernelLoadExtensionFromIni,
	xsGetKernelLoadedExtensionsCount,

	xsGetKernelLoadedExtensionInfo,
	xsGetKernelLoadedExtensionInfo,

	xsGetKernelLoadedExtensionHandle,
	xsGetKernelLoadedExtensionHandle,

	xsKernelShutdown
};

XS_KERNEL_API void xsKernelEntry(pfn_xsKernelMessageCallback Callback) {
	g_KernelMessage = Callback;
}

XS_KERNEL_API xsAPI* xsGetKernelApi(const uint32_t m_nVersion) {
	return &m_pAPI;
}