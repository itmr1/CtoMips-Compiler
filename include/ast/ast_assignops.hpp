#ifndef ast_assignops_hpp
#define ast_assignops_hpp

#include <string>
#include <iostream>
#include <cmath>

class AssignOps                           
    : public Expression
{
protected:
    std::string id;
    ExpressionPtr right;
    AssignOps(/*ExpressionPtr _left*/const std::string &_id, ExpressionPtr _right)
        :id(_id)
        , right(_right)
    {}

    /*AssignOps(const std::string &_type,const std::string &_id, ExpressionPtr _right)
        :type(_type)
        , id(_id)
        , right(_right)
    {}*/
public:
    virtual ~AssignOps()
    {
        delete right;
    }
    
    virtual const char *getOpcode() const =0;

    const std::string getid() const
    { return id; }

    ExpressionPtr getRight() const
    { return right; }

    virtual void print(std::ostream &dst) const override
    {
        //if(type==""){
            dst<<id;
            dst<<" ";
            dst<<getOpcode();
            dst<<" ";
            right->print(dst);
        /*}
        else{
            dst<<type;
            dst<<" ";
            dst<<id;
            dst<<getOpcode();
            dst<<" ";
            right->print(dst);
        }*/
    }

    virtual void CountFrameSize(int &CurrSize) const override
   {
       right->CountFrameSize(CurrSize);
   }
};

class AssignOperator
 : public AssignOps
{
protected:
    virtual const char *getOpcode() const override
    {return "=";}
public:
    AssignOperator(/*ExpressionPtr _left*/const std::string &_id, ExpressionPtr _right)
        : AssignOps(/*_left*/_id, _right)
    {}
    /*AssignOperator(const std::string &_type,const std::string &_id, ExpressionPtr _right)
        : AssignOps(_type,_id, _right)
    {}*/
    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg)const override{
        std::string name = id;
        right->MipsCodeGen(dst, data, DstReg);
        int varoffset = data.Stack.back().bindings[name].offset;
        dst<<"sw $"<<DstReg<<","<<varoffset<<"($30)"<<std::endl;
    }
};

class AddAssignOperator
 : public AssignOps
{
protected:
    virtual const char *getOpcode() const override
    {return "+=";}
public:
    AddAssignOperator(const std::string &_id, ExpressionPtr _right)
        : AssignOps(_id, _right)
    {}

    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg)const override{
        std::string name = id;
        int idx = data.registers.allocate();
        right->MipsCodeGen(dst, data, idx);
        dst<<"add $"<<DstReg<<",$"<<DstReg<<",$"<<idx<<std::endl;
        data.registers.free_reg(idx);
        int varoffset = data.Stack.back().bindings[name].offset;
        dst<<"sw $"<<DstReg<<","<<varoffset<<"($30)"<<std::endl;
    }
};

class SubAssignOperator
 : public AssignOps
{
protected:
    virtual const char *getOpcode() const override
    {return "-=";}
public:
    SubAssignOperator(const std::string &_id, ExpressionPtr _right)
        : AssignOps(_id, _right)
    {}
    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg)const override{
        std::string name = id;
        int idx = data.registers.allocate();
        right->MipsCodeGen(dst, data, idx);
        dst<<"sub $"<<DstReg<<",$"<<DstReg<<",$"<<idx<<std::endl;
        data.registers.free_reg(idx);
        int varoffset = data.Stack.back().bindings[name].offset;
        dst<<"sw $"<<DstReg<<","<<varoffset<<"($30)"<<std::endl;
    }
};

class MulAssignOperator
 : public AssignOps
{
protected:
    virtual const char *getOpcode() const override
    {return "*=";}
public:
    MulAssignOperator(const std::string &_id, ExpressionPtr _right)
        : AssignOps(_id, _right)
    {}
    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg)const override{
        std::string name = id;
        int idx = data.registers.allocate();
        right->MipsCodeGen(dst, data, idx);
        dst<<"mul $"<<DstReg<<",$"<<idx<<std::endl;
        dst<<"mflo $"<<DstReg<<std::endl;
        data.registers.free_reg(idx);
        int varoffset = data.Stack.back().bindings[name].offset;
        dst<<"sw $"<<DstReg<<","<<varoffset<<"($30)"<<std::endl;
    }
};

class DivAssignOperator
 : public AssignOps
{
protected:
    virtual const char *getOpcode() const override
    {return "/=";}
public:
    DivAssignOperator(const std::string &_id, ExpressionPtr _right)
        : AssignOps(_id, _right)
    {}
    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg)const override{
        std::string name = id;
        int idx = data.registers.allocate();
        right->MipsCodeGen(dst, data, idx);
        dst<<"div $"<<DstReg<<",$"<<idx<<std::endl;
        dst<<"mfhi $"<<DstReg<<std::endl;
        data.registers.free_reg(idx);
        int varoffset = data.Stack.back().bindings[name].offset;
        dst<<"sw $"<<DstReg<<","<<varoffset<<"($30)"<<std::endl;
    }
};

class ModAssignOperator
 : public AssignOps
{
protected:
    virtual const char *getOpcode() const override
    {return "%=";}
public:
    ModAssignOperator(const std::string &_id, ExpressionPtr _right)
        : AssignOps(_id, _right)
    {}
    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg)const override{
        std::string name = id;
        int idx = data.registers.allocate();
        right->MipsCodeGen(dst, data, idx);
        dst<<"div $"<<DstReg<<",$"<<idx<<std::endl;
        dst<<"mflo $"<<DstReg<<std::endl;
        data.registers.free_reg(idx);
        int varoffset = data.Stack.back().bindings[name].offset;
        dst<<"sw $"<<DstReg<<","<<varoffset<<"($30)"<<std::endl;
    }
};

#endif
