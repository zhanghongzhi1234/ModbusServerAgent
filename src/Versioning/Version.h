#ifndef VERSION_H
#define VERSION_H

namespace TA_Base_Core
{
	class Version
	{
	public:

		/**
		  * displayVersionInfo()
		  *
		  * This is a static method that will print out versionInformation to stdout.
		  */
		static void displayVersionInfo();
		static void checkCommandLine(int argc, char* argv[]);
	};
}

#endif //#ifndef VERSION_H
