#include "ini_parser_api.h"

#include "..//ini_parser.h"

xsIniCtx xsAPI_ParseIniFile(const char* m_pPath){
	return xsParseIniFile(m_pPath);
}

xsIniSection xsAPI_GetSection(xsIniCtx m_pCtx, const char* m_sName){
	return xsGetIniFileSection((xsIniFileCtx*)m_pCtx, m_sName);
}

xsIniSectionParameter* xsAPI_GetSectionParameter(xsIniSection m_pSection, const char* m_sName){
	return reinterpret_cast<xsIniSectionParameter*>(xsGetIniFileSectionParameter((xsIniFileSection*)m_pSection, m_sName));
}

void xsAPI_FreeFile(xsIniCtx* m_pCtx){
	return xsFreeIniFile((xsIniFileCtx*)*m_pCtx);
}

uint32_t xsAPI_GetIniFileSectionsCount(xsIniCtx m_pCtx){
	return ((xsIniFileCtx*)m_pCtx)->m_nSectionsCount;
}

uint32_t xsAPI_GetSectionParametersCount(xsIniSection m_pSection){
	return ((xsIniFileSection*)m_pSection)->m_nParametrsCount;
}

xsIniSection xsAPI_GetSectionByInx(xsIniCtx m_pCtx, uint32_t m_nInx){
	return &((xsIniFileCtx*)m_pCtx)->m_pSections[m_nInx];
}

xsIniSectionParameter* xsAPI_GetParameterByInx(xsIniSection m_pSection, uint32_t m_nInx){
	return reinterpret_cast<xsIniSectionParameter*>(&((xsIniFileSection*)m_pSection)->m_pParametrs[m_nInx]);
}

const char* xsAPI_GetSectionName(xsIniSection m_pSection){
	return ((xsIniFileSection*)m_pSection)->m_sName;
}

const char* xsAPI_GetParameterName(xsIniSectionParameter* m_pParameter){
	return m_pParameter->m_sName;
}

std::string xsAPI_GetArrayParameterArgument(const char* m_sVal, uint32_t* it){
	uint32_t m_nValStrLen = strlen(m_sVal);
	std::string m_sTmp = "";

	for (; *it < m_nValStrLen; *it += 1) {
		char m_cSymbol = m_sVal[*it];
		if (m_cSymbol == ';') {
			*it += 1;
			break;
		}

		m_sTmp.push_back(m_cSymbol);
	}

	return m_sTmp;
}
