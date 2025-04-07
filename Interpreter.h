#pragma once

#include "Lexer.h"
#include "Parser.h"

class Interpreter
{
private:
    // ������� �������� ��� �������� ����������
    unordered_map<string, int> variables;

    // ��������� ���������� ����������
    void evaluateDescriptions(ASTNode* node);

    // ��������� ����������
    void evaluateOperators(ASTNode* node);

    // ��������� �������� ��������
    int evaluateEnd(ASTNode* node);

    // ���������� ���������
    int evaluateExpr(ASTNode* node);

public:
    Interpreter() {}

    int evaluate(ASTNode* node);
};