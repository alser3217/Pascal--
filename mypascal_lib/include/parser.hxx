#ifndef __PARSER__
#define __PARSER__

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>
#include <queue>

#include "handler.hxx"
#include "hierarchy_list.hxx"
#include "exception.hxx"

using std::vector;
using std::string;
using std::tolower;
using std::remove;
using std::find;
using std::regex;
using std::regex_match;
using std::queue;
using std::shared_ptr;

namespace MyPascal {

	class Parser : public Handler {
	private:

		vector<string> split(const string& estring) const;
		string to_lowercase(const string& estring) const;
		string remove_parentheses(const string& estring);

		Exception init_type(HLink* elink);

		Exception level0_analyze(const string& estring);
		Exception analyze(const string& estring, Type type);
		Type analyze_type(const string& estring);

		bool parentheses_match(const string& estring);
		Exception traversal(HLink* elink);
	public:
		Exception check_syntax(HList elist);
		void process(shared_ptr<Data> edata) override;
	};
}	

#endif
