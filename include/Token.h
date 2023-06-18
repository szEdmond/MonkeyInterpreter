#pragma once
#include <string>
#include <unordered_map>

namespace interpreter
{
	enum class TokenType
	{
		ILLEGAL,
		ENDF,

		// Identifiers + literals
		IDENT,
		INT,

		// Operators
		ASSIGN,
		PLUS,

		// Delimiters
		COMMA,
		SEMICOLON,

		LPAREN,
		RPAREN,
		LBRACE,
		RBRACE,

		// Keywords
		FUNCTION,
		LET
	};

	struct Token
	{
		Token() {}
		Token(TokenType type, std::string byte) :
			_type(type),
			_literal(byte)
		{}
		Token(TokenType type, char byte) :
			_type(type),
			_literal(std::string(1, byte))
		{}

		TokenType _type;
		std::string _literal;
	};

	static std::unordered_map<TokenType, std::string> sTokenTypeToStringMap
	{
		{TokenType::ILLEGAL, "ILLEGAL"},
		{TokenType::ENDF, "EOF"},
		{TokenType::IDENT, "IDENT"},
		{TokenType::INT, "INT"},
		{TokenType::ASSIGN, "="},
		{TokenType::PLUS, "+"},
		{TokenType::COMMA, ","},
		{TokenType::SEMICOLON, ";"},
		{TokenType::LPAREN, "("},
		{TokenType::RPAREN, ")"},
		{TokenType::LBRACE, "{"},
		{TokenType::RBRACE, "}"},
		{TokenType::FUNCTION, "FUNCTION"},
		{TokenType::LET, "LET"}
	};

	static std::unordered_map<std::string, TokenType> sKeyWordsMap
	{
		{"fn", TokenType::FUNCTION},
		{"let", TokenType::LET}
	};
}
