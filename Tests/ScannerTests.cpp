#include "pch.h"
#include <sstream>
#include "../Lab7/Scanner.cpp"

TEST(Scanner, Empty) {
	{
		std::istringstream input("\t");
		Scanner scanner(input);

		EXPECT_EQ(LexemType::eof, scanner.getNextToken().type());
	}

	{
		std::istringstream input("");
		Scanner scanner(input);

		EXPECT_EQ(LexemType::eof, scanner.getNextToken().type());
	}

	{
		std::istringstream input("  ");
		Scanner scanner(input);

		EXPECT_EQ(LexemType::eof, scanner.getNextToken().type());
	}

	{
		std::istringstream input("\n\n");
		Scanner scanner(input);

		EXPECT_EQ(LexemType::eof, scanner.getNextToken().type());
	}

	{
		std::istringstream input("\n\n$");
		Scanner scanner(input);

		EXPECT_EQ(LexemType::eof, scanner.getNextToken().type());
	}

	{
		std::istringstream input("$");
		Scanner scanner(input);

		EXPECT_EQ(LexemType::eof, scanner.getNextToken().type());
	}

	{
		std::istringstream input("$$$$$$$$$$");
		Scanner scanner(input);

		for (int i = 0; i < 10; ++i) {
			EXPECT_EQ(LexemType::eof, scanner.getNextToken().type());
		}
	}
}

TEST(Scanner, Punc) {
	std::string Test = "()[]{};,:$";
	std::istringstream input(Test);
	Scanner scanner(input);

	for (int i = 0; i < Test.size() - 1; ++i) {
		Token token = scanner.getNextToken();
		EXPECT_EQ(punctuation.find(Test[i])->second, token.type());
	}
	EXPECT_EQ(LexemType::eof, scanner.getNextToken().type());
}

TEST(Scanner, operations) {
	std::vector<std::string> Test = { "=","+","-","*", "++", "==", "!=", "<", ">", "<=", "!", "||", "&&"};
	std::istringstream input("=+-*++==!=<><=!||&&$");
	Scanner scanner(input);

	for (int i = 0; i < Test.size(); ++i) {
		Token token = scanner.getNextToken();
		std::cout << (int)operations.find(Test[i])->second << ' ' << (int)token.type() << std::endl;
		EXPECT_EQ(operations.find(Test[i])->second, token.type());
	}
	EXPECT_EQ(LexemType::eof, scanner.getNextToken().type());
}

TEST(Scanner, keywords) {
	{
		std::vector<std::string> Test = { "int","char","if","else", "switch", "case", "while", "for", "return", "in", "out" };
		std::istringstream input("int char if else switch case while for return in out $");
		Scanner scanner(input);

		for (int i = 0; i < Test.size(); ++i) {
			Token token = scanner.getNextToken();
			EXPECT_EQ(keywords.find(Test[i])->second, token.type());
		}
		EXPECT_EQ(LexemType::eof, scanner.getNextToken().type());
	}
}

TEST(Scanner, nums) {
	{
		std::istringstream input("123456789$");
		Scanner scanner(input);

		Token token = scanner.getNextToken();
		EXPECT_EQ(Token(LexemType::num, 123456789).value(), token.value());
		EXPECT_EQ(Token(LexemType::num, 123456789).type(), token.type());
		EXPECT_EQ(LexemType::eof, scanner.getNextToken().type());
	}

	{
		std::istringstream input("9876$");
		Scanner scanner(input);

		Token token = scanner.getNextToken();
		EXPECT_EQ(Token(LexemType::num, 9876).type(), token.type());
		EXPECT_EQ(Token(LexemType::num, 9876).value(), token.value());
		EXPECT_EQ(Token(LexemType::eof).type(), scanner.getNextToken().type());
	}
}

