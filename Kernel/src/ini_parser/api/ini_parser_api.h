#ifndef _X_SYSTEM_INI_PARSER_API_H
#define _X_SYSTEM_INI_PARSER_API_H

#include<XSystem.kernel\ini.h>

xsIniCtx xsAPI_ParseIniFile(const char* m_pPath);
xsIniSection xsAPI_GetSection(xsIniCtx m_pCtx, const char* m_sName);
xsIniSectionParameter* xsAPI_GetSectionParameter(xsIniSection m_pSection, const char* m_sName);
void xsAPI_FreeFile(xsIniCtx* m_pCtx);

uint32_t xsAPI_GetIniFileSectionsCount(xsIniCtx m_pCtx);
uint32_t xsAPI_GetSectionParametersCount(xsIniSection m_pSection);

xsIniSection xsAPI_GetSectionByInx (xsIniCtx m_pCtx, uint32_t m_nInx);
xsIniSectionParameter* xsAPI_GetParameterByInx (xsIniSection m_pSection, uint32_t m_nInx);

const char* xsAPI_GetSectionName(xsIniSection m_pSection);
const char* xsAPI_GetParameterName(xsIniSectionParameter* m_pParameter);

std::string xsAPI_GetArrayParameterArgument(const char* m_sVal, uint32_t* it);

#endif