#include "Token.h"
#include <vector>

LexemType Token::type()
{
	return _type;
}

int Token::value()
{
	return _value;
}

std::string Token::str()
{
	return _str;
}

std::string Token::LexToString(LexemType type)
{
	switch (type)
	{
	case LexemType::num:
		return "num";
	case LexemType::chr:
		return "chr";
	case LexemType::str:
		return "str";
	case LexemType::id:
		return "id";
	case LexemType::lpar:
		return "lpar";
	case LexemType::rpar:
		return "rpar";
	case LexemType::lbrace:
		return "lbrace";
	case LexemType::rbrace:
		return "rbrace";
	case LexemType::lbracket:
		return "lbracket";
	case LexemType::rbracket:
		return "rbracket";
	case LexemType::semicolon:
		return "semicolon";
	case LexemType::comma:
		return "comma";
	case LexemType::colon:
		return "colon";
	case LexemType::opassign:
		return "opassign";
	case LexemType::opplus:
		return "opplus";
	case LexemType::opminus:
		return "opminus";
	case LexemType::opmult:
		return "opmult";
	case LexemType::opinc:
		return "opinc";
	case LexemType::opeq:
		return "opeq";
	case LexemType::opne:
		return "opne";
	case LexemType::oplt:
		return "oplt";
	case LexemType::opgt:
		return "opgt";
	case LexemType::ople:
		return "ople";
	case LexemType::opnot:
		return "opnot";
	case LexemType::opor:
		return "opor";
	case LexemType::opand:
		return "opand";
	case LexemType::kwint:
		return "kwint";
	case LexemType::kwchar:
		return "kwchar";
	case LexemType::kwif:
		return "kwif";
	case LexemType::kwelse:
		return "kwelse";
	case LexemType::kwswitch:
		return "kwswitch";
	case LexemType::kwcase:
		return "kwcase";
	case LexemType::kwwhile:
		return "kwwhile";
	case LexemType::kwfor:
		return "kwfor";
	case LexemType::kwreturn:
		return "kwreturn";
	case LexemType::kwin:
		return "kwin";
	case LexemType::kwout:
		return "kwout";
	case LexemType::eof:
		return "eof";
	case LexemType::error:
		return "error";
	}
}

Token::Token(LexemType type) : _type(type)
{
}

Token::Token(LexemType type, int value) : _type(type), _value(value)
{
}

Token::Token(LexemType type, const std::string& str) : _type(type), _str(str)
{
}

void Token::print(std::ostream& stream)
{
	stream << '[';
	stream << LexToString(_type);

	switch (_type)
	{
	case LexemType::num:
		stream << ", " << _value;
		break;
	case LexemType::chr:
		stream << ", '" << static_cast<char>(_value) << "'";
		break;
	case LexemType::str:
		stream << ", \"" << _str << "\"";
		break;
	case LexemType::id:
		stream << ", \"" << _str << "\"";
		break;
	case LexemType::error:
		stream << ", \"" << _str << "\"";
		break;
	}
	stream << ']' << '\n';
}
