#pragma once

#include "Interpreter.h"

// ��������� ���������� ����������
void Interpreter::evaluateDescriptions(ASTNode* node)
{
    for(auto child : node->children)
    {
        if(child->type == "Descr")
        {
            // ������������ ���������� � �������� ����������
            for(size_t i = 1; i < child->children.size(); i++)
            {
                auto varList = child->children[i];
                for(auto var : varList->children)
                {
                    variables[var->value] = 0;
                }
            }
        }
    }
}

// ��������� ����������
void Interpreter::evaluateOperators(ASTNode* node)
{
    for(auto child : node->children)
    {
        if(child->type == "Op")
        {
            // �������� ������������: Id = Expr;
            string varName = child->children[0]->value;
            int value = evaluateExpr(child->children[1]);
            variables[varName] = value;
        }
    }
}

// ��������� �������� ��������
int Interpreter::evaluateEnd(ASTNode* node)
{
    return variables.at(node->children[0]->value);
}

// ���������� ���������
int Interpreter::evaluateExpr(ASTNode* node)
{
    if(node->type == "Id")
    {
        return variables.at(node->value);
    }
    else if(node->type == "Const")
    {
        return stoi(node->value);
    }
    else if(node->type == "BinOp")
    {
        int left = evaluateExpr(node->children[0]);
        int right = evaluateExpr(node->children[1]);

        if(node->value == "+")
        {
            return left + right;
        }
        else if(node->value == "-")
        {
            return left - right;
        }
    }
    throw runtime_error("Unknown type of expression");
}

int Interpreter::evaluate(ASTNode* node)
{
    if(node->type == "Function")
    {
        // ������� ������� �������� ����� ����������� ����� �������
        variables.clear();

        // ��������� ��� ����� �������
        for(auto child : node->children)
        {
            if(child->type == "Descriptions")
            {
                evaluateDescriptions(child);
            }
            else if(child->type == "Operators")
            {
                evaluateOperators(child);
            }
            else if(child->type == "End")
            {
                return evaluateEnd(child);
            }
        }
    }
}
