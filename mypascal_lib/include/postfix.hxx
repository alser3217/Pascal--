#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include <vector>
#include <stack>
#include <list>
#include <map>

using std::string;
using std::vector;
using std::stack;
using std::list;
using std::map;

class TPostfix
{
  string infix;
  vector<string> postfix;
private:
  vector<string> infix_divide();
  vector<string> to_postfix();
  string postfix_to_string();
  bool correct_input_check();
public:
  TPostfix(string _infix = "") : infix(_infix)
  {
    if (!correct_input_check())
      throw "incorrect input.";
    postfix = to_postfix();
  }
  void set_infix(string _infix);
  string get_infix() { return infix; }
  vector<string> get_infix_divide() {
    return infix_divide();
  }
  string get_postfix();
  int operands_counter();
  double calculate(vector<double> values); // Ввод переменных, вычисление по постфиксной форме
};

#endif