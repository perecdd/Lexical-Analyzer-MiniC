#pragma once
#include "Token.h"
#include <map>

const std::map<std::string, LexemType> keywords{
	{"int", LexemType::kwint},
	{"char", LexemType::kwchar},
	{"if", LexemType::kwif},
	{"else", LexemType::kwelse},
	{"switch", LexemType::kwswitch},
	{"case", LexemType::kwcase},
	{"while", LexemType::kwwhile},
	{"for", LexemType::kwfor},
	{"return", LexemType::kwreturn},
	{"in", LexemType::kwin},
	{"out", LexemType::kwout},
	{"$", LexemType::eof}
};

const std::map<char, LexemType> punctuation{
	{'(', LexemType::lpar},
	{')', LexemType::rpar},
	{'{', LexemType::lbrace},
	{'}', LexemType::rbrace},
	{'[', LexemType::lbracket},
	{']', LexemType::lbracket},
	{';', LexemType::semicolon},
	{',', LexemType::comma},
	{':', LexemType::colon},
	{'$', LexemType::eof}
};

const std::map<std::string, LexemType> operations{
	{"=", LexemType::opassign},
	{"+", LexemType::opplus},
	{"-", LexemType::opminus},
	{"*", LexemType::opmult},
	{"++", LexemType::opinc},
	{"==", LexemType::opeq},
	{"!=", LexemType::opne},
	{"<", LexemType::oplt},
	{">", LexemType::opgt},
	{"<=", LexemType::ople},
	{"!", LexemType::opnot},
	{"||", LexemType::opor},
	{"&&", LexemType::opand},
	{"$", LexemType::eof},
};

class Scanner
{
private:
	std::istream& stream;

public:
	Scanner(std::istream& stream);
	Token getNextToken();
};

