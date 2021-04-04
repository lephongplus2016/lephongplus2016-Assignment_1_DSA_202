#include "VM.h"

bool VM::readfile(string filename)
{
    fstream f;
    f.open(filename, ios::in);
    string data;
    string line;
    int *codetemp = new int[500];
    while(!f.eof())
    {
        getline(f,line);
        data += line;
        loadToMemory(line);

    }
    f.close();
    return true;
}

Stack::Stack() { top = -1; }
 
bool Stack::push(int x)
{
    if (top >= (MAX - 1)) {
        cout << "Stack Overflow";
        return false;
    }
    else {
        s[++top] = x;
        cout << x << " pushed into stack\n";
        return true;
    }
}
 
int Stack::pop()
{
    if (top < 0) {
        cout << "Stack Underflow";
        return 0;
    }
    else {
        int x = s[top--];
        return x;
    }
}
int Stack::peek()
{
    if (top < 0) {
        cout << "Stack is Empty";
        return 0;
    }
    else {
        int x = s[top];
        return x;
    }
}
 
bool Stack::isEmpty()
{
    return (top < 0);
}

VM::~VM(){}
GReg::GReg(){ this->type = NONE; }
GReg::~GReg(){}

 VM::VM()
{
    
      this->ip = 0;
      for (int i = 0; i < 15; i++) {
            registerVM[i].type = NONE;
        }
        this->codeLoadedIndex = 0;
}
// nhom lenh doc ghi --------------------------------------------------------
//---------------------------------------------------------------------------
void VM::move(string dest, string src) {

    int destID= stoi(dest.substr(1))-1;
    if(src[0] == 'R')
    {
        int srcID = stoi(src.substr(1))-1;
        registerVM[destID].type = registerVM[srcID].type;   //nho tang ip len nua

        if(registerVM[srcID].type == INT )
        {
            registerVM[destID].data_int = registerVM[srcID].data_int;
        }
        else if(registerVM[srcID].type == FLOAT )
        {
            registerVM[destID].data_float = registerVM[srcID].data_float;
        }
        else if(registerVM[srcID].type == BOOL )
        {
            registerVM[destID].data_bool = registerVM[srcID].data_bool;
        }
        else { // case address
            registerVM[destID].data_address = registerVM[srcID].data_address;
            
        }

    }
    else {
        src = src.erase(src.length()-1);
        regex e ("[-+]?[0-9]*\\.[0-9]+");     // nho co \ nen regex moi nhan ra .
            bool correct = regex_match(src, e);

            if(src== "true")
            {
                registerVM[destID].data_bool = true;
                registerVM[destID].type = BOOL;
            }
            else if(src== "false")
            {
                registerVM[destID].data_bool = false;
                registerVM[destID].type = BOOL;
            }
            else if(correct == true)
            {
                registerVM[destID].data_float = stof(src);
                registerVM[destID].type = FLOAT;
            }
            else if(src[src.length()-1] == 'A' ){ //case address

                string temp = src.erase(src.length()-1);
                registerVM[destID].type = ADDRESS;  
                registerVM[destID].data_address = stoi(temp);
                
            }
            else{
                registerVM[destID].data_int = stoi(src);
                registerVM[destID].type = INT;
            }
    }
    this->ip++;
}
    
void VM::output(string dest) {
    int index = stoi(dest.substr(1)) - 1;
        if(registerVM[index].type == INT )
        {
            cout<<registerVM[index].data_int ;
        }
        else if(registerVM[index].type == FLOAT )
        {
            cout<<registerVM[index].data_float ;
        }
        else if(registerVM[index].type == BOOL )
        {
            cout<<registerVM[index].data_bool ;
        }
        else if(registerVM[index].type == ADDRESS ){
            cout<<registerVM[index].data_address;  //address case
        }
    ip++;
    }

// lay gia tri cua src gan cho dest; src van la address nhung dest thi khong.
void VM::load(string dest, string src)
{
    int destID= stoi(dest.substr(1))-1;
    int srcID= stoi(src.substr(1))-1;
    int indexStatic = registerVM[srcID].data_address;
    DataType srcType = StaticReg[indexStatic].type;
    registerVM[destID].type = srcType;

    // xu ly gan gia tri cua src cho dest, dest co type theo kieu cua gia tri duoc dan
    if(srcType == INT )
        {
            registerVM[destID].data_int = StaticReg[indexStatic].data_int;
        }
        else if(srcType== FLOAT )
        {
            registerVM[destID].data_float = StaticReg[indexStatic].data_float;
        }
        else 
        {
            registerVM[destID].data_bool = StaticReg[indexStatic].data_bool;
        }
    ip++;
}

