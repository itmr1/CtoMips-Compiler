#ifndef ast_statements_hpp
#define ast_statements_hpp

#include <string>
#include <iostream>

class SetStatement
    : public Expression
{
/*private:    
    ExpressionPtr Cond;
    ExpressionPtr Statement;
    ExpressionPtr Statement2;*/

protected:
    ExpressionPtr Cond;
    ExpressionPtr Statement;
    ExpressionPtr Statement2;
    ExpressionPtr Statement3;
    SetStatement(ExpressionPtr _Cond, ExpressionPtr _Statement, ExpressionPtr _Statement2, ExpressionPtr _Statement3)
        : Cond(_Cond)
        , Statement(_Statement)
        , Statement2(_Statement2)
        , Statement3(_Statement3)
    {}
    SetStatement(ExpressionPtr _Cond, ExpressionPtr _Statement, ExpressionPtr _Statement2)
        : Cond(_Cond)
        , Statement(_Statement)
        , Statement2(_Statement2)
    {}
    SetStatement(ExpressionPtr _Cond, ExpressionPtr _Statement)
        : Cond(_Cond)
        , Statement(_Statement)
    {}
    SetStatement()
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
        delete Statement3;
    }
   // virtual std::string MipsCodeGen(std::ostream &dst, std::string DestReg) const override{}
    virtual const char *getCondStmntTrue() const {return "";}
    virtual const char *getCondStmntFalse() const {return "";}
    virtual const char *getKeyWord()  const {return "";}
    virtual void MipsCodeGen(std::ostream &dst, Data &data, int DstReg)const override{return;}
    virtual void print(std::ostream &dst) const override{}

};

