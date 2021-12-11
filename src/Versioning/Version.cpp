#include "Version.h"
#include <boost/algorithm/string.hpp>
#include "SimpleIni.h" // TODO: <boost/property_tree/ini_parser.hpp>
#include <iostream>

namespace TA_Base_Core
{
	// These variables are all declared external so they
	// will be picked up on link time with individual applications
	/*extern char buildVersion[];
	extern char buildDate[];
	extern char componentName[];
	extern char componentVersion[];
	extern int libraryArraySize;
	extern char* libraryArray[];
	extern int headerArraySize;
	extern char* headerArray[];
	extern int otherArraySize;
	extern char* otherArray[];*/

	/**
	  * displayVersionInfo()
	  *
	  * This is a static method that will print out versionInformation to stdout.
	  */
	void Version::displayVersionInfo()
	{
		std::cout << std::endl;
		// Print out all the details relevant to this particular application
		std::cout << "Release Number:\t\t" << "1.0.0" << std::endl;
	}

	void Version::checkCommandLine(int argc, char* argv[])
	{
		if (argc == 2)
		{
			if (boost::iequals(argv[1], "--version"))
			{
				displayVersionInfo();
				exit(0);
			}
		}
	}
}
