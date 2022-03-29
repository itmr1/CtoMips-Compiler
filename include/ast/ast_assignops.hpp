#ifndef ast_assignops_hpp
#define ast_assignops_hpp

#include <string>
#include <iostream>
#include <cmath>

class AssignOps                           
    : public Expression
{
protected:
    ExpressionPtr id;
    ExpressionPtr right;
    
    AssignOps(/*ExpressionPtr _left*/const ExpressionPtr _id, ExpressionPtr _right)
        :id(_id)
        , right(_right)
    {}

public:
    virtual ~AssignOps()
    {
        delete right;
    }
    
    virtual const char *getOpcode() const =0;

    //const std::string getid() const
    //{ return id; }

    ExpressionPtr getRight() const
    { return right; }

    virtual void print(std::ostream &dst) const override
    {
        //if(type==""){
            id->print(dst);
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
    AssignOperator( ExpressionPtr &_id, ExpressionPtr _right)
        : AssignOps(_id, _right)
    {}

    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg)const override{
        std::string name = id->getId();
        ExpressionPtr arridx = id->getindex();
        if(arridx!= NULL){
            std::string arrid = name + "0";
            arridx->MipsCodeGen(dst,data,DstReg);
            dst<<"sll $"<<DstReg<<",2"<<std::endl;
            int arroffset = data.Stack.back().bindings[arrid].offset;
            int idx = data.registers.allocate();
            dst<<"addiu $"<<idx<<",$30,"<<arroffset<<std::endl;
            dst<<"addu $"<<idx<<",$"<<idx<<",$"<<DstReg<<std::endl;
            right->MipsCodeGen(dst, data, DstReg);
            dst<<"sw $"<<DstReg<<",($"<<idx<<")"<<std::endl;
            data.registers.free_reg(idx);
        }
        else if((id->IsPointerCall())||(id->getType()!="int")){
            int ptroffset = data.Stack.back().bindings[name].offset;
            dst<<"lw $"<<DstReg<<","<<ptroffset<<"($30)"<<std::endl;
            int idx = data.registers.allocate();
            right->MipsCodeGen(dst,data,idx);
            dst<<"sw $"<<idx<<",($"<<DstReg<<")"<<std::endl;
            data.registers.free_reg(idx);
        }
        else{
        right->MipsCodeGen(dst, data, DstReg);
        int varoffset = data.Stack.back().bindings[name].offset;
        dst<<"sw $"<<DstReg<<","<<varoffset<<"($30)"<<std::endl;
        }
    }
};

