#ifndef __HASH_TABLE__
#define __HASH_TABLE__

#include <vector>
#include <memory>
#include <list>
#include <limits>

#include "variable.hxx"

using std::shared_ptr;
using std::make_shared;
using std::vector;
using std::list;

namespace MyPascal {

	class HashTable {
		vector<list<Variable>> data;
		int size = 0;
	public:
		HashTable(int esize = 10) : data(esize) {}
		~HashTable() {}

		bool insert(Variable& evar);
		double find(const string& ekey);
		Variable* findobj(const string& ekey);
	};

	int hash(const string& key, int size);
}

#endif
