#include "VeStore.h"
#include "../Utilities/DebugUtil.h"

typedef int(*pInitConnect)(char* strParameters[], long nCount);
pInitConnect m_InitConnect;

typedef int(*pReleaseConnect)();
pReleaseConnect m_ReleaseConnect;

typedef int(*pGetRTDataByBatch)(char* tagNames[], TagData * pTagData, long nCount);
pGetRTDataByBatch m_GetRTDataByBatch;

using namespace TA_Base_Core;

VeStore::VeStore()
{
	hInst = LoadLibrary(_T("RTDBInterface.dll"));
	if (hInst)
	{
		LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Load RTDBInterface.dll successfully");
		m_InitConnect = (pInitConnect)GetProcAddress(hInst, "InitConnect");
		m_ReleaseConnect = (pReleaseConnect)GetProcAddress(hInst, "ReleaseConnect");
		m_GetRTDataByBatch = (pGetRTDataByBatch)GetProcAddress(hInst, "GetRTDataByBatch");
	}
	else
	{
		LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugError, "Load RTDBInterface.dll failed");
		printf("Load Library fail!\n");
	}

	//ReadConfig();
}

VeStore::~VeStore()
{
}

int VeStore::initConnect(std::string dllPath, std::string iniPath)
{
	char* strParameters[4];
	strParameters[0] = (char*)malloc(256);
	strParameters[1] = (char*)malloc(256);
	//strcpy(strParameters[0], "D:\\VeStore新版开发\\VeStore V3.0\\3.0版代码\\RTDBinterface\\VeStoreTest\\VeStoreTest\\Debug\\");
	//strcpy(strParameters[1], "D:\\VeStore新版开发\\VeStore V3.0\\3.0版代码\\RTDBinterface\\VeStoreTest\\VeStoreTest\\Debug\\");
	strcpy(strParameters[0], dllPath.c_str());
	strcpy(strParameters[1], iniPath.c_str());
	int nRet = m_InitConnect(strParameters, 4);
	if(nRet == 0)
		LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Init RTDB connect successfully");
	else
		LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugError, "Init RTDB connect failed");

	return nRet;
}

int VeStore::getRTDataByBatch(char* tagNames[], TagData * pTagData, long nCount)
{
	int nRet = -1;
	try
	{
		LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugDebug, "GetRTDataByBatch, try to read datapoint count: %d", nCount);
		nRet = m_GetRTDataByBatch(tagNames, pTagData, nCount);
		LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugDebug, "GetRTDataByBatch, return: %d", nRet);
	}
	catch (...)
	{
		printf("error\n");
	}
	return nRet;
}