#ifndef ast_logic_hpp
#define ast_logic_hpp


#include <string>
#include <iostream>
#include <cmath>

class Logic 
    : public Expression
{
protected:
    ExpressionPtr left;
    ExpressionPtr right;
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

class LeftShiftOperator
    :public Logic
{
protected:
    virtual const char *getOpcode() const override
    {return "<<";}
public:
    LeftShiftOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Logic(_left, _right)
    {}
    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg) const override{
        left->MipsCodeGen(dst,data, DstReg);
        int idx = data.registers.allocate();
        std::string tmp_reg = data.registers.make_regname(idx);
        dst<<"move "<<tmp_reg<<",$"<<DstReg<<std::endl;
        right->MipsCodeGen(dst,data, DstReg);
        dst<<"sll $"<<DstReg<<","<<tmp_reg<<",$"<<DstReg<<std::endl;
        data.registers.free_reg(idx);
    }

    virtual int evaluate(ExpressionPtr) const {
        int l = left->evaluate();
        int r = right->evaluate();
        return l<<r;
    }
};

class RightShiftOperator
    :public Logic
{
protected:
    virtual const char *getOpcode() const override
    {return ">>";}
public:
    RightShiftOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Logic(_left, _right)
    {}
    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg) const override{
        left->MipsCodeGen(dst,data, DstReg);
        int idx = data.registers.allocate();
        std::string tmp_reg = data.registers.make_regname(idx);
        dst<<"move "<<tmp_reg<<",$"<<DstReg<<std::endl;
        right->MipsCodeGen(dst,data, DstReg);
        dst<<"sra $"<<DstReg<<","<<tmp_reg<<",$"<<DstReg<<std::endl;
        data.registers.free_reg(idx);
    }

    virtual int evaluate(ExpressionPtr) const {
        int l = left->evaluate();
        int r = right->evaluate();
        return l>>r;
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
        dst<<"sltiu $"<<DstReg<<",$"<<DstReg<<","<<"1"<<std::endl;
        data.registers.free_reg(idx);
    }
    virtual int evaluate(ExpressionPtr) const {
        int l = left->evaluate();
        int r = right->evaluate();
        return l==r;
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
    virtual int evaluate(ExpressionPtr) const {
        int l = left->evaluate();
        int r = right->evaluate();
        return l!=r;
    }
};

class LogicalAndOperator
 : public Logic
{
protected:
    virtual const char *getOpcode() const override
    {return "&&";}
public:
    LogicalAndOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Logic(_left, _right)
    {}
    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg) const override{
        std::string And0 = data.MakeLabel("A");
        std::string And1 = data.MakeLabel("A");
        left->MipsCodeGen(dst,data, DstReg);
        dst<<"beq $"<<DstReg<<",$0,"<<And0<<std::endl;
        dst<<"nop"<<std::endl;
        right->MipsCodeGen(dst,data, DstReg);
        dst<<"beq $"<<DstReg<<",$0,"<<And0<<std::endl;
        dst<<"nop"<<std::endl;
        dst<<"li $"<<DstReg<<",1"<<std::endl;
        dst<<"b "<<And1<<std::endl;
        dst<<"nop"<<std::endl;
        dst<<And0<<":"<<std::endl;
        dst<<"move $"<<DstReg<<",$0"<<std::endl;
        dst<<And1<<":"<<std::endl;
    }

    virtual int evaluate(ExpressionPtr) const {
        int l = left->evaluate();
        int r = right->evaluate();
        return l&&r;
    }
};

class LogicalOrOperator
 : public Logic
{
protected:
    virtual const char *getOpcode() const override
    {return "||";}
public:
    LogicalOrOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Logic(_left, _right)
    {}
    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg) const override{
        std::string Or0 = data.MakeLabel("O");
        std::string Or1 = data.MakeLabel("O");
        left->MipsCodeGen(dst,data, DstReg);
        dst<<"bne $"<<DstReg<<",$0,"<<Or1<<std::endl;
        dst<<"nop"<<std::endl;
        right->MipsCodeGen(dst,data, DstReg);
        dst<<"bne $"<<DstReg<<",$0,"<<Or1<<std::endl;
        dst<<"nop"<<std::endl;
        dst<<"move $"<<DstReg<<",$0"<<std::endl;
        dst<<"b "<<Or0<<std::endl;
        dst<<"nop"<<std::endl;
        dst<<Or1<<":"<<std::endl;
        dst<<"li $"<<DstReg<<",1"<<std::endl;
        dst<<Or0<<":"<<std::endl;
    }

    virtual int evaluate(ExpressionPtr) const {
        int l = left->evaluate();
        int r = right->evaluate();
        return l||r;
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

    virtual int evaluate(ExpressionPtr) const {
        int l = left->evaluate();
        int r = right->evaluate();
        return l>r;
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

    virtual int evaluate(ExpressionPtr) const {
        int l = left->evaluate();
        int r = right->evaluate();
        return l<r;
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

    virtual int evaluate(ExpressionPtr) const {
        int l = left->evaluate();
        int r = right->evaluate();
        return l>=r;
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

    virtual int evaluate(ExpressionPtr) const {
        int l = left->evaluate();
        int r = right->evaluate();
        return l<=r;
    }
};

#endif

