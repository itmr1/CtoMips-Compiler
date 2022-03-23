#ifndef ast_primitives_hpp
#define ast_primitives_hpp

#include <string>
#include <iostream>

#include "ast/context.hpp"

class Variable
    : public Expression
{
private:
    std::string id;
public:
    Variable(const std::string &_id)
        : id(_id)
    {}

    const std::string getId() const
    { return id; }

    const int getSize() const
    {
        if(data.Stack.back().bindings.find(id) == data.Stack.back().bindings.end()){ //if not in stack
            std::cerr << "L" << std::endl; //doesnt exist
            exit(1);
        }
        else{return data.Stack.back().bindings.find(id)->second.size()}
    }

    virtual void print(std::ostream &dst) const override
    {
        dst<<id;
    }
    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg) const override{
        variable curVar;
        if(data.Stack.back().bindings.find(id) == data.Stack.back().bindings.end()){ //if not in stack
            std::cerr << "L" << std::endl; //doesnt exist
            exit(1);
        }
        else{
            hold = data.Stack.back().bindings.find(id)->second; //get variable struct
        }
        dst << "lw $"<<DstReg<< hold.offset<<" $30" <<std::endl; //load into DstReg from (sp+offset) 
    }
};

class Number
    : public Expression
{
private:
    double value;
public:
    Number(double _value)
        : value(_value)
    {}

    double getValue() const
    { return value; }

    virtual void print(std::ostream &dst) const override
    {
        dst<<value;
    }
    
    virtual void MipsCodeGen(std::ostream &dst,Data &data,int DstReg){
        dst << "li $"<< DstReg <<","<< value<<std::endl;
    }
};

class DeclareVar
    : public Expression
{
private:
    std::string type;
    ExpressionPtr right;
public:
    DeclareVar(const std::string &_type, ExpressionPtr _right)
        : type(_type)
        , right(_right)
    {}

    virtual void print(std::ostream &dst) const override
    {
        dst<<type;
        dst<<" ";
        right->print(dst);
    }
    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg){
        std::string id = right->getId();
        int size = sizeof(int);
        data.Stack.back().offset += size; //increase frame size
        //dst << "addiu $29 $29 -"<<size<<std::endl;
        data.Stack.back().bindings[id] = {size, -Stack.back().offset};
    }
   
};

class InitVar
    : public Expression
{
private:
    std::string type;
    ExpressionPtr right;
    ExpressionPtr val;
public:
    InitVar(const std::string &_type, ExpressionPtr _right, ExpressionPtr _val)
        : type(_type)
        , right(_right)
        , val(_val)
    {}
    virtual void print(std::ostream &dst) const override
    {
        dst<<type;
        dst<<" ";
        right->print(dst);
        dst<<"=";
        val->print(dst);
    }
    virtual void MipsCodeGen(std::ostream &dst,Data &data,int DstReg){
        std::string id = right->getId();
        int size = sizeof(int);
        data.Stack.back().offset += size; //increase frame size
        //dst << "addiu $29 $29 -"<<size<<std::endl;
        if(data.registers.regs[DstReg]){ //if reg is used
            DstReg = data.registers.allocate();
        }
        val->MipsCodeGen(dst,data,DstReg);
        data.Stack.back().bindings[id] = {size, -data.Stack.back().offset}
        dst << "sw $" << DstReg << -size << " $29"<<std::endl; //store val into sp
        data.registers.free_reg(DstReg);
    }
};

class Array
    : public Expression
{
private:
    std::string var;
    ExpressionPtr size;
public:
    Array(const std::string &_var, ExpressionPtr _size)
        : var(_var)
        , size(_size)
    {}
    Array(const std::string &_var)
        : var(_var)
    {}

    virtual void print(std::ostream &dst) const override
    {
        if(size){
            dst<<var;
            dst<<"[";
            size->print(dst);
            dst<<"]";
        }
        else{
            dst<<var;
            dst<<"[]";
        }
    }
   
};


#endif