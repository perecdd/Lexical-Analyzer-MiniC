#include "Scanner.h"
#include <fstream>

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