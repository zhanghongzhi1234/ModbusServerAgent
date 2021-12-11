#pragma once
#include <string>
#include <vector>

using namespace std;

class CommonFunction
{
public:
	CommonFunction();
	~CommonFunction();

public:
	static void tokenize(std::string const & str, const char delim, std::vector<std::string> &out);

	//need delete [] returnpoint after use this function to release memory
	static char** vector2StringArray(const std::vector<std::string>& svec);

	static bool readFileToVectorString(std::string fileName, vector<string>& vecStr);

	static std::vector<std::string> stringToVector(const std::string& strSrc, const std::string delimiter);
};

