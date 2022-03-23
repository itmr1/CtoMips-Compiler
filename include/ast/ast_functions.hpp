#ifndef ast_functions_hpp
#define ast_functions_hpp

#include "ast_expression.hpp"

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
       if(Args) Args->CountFrameSize(CurrSize);
       Statement->CountFrameSize(CurrSize);
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