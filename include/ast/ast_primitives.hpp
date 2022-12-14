#ifndef ast_primitives_hpp
#define ast_primitives_hpp

#include <string>
#include <iostream>
#include <vector>

class Variable
    : public Expression
{
private:
    std::string id;
public:
    Variable(const std::string &_id)
        : id(_id)
    {}

    virtual std::string getId() const override
     { return id; }

    int getSize(Data &data) const
    {
    
        return data.Stack.back().bindings.find(id)->second.size;
    }

    virtual void print(std::ostream &dst) const override
    {
        dst<<id;
    }

    virtual void CountFrameSize(int &CurrSize) const override
   {
       CurrSize+=0;
   }
    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg) const override{
        variable curVar;
        curVar = data.Stack.back().bindings.find(id)->second; //get variable struct
        dst << "lw $"<<DstReg<<","<< curVar.offset<<"($30)" <<std::endl; //load into DstReg from (sp+offset) 
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
    
    virtual void MipsCodeGen(std::ostream &dst,Data &data,int DstReg) const override{
        dst << "li $"<< DstReg <<","<< value<<std::endl;
    }

    virtual void CountFrameSize(int &CurrSize) const override
   {
       CurrSize+=0;
   }

   virtual int evaluate() const override {
        return value;
    }
};


class DeclareMemory
    : public Expression
{
private:
    std::string type;
    ExpressionPtr decl;
public:
    DeclareMemory(const std::string &_type, ExpressionPtr _decl)
        :type(_type)
        ,decl(_decl)
    {}
    virtual void CountFrameSize(int &CurrSize) const override{
        CurrSize+=1;
    }

    virtual std::string getType() const {return type;}
    
    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg)const override{
        std::string id = decl->getId();
        int size = sizeof(int);
        data.Stack.back().curroffset += size; //increase frame size
        //dst << "addiu $29 $29 -"<<size<<std::endl;
        data.Stack.back().bindings[id] = {size, data.Stack.back().curroffset};
        //std::cout<<data.Stack.back().curroffset<<"\n";
    }
};



