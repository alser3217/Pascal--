#ifndef __EXCEPTION__
#define __EXCEPTION__

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::to_string;

namespace MyPascal {
	class Exception {
		size_t code;
		size_t line;
	public:
		Exception(size_t ecode = 0, size_t eline = 0) : code(ecode), line(eline) {}
		void info();

		size_t get_code() { return code; }
	};
}

#endif
