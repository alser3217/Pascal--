#ifndef __HIERARCHY_LIST__
#define __HIERARCHY_LIST__

#include <string>
#include <stack>
#include <fstream>
#include <iostream>
#include <functional>


using std::stack;
using std::ostream;
using std::string;
using std::cout;
using std::endl;
using std::function;

namespace MyPascal {

	enum class Type { IF, BEGIN, ELSE, END, VAR, CONST, LEND, READ, WRITE, PROGRAM, INITV, INITC, ASSIGN, UNKNOWN};

	class HString {
		string data;
		size_t level;
		size_t lnumber;
		Type type;

	public:
		HString (string edata = string(), size_t elevel = -1, size_t elnumber = -1, Type etype = Type::UNKNOWN) :
			                                                                        data(edata),
			                                                                        level(elevel), 
			                                                                        lnumber(elnumber),
		                                                                          type(etype) {}

		string get_data() { return data; }
		size_t get_level() { return level; }
		size_t get_lnumber() { return lnumber; }
		Type get_type() { return type; }
		void set_type(Type etype) { type = etype; }


		friend struct HLink;
		friend class HList;
	};

	struct HLink {
		HLink* next;
		HLink* down;
		HString data;
	public:
		HLink(HString edata = HString()) : next(nullptr), down(nullptr), data(edata){}
		friend class HList;
    
		HString get_data() { return data; }
	};

	class HList {
		HLink* head;
		HLink* current;
		stack<HLink*> path;
	public:
		HList() : head(nullptr), current(nullptr) {}
		void insert_next(const HString edata);
		void insert_down(const HString edata);
		void pop();

		//bool traversal(HLink* elink, bool (*func)(const string&));

		HLink* get_head() { return head; }
	};
}

#endif