TEST(Scanner, strs) {
	{
		std::istringstream input("\"\"$");
		Scanner scanner(input);

		Token token = scanner.getNextToken();
		EXPECT_EQ(Token(LexemType::str, "").type(), token.type());
		EXPECT_EQ(Token(LexemType::str, "").str(), token.str());
		EXPECT_EQ(Token(LexemType::eof).type(), scanner.getNextToken().type());
	}

	{
		std::istringstream input("\"sometext\"$");
		Scanner scanner(input);

		Token token = scanner.getNextToken();
		EXPECT_EQ(Token(LexemType::str, "sometext").type(), token.type());
		EXPECT_EQ(Token(LexemType::str, "sometext").str(), token.str());
		EXPECT_EQ(Token(LexemType::eof).type(), scanner.getNextToken().type());
	}
}

TEST(Scanner, id) {
	{
		std::istringstream input("a84h5974huhufhdepo89heop49hg0e97th408pt4t$");
		Scanner scanner(input);

		Token token = scanner.getNextToken();
		EXPECT_EQ(Token(LexemType::id, "a84h5974huhufhdepo89heop49hg0e97th408pt4t").str(), token.str());
		EXPECT_EQ(Token(LexemType::id, "a84h5974huhufhdepo89heop49hg0e97th408pt4t").type(), token.type());
		EXPECT_EQ(Token(LexemType::eof).type(), scanner.getNextToken().type());
	}

	{
		std::istringstream input("b$");
		Scanner scanner(input);

		Token token = scanner.getNextToken();
		EXPECT_EQ(Token(LexemType::id, "b").type(), token.type());
		EXPECT_EQ(Token(LexemType::id, "b").str(), token.str());
		EXPECT_EQ(Token(LexemType::eof).type(), scanner.getNextToken().type());
	}
}

TEST(Scanner, chr) {
	{
		std::string Test;
		
		for (int i = 'a'; i <= 'z'; ++i) {
			Test += "'"[0];
			Test += (char)i;
			Test += "'"[0];
		}
		Test.push_back('$');

		std::stringstream input(Test);
		Scanner scanner(input);

		for (int i = 'a'; i <= 'z'; ++i) {
			Token token = scanner.getNextToken();
			std::cout << (char)token.value() << std::endl;
			EXPECT_EQ(i, token.value());
			EXPECT_EQ(LexemType::chr, token.type());
		}
		EXPECT_EQ(Token(LexemType::eof).type(), scanner.getNextToken().type());
	}
}

TEST(Scanner, error) {
	{
		std::string Test = "@#$";
		std::istringstream input(Test);
		Scanner scanner(input);

		for (int i = 0; i < Test.size() - 1; ++i) {
			Token token = scanner.getNextToken().type();
			EXPECT_EQ(Token(LexemType::error, "").type(), token.type());
		}
		EXPECT_EQ(LexemType::eof, scanner.getNextToken().type());
	}

	{
		std::istringstream input("|$");
		Scanner scanner(input);

		EXPECT_EQ(Token(LexemType::error, "").type(), scanner.getNextToken().type());
		EXPECT_EQ(LexemType::eof, scanner.getNextToken().type());
	}

	{
		std::istringstream input("&$");
		Scanner scanner(input);

		EXPECT_EQ(Token(LexemType::error, "").type(), scanner.getNextToken().type());
		EXPECT_EQ(LexemType::eof, scanner.getNextToken().type());
	}

	{
		std::istringstream input("'$");
		Scanner scanner(input);

		EXPECT_EQ(Token(LexemType::error, "").type(), scanner.getNextToken().type());
		EXPECT_EQ(LexemType::eof, scanner.getNextToken().type());
	}

	{
		std::istringstream input("'5$");
		Scanner scanner(input);

		EXPECT_EQ(Token(LexemType::error, "").type(), scanner.getNextToken().type());
		EXPECT_EQ(Token(LexemType::eof).type(), scanner.getNextToken().type());
	}

	{
		std::istringstream input("\"$");
		Scanner scanner(input);

		EXPECT_EQ(Token(LexemType::error, "").type(), scanner.getNextToken().type());
		EXPECT_EQ(Token(LexemType::eof).type(), scanner.getNextToken().type());
	}

	{
		std::istringstream input("\"ret$");
		Scanner scanner(input);

		EXPECT_EQ(Token(LexemType::error, "").type(), scanner.getNextToken().type());
		EXPECT_EQ(Token(LexemType::eof).type(), scanner.getNextToken().type());
	}
}