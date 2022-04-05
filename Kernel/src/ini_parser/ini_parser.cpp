#include "ini_parser.h"
#include<XSystem/XSystem.h>
#include<fstream>

#include "..//general.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <string.h>

xsIniFileCtx* xsParseIniFile(const char* m_sPath){
	std::ifstream m_ifstream(m_sPath);
	if (!m_ifstream.is_open()) {
		std::string m_sMessage
			= "[xs][ini_parser]:couldn't open the file: '";
		m_sMessage += m_sPath;
		m_sMessage += "'!";

		g_KernelMessage(m_sMessage.c_str(), xsResult::XS_RESULT_FAILED);

		return XS_NULL_HANDLE;
	}

	std::string m_sLine;

	uint32_t m_nStructureSize = sizeof(xsIniFileCtx);
	xsIniFileCtx* m_pCtx = (xsIniFileCtx*)malloc(m_nStructureSize);
	memset(m_pCtx, 0x0, m_nStructureSize);

	std::string m_sTmp;

	std::vector<xsIniFileSection> m_vSections;
	xsIniFileSection m_MainSec;
	memcpy(m_MainSec.m_sName, "main", 5);
	m_vSections.push_back(m_MainSec);

	std::string m_sCurrentSection = "main";
	std::vector<std::unordered_map<std::string, std::string>> 
		m_vumParameters;

	std::vector<std::unordered_map<std::string, bool>>
		m_vubParameters;

	while (!m_ifstream.eof()) {
		std::getline(m_ifstream, m_sLine);
		if (m_sLine.empty()) continue;

		if (m_sLine[0] == '[') {
			for (std::ptrdiff_t i = 1; i < m_sLine.size(); i++) {
				if (m_sLine[i] == ']') {
					m_sCurrentSection = m_sTmp;
					xsIniFileSection m_NewSection;
					memcpy(m_NewSection.m_sName, m_sTmp.data(), XS_MAX_C_STRING_SIZE);
					m_vSections.push_back(m_NewSection);
					m_sTmp.clear();
					break;
				}
				m_sTmp.push_back(m_sLine[i]);
			}
			continue;
		}
		else {
			bool m_bIsString = false;
			bool m_bIsArray = false;

			std::vector<std::string> m_vsArrayParameters;

			std::string m_sParameterName = "";
			std::string m_sParameterVal = "";

			std::ptrdiff_t i = 0;

			// Parameter name
			for (; i < m_sLine.size(); i++) {
				if (m_sLine[i] == '\t' || m_sLine[i] == ' ') {
					continue;
				}
				else if (m_sLine[i] == '=') {
					m_sParameterName = m_sTmp;
					m_sTmp.clear();
					i++;
					break;
				}

				m_sTmp.push_back(m_sLine[i]);
			}

			// Parameter value
			for (; i < m_sLine.size() + 1; i++) {
				if(!m_bIsString)
				if (m_sLine[i] == '"') {
					m_bIsString = true;
					continue;
				}
				else if (m_sLine[i] == '{') {
					m_bIsArray = true;
					continue;
				}

				if (!m_bIsString) {
					if (m_sLine[i] == '\t' || m_sLine[i] == ' ') {
						continue;
					}
					else if (m_sLine[i] == ';' || m_sLine[i] == '\0' || m_sLine[i] == '\n') {
						m_sParameterVal = m_sTmp;
						m_sTmp.clear();
						break;
					}
					
					if(m_bIsArray)
					if (m_sLine[i] == ',') {
						m_vsArrayParameters.push_back(m_sTmp);
						m_sTmp.clear();
						continue;
					}
					else if (m_sLine[i] == '}') {
						m_vsArrayParameters.push_back(m_sTmp);
						m_sTmp.clear();
						break;
					}
				}
				else {
					if (m_sLine[i] == '"') {
						if (!m_bIsArray) {
							m_sParameterVal = m_sTmp;
							m_sTmp.clear();
							break;
						}
						else {
							m_bIsString = false;
							continue;
						}
					}
				}

				m_sTmp.push_back(m_sLine[i]);
			}

			for (std::ptrdiff_t i = 0; m_vSections.size(); i++) {
				if (m_vSections[i].m_sName == m_sCurrentSection) {
					if (m_vumParameters.size() <= i) {
						m_vumParameters.resize(i + 1);
						m_vubParameters.resize(i + 1);
					}
					if (!m_bIsArray) {
						m_vumParameters[i][m_sParameterName] = m_sParameterVal;
					
					}
					else {
						std::string m_sVal = "";
						for (std::string& m_sArrayVal : m_vsArrayParameters) {
							m_sVal += m_sArrayVal;
							m_sVal += ";";
						}
						m_vumParameters[i][m_sParameterName] = m_sVal;
					}

					m_vubParameters[i][m_sParameterName] = m_bIsArray;
					break;
				}
			}

		}

	}

	m_ifstream.close();
	

	uint32_t m_nSectionsSize = sizeof(xsIniFileSection) * m_vSections.size();
	m_pCtx->m_pSections = (xsIniFileSection*)malloc(m_nSectionsSize);
	m_pCtx->m_nSectionsCount = m_vSections.size();
	memcpy(m_pCtx->m_pSections, m_vSections.data(), m_nSectionsSize);

	for (std::ptrdiff_t i = 0; i < m_vumParameters.size(); i++) {
		
		auto& m_Map = m_vumParameters[i];
		auto& m_bMap = m_vubParameters[i];
		std::ptrdiff_t m_nParametersCount = 0;
		std::vector<std::string> m_sNames;
		std::vector<std::string> m_sVals;
		std::vector<bool> m_bIsArray;
		for (auto It = m_Map.begin(); It != m_Map.end(); ++It) {
			m_sNames.push_back(It->first);
			m_sVals.push_back(It->second);

			m_nParametersCount++;
		}

		for (auto It = m_bMap.begin(); It != m_bMap.end(); ++It) {
			m_bIsArray.push_back(It->second);
		}

		xsIniFileSection* m_pSection = &m_pCtx->m_pSections[i];
		
		m_pSection->m_nParametrsCount = m_nParametersCount;
		m_pSection->m_pParametrs = (xsIniFileParameter*)
			malloc(sizeof(xsIniFileParameter) * m_nParametersCount);
		
		for (std::ptrdiff_t i = 0; i < m_pSection->m_nParametrsCount; i++) {
			memcpy(m_pSection->m_pParametrs[i].m_sName, m_sNames[i].c_str(), XS_MAX_C_STRING_SIZE);
			memcpy(m_pSection->m_pParametrs[i].m_sValue, m_sVals[i].c_str(), XS_MAX_C_STRING_SIZE);
			
			m_pSection->m_pParametrs[i].m_bIsArray = m_bIsArray[i];
		}
	}

	return m_pCtx;
}

xsIniFileSection* xsGetIniFileSection(xsIniFileCtx* m_pCtx, const char* m_sName){
	for (std::ptrdiff_t i = 0; i < m_pCtx->m_nSectionsCount; i++) {
		if (strcmp(m_pCtx->m_pSections[i].m_sName, m_sName) == 0) {
			return &m_pCtx->m_pSections[i];
		}
	}

	return XS_NULL_HANDLE;
}

xsIniFileParameter* xsGetIniFileSectionParameter(xsIniFileSection* m_pSection, const char* m_sName){
	for (std::ptrdiff_t i = 0; i < m_pSection->m_nParametrsCount; i++) {
		if (strcmp(m_pSection->m_pParametrs[i].m_sName, m_sName) == 0)
			return &m_pSection->m_pParametrs[i];
	}

	return XS_NULL_HANDLE;
}

void xsFreeIniFile(xsIniFileCtx* m_pCtx){
	for (std::ptrdiff_t i = 0; i < m_pCtx->m_nSectionsCount; i++) {
		free(m_pCtx->m_pSections[i].m_pParametrs);
	}

	free(m_pCtx->m_pSections);
	free(m_pCtx);
}