void VM::store(string dest, string src)  //xac dinh dest da la address variable , src la ko the la dia chi
{
    int destID= stoi(dest.substr(1))-1;
    int indexStatic = registerVM[destID].data_address;          // luu vao bo nho tinh
    if(src[0] == 'R')
    {
        int srcID = stoi(src.substr(1))-1;
        
        
        StaticReg[indexStatic].type = registerVM[srcID].type ;

        if(registerVM[srcID].type == INT )
        {
            StaticReg[indexStatic].data_int = registerVM[srcID].data_int;
        }
        else if(registerVM[srcID].type == FLOAT )
        {
            StaticReg[indexStatic].data_float = registerVM[srcID].data_float;
        }
        else if(registerVM[srcID].type == BOOL )                       // ko the la luu address vao bo nho tinh
        {
            StaticReg[indexStatic].data_bool = registerVM[srcID].data_bool;
        }

    }
    else {
        regex e ("[-+]?[0-9]+\\.[0-9]+");     // nho co \ nen regex moi nhan ra .
            bool correct = regex_match(src, e);

            if(src== "true")
            {
                StaticReg[indexStatic].data_bool = true;
                StaticReg[indexStatic].type = BOOL;
            }
            else if(src== "false")
            {
                StaticReg[indexStatic].data_bool = false;
                StaticReg[indexStatic].type = BOOL;

            }
            else if(correct == true)
            {
                StaticReg[indexStatic].data_float = stof(src);
                StaticReg[indexStatic].type = FLOAT;

            }
            else{
                StaticReg[indexStatic].data_int = stoi(src);
                StaticReg[indexStatic].type = INT;
  
            }
    }
    this->ip++;
}


// nhom lenh so hoc -----------------------------------------------------------
//-----------------------------------------------------------------------------
void VM::add(string dest, string src){
    int destID= stoi(dest.substr(1))-1;
        if(src[0] == 'R')
    {
        int srcID = stoi(src.substr(1))-1;
        

        if(registerVM[srcID].type == INT && registerVM[destID].type== INT)
        {
            registerVM[destID].data_int += registerVM[srcID].data_int;
        }
        else if(registerVM[srcID].type == FLOAT || registerVM[destID].type== FLOAT)
        {
            registerVM[destID].data_float += registerVM[srcID].data_float;
        }
        else {
            throw TypeMismatch(ip);
        }
        
    }
    else {
        src = src.erase(src.length()-1);
        regex e ("[-+]?[0-9]*\\.[0-9]+");     // nho co \ nen regex moi nhan ra .
            bool correct = regex_match(src, e);

            if(src== "true")
            {
                throw TypeMismatch(ip);
            }
            else if(src== "false")
            {
                throw TypeMismatch(ip);
            }
            else if(correct == true)
            {
                if(registerVM[destID].type == INT ) //xet src la float
                {
                    registerVM[destID].data_float = registerVM[destID].data_int;
                }
                registerVM[destID].data_float += stof(src);
                registerVM[destID].type = FLOAT;
            }
            else if(src[src.length()-1] == 'A' ){ //case address

                throw TypeMismatch(ip);
                
            }
            else{
                if(registerVM[destID].type == FLOAT )  // xet src la int
                {
                    registerVM[destID].data_float += stof(src);
                }
                registerVM[destID].data_int += stoi(src);
            }
    }
    this->ip++;
}

void VM::minus(string dest, string src){

}

void VM::mul(string dest, string src){


}

void VM::div(string dest, string src){

}


void VM::loadToMemory(string instruction)
{
    if(instruction[0] == ' ' || instruction[instruction.length()-1]==' ')
    {
         throw ("Invalid Instruction");
    }

    char* cstr = new char[instruction.length() + 1];
    strcpy(cstr, instruction.c_str());
    
    char* tok = strtok(cstr, " ,");
    Instruction ins;
    ins.code = string(tok);

    int i=0;
    while (tok != NULL) {
        tok = strtok(NULL, " ,");
        if(i==0 && tok !=NULL){
            ins.op1 = string(tok);
        }
        else if(i == 1 && tok!=NULL)
        {
            ins.op2= string(tok);
        }
        else if(tok!=NULL){
            throw ("Invalid Instruction");
        }
        i++;
    }
    this->codeMe[codeLoadedIndex]=ins;
    codeLoadedIndex++;
}

void VM::run(string filename)
{
    this->readfile(filename);
	//cout << 1;
    for(int i=0; i<this->codeLoadedIndex; i++)
    {
        if(codeMe[i].code == "Move")
        {
            move(codeMe[i].op1,codeMe[i].op2);
        }
        else if(codeMe[i].code == "Output")
        {
            output(codeMe[i].op1);
        }
        else if(codeMe[i].code == "Load")
        {
            load(codeMe[i].op1,codeMe[i].op2);
        }
        else if(codeMe[i].code == "Store")
        {
            store(codeMe[i].op1,codeMe[i].op2);
        }
    }
    dump();   // nho xoa
}

void VM::dump() {
        cout << endl << "VM Info: " << endl;
        cout << "IP: " << this->ip << endl;
        for (int i = 0; i < 7; i++) {
            
            if (registerVM[i].type != NONE) {
                cout << "R" << i + 1 << ": " << registerVM[i].data_int << endl;
            }
        }
    }


