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

enum DataType { NONE, INT ,FLOAT,BOOL, ADDRESS};

// struct address_type {
// 	string address;
// 	DataType add_type ;
// };

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
  GReg StaticReg[1000];

  // thanh ghi
  int ip; // thanh ghi chay lan luot cac opcode
  int codeLoadedIndex;

  VM();
  ~VM();
  void move(string dest , string src);
  void output(string dest);
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
  
  void run(string filename);
};
#endif


//Move R1, 0A      // dong nay luu dia chi bo nho tinh la 0A vao R1 , R1 co type la address , va gia tri la 0A
//Store R1, 10     // dong nay luu gia tri 10 vao vi tri 0 tren bo nho tinh, ko lien quan den R1
//Load R1, R1      // dong nay luu gia tri cua vi tri so 0, vao R1, nghia la luu 10 vao R1 va R1 co type la INT
//Output R1        // xuat ra R1
//Halt