#if !defined(AFX_FUNCTIONENTRY_H__C18B1889_31F5_4E0C_A713_CF7BBD70FCED__INCLUDED_)
#define AFX_FUNCTIONENTRY_H__C18B1889_31F5_4E0C_A713_CF7BBD70FCED__INCLUDED_

#include <string>

  /**
	* FUNCTION_ENTRY
	*
	* Used to log the entry into a member function of a class.
	*
	* @param functname  The name of the function.
	*/
#define FUNCTION_ENTRY(functname) TA_Base_Core::FunctionEntry fe(functname, __FILE__, __LINE__)


	/**
	  * FUNCTION_EXIT
	  *
	  * Used to log the exit of a function.
	  */
#define FUNCTION_EXIT fe.setExitLine(__LINE__);


namespace TA_Base_Core
{

	class FunctionEntry
	{
	public:

		/**
		  * Constructor
		  *
		  * @param functName  The name of the function
		  * @param file       The file name (supplied by FUNCTION_ENTRY)
		  * @param line       The line number (supplied by FUNCTION_ENTRY)
		  *
		  */
		FunctionEntry(const char* functName, char* file, int line);

		/**
		  * Destructor
		  */
		virtual ~FunctionEntry();

		/**
		  * setExitLine
		  *
		  * Sets the line number to be displayed in the FunctionExit LOG
		  * message. Called by the FUNCTION_EXIT macro.
		  *
		  * @param line  The line number where the function will exit from.
		  */
		void setExitLine(int line)
		{
			m_line = line;
		}

	private:

		unsigned int m_line;        // The line number
		std::string m_file;         // The filename
		std::string m_functName;    // The function name
	};

} // namespace TA_Base_Core

#endif // !defined(AFX_FUNCTIONENTRY_H__C18B1889_31F5_4E0C_A713_CF7BBD70FCED__INCLUDED_)
