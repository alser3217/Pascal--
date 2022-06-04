#ifndef __EXECUTOR__
#define __EXECUTOR__

#include <iostream>
#include <stack>
#include <queue>
#include <utility>
#include <limits>
#include <deque>
#include <map>
#include <string>

#include "handler.hxx"
#include "hierarchy_list.hxx"
#include "exception.hxx"

using std::shared_ptr;
using std::cout;
using std::endl;
using std::stack;
using std::queue;
using std::pair;
using std::deque;
using std::cin;
using std::string;
using std::stod;
using std::map;

namespace MyPascal {

	class Executor : public Handler {

	private:
		Exception proceed(HLink* elink, HashTable etable);
		Exception perfom(HLink* elink, HashTable* etable, int& current, bool& res);

		vector<string> split(const string& estring) const;
		vector<string> assign_split(const string& estring) const;
		string free_of_paranthesis(const string& estring) const;

		string writestr(const string& estring);
		deque<string> writevar(const string& estring);

		string readstr(const string& estring);
		deque<string> readvar(const string& estring);

		bool compare(const string& estring, HashTable* etable, Exception& ex) const;

		public:
			void process(shared_ptr<Data> _data) override;

	};
}



#endif