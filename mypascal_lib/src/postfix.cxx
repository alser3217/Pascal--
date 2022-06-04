
#include "postfix.hxx"

double calculate_function (double a, double b, string _operator) {
  double result;
  int value = 0;
  map<string, int> mp = { {"*", 1}, {"/", 2}, {"+", 3}, {"-", 4}, {"%", 5}};
  for (const auto& kv : mp)
    if (_operator == kv.first) {
      value = kv.second;
      break;
    }
  switch (value) {
    case 3: {
      result = a + b;
      break;
    }
    case 1: {
      result = a * b;
      break;
    }
    case 4: {
      result = a - b;
      break;
    }
    case 2: {
      result = a / b;
      break;
    }
    case 5: {
      result = (int)a % (int)b;
      break;
    }

  }
  return result;
}

int TPostfix::operands_counter() {
  int counter = 0;
  int postfix_size = postfix.size();
  string operations[5] = {"+", "-", "/", "*", "%"};
  for (int i = 0; i < postfix_size; i++) {
    for (string symbol : operations)
      if (postfix[i] == symbol) {
        counter++;
        break;
      }
  }
  return postfix_size - counter;
}

void TPostfix::set_infix (string _infix) {
  infix = _infix;
  postfix = to_postfix();
}

bool TPostfix::correct_input_check() {
  int counter = 0;
  vector<string> tmp(infix_divide());
  for (int i = 0; i < tmp.size(); i++)
    if (tmp[i] == "(" || tmp[i] == ")")
      counter++;
  if (!(counter % 2))
    return true;
  else
    return false;
}

string TPostfix::postfix_to_string() {
  string tmp;
  for (int i = 0; i < postfix.size(); i++)
    tmp += postfix[i];
  return tmp;
}

string TPostfix::get_postfix() {
  return postfix_to_string();
}

vector<string> TPostfix::infix_divide() {
  bool flag = false;
  string temp;
  vector<string> divided_infix;
  char operations[7] = {'+', '-', '/', '(', ')', '*', '%'};
  for (int i = 0; i < infix.size(); i++) {
    while (infix[i] == ' ')
     i++;
    flag = false;
    temp.clear();
    for (char symbol : operations)
      if (infix[i] == symbol) {
        flag = true;
        break;
      }
    if (flag) 
      temp.push_back(infix[i]);
    else {
      while (!flag && i < infix.size()) {
        if (infix[i] != ' ')
          temp.push_back(infix[i]);    
        i++;
        for (char symbol : operations) 
          if (infix[i] == symbol) {
            flag = true;
            break;
          }  
          if (flag)
            i--;
      }
    } 
    divided_infix.push_back(temp);
  }
  return divided_infix;
}

vector<string> TPostfix::to_postfix() {
  bool flag = true;
  bool flag_1 = true;;
  int status_infix;
  int status_operations;
  map<string, int> mp = { {"*", 1}, {"/", 1}, {"+", 0}, {"-", 0}, {"(", -1}, {")", -1}, {"%", 1}};
  stack<string> operations;
  vector<string> postfix_form;
  vector<string> divided_infix_form = infix_divide();
  for (int i = 0; i < divided_infix_form.size(); i++) {
    flag = true;
    flag_1 = true;
    for (const auto& kv : mp) {
      if (divided_infix_form[i] == kv.first) {
        flag = false;
        break;
      }
    }
    if (flag) {
      postfix_form.push_back(divided_infix_form[i]);
    }
    else if (divided_infix_form[i] == ")") {
      while (operations.top() != "(") {
        postfix_form.push_back(operations.top());
        operations.pop();
      }
      operations.pop();
    }
    else {
      for (const auto& kv : mp)
        if (divided_infix_form[i] == kv.first)
          status_infix = kv.second;
      while (operations.size() && operations.top() != "(" && flag_1) {
        flag_1 = true;
        for (const auto& kv : mp)
          if (operations.top() == kv.first)
            status_operations = kv.second;
        if (status_operations >= status_infix && divided_infix_form[i] != "(") {
          postfix_form.push_back(operations.top());
          operations.pop();
        }
        else
          flag_1 = false;
      }
      operations.push(divided_infix_form[i]);
    }
  }
  while (operations.size()) {
    postfix_form.push_back(operations.top());
    operations.pop();
  }
  return postfix_form;
}

double TPostfix::calculate(std::vector<double> values) {
  bool flag = false;
  string operations[5] = {"+", "-", "/", "*", "%"};
  int j = 0;
  stack<double> operands;
  for (int i = 0; i < postfix.size(); i++) {
    flag = false;
    for (std::string symbol : operations)
      if (postfix[i] == symbol) {
        flag = true;
        break;
      }
    if (!flag) {
      operands.push(values[j]);
      j++;
    }
    else {
      double a, b;
      a = operands.top();
      operands.pop();
      b = operands.top();
      operands.pop();
      operands.push(calculate_function (b, a, postfix[i]));
    }
  }

  return operands.top();
}
