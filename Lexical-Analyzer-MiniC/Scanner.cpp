#include "Scanner.h"
#include <sstream>

Scanner::Scanner(std::istream& stream) : stream(stream)
{
}

bool isDigit(char sym) {
	return sym >= '0' && sym <= '9';
}

bool isLetter(char sym) {
	return sym >= 'a' && sym <= 'z';
}

int getNum(std::istream& stream) {
	int value = 0;
	while (isDigit(stream.peek())) {
		value = value * 10 + (stream.get() - '0');
	}
	return value;
}

Token getString(std::istream& stream) {
	std::stringstream ss;

	while (stream.peek() != '\"' && stream.peek() != '$') {
		ss << (char)stream.get();
	}

	if (stream.peek() == '$') {
		return Token(LexemType::error, "string is not closed");
	}
	else {
		stream.get(); // "
		return Token(LexemType::str, ss.str());
	}
}

std::string getWord(std::istream& stream) {
	std::stringstream ss;

	if (!isLetter(stream.peek())) {
		throw std::runtime_error("Bad symbol in word");
	}

	ss << (char)stream.get();
	while (isLetter(stream.peek()) || isDigit(stream.peek())) {
		ss << (char)stream.get();
	}

	return ss.str();
}

Token Scanner::getNextToken()
{
	while (stream.peek() != -1 && stream.peek() == ' ' || stream.peek() == '\n' || stream.peek() == '\t') {
		stream.get();
	}
	if (stream.peek() == -1) {
		return Token(LexemType::eof);
	}

	if (isDigit(stream.peek())) {
		return Token(LexemType::num, getNum(stream));
	}
	else if (isLetter(stream.peek())) {
		std::string Word = getWord(stream);

		auto KeyWord = keywords.find(Word);

		if (KeyWord != keywords.end()) {
			return Token(KeyWord->second, KeyWord->first);
		}

		return Token(LexemType::id, Word);
	}
	else if (stream.peek() == '\"') {
		stream.get(); // "
		return getString(stream);
	}
	else if (stream.peek() == '\'') {
		stream.get();
		char symbol = stream.get();

		if (symbol == '\'') {
			return Token(LexemType::error, "Empty character");
		}
		else if (stream.peek() == '\'') {
			stream.get();
			return Token(LexemType::chr, symbol);
		}
		else {
			if (symbol == '$') {
				stream.unget();
			}
			return Token(LexemType::error, "\' is not closed");
		}
	}
	else {
		auto Punctuation = punctuation.find(stream.peek());
		
		if (Punctuation != punctuation.end()) {
			stream.get();
			return Token(Punctuation->second);
		}
	}

	switch (stream.get()) {
	case '-':
		if (isDigit(stream.peek())) {
			return Token(LexemType::num, -1 * getNum(stream));
		}
		else {
			return Token(LexemType::opminus);
		}
		break;
	case '!':
		if (stream.peek() == '=') {
			stream.get();
			return Token(LexemType::opne);
		}
		else {
			return Token(LexemType::opnot);
		}
		break;
	case '<':
		if (stream.peek() == '=') {
			stream.get();
			return Token(LexemType::ople);
		}
		else {
			return Token(LexemType::oplt);
		}
		break;
	case '>':
		return Token(LexemType::opgt);
		break;
	case '=':
		if (stream.peek() == '=') {
			stream.get();
			return Token(LexemType::opeq);
		}
		else {
			return Token(LexemType::opassign);
		}
		break;
	case '+':
		if (stream.peek() == '+') {
			stream.get();
			return Token(LexemType::opinc);
		}
		else {
			return Token(LexemType::opplus);
		}
		break;
	case '*':
		return Token(LexemType::opmult);
		break;
	case '|':
		if (stream.peek() == '|') {
			stream.get();
			return Token(LexemType::opor);
		}
		break;
	case '&':
		if (stream.peek() == '&') {
			stream.get();
			return Token(LexemType::opand);
		}
		break;
	}

	return Token(LexemType::error, "Unknown Lexem");
}
