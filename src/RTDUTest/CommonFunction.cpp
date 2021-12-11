#include "CommonFunction.h"
#include <sstream>


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

char** CommonFunction::vector2StringArray(std::vector<std::string>& svec)
{
	char ** parr = new char*[svec.size()];

	//convert vector to string array
	int i = 0;
	for (std::vector<std::string>::iterator it = svec.begin(); it < svec.end(); it++, i++)
	{
		int strLen = (*it).size() + 1;
		char *p = new char(strLen);
		strcpy_s(p, strLen, (*it).c_str());		//don't use sizeof(p) or sizeof(*p), it will return 4 or 1
		parr[i] = p;
	}

	return parr;
}