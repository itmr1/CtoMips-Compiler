#include <string>

class Registers
{
private:
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
public:

    void free_reg(int i) {regs[i] = 0;}
    void use_reg (int i) {regs[i] = 1;}

    int allocate(){
        for(int i = 8; i<26;i++){
            if(!regs[i]){
                regs[i] =1;
                return i;
            }
        }
        return -1;
    }

    std::string make_regname(int i){
        return "$"+std::to_string(i)
    }

};

std::string make_label(std::string s){
    static int  count = 0;
    return s+"__"+std::to_string(count++);
}
