#ifndef __COMPILER__
#define __COMPILER__

#include <iostream>
#include <regex>

#include "handler.hxx"
#include "hierarchy_list.hxx"

using std::vector;
using std::string;
using std::regex;
using std::regex_search;
using std::cmatch;
using std::stod;

namespace MyPascal {
	class Compiler : public Handler {
	public:

		HashTable form_table(HLink* elink);

		vector<string> get_names(const string& estring);
		vType get_type(const string& estring);	
		double get_values(const string& estring);

		void process(std::shared_ptr<Data> _data) override;
	};
}

#endif