class AddAssignOperator
 : public AssignOps
{
protected:
    virtual const char *getOpcode() const override
    {return "+=";}
public:
    AddAssignOperator( ExpressionPtr &_id, ExpressionPtr _right)
        : AssignOps(_id, _right)
    {}

    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg)const override{
        std::string name = id->getId();
        ExpressionPtr arridx = id->getindex();
        if(arridx!= NULL){
            std::string arrid = name + "0";
            arridx->MipsCodeGen(dst,data,DstReg);
            dst<<"sll $"<<DstReg<<",2"<<std::endl;
            int arroffset = data.Stack.back().bindings[arrid].offset - 4;
            int idx = data.registers.allocate();
            dst<<"addiu $"<<idx<<",$30,"<<arroffset<<std::endl;
            dst<<"addu $"<<idx<<",$"<<idx<<",$"<<DstReg<<std::endl;
            int tmp = data.registers.allocate();
            right->MipsCodeGen(dst, data, tmp);
            dst<<"lw $"<<DstReg<<",($"<<idx<<")"<<std::endl;
            dst<<"add $"<<DstReg<<",$"<<DstReg<<",$"<<tmp<<std::endl;
            dst<<"sw $"<<DstReg<<",($"<<idx<<")"<<std::endl;
            data.registers.free_reg(idx);
            data.registers.free_reg(tmp);
        }
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
    SubAssignOperator( ExpressionPtr &_id, ExpressionPtr _right)
        : AssignOps(_id, _right)
    {}
    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg)const override{
        std::string name = id->getId();
        ExpressionPtr arridx = id->getindex();
        if(arridx!= NULL){
            std::string arrid = name + "0";
            arridx->MipsCodeGen(dst,data,DstReg);
            dst<<"sll $"<<DstReg<<",2"<<std::endl;
            int arroffset = data.Stack.back().bindings[arrid].offset - 4;
            int idx = data.registers.allocate();
            dst<<"addiu $"<<idx<<",$30,"<<arroffset<<std::endl;
            dst<<"addu $"<<idx<<",$"<<idx<<",$"<<DstReg<<std::endl;
            int tmp = data.registers.allocate();
            right->MipsCodeGen(dst, data, tmp);
            dst<<"lw $"<<DstReg<<",($"<<idx<<")"<<std::endl;
            dst<<"sub $"<<DstReg<<",$"<<DstReg<<",$"<<tmp<<std::endl;
            dst<<"sw $"<<DstReg<<",($"<<idx<<")"<<std::endl;
            data.registers.free_reg(idx);
            data.registers.free_reg(tmp);
        }
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
    MulAssignOperator( ExpressionPtr &_id, ExpressionPtr _right)
        : AssignOps(_id, _right)
    {}
     virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg)const override{
        std::string name = id->getId();
        ExpressionPtr arridx = id->getindex();
        if(arridx!= NULL){
            std::string arrid = name + "0";
            arridx->MipsCodeGen(dst,data,DstReg);
            dst<<"sll $"<<DstReg<<",2"<<std::endl;
            int arroffset = data.Stack.back().bindings[arrid].offset - 4;
            int idx = data.registers.allocate();
            dst<<"addiu $"<<idx<<",$30,"<<arroffset<<std::endl;
            dst<<"addu $"<<idx<<",$"<<idx<<",$"<<DstReg<<std::endl;
            int tmp = data.registers.allocate();
            right->MipsCodeGen(dst, data, tmp);
            dst<<"lw $"<<DstReg<<",($"<<idx<<")"<<std::endl;
            dst<<"mult $"<<DstReg<<",$"<<tmp<<std::endl;
            dst<<"mflo $"<<DstReg<<std::endl;
            dst<<"sw $"<<DstReg<<",($"<<idx<<")"<<std::endl;
            data.registers.free_reg(idx);
            data.registers.free_reg(tmp);
        }
        int idx = data.registers.allocate();
        right->MipsCodeGen(dst, data, idx);
        dst<<"mult $"<<DstReg<<",$"<<idx<<std::endl;
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
    DivAssignOperator( ExpressionPtr &_id, ExpressionPtr _right)
        : AssignOps(_id, _right)
    {}
    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg)const override{
        std::string name = id->getId();
        ExpressionPtr arridx = id->getindex();
        if(arridx!= NULL){
            std::string arrid = name + "0";
            arridx->MipsCodeGen(dst,data,DstReg);
            dst<<"sll $"<<DstReg<<",2"<<std::endl;
            int arroffset = data.Stack.back().bindings[arrid].offset - 4;
            int idx = data.registers.allocate();
            dst<<"addiu $"<<idx<<",$30,"<<arroffset<<std::endl;
            dst<<"addu $"<<idx<<",$"<<idx<<",$"<<DstReg<<std::endl;
            int tmp = data.registers.allocate();
            right->MipsCodeGen(dst, data, tmp);
            dst<<"lw $"<<DstReg<<",($"<<idx<<")"<<std::endl;
            dst<<"div $"<<DstReg<<",$"<<tmp<<std::endl;
            dst<<"mflo $"<<DstReg<<std::endl;
            dst<<"sw $"<<DstReg<<",($"<<idx<<")"<<std::endl;
            data.registers.free_reg(idx);
            data.registers.free_reg(tmp);
        }
        int idx = data.registers.allocate();
        right->MipsCodeGen(dst, data, idx);
        dst<<"div $"<<DstReg<<",$"<<idx<<std::endl;
        dst<<"mflo $"<<DstReg<<std::endl;
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
    ModAssignOperator( ExpressionPtr &_id, ExpressionPtr _right)
        : AssignOps(_id, _right)
    {}
    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg)const override{
        std::string name = id->getId();
        ExpressionPtr arridx = id->getindex();
        if(arridx!= NULL){
            std::string arrid = name + "0";
            arridx->MipsCodeGen(dst,data,DstReg);
            dst<<"sll $"<<DstReg<<",2"<<std::endl;
            int arroffset = data.Stack.back().bindings[arrid].offset - 4;
            int idx = data.registers.allocate();
            dst<<"addiu $"<<idx<<",$30,"<<arroffset<<std::endl;
            dst<<"addu $"<<idx<<",$"<<idx<<",$"<<DstReg<<std::endl;
            int tmp = data.registers.allocate();
            right->MipsCodeGen(dst, data, tmp);
            dst<<"lw $"<<DstReg<<",($"<<idx<<")"<<std::endl;
            dst<<"div $"<<DstReg<<",$"<<tmp<<std::endl;
            dst<<"mfhi $"<<DstReg<<std::endl;
            dst<<"sw $"<<DstReg<<",($"<<idx<<")"<<std::endl;
            data.registers.free_reg(idx);
            data.registers.free_reg(tmp);
        }
        int idx = data.registers.allocate();
        right->MipsCodeGen(dst, data, idx);
        dst<<"div $"<<DstReg<<",$"<<idx<<std::endl;
        dst<<"mfhi $"<<DstReg<<std::endl;
        data.registers.free_reg(idx);
        int varoffset = data.Stack.back().bindings[name].offset;
        dst<<"sw $"<<DstReg<<","<<varoffset<<"($30)"<<std::endl;
    }
};

