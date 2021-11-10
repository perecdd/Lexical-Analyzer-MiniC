# Lexical Analyzer MiniC
## Part 1. Token Class

In the lexical analyzer, the following enumeration will be used to represent the category of a lexeme:

```cpp
enum class LexemType { num, chr, str, id, lpar, rpar, lbrace, rbrace, lbracket, rbracket, semicolon, comma, colon, opassign, opplus, opminus, opmult, opinc, opeq, opne, oplt, opgt, ople, opnot, opor, opand, kwint, kwchar, kwif, kwelse, kwswitch, kwcase, kwwhile, kwfor, kwreturn, kwin, kwout, eof, error };
```

The LexemType type contains all types of lexemes of the MiniC learning language plus two auxiliary types of meta-lexemes: eof - to indicate the end of the lexeme stream and error - to indicate a lexical error.

The following strategies can be used to distribute the code across files:

1. Two files are made for each class - .cpp and .h
2. We put the declaration of the corresponding class in the header files, the definition of its functions in the .cpp file.
3. The LexemType enumeration is placed in the Token.h file (where the Token class is declared)
4. In the Scanner.h file (with the declaration of the lexical analyzer), the Token.h file is connected.
5. The main function is placed in the file compiler.cpp . Scanner.h.
6 is connected from this file. Since there can be quite a lot of tests, they can be divided into several files, and in each connect a header with the class that is being tested.

Implement the Token class for lexical analyzer tokens. The class fields are:

- **_type** – the type of the token (lexemtype);
- **_value** - is an integer used as follows:
  - the value of a numeric constant for a LexemType::num;
  - the value of a character constant (character code) for a LexemType::chr;
- **_str** is a string that contains:
  - the identifier for a LexemType::id;
  - string for LexemType type LexemType::str;
  - an error message for a LexemType::error.

The following constructors must be implemented in the class:

- ```Token(lexemtype type)``` - will be used for tokens without parameters (lexemtype::lpar, etc.);
- ```Token(int value)``` - will be used for tokens with an integer parameter (lexemtype::num);
- ```Token(lexemtype type, const string &str)``` - will be used for tokens with a string value (lexemtype::error, LexemType::id and LexemType::str);
- ```Token(char c)``` - will be used for LexemType::chr.

Constructors must save parameters in class fields.

The void print(ostream &stream) method should be implemented in the class, which outputs the description of the token to the stream stream. The description of the token is printed in square brackets, and includes the name of the token (required) and the parameters used in the token of this type, for example:

```
[eof]
[id, "name"]
[chr, 'a']
[error, "character constant contains more than one character"]
```


To translate a constant type from LexemType to a string, implement an additional method using the switch operator.

Implement methods to access class fields:

- ```LexemType type();``` - returns the type of the token;
- ```int value();``` - returns the integer value of the token;
- ```string str();``` - returns a string of the token.

Implement tests for the Token class. In tests, in particular, it is necessary to check the correctness of the output for all types of tokens. For testing, use the ostringstream class.

## Part 2. Scanner Class

Implement the Scanner lexical analyzer class. The class constructor must receive a reference to the input stream (istream &stream) and save it in the class field.

The main method of the lexical analyzer class ``` Token getNextToken();``` it must return the following lexical analysis token at each call. The implementation of the function should be based on the scheme of the finite automaton constructed at the lecture [minicautomata.pdf](https://github.com/perecdd/Lexical-Analyzer-MiniC/files/7513357/minicautomata.pdf).

Upon successful completion of the analysis after the input stream is exhausted, the token [eof] is returned.

If a lexical error occurs, the lexical analysis function must store the error code in the value field of the token – at the same time, all possible types of errors must be encoded:

- a character unsupported by the language (except when this character is part of a string or character constant);
- no separator between operation symbols;
- single character | or single character &;
- empty character constant;
- a character constant containing more than one character.

To simplify the implementation of the getNextToken procedure, it may be useful to implement mappings (dictionaries in Python terms) to determine the token code for punctuation marks and keywords. Dictionaries can be initialized as follows:

```cpp
#include map
<char, LexemType> punctuation{
    { '[', LexemType::lbracket },
    { ']', LexemType::rbracket }
    // ...
};
map<string, LexemType> keywords{
    { "return", LexemType::kwreturn }
    // ...
};
```


To check for the presence of a key in the display, you can use the count(key) method, which returns the number of records with such a key (and 0 if there is no key). To access the value, the syntax with [ ] is used, for example ```keywords["return"]```.

## Lexical Analyzer Tests

Implement tests for the lexical analyzer. Approach testing carefully, as errors in the implementation of the lexical analyzer will interfere with the implementation of the parser. It is convenient to use istringstream for testing.

A reasonable approach to testing a lexical analyzer is to gradually implement tests for various transitions of the analyzer and add their implementation to the getNextToken() method. Start by making sure that the analyzer issues the [eof] token on an empty input. Then add a test for some one token and implement the corresponding transition of the automaton.

Make sure that all the transitions of the machine are tested at least once. If in some places the accumulation of information in auxiliary variables is used (Digit, value on the circuit of the automaton), test that these variables are correctly reinitialized when switching to the corresponding state again (so that the previous word or number is not "glued" to the beginning of the next one).

Make sure that wherever there is a return from the lexical analyzer, its internal state is set correctly (the next token will also be correctly recognized).

It is convenient to use short fragments of several tokens for testing, but do not forget to add several tests with a large amount of analyzed code.

### Main() function

To check the lexical analyzer, implement the code in the main() function that will parse the specified text file and print the received tokens. This function may look like this:

```cpp
int main() {
	std::ifstream ifile("myprog.minic");
	Scanner scanner(ifile);
	for (;;) {
		Token currentLexem = scanner.getNextToken();
		currentLexem.print(std::cout);
		if (currentLexem.type() == LexemType::error || currentLexem.type() == LexemType::eof) {
			break;
		}
	}
	return 0;
}
```

Example of how the program works:

```
char str[] = "Hello, world!";
int a = 5;
char c = 'c';
a = a + c;
```

```
[kwchar]
[id, "str"]
[lbracket]
[rbracket]
[opassign]
[str, "Hello, world!"]
[semicolon]
[kwint]
[id, "a"]
[opassign]
[num, 5]
[semicolon]
[kwchar]
[id, "c"]
[opassign]
[chr, 'c']
[semicolon]
[id, "a"]
[opassing]
[id, "a"]
[opplus]
[id, "c"]
[semicolon]
[eof]
```

