
#include "parser.hxx"

vector<string> MyPascal::Parser::split(const string& estring) const {
  string estringcopy(estring);
  vector<string> result;
  string delimiter = " ";
  string token;
  size_t pos = 0;
  while ((pos = estringcopy.find(delimiter)) != string::npos) {
    token = estringcopy.substr(0, pos);
    result.push_back(token);
    estringcopy.erase(0, pos + delimiter.length());
  }

  result.push_back(estringcopy);

  return result;
}

string MyPascal::Parser::to_lowercase(const string& estring) const{
  string result(estring);
  for (auto& i : result)
    i = tolower(i);

  return result;
}

string MyPascal::Parser::remove_parentheses(const string& estring) { // not done.
  string result(estring);
  result.erase(remove(result.begin(), result.end(), '('), result.end());
  result.erase(remove(result.begin(), result.end(), ')'), result.end());

  return result;
}

bool MyPascal::Parser::parentheses_match(const string& estring) {
  size_t index = 0;
  int lparenthesis = 0, rparenthesis = 0;
  while ((index = estring.find("(", index)) != std::string::npos) {
    lparenthesis++;
    index++;
  }

  index = 0;

  while ((index = estring.find(")", index)) != std::string::npos) {
    rparenthesis++;
    index++;
  }

  return lparenthesis == rparenthesis;
}

MyPascal::Exception MyPascal::Parser::check_syntax(HList elist) {
  
  Exception ex;
  ex = init_type(elist.get_head());
  ex = traversal(elist.get_head());

  return ex;
}

void MyPascal::Parser::process(std::shared_ptr<Data> _data) {
  Exception ex;

  ex = check_syntax(_data->list);
  if (ex.get_code()) {
    ex.info();
    return;
  }

	Handler::process(_data);
}

MyPascal::Exception MyPascal::Parser::level0_analyze(const string& estring) {
  regex reference("(var|const|program|begin|end.)", std::regex_constants::icase);

  if (regex_match(estring.c_str(), reference))
    return Exception(0);
  else
    return Exception(2);
}

MyPascal::Exception MyPascal::Parser::analyze(const string& estring, Type type) {
  bool result = false;
  regex program("(program)(\\s)([A-Z])([\\w]*)(;)", std::regex_constants::icase);
  regex begin("(begin)", std::regex_constants::icase);
  regex end("(end)", std::regex_constants::icase);
  regex rconst("(const)", std::regex_constants::icase);
  regex var("(var)", std::regex_constants::icase);
  regex lend("(end.)", std::regex_constants::icase);
  regex relse("(else)", std::regex_constants::icase);
  regex rif("(if)\\s*[\\( \\) a-zA-Z0-9-+\\*\\/=><]*(then)");
  regex write("(write)\\s*(\\('.*')((, )?[a-zA-Z0-9])*\\);", std::regex_constants::icase);
  regex read("(read) \\([\\w]*\\);", std::regex_constants::icase);
  regex assign(".*:=.*;", std::regex_constants::icase);
  regex initc("([a-zA-Z])[\\w]*:\\s*(double|integer)\\s*=\\s*-?[0-9]*\\.?[0-9]*;", std::regex_constants::icase);
  regex initv("^[a-zA-Z][\\w, ]*:\\s*(integer|double);", std::regex_constants::icase);

  if (type == Type::PROGRAM)
    result = regex_match(estring.c_str(), program);
  else if (type == Type::BEGIN)
    result = regex_match(estring.c_str(), begin);
  else if (type == Type::CONST)
    result = regex_match(estring.c_str(), rconst);
  else if (type == Type::VAR)
    result = regex_match(estring.c_str(), var);
  else if (type == Type::LEND)
    result = regex_match(estring.c_str(), lend);
  else if (type == Type::END)
    result = regex_match(estring.c_str(), end);
  else if (type == Type::INITC)
    result = regex_match(estring.c_str(), initc);
  else if (type == Type::INITV)
    result = regex_match(estring.c_str(), initv);
  else if (type == Type::IF)
    result = regex_match(estring.c_str(), rif);
  else if (type == Type::ELSE)
    result = regex_match(estring.c_str(), relse);
  else if (type == Type::ASSIGN)
    result = regex_match(estring.c_str(), assign);
  else if (type == Type::WRITE)
    result = regex_match(estring.c_str(), write);
  else if (type == Type::READ)
    result = regex_match(estring.c_str(), read);

  if (result)
    return Exception(0);
  else
    return Exception(2);  
}

