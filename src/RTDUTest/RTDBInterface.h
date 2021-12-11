
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the RTDBINTERFACE_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// RTDBINTERFACE_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef RTDBINTERFACE_EXPORTS
#define RTDBINTERFACE_API __declspec(dllexport)
#else
#define RTDBINTERFACE_API __declspec(dllimport)
#endif

// This class is exported from the RTDBInterface.dll
class RTDBINTERFACE_API CRTDBInterface {
public:
	CRTDBInterface(void);
	// TODO: add your methods here.
};


RTDBINTERFACE_API int InitConnect(char* strParameters[],long nCount);

RTDBINTERFACE_API int ReleaseConnect();

//��������:����ʵʱ���ݲ�ѯ
RTDBINTERFACE_API int GetRTDataByTagName(const char* tagName,TagData * pTagData );

//��������:����ʵʱ���ݲ�ѯ
RTDBINTERFACE_API int GetRTDataByBatch(char* tagNames[],TagData * pTagData,long nCount);

//��������:���ԭʼ���ݲ�ѯ
RTDBINTERFACE_API int GetRawDataByTagName(ReadHiDataRequest * pReadHiDataRequest, TagData * & pTagData,long * nCount);

//��������:���������ݲ�ѯ
RTDBINTERFACE_API int GetSnapshotDataByTagName(ReadHiDataRequest * pReadHiDataRequest, TagData *  pTagData);

//��������:���ͳ�����ݲ�ѯ
RTDBINTERFACE_API int GetAggregationDataByTagName(ReadHiDataRequest * pReadHiDataRequest, TagData * pTagData);

//��������:��ʷʱ�����ݲ�ѯ
RTDBINTERFACE_API int GetHistoryDataByTime(const char * tagName,long time, TagData *pTagData);

//��������:������ʷʱ�����ݲ�ѯ
RTDBINTERFACE_API int GetHisTimeDataByBatch(char* tagNames[],long time,TagData * pTagData,long nCount);

//��������:������Ϣ��ѯ
RTDBINTERFACE_API int GetTagInfoByTagName(char* tagName,TagInfo *pTagInfo);

//��������:������Ϣ��ѯ
RTDBINTERFACE_API int GetTagInfoByBatch(char* tagName[],TagInfo *pTagInfo,long nCount);

//��������:��������д�빦��
RTDBINTERFACE_API int AppendRTTagDataByTagName(InsertData *pInsertData);

//��������:��������д�빦��
RTDBINTERFACE_API int AppendRTTagDataByBatch(InsertData *pInsertData,int nCount);

//��������:�ͷź����з�����ڴ�
RTDBINTERFACE_API int RTDBFreePointer(void *p);

RTDBINTERFACE_API int SetDebug(int nDebug);

//��������:����DLL�Ļ��湦��
RTDBINTERFACE_API int SetCache(int nCache);

//��������:���DLL�Ļ�������
RTDBINTERFACE_API int ClearCache();

//��������:��ȡ���е���Ϣ
RTDBINTERFACE_API int GetNextTagsInfo(long beginPos,TagInfo *pTagInfo,long &nCount);

//��������:������ʷʱ�����ݲ�ѯ
RTDBINTERFACE_API int GetHisTimeDataByBatch(char* tagNames[],long time,TagData * pTagData,long nCount);

// �޹��������ľۺϺ���
RTDBINTERFACE_API int GetSummary(const char* tagName, long timeStart, long timeEnd, int valueType,TagData * pTagData);

// ��������ֵ���������ľۺϺ���
RTDBINTERFACE_API int GetSummaryFilter(const char* tagName, long timeStart, long timeEnd, int valueType,const char* tagNameFilter, double limitLower, double limitUpper, int modeFilter,TagData * pTagData);

// ���ʽ���������µľۺϺ���
RTDBINTERFACE_API int GetSummaryFilterEX(const char* tagName, long timeStart, long timeEnd, int valueType, char* expression,TagData * pTagData);

//��������:��ȡ�̶���������(�ؼ����ݲ�ѯ)
RTDBINTERFACE_API int GetMainDataByTagName(ReadHiDataRequest * pReadHiDataRequest, long nDataNum,TagData *  pTagData);

//��������:�������ѯ
RTDBINTERFACE_API int QueryTagInfo(const char* tagName,const char* tagDesc,TagInfo *pTagInfo,long &nCount);




