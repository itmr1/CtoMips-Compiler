#include "ast.hpp"

int main()
{
    const Expression *ast=parseAST();
    /*int size=0;
    ast->print(std::cout);
    std::cout<<std::endl;
    ast->CountFrameSize(size);
    //std::cout<<size<<std::endl;
    std::cout<<std::endl;*/
    Data data;
    ast->MipsCodeGen(std::cout, data, 0);
    std::cout<<std::endl;

    return 0;
}