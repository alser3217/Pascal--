
#include "lexer.hxx"

int MyPascal::Lexer::space_counter(const string& edata) {
	int counter = 0;
	while (edata[counter] == ' ')
		counter++;

	return counter;
}

string MyPascal::Lexer::space_remover(const string& edata) {
	string result(edata);
	size_t pos;
	pos = result.find_first_not_of(' ');

	return result.substr(pos, result.size() - pos);
}

MyPascal::HList MyPascal::Lexer::form_list(const string& path) {
	fstream file;
	HList result;
	int current_number = 1;
	string tmp;
	int current_level = 0;
	int cscounter = 0;
	file.open(path);
	if (!file)
		throw "Can't open file.";
	while (!file.eof()) {
		getline(file, tmp);
		int scounter = space_counter(tmp);
		if (scounter == cscounter)
			result.insert_next(HString(space_remover(tmp), current_level, current_number));
		else if (scounter > cscounter) {
			current_level++;
			result.insert_down(HString(space_remover(tmp), current_level, current_number));
		}
		else if (scounter < cscounter) {
			result.pop();
			current_level--;
			result.insert_next(HString(space_remover(tmp), current_level, current_number));
		}
		cscounter = scounter;
		current_number++;
	}
	file.close();

	return result;
}

void MyPascal::Lexer::process(shared_ptr<MyPascal::Data> _data) {
	_data->list = form_list(_data->path);

	Handler::process(_data);
}
	