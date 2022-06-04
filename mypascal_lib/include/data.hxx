#include <string>

#include "hierarchy_list.hxx"
#include "hash_table.hxx"
#include "variable.hxx"

namespace MyPascal {
	class Data {
		std::string path;
	private:
		HList list;
		HashTable table;
	public:
		Data(std::string _path) : path(_path), list(), table() {}

		friend class Handler;
		friend class Lexer;
		friend class Parser;
		friend class Compiler;
		friend class Executor;
	};
}
