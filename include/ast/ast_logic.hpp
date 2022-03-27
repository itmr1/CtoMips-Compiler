#ifndef ast_logic_hpp
#define ast_logic_hpp

#include <string>
#include <iostream>
#include <cmath>

class Logic 
    : public Expression
{
private:
    ExpressionPtr left;
    ExpressionPtr right;
protected:
    Logic(ExpressionPtr _left, ExpressionPtr _right)
        :left(_left)
        , right(_right)
    {}
public:
    virtual ~Logic()
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
        left->print(dst);
        dst<<" ";
        dst<<getOpcode();
        dst<<" ";
        right->print(dst);
    }
};

class EqOperator
 : public Logic
{
protected:
    virtual const char *getOpcode() const override
    {return "==";}
public:
    EqOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Logic(_left, _right)
    {}
    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg) const override{
        left->MipsCodeGen(dst,data, DstReg);
        int idx = data.registers.allocate();
        std::string tmp_reg = data.registers.make_regname(idx);
        dst<<"move "<<tmp_reg<<",$"<<DstReg<<std::endl;
        right->MipsCodeGen(dst,data, DstReg);
        dst<<"xor $"<<DstReg<<",$"<<DstReg<<","<<tmp_reg<<std::endl;
        dst<<"slti $"<<DstReg<<",$"<<DstReg<<"1"<<std::endl;
        data.registers.free_reg(idx);
    }
};

class NeqOperator
 : public Logic
{
protected:
    virtual const char *getOpcode() const override
    {return "!=";}
public:
    NeqOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Logic(_left, _right)
    {}
    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg) const override{
        left->MipsCodeGen(dst,data, DstReg);
        int idx = data.registers.allocate();
        std::string tmp_reg = data.registers.make_regname(idx);
        dst<<"move "<<tmp_reg<<",$"<<DstReg<<std::endl;
        right->MipsCodeGen(dst,data, DstReg);
        dst<<"xor $"<<DstReg<<",$"<<DstReg<<","<<tmp_reg<<std::endl;
        dst<<"slt $"<<DstReg<<",$0,"<<DstReg<<std::endl;
        data.registers.free_reg(idx);
    }
};

class BitwiseAndOperator
 : public Logic
{
protected:
    virtual const char *getOpcode() const override
    {return "&";}
public:
    BitwiseAndOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Logic(_left, _right)
    {}
    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg) const override{
        left->MipsCodeGen(dst,data, DstReg);
        int idx = data.registers.allocate();
        std::string tmp_reg = data.registers.make_regname(idx);
        dst<<"move "<<tmp_reg<<",$"<<DstReg<<std::endl;
        right->MipsCodeGen(dst,data, DstReg);
        dst<<"and $"<<DstReg<<",$"<<DstReg<<","<<tmp_reg<<std::endl;
        data.registers.free_reg(idx);
    }
};

class BitwiseOrOperator
 : public Logic
{
protected:
    virtual const char *getOpcode() const override
    {return "|";}
public:
    BitwiseOrOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Logic(_left, _right)
    {}
    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg) const override{
        left->MipsCodeGen(dst,data, DstReg);
        int idx = data.registers.allocate();
        std::string tmp_reg = data.registers.make_regname(idx);
        dst<<"move "<<tmp_reg<<",$"<<DstReg<<std::endl;
        right->MipsCodeGen(dst,data, DstReg);
        dst<<"or $"<<DstReg<<",$"<<DstReg<<","<<tmp_reg<<std::endl;
        data.registers.free_reg(idx);
    }
};

class GreaterThanOperator
    : public Logic
{
protected:
    virtual const char *getOpcode() const override
    {return ">";}
public:
    GreaterThanOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Logic(_left, _right)
    {} 

    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg) const override{
        left->MipsCodeGen(dst,data, DstReg);
        int idx = data.registers.allocate();
        std::string tmp_reg = data.registers.make_regname(idx);
        dst<<"move "<<tmp_reg<<",$"<<DstReg<<std::endl;
        right->MipsCodeGen(dst,data, DstReg);
        dst<<"slt $"<<DstReg<<",$"<<DstReg<<","<<tmp_reg<<std::endl;
        data.registers.free_reg(idx);
    }
};

class LessThanOperator
    : public Logic
{
protected:
    virtual const char *getOpcode() const override
    {return "<";}
public:
    LessThanOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Logic(_left, _right)
    {}

    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg) const override{
        left->MipsCodeGen(dst,data, DstReg);
        int idx = data.registers.allocate();
        std::string tmp_reg = data.registers.make_regname(idx);
        dst<<"move "<<tmp_reg<<",$" <<DstReg<<std::endl;
        right->MipsCodeGen(dst,data, DstReg);
        dst<<"slt $"<<DstReg<<","<<tmp_reg<<",$"<<DstReg<<std::endl;
        data.registers.free_reg(idx);
    }
};

class GreaterThanEqualOperator
    : public Logic
{
protected:
    virtual const char *getOpcode() const override 
    {return ">=";}
public:
    GreaterThanEqualOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Logic(_left, _right)
    {} 
    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg) const override{
        left->MipsCodeGen(dst,data, DstReg);
        int idx = data.registers.allocate();
        std::string tmp_reg = data.registers.make_regname(idx);
        dst<<"move "<<tmp_reg<<",$" <<DstReg<<std::endl;
        right->MipsCodeGen(dst,data, DstReg);
        dst<<"slt $"<<DstReg<<","<<tmp_reg<<",$"<<DstReg<<std::endl;
        dst<<"xori $"<<DstReg<<",$"<<DstReg<<",1"<<std::endl;
        data.registers.free_reg(idx);
    }
};

class LessThanEqualOperator
    : public Logic
{
protected:
    virtual const char *getOpcode() const override
    {return "<=";}
public:
    LessThanEqualOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Logic(_left, _right)
    {}

    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg) const override{
        left->MipsCodeGen(dst,data, DstReg);
        int idx = data.registers.allocate();
        std::string tmp_reg = data.registers.make_regname(idx);
        dst<<"move "<<tmp_reg<<",$" <<DstReg<<std::endl;
        right->MipsCodeGen(dst,data, DstReg);
        dst<<"slt $"<<DstReg<<",$"<<DstReg<<","<<tmp_reg<<std::endl;
        dst<<"xori $"<<DstReg<<",$"<<DstReg<<",1"<<std::endl;
        data.registers.free_reg(idx);
    }
};

#endif

