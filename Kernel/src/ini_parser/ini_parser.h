#ifndef _X_SYSTEM_INI_H
#define _X_SYSTEM_INI_H

#include <XSystem/XSystem.h>

#ifndef _XS_NOT_DEFINE_xsIniFileParameter
typedef struct {
	char m_sName[XS_MAX_C_STRING_SIZE];
	char m_sValue[XS_MAX_C_STRING_SIZE];
	bool m_bIsArray = false;
}xsIniFileParameter;
#endif

typedef struct {
	char m_sName[XS_MAX_C_STRING_SIZE];
	
	xsIniFileParameter* m_pParametrs;
	uint32_t m_nParametrsCount;
}xsIniFileSection;

typedef struct {
	/*
		without section parametrs: in main section!


	*/
	xsIniFileSection* m_pSections;
	uint32_t m_nSectionsCount;

} xsIniFileCtx;

xsIniFileCtx* xsParseIniFile(const char* m_sPath);
void xsFreeIniFile(xsIniFileCtx* m_pCtx);

xsIniFileSection* xsGetIniFileSection(xsIniFileCtx* m_pCtx, const char* m_sName);
xsIniFileParameter* xsGetIniFileSectionParameter(xsIniFileSection* m_pSection, const char* m_sName);

#endif