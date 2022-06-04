#ifndef __lexer__
#define __lexer__

#include <iostream>
#include <fstream>
#include <string>

#include "handler.hxx"
#include "hierarchy_list.hxx"

using std::fstream;
using std::string;
using std::getline;
using std::shared_ptr;

namespace MyPascal {
	class Lexer : public Handler {
	private:
		int space_counter(const string& estring);
		string space_remover(const string& estring);
	public:
		Lexer() {}
	  HList form_list(const string& _path);
		void process(shared_ptr<Data> _data) override;
	};
}

#endif
