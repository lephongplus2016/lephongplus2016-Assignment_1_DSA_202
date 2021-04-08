#ifndef VM_H
#define VM_H
#include "main.h"




//stack------------------------------
#define MAX 1000
class Stack { 
public:
int top;
    int s[MAX]; // Maximum size of Stack
 
    Stack() ;
    bool push(int x);
    int pop();
    int peek();
    bool isEmpty();
};
//--------------------------------------------------


enum DataType { NONE, INT ,FLOAT,BOOL, ADDRESS};


struct GReg {
   int data_int;
    float data_float;
    bool data_bool;
    int data_address;
    DataType type = NONE;
    GReg();
    ~GReg();

};



struct Instruction {
    string code;
    string op1;
    string op2;
};

class VM
{
public:
  //them thuoc tinh cua VM
	Instruction codeMe[1000];
	Stack *stack;
	GReg registerVM[15];
  GReg StaticReg[65535];

  // thanh ghi
  int ip; // thanh ghi chay lan luot cac opcode
  int codeLoadedIndex;

  VM();
  ~VM();
  void move(string dest , string src);
  void output(string dest);
  void input(string dest);
  void loadToMemory(string instruction);
  bool readfile(string filename);
  void dump();
  void load(string dest, string src);
  void store(string dest, string src);
  // nhom lenh logic so hoc
  void add(string dest, string src);
  void minus(string dest, string src);
  void mul(string dest, string src);
  void div(string dest, string src);
  //nhom lenh so sanh
  void CmpEQ(string dest, string src);
  void CmpNE(string dest, string src);
  void CmpLT(string dest, string src);
  void CmpGT(string dest, string src);
  void CmpGE(string dest, string src);
  void CmpLE(string dest, string src);
  //nhom lenh dieu khien
  void call(string src);
  void returnIp();
  //nhom lenh logic
  void notP(string dest);
  void andP(string dest, string src);
  void orP(string dest, string src);

  void run(string filename);
};
#endif


