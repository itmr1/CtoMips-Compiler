#ifndef ast_1_set_stmnts_hpp
#define ast_1_set_stmnts_hpp

#include <string>
#include <iostream>

class OneSetStmnts
    : public Expression
{
private:
    ExpressionPtr Mid;

protected:
    OneSetStmnts(ExpressionPtr _Mid)
        : Mid(_Mid);
    {}
public:
    virtual ~OneSetStmnts()
    {
        delete Mid;
    }

    virtual const char *getOpcode() const =0;

    ExpressionPtr getCond() const
    { return Mid; }

    virtual void print(std::ostream &dst) const override
    {
        dst<<getOpcode();
        dst<<" ";
        mid->print(dst);
        dst<<" ";
        dst<<";";
    }
};

class ReturnStmnt
    : public OneSetStmnts
{
protected:
    virtual const char *getOpcode() const override
    { return "return"; }

public:
    ReturnStmnt(ExpressionPtr Mid)
        : OneSetStmnts(Mid)
    {}
};

#endif