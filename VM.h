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

// union GregData{
//  	int data_int=0;
//     float data_float;
//     bool data_bool;
//     string data_address;
// };

enum DataType { NONE, INT ,FLOAT,BOOL};

struct GReg {
   int data_int=0;
    float data_float;
    bool data_bool;
    string data_address;
    DataType type ;
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

  // thanh ghi
  int ip; // thanh ghi chay lan luot cac opcode
  int codeLoadedIndex;

  VM();
  ~VM();
  void move(string dest , string src);
  void output(string dest);
  void load(string instruction);
  bool readfile(string filename);
  void dump();
  void run(string filename);
};
#endif