class InitMemory
    : public Expression
{
private:
    std::string type;
    ExpressionPtr decl;
    ExpressionPtr val;
public:
    InitMemory(const std::string &_type, ExpressionPtr _decl, ExpressionPtr _val)
        :type(_type)
        ,decl(_decl)
        ,val(_val)
    {}
    virtual void print(std::ostream &dst) const override
    {
        dst<<type;
        dst<<" ";
        decl->print(dst);
        dst<<"=";
        val->print(dst);
    }

    virtual std::string getType() const {return type;}

    virtual void CountFrameSize(int &CurrSize) const override{
        CurrSize+=1;
    }
    virtual void MipsCodeGen(std::ostream &dst,Data &data,int DstReg)const override{
        std::string id = decl->getId();
        int size = sizeof(int);
        //dst<<"size of int: "<<size<<std::endl;
        data.Stack.back().curroffset += size; //increase frame size
        //dst << "addiu $29 $29 -"<<size<<std::endl;
        if(data.registers.regs[DstReg]){ //if reg is used
            DstReg = data.registers.allocate(); //get a free register
        }
        val->MipsCodeGen(dst,data,DstReg); //store val in this register
        data.Stack.back().bindings[id] = {size,data.Stack.back().curroffset};
        dst << "sw $" << DstReg<<","<<data.Stack.back().curroffset<< "($29)"<<std::endl; //store val into sp
        data.registers.free_reg(DstReg);
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
    virtual void CountFrameSize(int &CurrSize) const override{
        CurrSize+=1;
    }
    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg)const override{
        std::string id = right->getId();
        int size = sizeof(int);
        //dst<<"size of int: "<<size<<std::endl;
        data.Stack.back().curroffset += size; //increase frame size
        //dst << "addiu $29 $29 -"<<size<<std::endl;
        data.Stack.back().bindings[id] = {size, data.Stack.back().curroffset};
        //std::cout<<data.Stack.back().curroffset<<"\n";
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

    virtual void CountFrameSize(int &CurrSize) const override{
        CurrSize+=1;
    }
    virtual void MipsCodeGen(std::ostream &dst,Data &data,int DstReg)const override{
        std::string id = right->getId();
        int size = sizeof(int);
        //dst<<"size of int: "<<size<<std::endl;
        data.Stack.back().curroffset += size; //increase frame size
        //dst << "addiu $29 $29 -"<<size<<std::endl;
        if(data.registers.regs[DstReg]){ //if reg is used
            DstReg = data.registers.allocate(); //get a free register
        }
        val->MipsCodeGen(dst,data,DstReg); //store val in this register
        data.Stack.back().bindings[id] = {size,data.Stack.back().curroffset};
        dst << "sw $" << DstReg<<","<<data.Stack.back().curroffset<< "($29)"<<std::endl; //store val into sp
        data.registers.free_reg(DstReg);
    }
};

class DeclareArray
    : public Expression
{
private:
    std::string type;
    ExpressionPtr right;
public:
    DeclareArray(const std::string &_type, ExpressionPtr _right)
        : type(_type)
        , right(_right)
    {}

    virtual void print(std::ostream &dst) const override
    {
        dst<<type;
        dst<<" ";
        right->print(dst);
    }

    virtual void CountFrameSize(int &CurrSize) const override{
        CurrSize+=right->evaluate();
    }

    virtual void MipsCodeGen(std::ostream &dst,Data &data,int DstReg)const override{
        std::string id = right->getId();
        int arrsize = right->evaluate();
        int size = sizeof(int);
        
         //increase frame size
            for(int i = 0; i<arrsize; i++){
            data.Stack.back().curroffset += size;
            //std::cout<<data.Stack.back().curroffset<<"\n";
            //valslist[i]->MipsCodeGen(dst, data, DstReg);
            std::string id_arr = id + std::to_string(i);
            data.Stack.back().bindings[id_arr] = {size,data.Stack.back().curroffset};
            //dst << "sw $" << DstReg<<","<<data.Stack.back().curroffset<< "($29)"<<std::endl; //store val into sp
            //data.Stack.back().curroffset += size;
            //data.registers.free_reg(DstReg);
            }
            /*if(arrsize>(int)valslist.size()){
                for(int i = valslist.size(); i<arrsize; i++){
                    std::string id_arr = id + std::to_string(i);
                    data.Stack.back().bindings[id_arr] = {size,data.Stack.back().curroffset};
                    dst << "sw $0,"<<data.Stack.back().curroffset<< "($29)"<<std::endl; //store val into sp
                    data.Stack.back().curroffset += size;
                }
            }*/
    }
   
};

class InitArray
    : public Expression
{
private:
    std::string type;
    ExpressionPtr right;
    ExpressionPtr val;
public:
    InitArray(const std::string &_type, ExpressionPtr _right, ExpressionPtr _val)
        : type(_type)
        , right(_right)
        , val(_val)
    {}
    virtual void print(std::ostream &dst) const override
    {
        dst<<type;
        dst<<" ";
        right->print(dst);
        dst<<"= {";
        val->print(dst);
        dst<<"}";
    }

    virtual void CountFrameSize(int &CurrSize) const override{
        CurrSize+=right->evaluate();
    }

    virtual void MipsCodeGen(std::ostream &dst,Data &data,int DstReg)const override{
        std::string id = right->getId();
        int arrsize = right->evaluate();
        int size = sizeof(int);
        int check=0;
        data.Stack.back().curroffset += size; //increase frame size
        //dst << "addiu $29 $29 -"<<size<<std::endl;
            std::vector<ExpressionPtr> valslist;
            val->GetArgs(valslist);
            for(int i = 0; i<(int)valslist.size(); i++){
            valslist[i]->MipsCodeGen(dst, data, DstReg);
            std::string id_arr = id + std::to_string(i);
            data.Stack.back().bindings[id_arr] = {size,data.Stack.back().curroffset};
            dst << "sw $" << DstReg<<","<<data.Stack.back().curroffset<< "($29)"<<std::endl; //store val into sp
            //data.Stack.back().curroffset += size;
            data.registers.free_reg(DstReg);
            }
            if(arrsize>(int)valslist.size()){
                for(int i = valslist.size(); i<arrsize; i++){
                    data.Stack.back().curroffset += size;
                    std::string id_arr = id + std::to_string(i);
                    data.Stack.back().bindings[id_arr] = {size,data.Stack.back().curroffset};
                    dst << "sw $0,"<<data.Stack.back().curroffset<< "($29)"<<std::endl; //store val into sp
                    
                }
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

    virtual std::string getId() const override
     { return var; }
    
    virtual int evaluate() const override{
        int left = size->evaluate();
        return left;
    }

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
    /*
   virtual void MipsCodeGen(std::ostream &dst,Data &data,int DstReg)const override{
        std::string id = right->getId();
        int arrsize = right->evaluate();
        int size = sizeof(int);
        data.Stack.back().curroffset += size; //increase frame size
        //dst << "addiu $29 $29 -"<<size<<std::endl;
                for(int i = 0; i<arrsize; i++){
                    std::string id_arr = id + std::to_string(i);
                    data.Stack.back().bindings[id_arr] = {size,data.Stack.back().curroffset};
                    dst << "sw $0,"<<data.Stack.back().curroffset<< "($29)"<<std::endl; //store val into sp
                    data.Stack.back().curroffset += size;
                }
    }*/
};

class InitZeroArray
    : public Expression
{
private:
    std::string type;
    ExpressionPtr right;
public:
    InitZeroArray(const std::string &_type, ExpressionPtr _right)
        : type(_type)
        , right(_right)
    {}

    /*virtual std::string getId() const override
     { return ; }
    
    virtual int evaluate() const override{
        int left = size->evaluate();
        return left;
    }*/

    virtual void print(std::ostream &dst) const override
    {
        
    }
   virtual void MipsCodeGen(std::ostream &dst,Data &data,int DstReg)const override{
        std::string id = right->getId();
        int arrsize = right->evaluate();
        int size = sizeof(int);
        //data.Stack.back().curroffset += size; //increase frame size
        //dst << "addiu $29 $29 -"<<size<<std::endl;
                for(int i = 0; i<arrsize; i++){
                    data.Stack.back().curroffset += size;
                    std::string id_arr = id + std::to_string(i);
                    data.Stack.back().bindings[id_arr] = {size,data.Stack.back().curroffset};
                    dst << "sw $0,"<<data.Stack.back().curroffset<< "($29)"<<std::endl; //store val into sp
                    
                }
    }
};

class FuncCall
    : public Expression
{
private:
    std::string name;
    ExpressionPtr args;
public:
    FuncCall(const std::string &_name, ExpressionPtr _args)
        : name(_name)
        , args(_args)
    {}
    FuncCall(const std::string &_name)
        : name(_name)
    {}
    virtual void print(std::ostream &dst) const override
    {}
    virtual bool IsFuncCall() const override{ return true;}
    
    virtual void MipsCodeGen(std::ostream &dst,Data &data,int DstReg)const override{
        
        std::vector<ExpressionPtr> arglist;
        if(args){
            args->GetArgs(arglist);
                    for(int i = 4; i<(int)arglist.size()+4; i++){
                        arglist[i-4]->MipsCodeGen(dst, data, i);
                    }   
                }
        std::string label = name;
        dst<<"jal "<<label<<std::endl;
        dst<<"nop"<<std::endl;
    }

};

class ArrayCall
    : public Expression
{
private:
    std::string name;
    ExpressionPtr index;
public:
    ArrayCall(const std::string &_name, ExpressionPtr _index)
        : name(_name)
        , index(_index)
    {} 
    virtual std::string getId() const override{
        return name;
    }
    virtual ExpressionPtr getindex() const override{
        return index;
    }
    virtual void print(std::ostream &dst) const override
    {}
    virtual void MipsCodeGen(std::ostream &dst,Data &data,int DstReg)const override{
        std::string arrid = name + "0";
        index->MipsCodeGen(dst,data,DstReg);
        dst<<"sll $"<<DstReg<<",2"<<std::endl;
        int arroffset = data.Stack.back().bindings[arrid].offset;
        int idx = data.registers.allocate();
        dst<<"addiu $"<<idx<<",$30,"<<arroffset<<std::endl;
        dst<<"addu $"<<idx<<",$"<<idx<<",$"<<DstReg<<std::endl;
        dst<<"lw $"<<DstReg<<",($"<<idx<<")"<<std::endl;
        data.registers.free_reg(idx);
    }

};


#endif