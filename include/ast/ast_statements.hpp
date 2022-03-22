#ifndef ast_statements_hpp
#define ast_statements_hpp

#include <string>
#include <iostream>

class SetStatement
    : public Expression
{
private:    
    ExpressionPtr Cond;
    ExpressionPtr Statement;
    ExpressionPtr Statement2;
    std::string type;

protected:
    SetStatement(ExpressionPtr _Cond, ExpressionPtr _Statement, ExpressionPtr _Statement2)
        : Cond(_Cond)
        , Statement(_Statement)
        , Statement2(_Statement2)
    {}
    SetStatement(ExpressionPtr _Cond, ExpressionPtr _Statement, const std::string &_type)
        : Cond(_Cond)
        , Statement(_Statement)
        , type(_type)
    {}
    SetStatement(const std::string &_type)
        : type(_type)
    {}
    SetStatement(ExpressionPtr _Statement)
        : Statement(_Statement)
    {}
public:
    virtual ~SetStatement()
    {
        delete Cond;
        delete Statement;
        delete Statement2;
    }

    virtual void print(std::ostream &dst) const override
    {   
        if(type=="if"){ //if
            dst<<type;
            dst<<"(";
            Cond->print(dst);
            dst<<"){";
            Statement->print(dst);
            dst<<"}";
        }
        else if(type=="while"){ //while
            dst<<type;
            dst<<"(";
            Cond->print(dst);
            dst<<"){";
            Statement->print(dst);
            dst<<"}";
        }
        else if(Statement2){ //if else
            dst<<"if(";
            Cond->print(dst);
            dst<<"){";
            Statement->print(dst);
            dst<<"}else{";
            Statement2->print(dst);
            dst<<"}";
        }
        else if(type=="return"){
            dst<<"return;";
        }
        else if(type=="break"){
            dst<<"break;";
        }
        else if(type=="continue"){
            dst<<"continue;";
        }
        else{
            dst<<"return ";
            Statement->print(dst);
        }
    }

};

class IfStatement
    : public SetStatement
{
public:
    IfStatement(ExpressionPtr _Cond, ExpressionPtr _Statement, const std::string &_type)
        : SetStatement(_Cond, _Statement, _type)
    {}

    IfStatement(ExpressionPtr _Cond, ExpressionPtr _Statement, ExpressionPtr _Statement2)
        : SetStatement(_Cond, _Statement, _Statement2)
    {}
};

class WhileStatement
    : public SetStatement
{
public:
    WhileStatement(ExpressionPtr _Cond, ExpressionPtr _Statement, const std::string &_type)
        : SetStatement(_Cond, _Statement, _type)
    {}
};

class JumpStatement
    : public SetStatement
{
public:
    JumpStatement(ExpressionPtr _Statement)
        : SetStatement(_Statement)
    {}
    JumpStatement(const std::string &_type)
        : SetStatement(_type)
    {}
};


#endif