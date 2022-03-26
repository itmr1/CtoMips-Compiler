#ifndef context_hpp
#define context_hpp

#include <string>
#include <vector>
#include <iostream>
#include <map>
class Registers
{
public:

    int regs[32] = 
    {   1, // 0 register 
        1, // dont change
        1, 1, // return registers, cannot change
        1, 1, 1, 1, // function arguments dont chnage
        0, 0, 0, 0, 0, 0, 0, 0, // temporary registers can change
        1, 1, 1, 1, 1, 1, 1, 1, // vaues preserved across fucntions
        0, 0, // temporary registers 
        1, 1, // dont change
        1, // global pointer 
        1, // stack pointer 
        1, // frame pointer 
        1 // jump register 
    };

    void free_reg(int i) {regs[i] = 0;}
    void use_reg (int i) {regs[i] = 1;}

    int allocate(){
        for(int i = 8; i<26;i++){
            if(!regs[i]){
                use_reg(i);
                return i;
            }
        }
        return -1;
    }
    std::string make_regname(int i){
        return "$"+std::to_string(i);
    } 

};


class variable
{
public:
  /*unsigned*/ int size; // How many bytes does the variable take up
  int offset; // Offset from frame pointer (+ for arguments, - for variables)
  //enum Specifier type = Specifier::_int; // keeps track of type, int by default (refactor this to enum if possible at some point)
};

class stackframe
{
public:
    int frameSize =0; //size of frame
    int curroffset =0;
    std::map<std::string, variable> bindings;
};

class Data
{
public:
    Registers registers;
    std::vector<stackframe> Stack;
    std::map<std::string, std::string> globaldec;
    std::string CurrLabel ="";
    std::string MakeLabel(std::string s){
        static count = 0;
        std::string label = s+std::tostring(count);
        count++;
        return label;
    }
};

class function
{
public:
  /*unsigned*/ int size; // Total size of arguments
  std::vector<unsigned int> argSize; // Individual size of each argument
};

//int FrameSize;

#endif