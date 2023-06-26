#pragma once
#include <sstream>

#include"Token.h"

using namespace interpreter;

enum Precedence {
    _ = 0,
    LOWEST = 1,
    EQUALS = 2,
    LESSGREATER = 3,
    SUM = 4,
    PRODUCT = 5,
    PREFIX = 6,
    CALL = 7
};

struct Node 
{
    virtual ~Node() = default;
    virtual std::string tokenLiteral() = 0;
};

struct Statement : public Node
{
    virtual void statementNode() = 0;
    virtual ~Statement() = default;
};

struct Expression : public Node
{
    virtual void expressionNode() = 0;
    virtual ~Expression() = default;
    std::unique_ptr<Expression> prefixParse() {}
    std::unique_ptr<Expression> inifixParse(std::unique_ptr<Expression> leftExpression) {}
};

struct Identifier : public Expression
{
    Token identifierToken;
    std::string identifierValue;

    void expressionNode() override {}
    std::string tokenLiteral() override { return identifierToken.m_literal; }
    ~Identifier() {}
};


// ========================
struct LetStatement : public Statement
{
    Token token; // do i need this? in 'Let x', Node::token is 'Let', identifier is 'x'
    std::unique_ptr<Expression> value;
    std::unique_ptr<Identifier> name;

    void statementNode() override {}

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
    std::string tokenLiteral() override { return token.m_literal; }
    ~ReturnStatement() {}
};

//------------

struct ExpressionStatement : public Statement
{
    Token token; // ?
    std::unique_ptr<Expression> expression;

    void statementNode() override {}
    std::string tokenLiteral() override { return token.m_literal; }
    ~ExpressionStatement() {}
};
// ------------------
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
    ~Program() {}
};
