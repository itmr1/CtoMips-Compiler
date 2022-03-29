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
    ExpressionPtr *exprp;
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

    virtual int evaluate(ExpressionPtr) const {
        int e = expr->evaluate();
        return 0-e;
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

    virtual int evaluate(ExpressionPtr) const {
        int e = expr->evaluate();
        return ~e;
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

    virtual int evaluate(ExpressionPtr) const {
        int e = expr->evaluate();
        return !e;
    }
};

class IncrAfterOperator
 : public Unary
{
protected:
    virtual const char *getOpcode() const override
    {return "++";}
public:
    IncrAfterOperator( ExpressionPtr _expr)
        : Unary(_expr)
    {}

    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg)const override{
        std::string name = expr->getId();
        ExpressionPtr arridx = expr->getindex();
        if(arridx!= NULL){
            std::string arrid = name + "0";
            arridx->MipsCodeGen(dst,data,DstReg);
            dst<<"sll $"<<DstReg<<",2"<<std::endl;
            int arroffset = data.Stack.back().bindings[arrid].offset - 4;
            int idx = data.registers.allocate();
            dst<<"addiu $"<<idx<<",$30,"<<arroffset<<std::endl;
            dst<<"addu $"<<idx<<",$"<<idx<<",$"<<DstReg<<std::endl;
            dst<<"lw $"<<DstReg<<",($"<<idx<<")"<<std::endl;
            dst<<"addi $"<<DstReg<<",$"<<DstReg<<",1"<<std::endl;
            dst<<"sw $"<<DstReg<<",($"<<idx<<")"<<std::endl;
            data.registers.free_reg(idx);
        }
        int idx = data.registers.allocate();
        expr->MipsCodeGen(dst,data,DstReg);
        dst<<"addi $"<<DstReg<<",$"<<DstReg<<",1"<<std::endl;
        int varoffset = data.Stack.back().bindings[name].offset;
        dst<<"sw $"<<DstReg<<","<<varoffset<<"($30)"<<std::endl;
        data.registers.free_reg(idx);
    }
};

class IncrBeforeOperator
 : public Unary
{
protected:
    virtual const char *getOpcode() const override
    {return "++";}
public:
    IncrBeforeOperator( ExpressionPtr _expr)
        : Unary(_expr)
    {}

    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg)const override{
        std::string name = expr->getId();
        ExpressionPtr arridx = expr->getindex();
        if(arridx!= NULL){
            std::string arrid = name + "0";
            arridx->MipsCodeGen(dst,data,DstReg);
            dst<<"sll $"<<DstReg<<",2"<<std::endl;
            int arroffset = data.Stack.back().bindings[arrid].offset - 4;
            int idx = data.registers.allocate();
            dst<<"addiu $"<<idx<<",$30,"<<arroffset<<std::endl;
            dst<<"addu $"<<idx<<",$"<<idx<<",$"<<DstReg<<std::endl;
            dst<<"lw $"<<DstReg<<",($"<<idx<<")"<<std::endl;
            dst<<"addi $"<<DstReg<<",$"<<DstReg<<",1"<<std::endl;
            dst<<"sw $"<<DstReg<<",($"<<idx<<")"<<std::endl;
            data.registers.free_reg(idx);
        }
        int idx = data.registers.allocate();
        expr->MipsCodeGen(dst,data,DstReg);
        dst<<"addi $"<<DstReg<<",$"<<DstReg<<",1"<<std::endl;
        int varoffset = data.Stack.back().bindings[name].offset;
        dst<<"sw $"<<DstReg<<","<<varoffset<<"($30)"<<std::endl;
        data.registers.free_reg(idx);
    }
};


class DecrAfterOperator
 : public Unary
{
protected:
    virtual const char *getOpcode() const override
    {return "--";}
public:
    DecrAfterOperator( ExpressionPtr _expr)
        : Unary(_expr)
    {}

    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg)const override{
        std::string name = expr->getId();
        ExpressionPtr arridx = expr->getindex();
        if(arridx!= NULL){
            std::string arrid = name + "0";
            arridx->MipsCodeGen(dst,data,DstReg);
            dst<<"sll $"<<DstReg<<",2"<<std::endl;
            int arroffset = data.Stack.back().bindings[arrid].offset - 4;
            int idx = data.registers.allocate();
            dst<<"addiu $"<<idx<<",$30,"<<arroffset<<std::endl;
            dst<<"addu $"<<idx<<",$"<<idx<<",$"<<DstReg<<std::endl;
            dst<<"lw $"<<DstReg<<",($"<<idx<<")"<<std::endl;
            dst<<"subi $"<<DstReg<<",$"<<DstReg<<",1"<<std::endl;
            dst<<"sw $"<<DstReg<<",($"<<idx<<")"<<std::endl;
            data.registers.free_reg(idx);
        }
        int idx = data.registers.allocate();
        expr->MipsCodeGen(dst,data,DstReg);
        dst<<"subi $"<<DstReg<<",$"<<DstReg<<",1"<<std::endl;
        int varoffset = data.Stack.back().bindings[name].offset;
        dst<<"sw $"<<DstReg<<","<<varoffset<<"($30)"<<std::endl;
        data.registers.free_reg(idx);
    }
};

class DecrBeforeOperator
 : public Unary
{
protected:
    virtual const char *getOpcode() const override
    {return "--";}
public:
    DecrBeforeOperator( ExpressionPtr _expr)
        : Unary(_expr)
    {}

    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg)const override{
        std::string name = expr->getId();
        ExpressionPtr arridx = expr->getindex();
        if(arridx!= NULL){
            std::string arrid = name + "0";
            arridx->MipsCodeGen(dst,data,DstReg);
            dst<<"sll $"<<DstReg<<",2"<<std::endl;
            int arroffset = data.Stack.back().bindings[arrid].offset - 4;
            int idx = data.registers.allocate();
            dst<<"addiu $"<<idx<<",$30,"<<arroffset<<std::endl;
            dst<<"addu $"<<idx<<",$"<<idx<<",$"<<DstReg<<std::endl;
            dst<<"lw $"<<DstReg<<",($"<<idx<<")"<<std::endl;
            dst<<"subi $"<<DstReg<<",$"<<DstReg<<",1"<<std::endl;
            dst<<"sw $"<<DstReg<<",($"<<idx<<")"<<std::endl;
            data.registers.free_reg(idx);
        }
        int idx = data.registers.allocate();
        expr->MipsCodeGen(dst,data,DstReg);
        dst<<"subi $"<<DstReg<<",$"<<DstReg<<",1"<<std::endl;
        int varoffset = data.Stack.back().bindings[name].offset;
        dst<<"sw $"<<DstReg<<","<<varoffset<<"($30)"<<std::endl;
        data.registers.free_reg(idx);
    }
};

#endif