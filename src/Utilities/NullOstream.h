#ifndef NULL_OSTREAM_H
#define NULL_OSTREAM_H

#include <iostream>
  //#include <streambuf>
using std::streambuf;

using std::ostream;

namespace TA_Base_Core
{
	class NullStreamBuf : public streambuf
	{
	public:
		NullStreamBuf() : streambuf() {}
		virtual ~NullStreamBuf() {}

		void	put_buffer(void) {};
		void	put_char(int) {};
	};


	class NullOstream : public ostream
	{
	public:
		NullOstream() : ostream(new NullStreamBuf()) {}
		virtual ~NullOstream() {}
	};
};

#endif // NULL_OSTREAM_H
