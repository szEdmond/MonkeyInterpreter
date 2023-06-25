#include "Lexer.h"
#include "Parser.h"
#include "utility.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#undef TRUE
#undef FALSE

using namespace interpreter;

TEST_CASE("LexerTest_EveryToken")
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
		
		REQUIRE(tokens[i].m_literal == expected[i].m_literal);
		REQUIRE(tokens[i].m_type == expected[i].m_type);
	}
}

TEST_CASE("LexerTest_FromFile")
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
		REQUIRE(expected[i].m_literal == tokens[i].m_literal);
		REQUIRE(expected[i].m_type == tokens[i].m_type);
	}
}

TEST_CASE("ParserTest_LET")
{
	std::string input = "let x = 5; let y = 10; let foobar = 838383;";
	std::unique_ptr<Lexer> lexer { std::make_unique<Lexer>(input) };
	Parser parser(std::move(lexer));
	auto program = parser.parseProgram();

	if (program == nullptr)
	{
		FAIL("ParseProgram NULL");
	}

	if (program->statements.size() != 3)
	{
		FAIL("Program.m_statements does not contain 3 statements");
	}

	std::vector<std::string> expectedIdentifiers { "x", "y", "foobar" };

	for (int i = 0; i < program->statements.size(); ++i)
	{
		LetStatement* letStatement{ dynamic_cast<LetStatement*>(program->statements[i].get()) };
		REQUIRE(letStatement->token.m_type == TokenType::LET);
		REQUIRE(letStatement->identifier.m_literal == expectedIdentifiers[i]);
	}
}

TEST_CASE("ParserTest_RETURN")
{
	std::string input = "return 5; return 44; return 808080;";
	std::unique_ptr<Lexer> lexer { std::make_unique<Lexer>(input) };
	Parser parser(std::move(lexer));
	auto program = parser.parseProgram();

	if (program == nullptr)
	{
		FAIL("ParseProgram NULL");
	}

	if (program->statements.size() != 3)
	{
		FAIL("Program.m_statements does not contain 3 statements");
	}

	for (int i = 0; i < program->statements.size(); ++i)
	{
		ReturnStatement* returnStatement{ dynamic_cast<ReturnStatement*>(program->statements[i].get()) };
		REQUIRE(returnStatement->token.m_literal == "return");
	}
}


