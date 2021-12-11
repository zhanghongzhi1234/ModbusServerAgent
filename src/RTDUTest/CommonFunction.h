#pragma once
#include <string>
#include <vector>

class CommonFunction
{
public:
	CommonFunction();
	~CommonFunction();

public:
	static void tokenize(std::string const & str, const char delim, std::vector<std::string> &out);

	//need delete [] returnpoint after use this function to release memory
	static char** vector2StringArray(std::vector<std::string>& svec);
};

