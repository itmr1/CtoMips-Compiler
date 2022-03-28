#ifndef ast_expression_hpp
#define ast_expression_hpp

#include "context.hpp"
#include <string>
#include <iostream>
#include <map>
#include <vector>

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
    virtual void GetArgs(std::vector<ExpressionPtr> &arglist) const {return;}
    virtual ExpressionPtr getindex() const { return NULL;}
    virtual int evaluate() const {return 0;}
};

class SingleExpr
    : public Expression
{
private:
    ExpressionPtr expr;
public:
    SingleExpr(ExpressionPtr _expr)
        : expr(_expr)       
    {}
    virtual ~SingleExpr()
    {
        delete expr;
    }
    virtual void print(std::ostream &dst) const override
    {   

        expr->print(dst);
    }

    virtual void CountFrameSize(int &CurrSize) const override
   {
       expr->CountFrameSize(CurrSize);
   }

   virtual void MipsCodeGen(std::ostream &dst, Data &data, int DstReg)const override{
       expr->MipsCodeGen(dst, data, DstReg);
   }
   virtual void GetArgs(std::vector<ExpressionPtr> &arglist)const override{
        //std::cout<<"hello";
        arglist.push_back(expr);
   }

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
   virtual void GetArgs(std::vector<ExpressionPtr> &arglist)const override{
        left->GetArgs(arglist);
        right->GetArgs(arglist);
        
   }

};

#endif