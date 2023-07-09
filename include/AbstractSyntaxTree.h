#pragma once
#include <sstream>

#include"Token.h"

using namespace interpreter;

struct Node 
{
    virtual ~Node() = default;
    virtual std::string tokenLiteral() = 0;
    virtual std::string String() = 0;
};

struct Statement : public Node
{
    virtual void statementNode() = 0;
    virtual std::string String() = 0;
    virtual ~Statement() = default;
};

struct Expression : public Node
{
    virtual std::string String() = 0;
    virtual ~Expression() = default;
};

struct Identifier : public Expression
{
    Token identifierToken;
    std::string identifierValue;

    std::string String() override { return identifierValue; }
    std::string tokenLiteral() override { return identifierToken.m_literal; }
    ~Identifier() {}
};

struct IntegerLiteral : public Expression
{
    Token token;
    int value;

    std::string String() override { return std::to_string(value); }
    std::string tokenLiteral() override { return token.m_literal; }
    ~IntegerLiteral() {};
};

struct PrefixExpression : public Expression
{
    Token token;
    std::string op;
    std::unique_ptr<Expression> right;

    std::string String() override {
        std::string res = "(" + op + right->String() + ")";
        return res;
    }
    std::string tokenLiteral() override { return token.m_literal; }
    ~PrefixExpression() = default;
};

struct InfixExpression : public Expression
{
    Token token;
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
    std::string op;

    std::string String() override {
        std::string res = "(" + left->String() + op + right->String() + ")";
        return res;
    }
    std::string tokenLiteral() override { return token.m_literal; }
    ~InfixExpression() = default;
};

// ========================
struct LetStatement : public Statement
{
    Token token;
    std::unique_ptr<Expression> value;
    std::unique_ptr<Identifier> name;

    void statementNode() override {}
    std::string String() override {
        std::string res = tokenLiteral() + " " + name->String() + " = ";
        if (value != nullptr) {
            res += value->String();
        }
        res += ";";
        return res;
    }

    std::string tokenLiteral() override {
        return token.m_literal;
    }
    ~LetStatement() {}
};

struct  ReturnStatement : public Statement
{
    Token token; 
    std::unique_ptr<Expression> returnValue;
    
    void statementNode() override {}
    std::string String() override {
        std::string res = tokenLiteral() + " ";
        if (returnValue != nullptr) {
            res += returnValue->String();
        }
        res += ";";
        return res;
    }
    std::string tokenLiteral() override { return token.m_literal; }
    ~ReturnStatement() {}
};


struct ExpressionStatement : public Statement
{
    Token token; // ?
    std::unique_ptr<Expression> expression;

    void statementNode() override {}
    std::string String() override {
        std::string res = "";
        if (expression != nullptr) {
            res += expression->String();
        }
        res += ";";
        return res;
    }
    std::string tokenLiteral() override { return token.m_literal; }
    ~ExpressionStatement() {}
};

//------------

struct Program : public Node
{
    std::vector<std::unique_ptr<Statement>> statements;

    std::string tokenLiteral() override{
        if (statements.size() > 0) {
            return statements[0]->tokenLiteral();
        }
        else {
            return "";
        }
    }

    std::string String() override {
        std::string res;
        for (auto& stmt : statements) {
            res += stmt->String() ;
        }
        return res;
    }

    ~Program() {}
};
