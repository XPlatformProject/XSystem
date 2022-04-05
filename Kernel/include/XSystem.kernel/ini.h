#ifndef _INI_X_SYSTEM_H
#define _INI_X_SYSTEM_H

#include<XSystem/XSystem.h>

typedef void* xsIniCtx;
typedef void* xsIniSection;

typedef struct {
	char m_sName[XS_MAX_C_STRING_SIZE];
	char m_sValue[XS_MAX_C_STRING_SIZE];
	bool m_bIsArray = false;
}xsIniSectionParameter;

typedef struct {
	xsIniCtx(*xsParseIniFile)(const char* m_pPath);
	xsIniSection(*xsGetSection)(xsIniCtx m_pCtx, const char* m_sName);
	xsIniSectionParameter* (*xsGetSectionParameter)(xsIniSection m_pSection,const char* m_sName);
	void (*xsFreeIniFile)(xsIniCtx* m_pCtx);

	uint32_t(*xsGetIniFileSectionsCount)(xsIniCtx m_pCtx);
	uint32_t(*xsGetSectionParametersCount)(xsIniSection m_pSection);
	
	xsIniSection (*xsGetSectionByInx)(xsIniCtx m_pCtx,uint32_t m_nInx);
	xsIniSectionParameter* (*xsGetSectionParameterByInx)(xsIniSection,uint32_t m_nInx);

	const char* (*xsGetSectionName)(xsIniSection m_pSection);
	const char* (*xsGetParameterName)(xsIniSectionParameter* m_pSection);

	std::string (*xsGetArrayParameterArgument)(const char* m_sVal, uint32_t* it);
} xsIniParserAPI;

#endif