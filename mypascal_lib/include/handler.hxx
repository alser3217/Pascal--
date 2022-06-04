#ifndef __HANDLER__
#define __HANDLER__

#include <memory>

#include "data.hxx"
#include "postfix.hxx"

namespace MyPascal {
  class Handler {
    std::shared_ptr<Handler> next = nullptr;
  public:
    Handler() {}
    virtual ~Handler() {}
    std::shared_ptr<Handler> setNext(std::shared_ptr<Handler> _next) { next = _next; return next; }
    virtual void process(std::shared_ptr<Data> _data);
  };
}

#endif

