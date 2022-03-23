#ifndef ast_operators_hpp
#define ast_operators_hpp


#include <string>
#include <iostream>
#include <cmath>
#include context.hpp

class Operator
    : public Expression
{
private:
    ExpressionPtr left;
    ExpressionPtr right;
protected:
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

    virtual std::string MipsCodeGen(std::ostream &dst,Data &data,int DestReg) const override{}
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
        left->MipsCodeGen(std::ostream &dst,data, DstReg);
        int idx = data.registers.allocate()
        std::string tmp_reg = make_regname(idx);
        dst<<"move "<<tmp_reg<<" " <<DstReg<<std::endl;
        right->MipsCodeGen(std::ostream &dst,data, DstReg);
        dst<<"add "<<DstReg<<" "<<DstReg<<" "<<tmp_reg<<std::endl;
        data.registers.free_reg(idx);
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

    virtual void MipsCodeGen(std::ostream &dst, std::string DstReg) const override{
        right->MipsCodeGen(std::ostream &dst, DstReg);
        int idx = Registers.allocate()
        std::string tmp_reg = make_regname(idx);
        dst<<"move "<<tmp_reg<<" " <<DstReg<<std::endl;
        left->MipsCodeGen(std::ostream &dst, DstReg);
        dst<<"sub "<<DstReg<<" "<<DstReg<<" "<<tmp_reg<<std::endl;
        Registers.free_reg(idx);
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

    virtual void MipsCodeGen(std::ostream &dst, std::string DstReg){
        left->MipsCodeGen(std::ostream &dst, DstReg);
        int idx = Registers.allocate()
        std::string tmp_reg = make_regname(idx);
        dst<<"move "<<tmp_reg<<" " <<DstReg<<std::endl;
        right->MipsCodeGen(std::ostream &dst, DstReg);
        dst<<"mul "<<DstReg<<" "<<tmp_reg<<std::endl;
        dst<<"mflo "<<DstReg<<std::endl;
        Registers.free_reg(idx);
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

    virtual void MipsCodeGen(std::ostream &dst, std::string DstReg){
        left->MipsCodeGen(std::ostream &dst, DstReg);
        int idx = Registers.allocate()
        std::string tmp_reg = make_regname(idx);
        dst<<"move "<<tmp_reg<<" " <<DstReg<<std::endl;
        right->MipsCodeGen(std::ostream &dst, DstReg);
        dst<<"div "<<DstReg<<" "<<tmp_reg<<std::endl;
        dst<<"mfhi "<<DstReg<<" "<<std::endl;
        Registers.free_reg(idx);
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
    virtual void MipsCodeGen(std::ostream &dst, std::string DstReg){
        right->MipsCodeGen(std::ostream &dst, DstReg);
        int idx = Registers.allocate()
        std::string tmp_reg = make_regname(idx);
        dst<<"move "<<tmp_reg<<" " <<DstReg<<std::endl;
        left->MipsCodeGen(std::ostream &dst, DstReg);
        dst<<"div "<<DstReg<<" "<<tmp_reg<<std::endl;
        dst<<"mflo "<<DstReg<<" "<<std::endl;
        Registers.free_reg(idx);
    }
};


#endif