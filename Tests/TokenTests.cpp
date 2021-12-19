#include "pch.h"
#include "../Lab7/Token.cpp"
#include <vector>
#include <sstream>


const std::vector<std::string> Lexs{
	"num",
	"chr",
	"str",
	"id",
	"lpar",
	"rpar",
	"lbrace",
	"rbrace",
	"lbracket",
	"rbracket",
	"semicolon",
	"comma",
	"colon",
	"opassign",
	"opplus",
	"opminus",
	"opmult",
	"opinc",
	"opeq",
	"opne",
	"oplt",
	"opgt",
	"ople",
	"opnot",
	"opor",
	"opand",
	"kwint",
	"kwchar",
	"kwif",
	"kwelse",
	"kwswitch",
	"kwcase",
	"kwwhile",
	"kwfor",
	"kwreturn",
	"kwin",
	"kwout",
	"eof",
	"error"
};

TEST(Token, Lexems) {
{
		for (int i = 0; i < 256; ++i) {
			Token token(LexemType::num, i);
			EXPECT_EQ(token.type(), LexemType::num);
			EXPECT_EQ(token.value(), i);
		}
	} // NUM

	{
		for (int i = 0; i < 256; ++i) {
			Token token(LexemType::chr, static_cast<unsigned char>(i));
			EXPECT_EQ(token.type(), LexemType::chr);
			EXPECT_EQ(token.value(), i);
		}
	} // CHR

	{
		std::string testString = "Some tests.";
		std::string buffer;

		for (char c : testString) {
			Token error(LexemType::error, buffer);
			Token id(LexemType::id, buffer);
			Token str(LexemType::str, buffer);

			EXPECT_EQ(error.type(), LexemType::error);
			EXPECT_EQ(id.type(), LexemType::id);
			EXPECT_EQ(str.type(), LexemType::str);

			EXPECT_EQ(error.str(), buffer);
			EXPECT_EQ(id.str(), buffer);
			EXPECT_EQ(str.str(), buffer);

			buffer += c;
		}
	} // id, error, str

	auto func = [&](LexemType lex, int index) {
		Token token(lex);
		EXPECT_EQ(token.type(), lex);
	};

	{
		for (int i = 4; i < Lexs.size(); ++i) {
			func(static_cast<LexemType>(i), i);
		}
	} // Other Lexs
}

TEST(Token, LexToString) {
	for (int i = 0; i < Lexs.size(); ++i) {
		EXPECT_EQ(Token::LexToString(static_cast<LexemType>(i)), Lexs[i]);
	}
}

TEST(Token, print) {
	{
		for (int i = 4; i < Lexs.size() - 1; ++i) {
			std::stringstream ss;
			Token token(static_cast<LexemType>(i));
			token.print(ss);
			EXPECT_EQ(ss.str(), '[' + Lexs[i] + "]\n");
		}
	} // all without id, num, chr, str, error

	std::vector<LexemType> TestVector{ LexemType::id, LexemType::str, LexemType::error };

	for (auto Lex : TestVector) {
		std::string TestData = "sifhosdhufhsdfafdsadsfsdaffsafiuoreiweow";

		for (int i = 0; i < TestData.size(); ++i) {
			std::stringstream ss;

			Token token(Lex, TestData.substr(0, i));
			token.print(ss);
			EXPECT_EQ(ss.str(), ("[" + Token::LexToString(Lex) + ", \"") + (TestData.substr(0, i) + "\"]\n"));
		}
	} // ID, STR, ERROR

	{
		for (int i = 33; i < 127; ++i) {
			std::stringstream ss;

			Token token(LexemType::chr, static_cast<char>(i));
			token.print(ss);

			EXPECT_EQ(ss.str(), std::string("[chr, '") + static_cast<char>(i) + std::string("']\n"));
		}
	} // chr

	{
		for (int i = 0; i < 256; ++i) {
			std::stringstream ss;

			Token token(LexemType::num, i);
			token.print(ss);

			EXPECT_EQ(ss.str(), std::string("[num, ") + std::to_string(i) + "]\n");
		}
	} // num
}
