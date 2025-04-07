#pragma once

#include "Lexer.h"
#include "Parser.h"

class Interpreter
{
private:
    // Таблица символов для хранения переменных
    unordered_map<string, int> variables;

    // Обработка объявлений переменных
    void evaluateDescriptions(ASTNode* node);

    // Обработка операторов
    void evaluateOperators(ASTNode* node);

    // Обработка возврата значения
    int evaluateEnd(ASTNode* node);

    // Вычисление выражения
    int evaluateExpr(ASTNode* node);

public:
    Interpreter() {}

    int evaluate(ASTNode* node);
};