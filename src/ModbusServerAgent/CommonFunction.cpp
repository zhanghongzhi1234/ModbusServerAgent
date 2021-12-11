#include "CommonFunction.h"
#include <sstream>
#include <fstream>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

CommonFunction::CommonFunction()
{
}


CommonFunction::~CommonFunction()
{
}

void CommonFunction::tokenize(std::string const & str, const char delim, std::vector<std::string> &out)
{
	std::stringstream ss(str);
	std::string s;
	while (std::getline(ss, s, delim)) {
		out.push_back(s);
	}
}

char** CommonFunction::vector2StringArray(const std::vector<std::string>& svec)
{
	char ** parr = new char*[svec.size()];

	//convert vector to string array
	int i = 0;
	for (std::vector<std::string>::const_iterator it = svec.begin(); it < svec.end(); it++, i++)
	{
		int strLen = (*it).size() + 1;
		char *p = new char(strLen);
		strcpy_s(p, strLen, (*it).c_str());		//don't use sizeof(p) or sizeof(*p), it will return 4 or 1
		parr[i] = p;
	}

	return parr;
}

bool CommonFunction::readFileToVectorString(std::string fileName, vector<string>& vecStr)
{
	ifstream file(fileName.c_str()); //打开文件用于读
	if (!file.is_open())
	{
		return false;
	}

	string line;
	while (getline(file, line)) //如果未到文件的末尾就一直循环读
	{
		vecStr.push_back(line.c_str());
	}

	return true;
}

std::vector<std::string> CommonFunction::stringToVector(const std::string& strSrc, const std::string delimiter)
{
	std::vector<std::string> vecStr;
	boost::split(vecStr, strSrc, boost::is_any_of(delimiter), boost::token_compress_on);
	return vecStr;
}