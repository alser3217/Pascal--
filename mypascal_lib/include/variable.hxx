#ifndef __VARIABLE__
#define __VARIABLE__

#include <string>

using std::string;

namespace MyPascal {

  enum class vType {INTEGER, DOUBLE};

  class Variable {
    string name;
    double value;
    vType type;
  public:

    Variable(string ename = string(), double evalue = 0, vType etype = vType::DOUBLE) : name(ename), value(evalue), type(etype) {}
    virtual ~Variable() {}

    string get_name() { return name; }
    double get_value() { return value; }
    vType get_vtype() { return type; }
    void set_value(double evalue) { value = evalue;  }

  };
}

#endif 