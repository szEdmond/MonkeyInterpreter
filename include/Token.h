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
		MINUS,
		BANG,
		ASTERISK,
		SLASH,

		LT,
		GT,
		EQ,
		NOT_EQ,

		// Delimiters
		COMMA,
		SEMICOLON,

		LPAREN,
		RPAREN,
		LBRACE,
		RBRACE,

		// Keywords
		FUNCTION,
		LET,
		TRUE,
		FALSE,
		IF,
		ELSE,
		RETURN
	};

	struct Token
	{
		Token() {}
		Token(TokenType type, std::string byte) :
			m_type(type),
			m_literal(byte)
		{}
		Token(TokenType type, char byte) :
			m_type(type),
			m_literal(std::string(1, byte))
		{}

		TokenType m_type;
		std::string m_literal;
	};

	static std::unordered_map<TokenType, std::string> sTokenTypeToStringMap
	{
		{TokenType::ILLEGAL, "ILLEGAL"},
		{TokenType::ENDF, "EOF"},
		{TokenType::IDENT, "IDENT"},
		{TokenType::INT, "INT"},
		{TokenType::ASSIGN, "="},
		{TokenType::PLUS, "+"},
		{TokenType::MINUS, "-"},
		{TokenType::BANG, "!"},
		{TokenType::ASTERISK, "*"},
		{TokenType::SLASH, "/"},
		{TokenType::LT, "<"},
		{TokenType::GT, ">"},
		{TokenType::EQ, "=="},
		{TokenType::NOT_EQ, "!="},
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
		{"let", TokenType::LET},
		{"true", TokenType::TRUE},
		{"false", TokenType::FALSE},
		{"if", TokenType::IF},
		{"else", TokenType::ELSE},
		{"return", TokenType::RETURN}
	};
}
