#ifndef ast_2_set_stmnts_hpp
#define ast_2_set_stmnts_hpp

#include <string>
#include <iostream>

class TwoSetStmnts
    : public Expression
{
private:
    ExpressionPtr left;
    ExpressionPtr right;
protected:
    TwoSetStmnts(ExpressionPtr cond, ExpressionPtr chunk)
        : left(cond)
        , right(chunk)
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
        dst<<getOpcode();
        dst<<" ";
        dst<<"( ";
        left->print(dst);
        dst<<" )";
        dst<<" ";
        dst<<"{ ";
        right->print(dst);
        dst<<" }";
    }
};

class IfStmnt
    : public TwoSetStmnts
{
protected:
    virtual const char *getOpcode() const override
    { return "if"; }
public:
    IfStmnt(ExpressionPtr cond, ExpressionPtr chunk)
        : TwoSetStmnts(cond, chunk)
    {}
};

class WhileStmnt
    : public TwoSetStmnts
{
protected:
    virtual const char *getOpcode() const override
    { return "while"; }
public:
    WhileStmnt(ExpressionPtr cond, ExpressionPtr chunk)
        : TwoSetStmnts(cond, chunk)
    {}
};

#endif