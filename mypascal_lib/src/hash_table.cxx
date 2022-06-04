
#include "hash_table.hxx"

int MyPascal::hash(const string& key, int size) {
	int result = 0;
	for (int i = 0; i < key.size(); ++i)
		result += key[i];

	return result % size;
}

double MyPascal::HashTable::find(const string& ekey) {
	int key = hash(ekey, data.size());

	for (auto& i : data[key])
		if (i.get_name() == ekey)
			return i.get_value();

	return DBL_MAX;
}

MyPascal::Variable* MyPascal::HashTable::findobj(const string& ekey) {
	int key = hash(ekey, data.size());

	for (auto& i : data[key])
		if (i.get_name() == ekey)
			return &i;

	return nullptr;

}

bool MyPascal::HashTable::insert(Variable& evar) {
	int pos = 0;
	int key = hash(evar.get_name(), data.size()); // const get_name();

	if (size == data.size())
		return false;

	if (find(evar.get_name()) != DBL_MAX)
		return false;

	data[key].push_front(evar);
	size++;

	return true;
}
