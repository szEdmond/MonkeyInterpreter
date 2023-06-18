#include "Lexer.h"

/**/#define UNIT_TEST//*/

#ifndef UNIT_TEST

int main()
{

}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
using namespace interpreter;

TEST_CASE("LEXER TEST", "=+(){},;")
{
	std::string input = "=+(){},;";
	Lexer lex{ input };

	std::vector<Token> expected
	{
		{TokenType::ASSIGN, "=" },
		{TokenType::PLUS, "+"},
		{TokenType::LPAREN, "("},
		{TokenType::RPAREN, ")"},
		{TokenType::LBRACE, "{"},
		{TokenType::RBRACE, "}"},
		{TokenType::COMMA, ","},
		{TokenType::SEMICOLON, ";"},
		{TokenType::ENDF, 0}
	};

	for (int i = 0; i < input.size(); ++i)
	{
		Token tok = lex.nextToken();

		REQUIRE(tok._literal == expected[i]._literal);
		REQUIRE(tok._type == expected[i]._type);
	}
}

TEST_CASE("LEXER TEST2", "monkeyCode")
{
		std::string input{ "let five = 5; let ten = 10; let add = fn(x, y) { x + y; }; let result = add(five, ten);" };
	Lexer lex{ input };

	std::vector<Token> expected
	{
		{TokenType::LET, "let"},
		{TokenType::IDENT, "five"},
		{TokenType::ASSIGN, "="},
		{TokenType::INT, "5"},
		{TokenType::SEMICOLON, ";"},
		{TokenType::LET, "let"},
		{TokenType::IDENT, "ten"},
		{TokenType::ASSIGN, "="},
		{TokenType::INT, "10"},
		{TokenType::SEMICOLON, ";"},
		{TokenType::LET, "let"},
		{TokenType::IDENT, "add"},
		{TokenType::ASSIGN, "="},
		{TokenType::FUNCTION, "fn"},
		{TokenType::LPAREN, "("},
		{TokenType::IDENT, "x"},
		{TokenType::COMMA, ","},
		{TokenType::IDENT, "y"},
		{TokenType::RPAREN, ")"},
		{TokenType::LBRACE, "{"},
		{TokenType::IDENT, "x"},
		{TokenType::PLUS, "+"},
		{TokenType::IDENT, "y"},
		{TokenType::SEMICOLON, ";"},
		{TokenType::RBRACE, "}"},
		{TokenType::SEMICOLON, ";"},
		{TokenType::LET, "let"},
		{TokenType::IDENT, "result"},
		{TokenType::ASSIGN, "="},
		{TokenType::IDENT, "add"},
		{TokenType::LPAREN, "("},
		{TokenType::IDENT, "five"},
		{TokenType::COMMA, ","},
		{TokenType::IDENT, "ten"},
		{TokenType::RPAREN, ")"},
		{TokenType::SEMICOLON, ";"},
		{TokenType::ENDF, ""},
	};

	for (int i = 0; i < expected.size(); ++i)
	{
		Token tok = lex.nextToken();

		REQUIRE(tok._literal == expected[i]._literal);
		REQUIRE(tok._type == expected[i]._type);
	}

}


#endif // !UNIT_TESTING


