#include "Lexer.h"
#include "utility.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace interpreter;

TEST_CASE("LEXER_TEST_2")
{
	std::string input{"let five = 5; let ten = 10; let add = fn(x, y) { x + y; }; let result = add(five, ten);" };
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
    std::vector<Token> tokens = lex.getTokens();

	for (int i = 0; i < tokens.size(); ++i)
	{
		
		REQUIRE(tokens[i]._literal == expected[i]._literal);
		REQUIRE(tokens[i]._type == expected[i]._type);
	}
}

TEST_CASE("LEXER_TEST_3")
{
	std::string input = utility::stringFromFile("../../tests/monkeycode.txt");
	Lexer lex{ input };
	std::vector<Token> tokens = lex.getTokens();

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

		{TokenType::BANG, "!"},
		{TokenType::MINUS, "-"},
		{TokenType::SLASH, "/"},
		{TokenType::ASTERISK, "*"},
		{TokenType::INT, "5"},
		{TokenType::SEMICOLON, ";"},

		{TokenType::INT, "5"},
		{TokenType::LT, "<"},
		{TokenType::INT, "10"},
		{TokenType::GT, ">"},
		{TokenType::INT, "5"},
		{TokenType::SEMICOLON, ";"},
		#undef TRUE
		#undef FALSE
		{TokenType::IF, "if"},
		{TokenType::LPAREN, "("},
		{TokenType::INT, "5"},
		{TokenType::LT, "<"},
		{TokenType::INT, "10"},
		{TokenType::RPAREN, ")"},

		{TokenType::LBRACE, "{"},
		{TokenType::RETURN, "return"},
		{TokenType::TRUE, "true"},
		{TokenType::SEMICOLON, ";"},
		{TokenType::RBRACE, "}"},

		{TokenType::ELSE, "else"},
		{TokenType::LBRACE, "{"},
		{TokenType::RETURN, "return"},
		{TokenType::FALSE, "false"},
		{TokenType::SEMICOLON, ";"},
		{TokenType::RBRACE, "}"},

		{TokenType::INT, "10"},
		{TokenType::EQ, "=="},
		{TokenType::INT, "10"},
		{TokenType::SEMICOLON, ";"},

		{TokenType::INT, "10"},
		{TokenType::NOT_EQ, "!="},
		{TokenType::INT, "9"},
		{TokenType::SEMICOLON, ";"},

		{TokenType::ENDF, ""},
	};

	for (int i = 0; i < expected.size(); ++i)
	{
		REQUIRE(expected[i]._literal == tokens[i]._literal);
		REQUIRE(expected[i]._type == tokens[i]._type);
	}
}


