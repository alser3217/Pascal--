
#include "executor.hxx"

vector<string> MyPascal::Executor::split(const string& estring) const {
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

vector<string> MyPascal::Executor::assign_split(const string& estring) const {
  string estringcopy(estring);
  string expression;
  vector<string> result;
  string delimiter = ":=";
  string token;
  size_t pos = 0;
  while ((pos = estringcopy.find(delimiter)) != string::npos) {
    token = estringcopy.substr(0, pos);
    token.pop_back();
    result.push_back(token);
    estringcopy.erase(0, pos + delimiter.length());
  }

  pos = estringcopy.find_first_not_of(" ");
  expression = estringcopy.substr(pos);
  expression.pop_back();


  result.push_back(expression);

  return result;
}

string MyPascal::Executor::free_of_paranthesis(const string& estring) const {
  string result(estring);

  if (result[0] == '(') {
    int pos = estring.find_first_not_of("(");
    result = estring.substr(pos);
  }

  if (result[result.size() - 1] == ')')
    result.pop_back();

  return result;
}

bool MyPascal::Executor::compare(const string& estring, HashTable* etable, Exception& ex) const {

  vector<string> vec = split(estring);
  int value = 0;
  double left, right;

  map<string, int> mp = { {">", 1}, {"<", 2}, {"=", 3}, {">=", 4}, {"<=", 5}};

  for (const auto& kv : mp)
    if (vec[1] == kv.first) {
      value = kv.second;
      break;
    }

  try {
    left = stod(vec[0]);
  }
  catch (...) {
    Variable* var = etable->findobj(vec[0]);
    if (var == nullptr)
      ex = Exception(3);
    else
      left = var->get_value();
  }

  try {
    right = stod(vec[2]);
  }
  catch (...) {
    Variable* var = etable->findobj(vec[2]);
    if (var == nullptr)
      ex = Exception(3);
    else
      right = var->get_value();
  }

  if (ex.get_code() != 2) {
    switch (value) {
      case 1: {
        if (left > right)
          return true;
        else
          return false;
        break;
      }

      case 2: {
        if (left < right)
          return true;
        else
          return false;
        break;
      }

      case 3: {
        if (left = right)
          return true;
        else
          return false;
        break;
      }
    }
  }
  else
    return false;
}

string MyPascal::Executor::writestr(const string& estring) {
  pair<int, int> brackets;
  string estringcopy(estring);
  string delimiter = "'";

  brackets.first = estringcopy.find(delimiter);
  estringcopy.erase(0, brackets.first + delimiter.length());
  brackets.second = estringcopy.find(delimiter);

  return estring.substr(brackets.first + 1, brackets.second);

}

deque<string> MyPascal::Executor::writevar(const string& estring) {
  string estringcopy(estring);
  deque<string> result;
  string delimiter = ", ";
  string token;
  size_t pos = 0;
  while ((pos = estringcopy.find(delimiter)) != string::npos) {
    token = estringcopy.substr(0, pos);
    result.push_back(token);
    estringcopy.erase(0, pos + delimiter.length());
  }

  result.push_back(estringcopy);

  result.pop_front();

  return result;
}

string MyPascal::Executor::readstr(const string& estring) {
  string estringcopy(estring);
  string delimiter = "(";
  string res;
  string token;
  size_t pos = 0;
  pos = estringcopy.find(delimiter);
  estringcopy.erase(0, pos + delimiter.length());
  while ((pos = estringcopy.find(delimiter)) != string::npos) {
    token = estringcopy.substr(0, pos);
    res += token;
    estringcopy.erase(0, pos + delimiter.length());
  }

  estringcopy.pop_back();
  estringcopy.pop_back();

  res += estringcopy;

  return res;
}

deque<string> MyPascal::Executor::readvar(const string& estring) {
  string estringcopy(estring);
  deque<string> result;
  string delimiter = ", ";
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

MyPascal::Exception MyPascal::Executor::perfom(HLink* elink, HashTable* etable, int& current, bool& res) {
  current = elink->data.get_lnumber();
  Type etype = elink->data.get_type();
  if (etype == Type::WRITE) {
    string str = writestr(elink->data.get_data());
    deque<string> deq;
    cout << str << endl;
    str = readstr(elink->data.get_data());
    deq = writevar(str);
      for (auto& i : deq) {
        double value = etable->find(i);
        if (value != DBL_MAX)
          cout << value << endl;
        else
          return Exception(3);
      }

    return Exception(0);
  } 

  else if (etype == Type::READ) {
    string str;
    deque<string> deq;
    str = readstr(elink->data.get_data());
    deq = readvar(str);
    for (auto& i : deq) {
      double tmp;
      Variable* var = etable->findobj(i);
      if (var != nullptr) {
        cin >> tmp;
        var->set_value(tmp);
      }
      else
        return Exception(3);
    }
  }

  else if (etype == Type::ASSIGN) {
    double res;
    vector<double> values;
    TPostfix postfix;
    vector<string> vec = assign_split(elink->data.get_data());
    vector<string> d_infix;
    string assign = vec[0];
    string infix = vec[1];
    postfix.set_infix(infix);
    d_infix = split(infix);
    for (auto& i : d_infix)
      i = free_of_paranthesis(i);
    for (int i = 0; i < d_infix.size(); i += 2) {
      double value;
      try {
        value = stod(d_infix[i]);
      }
      catch (...) {
        Variable* var = etable->findobj(d_infix[i]);
        if (var == nullptr)
          return Exception(3);
        value = var->get_value();
      }
      values.push_back(value);
    }
    Variable* var = etable->findobj(assign);
    if (var == nullptr)
      return Exception(3);
    res = postfix.calculate(values);

    var->set_value(res);
  }

  else if (etype == Type::IF) {
    bool result;
    Exception ex(0);
    vector<string> vec = split(elink->data.get_data());

    string expression = vec[1] + " " + vec[2] + " " + vec[3];
    expression = free_of_paranthesis(expression);
    result = compare(expression, etable, ex);
    if (ex.get_code() == 2)
      return Exception(3);
    if (result) {
      res = false;
      perfom(elink->next->down, etable, current, res);
    }
    else {
      res = true;
      perfom(elink->next->next, etable, current, res);
    }
  }
  else if (etype == Type::ELSE) {
    if (res)
      perfom(elink->next->down, etable, current, res);
    else
      perfom(elink->next->next, etable, current, res);
  }

  return Exception(0);
}

void MyPascal::Executor::process(shared_ptr<Data> edata) {

  Exception ex;

	ex = proceed(edata->list.get_head(), edata->table);
  if (ex.get_code()) {
    ex.info();
    return;
  }
}

MyPascal::Exception MyPascal::Executor::proceed(HLink* elink, HashTable etable) {
  HLink* curr = elink;
  bool result = false;
  stack<HLink*> st;
  queue<HLink*> st2;
  while (curr != nullptr) {
    if (curr->data.get_data() == "begin")
      break;
    curr = curr->next;
  }
  while (curr != nullptr || !st.empty())
  {
    while (curr != nullptr)
    {
      st.push(curr);
      st2.push(curr);
      curr = curr->down;
    }

    curr = st.top();
    st.pop();

    curr = curr->next;
  }

  int current = st2.front()->data.get_lnumber();
  int line = st2.front()->data.get_lnumber();

  while (!st2.empty()) {
    int difference = current - line;
    if (difference > 0) {
      for (int i = 0; i < difference; ++i)
        st2.pop();
      current = line;
    }
    Exception ex;
    ex = perfom(st2.front(), &etable, current, result);
    if (ex.get_code())
      return Exception(ex.get_code(), current);
    line = st2.front()->data.get_lnumber();
    st2.pop();
  }

  return Exception(0);
}