class IfStatement
    : public SetStatement
{
public:
    IfStatement(ExpressionPtr _Cond, ExpressionPtr _Statement)
        : SetStatement(_Cond, _Statement)
    {}

    virtual const char *getCondStmntTrue() const override{
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
    
   virtual void MipsCodeGen(std::ostream &dst, Data &data, int DstReg) const override{
    Cond->MipsCodeGen(dst, data, DstReg);
    std::string EndIf = data.MakeLabel("EndIf");
    dst<<"beq $0,$"<<DstReg<<","<<EndIf<<std::endl;
    dst<<"nop"<<std::endl;
    Statement->MipsCodeGen(dst, data, DstReg);
    dst<<EndIf<<":"<<std::endl;
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
    virtual const char *getCondStmntTrue() const override{
        return "if";
    }

    virtual const char *getCondStmntFalse() const override{
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

   virtual void MipsCodeGen(std::ostream &dst, Data &data, int DstReg) const override{
        //std::cout<<"hello\n";
        Cond->MipsCodeGen(dst, data, DstReg);
        //std::cout<<"hello\n";
        std::string Else = data.MakeLabel("Else");
        std::string EndIfElse = data.MakeLabel("EndIfElse");
        dst<<"beq $0,$"<<DstReg<<","<<Else<<std::endl;
        dst<<"nop"<<std::endl;
        Statement->MipsCodeGen(dst, data, DstReg);
        dst<<"b "<<EndIfElse<<std::endl;
        dst<<"nop"<<std::endl;
        dst<<Else<<":"<<std::endl;
        Statement2->MipsCodeGen(dst, data, DstReg);
        dst<<EndIfElse<<":"<<std::endl;
   }
};

class WhileStatement
    : public SetStatement
{
public:
    WhileStatement(ExpressionPtr _Cond, ExpressionPtr _Statement)
        : SetStatement(_Cond, _Statement)
    {}
    /*virtual void MipsCodeGen(std::ostream &dst, std::string DstReg) const override{
       //TODO
    }*/
    virtual const char *getCondStmntTrue() const override{
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

   virtual void MipsCodeGen(std::ostream &dst, Data &data, int DstReg) const override{
    int idx = data.registers.allocate();
    Cond->MipsCodeGen(dst, data, idx);
    std::string LoopStart = data.MakeLabel("LoopStart");
    data.Loopstarts.push_back(LoopStart);
    std::string LoopEnd = data.MakeLabel("LoopEnd");
    data.Loopends.push_back(LoopEnd);
    dst<<"beq $0,$"<<idx<<","<<LoopEnd<<std::endl;
    dst<<"nop"<<std::endl;
    dst<<LoopStart<<":"<<std::endl;
    Statement->MipsCodeGen(dst, data, DstReg);
    Cond->MipsCodeGen(dst, data, idx);
    dst<<"bne $0,$"<<idx<<","<<LoopStart<<std::endl;
    dst<<"nop"<<std::endl;
    dst<<LoopEnd<<":"<<std::endl;
    data.registers.free_reg(idx);
    data.Loopstarts.pop_back();
    data.Loopends.pop_back();
   }
};

class ForStatement
    : public SetStatement
{
public:
    ForStatement(ExpressionPtr _Cond, ExpressionPtr _Cond2, ExpressionPtr _Cond3, ExpressionPtr _Statement)
        : SetStatement(_Cond, _Cond2, _Cond3, _Statement)
    {}
    virtual const char *getCondStmntTrue() const override{
        return "for";
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
        Statement2->CountFrameSize(CurrSize);
        Statement3->CountFrameSize(CurrSize);
   }

   virtual void MipsCodeGen(std::ostream &dst, Data &data, int DstReg) const override{
    int tmp = data.registers.allocate();
    Cond->MipsCodeGen(dst,data,tmp);
    std::string EndOfLoop = data.MakeLabel("EndOfLoop");
    std::string StartOfLoop = data.MakeLabel("StartOfLoop");
    data.Loopstarts.push_back(StartOfLoop);
    data.Loopends.push_back(EndOfLoop);
    std::string CondCheck = data.MakeLabel("CondCheck");
    dst<<"b "<<CondCheck<<std::endl;
    dst<<"nop"<<std::endl;
    dst<<StartOfLoop<<":"<<std::endl;
    Statement3->MipsCodeGen(dst,data,DstReg);
    int tmp2 = data.registers.allocate();
    Statement2->MipsCodeGen(dst,data,DstReg);
    dst<<CondCheck<<":"<<std::endl;
    Statement->MipsCodeGen(dst,data,tmp);
    dst<<"bne $"<<tmp<<",$0"<<","<<StartOfLoop<<std::endl;
    data.registers.free_reg(tmp);
    data.registers.free_reg(tmp2);
    dst<<EndOfLoop<<":"<<std::endl;
    data.Loopstarts.pop_back();
    data.Loopends.pop_back();
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
    virtual const char *getKeyWord() const override{
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

    virtual void MipsCodeGen(std::ostream &dst, Data &data, int DstReg)const override{
        Statement->MipsCodeGen(dst, data, 2);
        dst<<"b "<<data.CurrLabel<<std::endl;
        dst<<"nop"<<std::endl;
   }

};

class ReturnStatement
    : public SetStatement
{
public:
    ReturnStatement()
        : SetStatement()
    {}
    /*virtual void MipsCodeGen(std::ostream &dst, std::string DstReg) const override{
        //TODO
    }*/

    virtual const char *getKeyWord() const override{
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

   virtual void MipsCodeGen(std::ostream &dst, Data &data, int DstReg)const override{
        dst<<"b "<<data.CurrLabel<<std::endl;
        dst<<"nop"<<std::endl;
   }
};

class BreakStatement
    : public SetStatement
{
public:
    BreakStatement()
        : SetStatement()
    {}
    /*virtual void MipsCodeGen(std::ostream &dst, std::string DstReg) const override{
        //TODO
    }*/

    virtual const char *getKeyWord() const override{
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
    virtual void MipsCodeGen(std::ostream &dst, Data &data, int DstReg)const override{
        dst<<"b "<<data.Loopends.back()<<std::endl;
        dst<<"nop"<<std::endl;

   }
};

class ContinueStatement
    : public SetStatement
{
public:
    ContinueStatement()
        : SetStatement()
    {}
    /*virtual void MipsCodeGen(std::ostream &dst, std::string DstReg) const override{
        //TODO
    }*/

    virtual const char *getKeyWord() const override{
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
   virtual void MipsCodeGen(std::ostream &dst, Data &data, int DstReg)const override{
       dst<<"b "<<data.Loopstarts.back()<<std::endl;
        dst<<"nop"<<std::endl;
   }    

};

class EmptyStatement
    : public SetStatement
{
public:
    EmptyStatement()
        : SetStatement()
    {}
    /*virtual void MipsCodeGen(std::ostream &dst, std::string DstReg) const override{
        //TODO
    }*/

    virtual const char *getKeyWord() const override{
        return " ";
    }
    
    virtual void print(std::ostream &dst){
        dst<<getKeyWord();
        dst<<";";
    }

    virtual void CountFrameSize(int &CurrSize) const override
   {
        CurrSize+=0;
   }
   virtual void MipsCodeGen(std::ostream &dst, Data &data, int DstReg)const override()}
};


#endif