#ifndef ast_0_set_stmnts_hpp
#define ast_0_set_stmnts_hpp

#include <string>
#include <iostream>

class ZeroSetStmnts
    : public Expression
{
public:
    virtual ~ZeroSetStmnts()
    {
        delete Mid;
    }

    virtual const char *getOpcode() const =0;

    virtual void print(std::ostream &dst) const override
    {
        dst<<getOpcode();
        dst<<";";
    }
};

class BreakStmnt
    : public ZeroSetStmnts
{
protected:
    virtual const char *getOpcode() const override
    { return "break"; }

public:
    BreakStmnt
        : ZeroSetStmnts
    {}
};

class BreakStmnt
    : public ZeroSetStmnts
{
protected:
    virtual const char *getOpcode() const override
    { return "break"; }

public:
    BreakStmnt
        : ZeroSetStmnts
    {}
};

class ContinueStmnt
    : public ZeroSetStmnts
{
protected:
    virtual const char *getOpcode() const override
    { return "continue"; }

public:
    ContinueStmnt
        : ZeroSetStmnts
    {}
};

#endif