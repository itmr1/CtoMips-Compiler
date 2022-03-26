#ifndef ast_expression_hpp
#define ast_expression_hpp

#include "context.hpp"
#include <string>
#include <iostream>
#include <map>

#include <memory>

class Expression;

typedef const Expression *ExpressionPtr;

class Expression
{
public:
    virtual ~Expression()
    {}
    //! Tell and expression to print itself to the given stream
    virtual void print(std::ostream &dst) const =0;
    virtual std::string getId()const {return "";}
    virtual void MipsCodeGen(std::ostream &dst, Data &data, int DstReg)const {return;}
    virtual void CountFrameSize(int &CurrSize)const {return;}
};

class RecExpr
    : public Expression
{
private:
    ExpressionPtr left;
    ExpressionPtr right;
public:
    RecExpr(ExpressionPtr _left, ExpressionPtr _right)
        : left(_left)
        , right(_right)       
    {}
    virtual ~RecExpr()
    {
        delete left;
        delete right;
    }
    virtual void print(std::ostream &dst) const override
    {   

        left->print(dst);
        dst<<" ";
        right->print(dst);
    }

    virtual void CountFrameSize(int &CurrSize) const override
   {
       left->CountFrameSize(CurrSize);
       right->CountFrameSize(CurrSize);
   }

   virtual void MipsCodeGen(std::ostream &dst, Data &data, int DstReg)const override{
       left->MipsCodeGen(dst, data, DstReg);
       right->MipsCodeGen(dst, data, DstReg);
   }

};

#endif