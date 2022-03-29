#ifndef ast_operators_hpp
#define ast_operators_hpp


#include <string>
#include <iostream>
#include <cmath>
//#include "context.hpp"

class Operator
    : public Expression
{
/*private:
    ExpressionPtr left;
    ExpressionPtr right;*/
protected:
    ExpressionPtr left;
    ExpressionPtr right;
    Operator(ExpressionPtr _left, ExpressionPtr _right)
        : left(_left)
        , right(_right)
    {}
public:
    virtual ~Operator()
    {
        delete left;
        delete right;
    }

    virtual const char *getOpcode() const =0;

    ExpressionPtr getLeft() const
    { return left; }

    ExpressionPtr getRight() const
    { return right; }

    virtual void print(std::ostream &dst) const override
    {
        dst<<"( ";
        left->print(dst);
        dst<<" ";
        dst<<getOpcode();
        dst<<" ";
        right->print(dst);
        dst<<" )";
    }
    virtual void CountFrameSize(int &CurrSize) const override
    {
       left->CountFrameSize(CurrSize);
       right->CountFrameSize(CurrSize);
    }
    virtual void MipsCodeGen(std::ostream &dst,Data &data,int DestReg) const override{}
};

class AddOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
public:
    AddOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg) const override{
        if(left->IsFuncCall()){
            int idx = data.registers.allocate();
            left->MipsCodeGen(dst,data, DstReg);
            std::string tmp_reg = data.registers.make_regname(idx);
            dst<<"move "<<tmp_reg<<",$"<<DstReg<<std::endl;
            right->MipsCodeGen(dst,data, DstReg);
            dst<<"add $"<<DstReg<<",$"<<DstReg<<","<<tmp_reg<<std::endl;
            data.registers.free_reg(idx);
        }
        else{
        int idx = data.registers.allocate();
        right->MipsCodeGen(dst,data, DstReg);
        std::string tmp_reg = data.registers.make_regname(idx);
        dst<<"move "<<tmp_reg<<",$"<<DstReg<<std::endl;
        left->MipsCodeGen(dst,data, DstReg);
        dst<<"add $"<<DstReg<<",$"<<DstReg<<","<<tmp_reg<<std::endl;
        data.registers.free_reg(idx);
        }
    }
        virtual int evaluate() const override {
        int l = left->evaluate();
        int r = right->evaluate();
        return l+r;
    }
};

class SubOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "-"; }
public:
    SubOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg) const override{
        if(left->IsFuncCall()){
            int idx = data.registers.allocate();
            left->MipsCodeGen(dst,data, DstReg);
            std::string tmp_reg = data.registers.make_regname(idx);
            dst<<"move "<<tmp_reg<<",$"<<DstReg<<std::endl;
            right->MipsCodeGen(dst,data, DstReg);
            dst<<"sub $"<<DstReg<<",$"<<tmp_reg<<","<<DstReg<<std::endl;
            data.registers.free_reg(idx);
        }
        else{
        int idx = data.registers.allocate();
        right->MipsCodeGen(dst,data, DstReg);
        std::string tmp_reg = data.registers.make_regname(idx);
        dst<<"move "<<tmp_reg<<",$"<<DstReg<<std::endl;
    
        left->MipsCodeGen(dst,data, DstReg);
        dst<<"sub $"<<DstReg<<",$"<<DstReg<<","<<tmp_reg<<std::endl;
        data.registers.free_reg(idx);
        }
    }

    virtual int evaluate() const override {
        int l = left->evaluate();
        int r = right->evaluate();
        return l-r;
    }
};


class MulOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "*"; }
public:
    MulOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg) const override{
        if(left->IsFuncCall()){
            int idx = data.registers.allocate();
            left->MipsCodeGen(dst,data, DstReg);
            std::string tmp_reg = data.registers.make_regname(idx);
            dst<<"move "<<tmp_reg<<",$"<<DstReg<<std::endl;
            right->MipsCodeGen(dst,data, DstReg);
            dst<<"mult $"<<DstReg<<","<<tmp_reg<<std::endl;
            dst<<"mflo $"<<DstReg<<std::endl;
            data.registers.free_reg(idx);
        }
        else{
        int idx = data.registers.allocate();
        right->MipsCodeGen(dst,data, DstReg);
        std::string tmp_reg = data.registers.make_regname(idx);
        dst<<"move "<<tmp_reg<<",$"<<DstReg<<std::endl;
        left->MipsCodeGen(dst,data, DstReg);
        dst<<"mult $"<<DstReg<<","<<tmp_reg<<std::endl;
        dst<<"mflo $"<<DstReg<<std::endl;
        data.registers.free_reg(idx);
        }
    }

    virtual int evaluate() const override{
        int l = left->evaluate();
        int r = right->evaluate();
        return l*r;
    }
};

class DivOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "/"; }
public:
    DivOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg) const override{
        if(left->IsFuncCall()){
            int idx = data.registers.allocate();
            left->MipsCodeGen(dst,data, DstReg);
            std::string tmp_reg = data.registers.make_regname(idx);
            dst<<"move "<<tmp_reg<<",$"<<DstReg<<std::endl;
            right->MipsCodeGen(dst,data, DstReg);
            dst<<"div $"<<tmp_reg<<","<<DstReg<<std::endl;
            dst<<"mflo $"<<DstReg<<std::endl;
            data.registers.free_reg(idx);
        }
        else{
        int idx = data.registers.allocate();
        right->MipsCodeGen(dst,data, DstReg);
        std::string tmp_reg = data.registers.make_regname(idx);
        dst<<"move "<<tmp_reg<<",$"<<DstReg<<std::endl;
        left->MipsCodeGen(dst,data, DstReg);
        dst<<"div $"<<DstReg<<","<<tmp_reg<<std::endl;
        dst<<"mflo $"<<DstReg<<std::endl;
        data.registers.free_reg(idx);
        }
    }
    virtual int evaluate() const override{
        int l = left->evaluate();
        int r = right->evaluate();
        return l/r;
    }
};

class ModOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "%"; }
public:
    ModOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg) const override{
        if(left->IsFuncCall()){
            int idx = data.registers.allocate();
            left->MipsCodeGen(dst,data, DstReg);
            std::string tmp_reg = data.registers.make_regname(idx);
            dst<<"move "<<tmp_reg<<",$"<<DstReg<<std::endl;
            right->MipsCodeGen(dst,data, DstReg);
            dst<<"div $"<<tmp_reg<<","<<DstReg<<std::endl;
            dst<<"mfhi $"<<DstReg<<std::endl;
            data.registers.free_reg(idx);
        }
        else{
        int idx = data.registers.allocate();
        right->MipsCodeGen(dst,data, DstReg);
        std::string tmp_reg = data.registers.make_regname(idx);
        dst<<"move "<<tmp_reg<<",$"<<DstReg<<std::endl;
        left->MipsCodeGen(dst,data, DstReg);
        dst<<"div $"<<DstReg<<","<<tmp_reg<<std::endl;
        dst<<"mfhi $"<<DstReg<<std::endl;
        data.registers.free_reg(idx);
        }
    }

    virtual int evaluate() const override {
        int l = left->evaluate();
        int r = right->evaluate();
        return l%r;
    }
};

class BitwiseAndOperator
 : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {return "&";}
public:
    BitwiseAndOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
     virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg) const override{
        if(left->IsFuncCall()){
            int idx = data.registers.allocate();
            left->MipsCodeGen(dst,data, DstReg);
            std::string tmp_reg = data.registers.make_regname(idx);
            dst<<"move "<<tmp_reg<<",$"<<DstReg<<std::endl;
            right->MipsCodeGen(dst,data, DstReg);
            dst<<"and $"<<DstReg<<",$"<<tmp_reg<<","<<DstReg<<std::endl;
            data.registers.free_reg(idx);
        }
        else{
        int idx = data.registers.allocate();
        right->MipsCodeGen(dst,data, DstReg);
        std::string tmp_reg = data.registers.make_regname(idx);
        dst<<"move "<<tmp_reg<<",$"<<DstReg<<std::endl;
        left->MipsCodeGen(dst,data, DstReg);
        dst<<"and $"<<DstReg<<",$"<<DstReg<<","<<tmp_reg<<std::endl;
        data.registers.free_reg(idx);
        }
    }

    virtual int evaluate(ExpressionPtr) const {
        int l = left->evaluate();
        int r = right->evaluate();
        return l&r;
    }
};

class BitwiseOrOperator
 : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {return "|";}
public:
    BitwiseOrOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
     virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg) const override{
        if(left->IsFuncCall()){
            int idx = data.registers.allocate();
            left->MipsCodeGen(dst,data, DstReg);
            std::string tmp_reg = data.registers.make_regname(idx);
            dst<<"move "<<tmp_reg<<",$"<<DstReg<<std::endl;
            right->MipsCodeGen(dst,data, DstReg);
            dst<<"or $"<<DstReg<<",$"<<tmp_reg<<","<<DstReg<<std::endl;
            data.registers.free_reg(idx);
        }
        else{
        int idx = data.registers.allocate();
        right->MipsCodeGen(dst,data, DstReg);
        std::string tmp_reg = data.registers.make_regname(idx);
        dst<<"move "<<tmp_reg<<",$"<<DstReg<<std::endl;
        left->MipsCodeGen(dst,data, DstReg);
        dst<<"or $"<<DstReg<<",$"<<DstReg<<","<<tmp_reg<<std::endl;
        data.registers.free_reg(idx);
        }
    }
    virtual int evaluate(ExpressionPtr) const {
        int l = left->evaluate();
        int r = right->evaluate();
        return l|r;
    }
};

class BitwiseXorOperator
 : public Operator
{
protected:
    virtual const char *getOpcode() const override
    {return "^";}
public:
    BitwiseXorOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
     virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg) const override{
        if(left->IsFuncCall()){
            int idx = data.registers.allocate();
            left->MipsCodeGen(dst,data, DstReg);
            std::string tmp_reg = data.registers.make_regname(idx);
            dst<<"move "<<tmp_reg<<",$"<<DstReg<<std::endl;
            right->MipsCodeGen(dst,data, DstReg);
            dst<<"xor $"<<DstReg<<",$"<<tmp_reg<<","<<DstReg<<std::endl;
            data.registers.free_reg(idx);
        }
        else{
        int idx = data.registers.allocate();
        right->MipsCodeGen(dst,data, DstReg);
        std::string tmp_reg = data.registers.make_regname(idx);
        dst<<"move "<<tmp_reg<<",$"<<DstReg<<std::endl;
        left->MipsCodeGen(dst,data, DstReg);
        dst<<"xor $"<<DstReg<<",$"<<DstReg<<","<<tmp_reg<<std::endl;
        data.registers.free_reg(idx);
        }
    }

    virtual int evaluate(ExpressionPtr) const {
        int l = left->evaluate();
        int r = right->evaluate();
        return l^r;
    }
};


#endif