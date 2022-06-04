
#include "exception.hxx"

void MyPascal::Exception::info() {
  if (code == 1)
    cout << "no program, begin or end. key words exist." << endl;
  else if (code == 2)
    cout << "syntax error at line." << line << endl;
  else if (code == 3)
    cout << "compile erroe: no such variable or constant exist." << line << endl;
  else if (code == 4)
    cout << "parentheses missmatch." << line << endl;
  else if (code == 5)
    cout << "no program key word exists." << endl;
  else if (code == 6)
    cout << "no begin key word exists." << endl;
  else if (code == 7)
    cout << "no end. key word exists." << endl;
}