
#include "handler.hxx"


void MyPascal::Handler::process(std::shared_ptr<Data> _data) {
	if (next)
	  next->process(_data);
}