
#include "compiler.hxx"

void MyPascal::Compiler::process(std::shared_ptr<MyPascal::Data> _data) {

  _data->table = form_table(_data->list.get_head());
	Handler::process(_data);
}

vector<string> MyPascal::Compiler::get_names(const string& estring) {
  string estringcopy(estring);
  vector<string> result;
  string delimiter = ", ";
  string token;
  size_t pos = 0;

  pos = estring.find(":");
  estringcopy.erase(pos, estringcopy.size() - 1);


  while ((pos = estringcopy.find(delimiter)) != string::npos) {
    token = estringcopy.substr(0, pos);
    result.push_back(token);
    estringcopy.erase(0, pos + delimiter.length());
  }

  result.push_back(estringcopy);

  return result;
}

MyPascal::vType MyPascal::Compiler::get_type(const string& estring) {
  regex i("(integer)");

  if (regex_search(estring.c_str(), i))
    return vType::INTEGER;
  else
    return vType::DOUBLE;
}

double MyPascal::Compiler::get_values(const string& estring) {
  regex val("[+-]?([0-9]*[.])?[0-9]+");
  cmatch match;
  double result;
  regex_search(estring.c_str(), match, val);

  result = stod(match[0]);

  return result;
}

MyPascal::HashTable MyPascal::Compiler::form_table(HLink* elink) {
	HashTable result;
  HLink* curr = elink;
  stack<HLink*> st;

  while (curr != nullptr || !st.empty())
  {
    while (curr != nullptr)
    {
      st.push(curr);
      curr = curr->down;
    }
    curr = st.top();
    st.pop();
    if (curr->data.get_type() == Type::INITC) {
      vector<string> name = get_names(curr->data.get_data());
      double value = get_values(curr->data.get_data());
      vType type = get_type(curr->data.get_data());
      Variable var(name[0], value, type);

      result.insert(var);
    }

    if (curr->data.get_type() == Type::INITV) {
      vector<string> name = get_names(curr->data.get_data());
      vType type = get_type(curr->data.get_data());

      for (auto& i : name) {
        Variable var(i, 0, type);
        result.insert(var);
      }
    }

    curr = curr->next;
  }

  return result;
}