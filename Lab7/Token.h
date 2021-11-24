#pragma once
#include <string>
#include <iostream>
#include <type_traits>

enum class LexemType
{ num, chr, str, id, lpar, rpar, lbrace, rbrace, lbracket, rbracket, semicolon, comma, colon, opassign,
	opplus, opminus, opmult, opinc, opeq, opne, oplt, opgt, ople, opnot, opor, opand, kwint, kwchar,
	kwif, kwelse, kwswitch, kwcase, kwwhile, kwfor, kwreturn, kwin, kwout, eof, error };

class Token
{
private:
	LexemType _type;
	int _value = 0;
	std::string _str = "";

public:
	static std::string LexToString(LexemType type);

	Token(LexemType type);
	Token(LexemType type, int value);
	Token(LexemType type, const std::string& str);

	void print(std::ostream& stream);

	LexemType type();
	int value();
	std::string str();
};

