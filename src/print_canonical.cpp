#include "ast.hpp"
#include <fstream>
int main(int argc, char *argv[])
{
    const Expression *ast=parseAST(argv[2]);
    //int size=0;
    //ast->print(std::cout);
    //std::cout<<std::endl;
    //ast->CountFrameSize(size);
    //std::cout<<size<<std::endl;
    //std::cout<<std::endl;
    Data data;
    std::ofstream output(argv[4], std::ofstream::out);
    ast->MipsCodeGen(output, data, 2);
    output.close();
    //std::cout<<std::endl;

    return 0;
} 