class AndAssignOperator
 : public AssignOps
{
protected:
    virtual const char *getOpcode() const override
    {return "&=";}
public:
    AndAssignOperator( ExpressionPtr &_id, ExpressionPtr _right)
        : AssignOps(_id, _right)
    {}
    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg)const override{
        std::string name = id->getId();
        ExpressionPtr arridx = id->getindex();
        if(arridx!= NULL){
            std::string arrid = name + "0";
            arridx->MipsCodeGen(dst,data,DstReg);
            dst<<"sll $"<<DstReg<<",2"<<std::endl;
            int arroffset = data.Stack.back().bindings[arrid].offset - 4;
            int idx = data.registers.allocate();
            dst<<"addiu $"<<idx<<",$30,"<<arroffset<<std::endl;
            dst<<"addu $"<<idx<<",$"<<idx<<",$"<<DstReg<<std::endl;
            int tmp = data.registers.allocate();
            right->MipsCodeGen(dst, data, tmp);
            dst<<"lw $"<<DstReg<<",($"<<idx<<")"<<std::endl;
            dst<<"and $"<<DstReg<<",$"<<DstReg<<",$"<<tmp<<std::endl;
            dst<<"sw $"<<DstReg<<",($"<<idx<<")"<<std::endl;
            data.registers.free_reg(idx);
            data.registers.free_reg(tmp);
        }
        int idx = data.registers.allocate();
        right->MipsCodeGen(dst, data, idx);
        dst<<"and $"<<DstReg<<",$"<<DstReg<<",$"<<idx<<std::endl;
        data.registers.free_reg(idx);
        int varoffset = data.Stack.back().bindings[name].offset;
        dst<<"sw $"<<DstReg<<","<<varoffset<<"($30)"<<std::endl;
    }
};

class OrAssignOperator
 : public AssignOps
{
protected:
    virtual const char *getOpcode() const override
    {return "|=";}
public:
    OrAssignOperator( ExpressionPtr &_id, ExpressionPtr _right)
        : AssignOps(_id, _right)
    {}
    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg)const override{
        std::string name = id->getId();
        ExpressionPtr arridx = id->getindex();
        if(arridx!= NULL){
            std::string arrid = name + "0";
            arridx->MipsCodeGen(dst,data,DstReg);
            dst<<"sll $"<<DstReg<<",2"<<std::endl;
            int arroffset = data.Stack.back().bindings[arrid].offset - 4;
            int idx = data.registers.allocate();
            dst<<"addiu $"<<idx<<",$30,"<<arroffset<<std::endl;
            dst<<"addu $"<<idx<<",$"<<idx<<",$"<<DstReg<<std::endl;
            int tmp = data.registers.allocate();
            right->MipsCodeGen(dst, data, tmp);
            dst<<"lw $"<<DstReg<<",($"<<idx<<")"<<std::endl;
            dst<<"or $"<<DstReg<<",$"<<DstReg<<",$"<<tmp<<std::endl;
            dst<<"sw $"<<DstReg<<",($"<<idx<<")"<<std::endl;
            data.registers.free_reg(idx);
            data.registers.free_reg(tmp);
        }
        int idx = data.registers.allocate();
        right->MipsCodeGen(dst, data, idx);
        dst<<"or $"<<DstReg<<",$"<<DstReg<<",$"<<idx<<std::endl;
        data.registers.free_reg(idx);
        int varoffset = data.Stack.back().bindings[name].offset;
        dst<<"sw $"<<DstReg<<","<<varoffset<<"($30)"<<std::endl;
    }
};

class XorAssignOperator
 : public AssignOps
{
protected:
    virtual const char *getOpcode() const override
    {return "^=";}
public:
    XorAssignOperator( ExpressionPtr &_id, ExpressionPtr _right)
        : AssignOps(_id, _right)
    {}
    virtual void MipsCodeGen(std::ostream &dst,Data &data, int DstReg)const override{
        std::string name = id->getId();
        ExpressionPtr arridx = id->getindex();
        if(arridx!= NULL){
            std::string arrid = name + "0";
            arridx->MipsCodeGen(dst,data,DstReg);
            dst<<"sll $"<<DstReg<<",2"<<std::endl;
            int arroffset = data.Stack.back().bindings[arrid].offset - 4;
            int idx = data.registers.allocate();
            dst<<"addiu $"<<idx<<",$30,"<<arroffset<<std::endl;
            dst<<"addu $"<<idx<<",$"<<idx<<",$"<<DstReg<<std::endl;
            int tmp = data.registers.allocate();
            right->MipsCodeGen(dst, data, tmp);
            dst<<"lw $"<<DstReg<<",($"<<idx<<")"<<std::endl;
            dst<<"xor $"<<DstReg<<",$"<<DstReg<<",$"<<tmp<<std::endl;
            dst<<"sw $"<<DstReg<<",($"<<idx<<")"<<std::endl;
            data.registers.free_reg(idx);
            data.registers.free_reg(tmp);
        }
        int idx = data.registers.allocate();
        right->MipsCodeGen(dst, data, idx);
        dst<<"xor $"<<DstReg<<",$"<<DstReg<<",$"<<idx<<std::endl;
        data.registers.free_reg(idx);
        int varoffset = data.Stack.back().bindings[name].offset;
        dst<<"sw $"<<DstReg<<","<<varoffset<<"($30)"<<std::endl;
    }
};




#endif
