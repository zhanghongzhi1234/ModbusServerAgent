#if !defined(AFX_BaseException_H__E2DE1FE6_479C_11D7_B150_0080C8E32E69__INCLUDED_)
#define AFX_BaseException_H__E2DE1FE6_479C_11D7_B150_0080C8E32E69__INCLUDED_

#include <exception>
#include <string>
#include <memory>

  /**
	* TA_THROW
	*
	* This macro throws exceptions while providing logging. It takes the
	* place of the throw keyword, and is used identically.
	* eg: TA_THROW(CCTVException("A CCTV error occurred"));
	*
	* @param exc  The exception (with parameters) to throw
	*/
#define TA_THROW(exc)															\
{																				\
	LOG(SourceInfo,																\
		TA_Base_Core::DebugUtil::ExceptionConstruction,				\
		std::string(#exc).substr(0, (std::string(#exc).find("("))).c_str(),		\
		exc.what());															\
	throw exc;																	\
}


namespace TA_Base_Core
{
	class BaseException : public std::exception
	{
	public:
		BaseException() throw();
		BaseException(const std::string& msg) throw();
		virtual const char* what() const throw();
		virtual ~BaseException() throw();

	protected:
		// Description of the reason for the exception.  It is protected (rather than
		// private) so that derived classes can build the message in their constructor
		// after the member initialisation list.
		std::string m_msg;
	};
}

#endif // !defined(AFX_BaseException_H__E2DE1FE6_479C_11D7_B150_0080C8E32E69__INCLUDED_)

