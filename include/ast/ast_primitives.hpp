#ifndef ast_primitives_hpp
#define ast_primitives_hpp

#include <string>
#include <iostream>

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

   // const int getSize()

    virtual void print(std::ostream &dst) const override
    {
        dst<<id;
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
    
    virtual void MipsCodeGen(std::ostream &dst, std::string DstReg){
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