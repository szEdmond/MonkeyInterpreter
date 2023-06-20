#include "Lexer.h"
#include "Utility.h"
#include "string"


using namespace interpreter;
int main()
{
    std::string in;
    std::string text;
    while (std::cin >> in) {
        text += in + " ";
    }
    Lexer lex2{ text };
    std::vector<Token> tokens = lex2.getTokens();
    for (const auto& token : tokens)
    {
        std::cout << token._literal << "\n";
    }
}


