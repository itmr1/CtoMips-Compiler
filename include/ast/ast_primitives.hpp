#ifndef ast_primitives_hpp
#define ast_primitives_hpp

#include <string>
#include <iostream>

//#include "context.hpp"

class Variable
    : public Expression
{
private:
    std::string id;
public:
    Variable(const std::string &_id)
        : id(_id)
    {}

    virtual std::string getId() const override
     { return id; }

    const int getSize(Data &data) const
    {
        if(data.Stack.back().bindings.find(id) == data.Stack.back().bindings.end()){ //if not in stack
            std::cerr << "L" << std::endl; //doesnt exist
            exit(1);
        }
        else{return data.Stack.back().bindings.find(id)->second.size;}
    }

    virtual void print(std::ostream &dst) const override
    {
        dst<<id;
    }

    virtual void CountFrameSize(int &CurrSize) const override
   {
       CurrSize+=0;
   }
    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg) const override{
        variable curVar;
        if(data.Stack.back().bindings.find(id) == data.Stack.back().bindings.end()){ //if not in stack
            std::cerr << "L" << std::endl; //doesnt exist
            exit(1);
        }
        else{
            curVar = data.Stack.back().bindings.find(id)->second; //get variable struct
        }
        dst << "lw $"<<DstReg<< curVar.offset<<" $30" <<std::endl; //load into DstReg from (sp+offset) 
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
    
    virtual void MipsCodeGen(std::ostream &dst,Data &data,int DstReg) const override{
        dst << "li $"<< DstReg <<","<< value<<std::endl;
    }

    virtual void CountFrameSize(int &CurrSize) const override
   {
       CurrSize+=0;
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
    virtual void CountFrameSize(int &CurrSize) const override{
        CurrSize+=1;
    }
    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg)const override{
        std::string id = right->getId();
        int size = sizeof(int);
        data.Stack.back().curroffset += size; //increase frame size
        //dst << "addiu $29 $29 -"<<size<<std::endl;
        data.Stack.back().bindings[id] = {size, -data.Stack.back().curroffset};
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

    virtual void CountFrameSize(int &CurrSize) const override{
        CurrSize+=1;
    }
    virtual void MipsCodeGen(std::ostream &dst,Data &data,int DstReg)const override{
        std::string id = right->getId();
        int size = sizeof(int);
        data.Stack.back().frameSize += size; //increase frame size
        //dst << "addiu $29 $29 -"<<size<<std::endl;
        if(data.registers.regs[DstReg]){ //if reg is used
            DstReg = data.registers.allocate(); //get a free register
        }
        val->MipsCodeGen(dst,data,DstReg); //store val in this register
        data.Stack.back().bindings[id] = {size, data.Stack.back().frameSize};
        dst << "sw $" << DstReg << size << " $29"<<std::endl; //store val into sp
        data.registers.free_reg(DstReg);
    }
};

class DeclareArray
    : public Expression
{
private:
    std::string type;
    ExpressionPtr right;
public:
    DeclareArray(const std::string &_type, ExpressionPtr _right)
        : type(_type)
        , right(_right)
    {}

    virtual void print(std::ostream &dst) const override
    {
        dst<<type;
        dst<<" ";
        right->print(dst);
    }

    virtual void CountFrameSize(int &CurrSize) const override{
        CurrSize+=1;
    }

    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg)const override{
        std::string id = right->getId();
        int size = sizeof(int);
        data.Stack.back().frameSize += size; //increase frame size
        //dst << "addiu $29 $29 -"<<size<<std::endl;
        data.Stack.back().bindings[id] = {size, -data.Stack.back().frameSize};
    }
   
};

class InitArray
    : public Expression
{
private:
    std::string type;
    ExpressionPtr right;
    ExpressionPtr val;
public:
    InitArray(const std::string &_type, ExpressionPtr _right, ExpressionPtr _val)
        : type(_type)
        , right(_right)
        , val(_val)
    {}
    virtual void print(std::ostream &dst) const override
    {
        dst<<type;
        dst<<" ";
        right->print(dst);
        dst<<"= {";
        val->print(dst);
        dst<<"}";
    }

    virtual void CountFrameSize(int &CurrSize) const override{
        CurrSize++;
    }

    virtual void MipsCodeGen(std::ostream &dst,Data &data,int DstReg)const override{
        std::string id = right->getId();
        int size = sizeof(int);
        data.Stack.back().curroffset += size; //increase frame size
        //dst << "addiu $29 $29 -"<<size<<std::endl;
        if(data.registers.regs[DstReg]){ //if reg is used
            DstReg = data.registers.allocate(); //get a free register
        }
        val->MipsCodeGen(dst,data,DstReg); //store val in this register
        data.Stack.back().bindings[id] = {size, data.Stack.back().curroffset};
        dst << "sw $" << DstReg <<","<< data.Stack.back().curroffset << "($29)"<<std::endl; //store val into sp
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

    virtual std::string getId() const override
     { return var; }

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
   /*virtual void CountFrameSize(int &CurrSize) const override
   {
       CurrSize+=size;
   }*/
};

class FuncCall
    : public Expression
{
private:
    std::string name;
    ExpressionPtr args;
public:
    FuncCall(const std::string &_name, ExpressionPtr _args)
        : name(_name)
        , args(_args)
    {}
    FuncCall(const std::string &_name)
        : name(_name)
    {}
    virtual void print(std::ostream &dst) const override
    {}
    
    virtual void MipsCodeGen(std::ostream &dst,Data &data,int DstReg)const override{
        if(args){
            //TODO
        }
        else{
            //TODO
        }
    }

};


#endif