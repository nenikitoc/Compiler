#pragma once

#include "Lexer.h"

Token Lexer::getNextToken()
{
    while(pos < input.size() && isspace(input[pos]))
    {
        pos++;
    }

    if(pos >= input.size())
    {
        return Token(TOKEN_END, "");
    }

    char current = input[pos];

    if(current == '{')
    {
        pos++;
        return Token(TOKEN_OPEN_BRACE, "{");
    }
    else if(current == '}')
    {
        pos++;
        return Token(TOKEN_CLOSE_BRACE, "}");
    }
    else if(current == '(')
    {
        pos++;
        return Token(TOKEN_OPEN_PAREN, "(");
    }
    else if(current == ')')
    {
        pos++;
        return Token(TOKEN_CLOSE_PAREN, ")");
    }
    else if(current == ';')
    {
        pos++;
        return Token(TOKEN_SEMICOLON, ";");
    }
    else if(current == ',')
    {
        pos++;
        return Token(TOKEN_COMMA, ",");
    }
    else if(current == '=')
    {
        pos++;
        return Token(TOKEN_ASSIGN, "=");
    }
    else if(current == '+')
    {
        pos++;
        return Token(TOKEN_PLUS, "+");
    }
    else if(current == '-')
    {
        pos++;
        return Token(TOKEN_MINUS, "-");
    }
    else if(isdigit(current))
    {
        string value;
        while(pos < input.size() && isdigit(input[pos]))
        {
            value += input[pos];
            pos++;
        }
        return Token(TOKEN_NUMBER, value);
    }
    else if(isalpha(current))
    {
        string value;
        while(pos < input.size() && (isalnum(input[pos]) || input[pos] == '_'))
        {
            value += input[pos];
            pos++;
        }

        if(value == "int")
        {
            return Token(TOKEN_TYPE, value);
        }
        else if(value == "return")
        {
            return Token(TOKEN_RETURN, value);
        }
        else
        {
            return Token(TOKEN_ID, value);
        }
    }

    pos++;
    return Token(TOKEN_UNKNOWN, string(1, current));
}