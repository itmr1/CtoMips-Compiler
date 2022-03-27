#ifndef ast_unary_hpp
#define ast_unary_hpp

#include <string>
#include <iostream>

class Unary
    : public Expression
{
//private:
  //  ExpressionPtr expr;
protected:
    ExpressionPtr expr;
    Unary(const ExpressionPtr _expr)
        : expr(_expr)
    {}
public:
    virtual ~Unary()
    {
        delete expr;
    }

    virtual const char *getOpcode() const =0;

    ExpressionPtr getExpr() const
    { return expr; }

    virtual void print(std::ostream &dst) const override
    {
        dst << "( ";
        dst << getOpcode();
        dst << " ";
        expr->print(dst);
        dst << " )";
    }
    /*virtual void GetArgs(std::vector<ExpressionPtr> &arglist)const override{
       arglist.pushback(expr)
   }*/
};

class NegOperator
    : public Unary
{
public:
    NegOperator(const ExpressionPtr _expr)
        : Unary(_expr)
    {}

    virtual const char *getOpcode() const override
    { return "-"; }

    virtual void CountFrameSize(int &CurrSize) const override
   {
       expr->CountFrameSize(CurrSize);
   }
   virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg) const override{
        expr->MipsCodeGen(dst,data, DstReg);
        dst<<"sub $"<<DstReg<<",$0"<<",$"<<DstReg<<std::endl;
        //data.registers.free_reg(idx);
    }
};

class BitNotOperator
    : public Unary
{
public:
    BitNotOperator(const ExpressionPtr _expr)
        : Unary(_expr)
    {}

    virtual const char *getOpcode() const override
    { return "~"; }

    virtual void CountFrameSize(int &CurrSize) const override
   {
       expr->CountFrameSize(CurrSize);
   }
   virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg) const override{
        expr->MipsCodeGen(dst,data, DstReg);
        dst<<"nor $"<<DstReg<<",$0"<<",$"<<DstReg<<std::endl;
    }
};

class LogicalNotOperator
    : public Unary
{
public:
    LogicalNotOperator(const ExpressionPtr _expr)
        : Unary(_expr)
    {}

    virtual const char *getOpcode() const override
    { return "!"; }

    virtual void CountFrameSize(int &CurrSize) const override
   {
       expr->CountFrameSize(CurrSize);
   }
   virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg) const override{
        expr->MipsCodeGen(dst,data, DstReg);
        dst<<"slti $"<<DstReg<<",$"<<DstReg<<",1"<<std::endl;
    }
};

#endif