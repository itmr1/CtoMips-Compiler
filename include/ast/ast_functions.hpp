#ifndef ast_functions_hpp
#define ast_functions_hpp

//#include "ast_expression.hpp"
//#include "context.hpp"

#include <string>
#include <iostream>
#include <cmath>

class Function
    : public Expression
{
private:
    std::string type;
    ExpressionPtr Declarator;
    ExpressionPtr Args;
    ExpressionPtr Statement;

public:
    Function(const std::string &_type, ExpressionPtr _Declarator, ExpressionPtr _Args, ExpressionPtr _Statement)
        : type(_type)
        , Declarator(_Declarator)
        , Args(_Args)
        , Statement(_Statement)
    {}

    Function(const std::string &_type, ExpressionPtr _Declarator,ExpressionPtr _Statement)
        : type(_type)
        , Declarator(_Declarator)
        , Statement(_Statement)
    {}

    virtual ~Function()
    {
        delete Declarator;
        delete Args;
        delete Statement;
    }

     const std::string getType() const
    { return type; }

    virtual void print(std::ostream &dst) const override
    {   
        dst<<getType();
        dst<<" ";
        Declarator->print(dst);
        dst<<"(";
        if(Args) Args->print(dst);
        dst<<"){";
        Statement->print(dst);
        dst<<"}";
    }

    virtual void CountFrameSize(int &CurrSize) const override
   {
       CurrSize = 0;
       if(Args){Args->CountFrameSize(CurrSize);}
       Statement->CountFrameSize(CurrSize);
       //std::cout<<"size of variables: "<<CurrSize<<std::endl;
       
   }

   virtual void MipsCodeGen(std::ostream &dst, Data &data, int DstReg)const override{
        
        std::string label = Declarator->getId();
        dst<<label<<": "<<std::endl;
        stackframe func;
        data.Stack.push_back(func);
        data.Stack.back().frameSize = 0;
        CountFrameSize(data.Stack.back().frameSize);
        data.Stack.back().frameSize+=2;
        int frealsize = data.Stack.back().frameSize*4;
        dst<<"addiu"<<" $29,"<<"$29,"<<"-"<<frealsize<<std::endl;
        dst<<"sw"<<" $30,"<<frealsize - 4<<"($29)"<<std::endl;
        dst<<"move"<<" $30,$29"<<std::endl;
        if(Args){
            int ArgSize = 0;
            Args->CountFrameSize(ArgSize);
            Args->MipsCodeGen(dst, data, DstReg);
            for(int i = 4; i<ArgSize+4; i++){
                dst<<"sw $"<<i<<","<<4*(i-3)<<"($29)"<<std::endl;
            }
             
        }
        data.CurrLabel = data.MakeLabel("EoF");
        Statement->MipsCodeGen(dst, data, DstReg);
        dst<<data.CurrLabel<<":"<<std::endl;
        dst<<"lw"<<" $30,"<<frealsize - 4<<"($29)"<<std::endl;
        dst<<"addiu"<<" $29,"<<"$29,"<<frealsize<<std::endl;
        dst<<"j $31"<<std::endl;
        dst<<"nop"<<std::endl;
    }

};

class FuncNoArgs
    : public Function
{
public:
    FuncNoArgs(const std::string &_type, ExpressionPtr _Declarator,ExpressionPtr _Statement)
        : Function(_type, _Declarator, _Statement)
    {}
    /*virtual void MipsCodeGen(std::ostream &dst, std::string DstReg) const override{
        //TODO
    }*/
    
};

class FuncWithArgs
    : public Function
{
public:
    FuncWithArgs(const std::string &_type, ExpressionPtr _Declarator,ExpressionPtr _Args,ExpressionPtr _Statement)
        : Function(_type, _Declarator,_Args, _Statement)
    {}
    /*virtual void MipsCodeGen(std::ostream &dst, std::string DstReg) const override{
        //TODO
    }*/
};

#endif