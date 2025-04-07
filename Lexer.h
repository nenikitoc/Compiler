#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_map>
#include <stdexcept>

using namespace std;

enum TokenType
{
    TOKEN_TYPE,        // int
    TOKEN_ID,          // идентификатор
    TOKEN_NUMBER,      // числовая константа
    TOKEN_OPEN_BRACE,  // {
    TOKEN_CLOSE_BRACE, // }
    TOKEN_OPEN_PAREN,  // (
    TOKEN_CLOSE_PAREN, // )
    TOKEN_SEMICOLON,   // ;
    TOKEN_COMMA,       // ,
    TOKEN_RETURN,      // return
    TOKEN_ASSIGN,      // =
    TOKEN_PLUS,        // +
    TOKEN_MINUS,       // -
    TOKEN_END,         // конец входных данных
    TOKEN_UNKNOWN      // неизвестный токен
};

struct Token
{
    TokenType type;
    string value;

    Token() = default;
    Token(TokenType type, string value) : type(type), value(value) {}
};

class Lexer
{
public:
    Lexer(const string& input) : input(input), pos(0) {}

    Token getNextToken();

private:
    string input;
    size_t pos;
};