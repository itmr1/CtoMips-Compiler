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

    virtual void print(std::ostream &dst) const override
    {
        dst<<id;
    }

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
        // TODO-B : Run bin/eval_expr with a variable binding to make sure you understand how this works.
        // If the binding does not exist, this will throw an error
        return bindings.at(id);
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

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
        // TODO-A : Run bin/eval_expr with a numeric expression to make sure you understand how this works.
        return value;
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
    InitVar(const std::string &_type, ExpressionPtr _right)
        : type(_type)
        , right(_right)
    {}
    InitVar(const std::string &_type, ExpressionPtr _right, ExpressionPtr _val)
        : type(_type)
        , right(_right)
        , val(_val)
    {}

    virtual void print(std::ostream &dst) const override
    {
        if(val){
            dst<<type;
            dst<<" ";
            right->print(dst);
            dst<<"=";
            val->print(dst);
        }
        else{
            dst<<type;
            dst<<" ";
            right->print(dst);
        }
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