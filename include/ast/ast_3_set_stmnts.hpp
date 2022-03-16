#ifndef ast_3_set_stmnts_hpp
#define ast_3_set_stmnts_hpp

#include <string>
#include <iostream>

class ThreeSetStmnts
    : public Expression
{
private:
    ExpressionPtr cond;
    ExpressionPtr left;
    ExpressionPtr right;
protected:
    ThreeSetStmnts(ExpressionPtr _cond, ExpressionPtr chunk, ExpressionPtr chunk2)
        : cond(_cond)
        , left(chunk)
        , right(chunk2)
    {}
public:
    virtual ~ThreeSetStmnts()
    {
        delete cond;
        delete left;
        delete right;
    }

    virtual const char *getOpcodeleft() const =0;
    virtual const char *getOpcoderight() const =0;

    ExpressionPtr getCond() const
    { return cond; }

    ExpressionPtr getLeft() const
    { return left; }

    ExpressionPtr getRight() const
    { return right; }

    virtual void print(std::ostream &dst) const override
    {
        dst<<getOpcodeleft();
        dst<<" ";
        dst<<"( ";
        cond->print(dst);
        dst<<" )";
        dst<<" ";
        dst<<getOpcoderight();
        dst<<"{ ";
        right->print(dst);
        dst<<" }";
    }
};

class IfElseStmnt
    : public ThreeSetStmnts
{
protected:
    virtual const char *getOpcodeleft() const override
    { return "if"; }

    virtual const char *getOpcoderight() const override
    { return "else"; }
public:
    IfElseStmnt(ExpressionPtr cond, ExpressionPtr chunk, ExpressionPtr chunk2,)
        : ThreeSetStmnts(cond, chunk, chunk2)
    {}
};

#endif