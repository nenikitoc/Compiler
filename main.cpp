#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include <string>

using namespace std;

void printAST(ASTNode* node, int depth = 0)
{
    if(node == nullptr) return;

    for(int i = 0; i < depth; i++)
    {
        cout << "  ";
    }
    cout << node->type;

    if(!node->value.empty())
    {
        cout << " (" << node->value << ")";
    }
    cout << endl;

    for(ASTNode* child : node->children)
    {
        printAST(child, depth + 1);
    }
}

int main()
{
    string input =
        "int func_name() {" 
        "int a, b, c;" 
        "a = 10 + 10;" 
        "a = 20 + 1000;" 
        "b = a - 3;" 
        "c = a + b;" 
        "return c; }";

    try
    {
        Lexer lexer(input);
        Parser parser(lexer);
        ASTNode* ast = parser.parse();

        cout << "AST-tree:" << endl;
        printAST(ast);

        Interpreter interpreter;
        int result = interpreter.evaluate(ast);
        cout << "Result: " << result << endl;

    }
    catch(const exception& e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}