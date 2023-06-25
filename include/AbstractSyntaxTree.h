#pragma once
#include"Token.h"

using namespace interpreter;

struct Node 
{
    Token token;
    virtual ~Node() = default;
};

struct Statement : public Node
{
    virtual ~Statement() = default;
};

struct Expression : public Node
{
    virtual ~Expression() = default;
};

// ========================
struct LetStatement : public Statement
{
    Token identifier; // do i need this? in 'Let x', Node::token is 'Let', identifier is 'x'
    // std::unique_ptr<Expression> expression;
};

struct  ReturnStatement : public Statement
{
    Token identifier;
};

struct Program 
{
    std::vector<std::unique_ptr<Statement>> statements;
};
