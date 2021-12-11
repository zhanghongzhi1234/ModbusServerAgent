#ifndef VESTORE__INCLUDED_
#define VESTORE__INCLUDED_

#include "RTDBDefine.h"
#include "afxmt.h"
#include <string>


class VeStore
{
public:
	VeStore();
	~VeStore();

	int initConnect(std::string dllPath, std::string iniPath);
	int getRTDataByBatch(char* tagNames[], TagData * pTagData, long nCount);

private:

	HINSTANCE hInst;
};

#endif