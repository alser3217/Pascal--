#include <iostream>

#include "include/handler.hxx"
#include "include/lexer.hxx"
#include "include/compiler.hxx"
#include "include/parser.hxx" 
#include "include/executor.hxx"


int main() {
	std::string path = "K:\\Labs\\2Year\\Pascal--\\program_samples\\prog1.pas";
	std::shared_ptr<MyPascal::Handler> handler = std::make_shared<MyPascal::Lexer>();
	handler->setNext(std::make_shared<MyPascal::Parser>())->setNext(std::make_shared<MyPascal::Compiler>())->setNext(std::make_shared<MyPascal::Executor>());
	handler->process(std::make_shared<MyPascal::Data>(path));

	return 0;
}	
