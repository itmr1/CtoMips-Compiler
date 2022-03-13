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
};

#endif

