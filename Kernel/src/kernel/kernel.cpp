#include "kernel.h"

#include<vector>
#include<cassert>

#include "..//ini_parser/ini_parser.h"
#include "..//general.h"

std::vector<xsExtensionInfo> m_vLoadedExtensionsInfo;
std::vector<xsExtensionModuleHandle> m_vLoadedExtensionsHandles;

xsResult xsKernelInit(xsExtensionInfo* KernelExtInfo){
	//Add kernel extension!
	m_vLoadedExtensionsInfo.push_back(*KernelExtInfo);
	m_vLoadedExtensionsHandles.push_back(XS_NULL_HANDLE);

	return xsResult::XS_RESULT_SUCCESS;
}

void xsKernelShutdown() {
	if (!m_vLoadedExtensionsHandles.empty()) {
		for (xsExtensionModuleHandle m_pHandle : m_vLoadedExtensionsHandles) {
			if (m_pHandle != XS_NULL_HANDLE) {
				xsAddress m_pShutdownAddr = xsGetProcAddr(
					m_pHandle,
					XS_LIBRARY_SHUTDOWN_FUNCTION);

				if (m_pShutdownAddr != NULL) {
					void (*_shutdown)() = reinterpret_cast<void(*)()>(m_pShutdownAddr);

					_shutdown();
				}
			}
		}
	}

	m_vLoadedExtensionsInfo.clear();
	m_vLoadedExtensionsHandles.clear();
}

#include<iostream>

xsResult xsKernelLoadExtensionFromIni(const char* m_sPath, xsExtensionInfo* m_pExtInfo){
	xsIniFileCtx* m_pCtx = xsParseIniFile(m_sPath);

	xsIniFileSection* m_pSection = xsGetIniFileSection(m_pCtx, "XSystem");
	if (m_pSection == XS_NULL_HANDLE) {
		std::string m_sMessage = "[xs]failed to find XSystem in file: '";
		m_sMessage += m_sPath;
		m_sMessage += "'!";

		g_KernelMessage(m_sMessage.c_str(), xsResult::XS_RESULT_FAILED);

		return xsResult::XS_RESULT_FAILED;
	}

	xsIniFileParameter* m_pParName = xsGetIniFileSectionParameter(m_pSection, "Name");
	if (m_pParName == XS_NULL_HANDLE) {
		std::string m_sMessage = "[xs]failed to find XSystem::Name in file: '";
		m_sMessage += m_sPath;
		m_sMessage += "'!";

		g_KernelMessage(m_sMessage.c_str(), xsResult::XS_RESULT_FAILED);

		return xsResult::XS_RESULT_FAILED;
	}
	xsIniFileParameter* m_pParPath = xsGetIniFileSectionParameter(m_pSection, "Path");
	if (m_pParPath == XS_NULL_HANDLE) {
		std::string m_sMessage = "[xs]failed to find XSystem::Path in file: '";
		m_sMessage += m_sPath;
		m_sMessage += "'!";

		g_KernelMessage(m_sMessage.c_str(), xsResult::XS_RESULT_FAILED);

	}
	xsIniFileParameter* m_pParVersion = xsGetIniFileSectionParameter(m_pSection, "Version");
	if (m_pParVersion == XS_NULL_HANDLE) {
		std::string m_sMessage = "[xs]failed to find XSystem::Version in file: '";
		m_sMessage += m_sPath;
		m_sMessage += "'!";

		g_KernelMessage(m_sMessage.c_str(), xsResult::XS_RESULT_FAILED);

	}

	xsExtensionInfo m_sExtInfo;
	m_sExtInfo.m_sPath = m_pParPath->m_sValue;
	m_sExtInfo.m_nVersion = atoi(m_pParVersion->m_sValue);
	m_sExtInfo.m_sName = m_pParName->m_sValue;

	xsResult m_nRes = xsKernelLoadExtension(&m_sExtInfo);

	xsFreeIniFile(m_pCtx);
	return m_nRes;
}

xsResult xsKernelLoadExtension(xsExtensionInfo* m_pExtInfo){
	xsExtensionModuleHandle m_pHandle = xsLoadLibrary(m_pExtInfo->m_sPath);
	if (m_pHandle == XS_NULL_HANDLE) {
		return xsResult::XS_RESULT_FAILED;
	}

	xsAddress m_pEntryFunctionAddr = xsGetProcAddr(m_pHandle, "xsModuleEntry");

	xsResult(*xsModuleEntry)(xsAPI* m_pAPI)= reinterpret_cast<xsResult (*)(xsAPI*)>(m_pEntryFunctionAddr);

	xsResult m_nRes = xsModuleEntry(xsGetKernelApi(XS_VERSION_0_1));

	if (m_nRes == xsResult::XS_RESULT_FAILED) {
		xsUnloadLibrary(m_pHandle);
		return m_nRes;
	}

	m_vLoadedExtensionsHandles.push_back(m_pHandle);
	m_vLoadedExtensionsInfo.push_back(*m_pExtInfo);
	return xsResult::XS_RESULT_SUCCESS;
}

uint32_t xsGetKernelLoadedExtensionsCount(){
	return m_vLoadedExtensionsInfo.size();
}

xsExtensionInfo* xsGetKernelLoadedExtensionInfo(uint32_t m_nInx){
	assert(m_vLoadedExtensionsInfo.size() <= m_nInx);

	return &m_vLoadedExtensionsInfo[m_nInx];
}

void* xsGetKernelLoadedExtensionHandle(uint32_t m_nInx) {
	assert(m_vLoadedExtensionsInfo.size() <= m_nInx);

	return (void*) &m_vLoadedExtensionsHandles[m_nInx];
}

void* xsGetKernelLoadedExtensionHandle(const char* m_sName){
	for (std::ptrdiff_t i = 0; i < m_vLoadedExtensionsInfo.size(); i++) {
		if (strcmp(m_vLoadedExtensionsInfo[i].m_sName, m_sName) == 0) {
			return (void*) & m_vLoadedExtensionsHandles[i];
		}
	}

	return XS_NULL_HANDLE;
}
