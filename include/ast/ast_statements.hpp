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

protected:
    SetStatement(ExpressionPtr _Cond, ExpressionPtr _Statement, ExpressionPtr _Statement2)
        : Cond(_Cond)
        , Statement(_Statement)
        , Statement2(_Statement2)
    {}
    SetStatement(ExpressionPtr _Cond, ExpressionPtr _Statement)
        : Cond(_Cond)
        , Statement(_Statement)
    {}
    SetStatement();
  
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
   // virtual std::string MipsCodeGen(std::ostream &dst, std::string DestReg) const override{}
    virtual const std::string *getCondStmntTrue() const =0;
    virtual const std::string *getCondStmntFalse() const =0;
    virtual const std::string *getKeyWord()  const =0;

    virtual void print(std::ostream &dst) const override
    {   
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
    IfStatement(ExpressionPtr _Cond, ExpressionPtr _Statement)
        : SetStatement(_Cond, _Statement)
    {}

    virtual const std::string *getCondStmntTrue() const override{
        return "if";
    }

    virtual void print(std::ostream &dst){
        dst<<getCondStmntTrue();
        dst<<"(";
        Cond->print(dst);
        dst<<"){";
        Statement->print(dst);
        dst<<"}";
    }
    /*virtual void MipsCodeGen(std::ostream &dst, std::string DstReg) const override{
        //TODO
    }*/
    virtual void CountFrameSize(int &CurrSize) const override
   {
       Cond->CountFrameSize(CurrSize);
       Statement->CountFrameSize(CurrSize);
   }
};

class IfElseStatement
    : public SetStatement
{
public:
    IfElseStatement(ExpressionPtr _Cond, ExpressionPtr _Statement, ExpressionPtr _Statement2)
        : SetStatement(_Cond, _Statement, _Statement2)
    {}
    /*virtual void MipsCodeGen(std::ostream &dst, std::string DstReg) const override{
        //TODO
    }*/
    virtual void std::string *getCondStmntTrue() const override{
        return "if";
    }

    virtual void std::string *getCondStmntFalse() const override{
        return "else";
    }
    
    virtual void print(std::ostream &dst){
        dst<<getCondStmntTrue();
        dst<<"( ";
        Cond->print(dst);
        dst<<") ";
        dst<<getCondStmntFalse();
        dst<<" {";
        Statement->print(dst);
        dst<<"}";
    }

    virtual void CountFrameSize(int &CurrSize) const override
   {
        Cond->CountFrameSize(CurrSize);
        Statement->CountFrameSize(CurrSize);
        Statement2->CountFrameSize(CurrSize);
   }
};

class WhileStatement
    : public SetStatement
{
public:
    WhileStatement(ExpressionPtr _Cond, ExpressionPtr _Statement, const std::string &_type)
        : SetStatement(_Cond, _Statement, _type)
    {}
    /*virtual void MipsCodeGen(std::ostream &dst, std::string DstReg) const override{
       //TODO
    }*/
    virtual void std::string *getCondStmntTrue() const override{
        return "while";
    }

    virtual void print(std::ostream &dst){
        dst<<getCondStmntTrue();
        dst<<"(";
        Cond->print(dst);
        dst<<"){";
        Statement->print(dst);
        dst<<"}";
    }

    virtual void CountFrameSize(int &CurrSize) const override
   {
        Cond->CountFrameSize(CurrSize);
        Statement->CountFrameSize(CurrSize);
   }
};

class ReturnExprStatement
    : public SetStatement
{
public:
    ReturnExprStatement(ExpressionPtr _Statement)
        : SetStatement(_Statement)
    {}
    /*virtual void MipsCodeGen(std::ostream &dst, std::string DstReg) const override{
        //TODO
    }*/
    virtual void std::string *getKeyWord() const override{
        return "return";
    }

    virtual void print(std::ostream &dst){
        dst<<getKeyWord();
        dst<<"( ";
        Statement->print(dst);
        dst<<" )";
        dst<<";";
    }

    virtual void CountFrameSize(int &CurrSize) const override
   {
        Statement->CountFrameSize(CurrSize);
   }


};

class ReturnStatement
    : public SetStatement
{
public:
    ReturnStatement();
    /*virtual void MipsCodeGen(std::ostream &dst, std::string DstReg) const override{
        //TODO
    }*/

    virtual void std::string *getKeyWord() const override{
        return "return";
    }
    
    virtual void print(std::ostream &dst){
        dst<<getKeyWord();
        dst<<";";
    }

    virtual void CountFrameSize(int &CurrSize) const override
   {
        CurrSize+=0;
   }

};

class BreakStatement
    : public SetStatement
{
public:
    BreakStatement();
    /*virtual void MipsCodeGen(std::ostream &dst, std::string DstReg) const override{
        //TODO
    }*/

    virtual void std::string *getKeyWord() const override{
        return "break";
    }
    
    virtual void print(std::ostream &dst){
        dst<<getKeyWord();
        dst<<";";
    }

    virtual void CountFrameSize(int &CurrSize) const override
   {
        CurrSize+=0;
   }
};

class ContinueStatement
    : public SetStatement
{
public:
    ContinueStatement();
    /*virtual void MipsCodeGen(std::ostream &dst, std::string DstReg) const override{
        //TODO
    }*/

    virtual void std::string *getKeyWord() const override{
        return "continue";
    }
    
    virtual void print(std::ostream &dst){
        dst<<getKeyWord();
        dst<<";";
    }

    virtual void CountFrameSize(int &CurrSize) const override
   {
        CurrSize+=0;
   }
};


#endif