MyPascal::Exception MyPascal::Parser::traversal(HLink* elink) {
  int beginend = 0;
  stack<HLink*> st;
  vector<string> vec;
	HLink* curr = elink;
  size_t code = 0;
  Exception ex;
  Type type = Type::UNKNOWN;

  if (curr->down != nullptr)
    return Exception(2);

  while (curr != nullptr) {
    vector<string> tmp = split(curr->data.get_data());
    vec.push_back(tmp[0]);
    curr = curr->next;
  }

  if (vec.size() < 3)
    return Exception(1); //
  if (find(vec.begin(), vec.end(), "begin") == vec.end()) // no begin found.
    return Exception(6);
  if (find(vec.begin(), vec.end(), "program") == vec.end()) // no program found.
    return Exception(5);
  if (find(vec.begin(), vec.end(), "end.") == vec.end()) // no end. found.
    return Exception(7);

  for (auto& i : vec) {
    size_t code;
    if (code = level0_analyze(i).get_code())
      return Exception(code);
  }

  curr = elink;
	while (curr != nullptr || !st.empty())
	{
		while (curr != nullptr)
		{
		  st.push(curr);
			curr = curr->down;
		}

		curr = st.top();
		st.pop();  
    if (curr->data.get_data() == "begin" || curr->data.get_data() == "end")
      beginend++;
    if (!parentheses_match(curr->data.get_data()))
      return Exception(4, curr->data.get_lnumber());
    ex = analyze(curr->data.get_data(), curr->data.get_type());
    if (ex.get_code())
      return Exception(ex.get_code(), curr->data.get_lnumber());
		curr = curr->next;
	}
  if ((beginend - 1) % 2 != 0)
    return Exception(2);

  return Exception(0);
}

MyPascal::Type MyPascal::Parser::analyze_type(const string& estring) {
  vector<string> vec = split(to_lowercase(estring));
  string first_token = vec[0];
  string second_token;
  if (vec.size() > 1)
    second_token = vec[1];

  if (first_token == "program")
    return Type::PROGRAM;
  else if (first_token == "begin")
    return Type::BEGIN;
  else if (first_token == "end")
    return Type::END;
  else if (first_token == "end.")
    return Type::LEND;
  else if (first_token == "if")
    return Type::IF;
  else if (first_token == "else")
    return Type::ELSE;
  else if (first_token == "write")
    return Type::WRITE;
  else if (first_token == "read")
    return Type::READ;
  else if (first_token == "const")
    return Type::CONST;
  else if (first_token == "var")
    return Type::VAR;
  else if (second_token == ":=")
    return Type::ASSIGN;
  else
    return Type::UNKNOWN;
}

MyPascal::Exception MyPascal::Parser::init_type(HLink* elink) {
  HLink* curr = elink;
  stack<HLink*> st;
  Type type = Type::UNKNOWN;

  while (curr != nullptr) {
    if (to_lowercase(curr->data.get_data()) == "const") {
      HLink* tmp = curr->down;
      if (tmp == nullptr)
        return Exception(2);
      else
        while (tmp != nullptr) {
          tmp->data.set_type(Type::INITC);
          tmp = tmp->next;
        }
      break;
    }
    curr = curr->next;
  }
  curr = elink;
  while (curr != nullptr) {
    if (to_lowercase(curr->data.get_data()) == "var") {
      HLink* tmp = curr->down;
      if (tmp == nullptr)
        return Exception(2);
      else
        while (tmp != nullptr) {
          tmp->data.set_type(Type::INITV);
          tmp = tmp->next;
        }
      break;
    }
    curr = curr->next;
  }

  curr = elink;

  while (curr != nullptr || !st.empty())
  {
    while (curr != nullptr)
    {
      st.push(curr);
      curr = curr->down;
    }
    curr = st.top();
    st.pop();
    if (curr->data.get_type() == Type::UNKNOWN) {
      type = analyze_type(curr->data.get_data());
      if (type != Type::UNKNOWN)
        curr->data.set_type(type);
      else
        return Exception(2, curr->data.get_lnumber());
    }

    curr = curr->next;
  }

  return Exception(0);
}
