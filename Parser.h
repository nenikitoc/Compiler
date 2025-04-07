#pragma once

#include "Lexer.h"

struct ASTNode
{
    string type;
    string value;
    vector<ASTNode*> children;

    ASTNode(string t, string v = "") : type(t), value(v) {}
};

class Parser
{
private:
    Lexer& lexer;
    Token currentToken;

public:
    Parser(Lexer& lexer) : lexer(lexer)
    {
        currentToken = lexer.getNextToken();
    }

    void error()
    {
        throw runtime_error("Incorrect syntax");
    }

    void eat(TokenType type)
    {
        if(currentToken.type == type)
        {
            currentToken = lexer.getNextToken();
        }
        else
        {
            error();
        }
    }

    // Id → id_name
    ASTNode* parseId();

    // Const → int_num
    ASTNode* parseConst();

    // SimpleExpr → Id | Const
    ASTNode* parseSimpleExpr();

    // Expr → SimpleExpr | SimpleExpr + Expr | SimpleExpr - Expr
    ASTNode* parseExpr();

    // Op → Id = Expr ;
    ASTNode* parseOp();

    // Operators → Op | Op Operators
    ASTNode* parseOperators();

    // Остальные методы остаются без изменений
    ASTNode* parseType();

    ASTNode* parseVarList();

    ASTNode* parseDescr();

    ASTNode* parseDescriptions();

    ASTNode* parseFunctionName();

    ASTNode* parseEnd();

    ASTNode* parseBegin();

    ASTNode* parseFunction();

    ASTNode* parse();
};