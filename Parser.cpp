#pragma once

#include "Parser.h"

ASTNode* Parser::parseId()
{
    if(currentToken.type != TOKEN_ID)
    {
        error();
    }
    ASTNode* node = new ASTNode("Id", currentToken.value);
    eat(TOKEN_ID);
    return node;
}

// Const → int_num
ASTNode* Parser::parseConst()
{
    if(currentToken.type != TOKEN_NUMBER)
    {
        error();
    }
    ASTNode* node = new ASTNode("Const", currentToken.value);
    eat(TOKEN_NUMBER);
    return node;
}

// SimpleExpr → Id | Const
ASTNode* Parser::parseSimpleExpr()
{
    if(currentToken.type == TOKEN_ID)
    {
        return parseId();
    }
    else if(currentToken.type == TOKEN_NUMBER)
    {
        return parseConst();
    }
    else
    {
        error();
        return nullptr;
    }
}

// Expr → SimpleExpr | SimpleExpr + Expr | SimpleExpr - Expr
ASTNode* Parser::parseExpr()
{
    ASTNode* node = parseSimpleExpr();

    if(currentToken.type == TOKEN_PLUS || currentToken.type == TOKEN_MINUS)
    {
        ASTNode* opNode = new ASTNode("BinOp", currentToken.value);
        eat(currentToken.type);
        opNode->children.push_back(node);
        opNode->children.push_back(parseExpr());
        return opNode;
    }

    return node;
}

// Op → Id = Expr ;
ASTNode* Parser::parseOp()
{
    ASTNode* node = new ASTNode("Op");

    node->children.push_back(parseId());
    eat(TOKEN_ASSIGN);
    node->children.push_back(parseExpr());
    eat(TOKEN_SEMICOLON);

    return node;
}

// Operators → Op | Op Operators
ASTNode* Parser::parseOperators()
{
    ASTNode* node = new ASTNode("Operators");

    node->children.push_back(parseOp());

    while(currentToken.type == TOKEN_ID)
    {
        node->children.push_back(parseOp());
    }

    return node;
}

// Остальные методы остаются без изменений
ASTNode* Parser::parseType()
{
    if(currentToken.type != TOKEN_TYPE)
    {
        error();
    }
    ASTNode* node = new ASTNode("Type", currentToken.value);
    eat(TOKEN_TYPE);
    return node;
}

ASTNode* Parser::parseVarList()
{
    ASTNode* node = new ASTNode("VarList");

    node->children.push_back(parseId());

    while(currentToken.type == TOKEN_COMMA)
    {
        eat(TOKEN_COMMA);
        node->children.push_back(parseId());
    }

    return node;
}

ASTNode* Parser::parseDescr()
{
    ASTNode* node = new ASTNode("Descr");

    node->children.push_back(parseType());
    node->children.push_back(parseVarList());
    eat(TOKEN_SEMICOLON);

    return node;
}

ASTNode* Parser::parseDescriptions()
{
    ASTNode* node = new ASTNode("Descriptions");

    node->children.push_back(parseDescr());

    while(currentToken.type == TOKEN_TYPE)
    {
        node->children.push_back(parseDescr());
    }

    return node;
}

ASTNode* Parser::parseFunctionName()
{
    return parseId();
}

ASTNode* Parser::parseEnd()
{
    ASTNode* node = new ASTNode("End");

    eat(TOKEN_RETURN);
    node->children.push_back(parseId());
    eat(TOKEN_SEMICOLON);
    eat(TOKEN_CLOSE_BRACE);

    return node;
}

ASTNode* Parser::parseBegin()
{
    ASTNode* node = new ASTNode("Begin");

    node->children.push_back(parseType());
    node->children.push_back(parseFunctionName());
    eat(TOKEN_OPEN_PAREN);
    eat(TOKEN_CLOSE_PAREN);
    eat(TOKEN_OPEN_BRACE);

    return node;
}

ASTNode* Parser::parseFunction()
{
    ASTNode* node = new ASTNode("Function");

    node->children.push_back(parseBegin());
    node->children.push_back(parseDescriptions());
    node->children.push_back(parseOperators());
    node->children.push_back(parseEnd());

    return node;
}

ASTNode* Parser::parse()
{
    return parseFunction();
}