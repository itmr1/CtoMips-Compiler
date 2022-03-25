#include "ast.hpp"

int main()
{
    const Expression *ast=parseAST();
    int size=0;
    ast->print(std::cout);
    ast->CountFrameSize(size);
    std::cout<<size<<std::endl;
    std::cout<<std::endl;

    return 0;
}