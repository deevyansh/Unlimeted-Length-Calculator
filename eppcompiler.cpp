/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"
#include<iostream>

using namespace std;
//Write your code below this line

EPPCompiler::EPPCompiler(){
    
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    memory_size=mem_limit;
    output_file=out_file;
    mem_loc.resize(memory_size);
    for (int i=0; i<memory_size; i++){
        mem_loc[i]=(memory_size- i);
    }
    Parser targ;
}

void EPPCompiler::compile(vector<vector<string>> code){
    vector<vector<string>> v;
    for (int i=0; i<code.size(); i++){
        if (code[i][0]!="del"){
            targ.parse(code[i]);
            v.push_back(generate_targ_commands());}
        else{
            int k=targ.symtable->search(code[i][2]);
            mem_loc.push_back(k);
            targ.parse(code[i]);
            vector<string> v1;
            v1.push_back("DEL = mem["+to_string(k)+ "]");
            v.push_back(v1);
        }
    }
    vector<string> v1;
    for (int i=0; i<v.size(); i++){
        for (int j=0; j<v[i].size(); j++){
            v1.push_back(v[i][j]);
        }
    }
    write_to_file(v1);
    return;
}


void generate(ExprTreeNode* s, vector<string> &v1,SymbolTable* s1){
    if (s->left==NULL && s->right==NULL){
    }
    else{
        generate(s->right,v1,s1);
        generate(s->left,v1,s1);
    }
    if (s->type=="VAL"){
        v1.push_back("PUSH "+ to_string(s->num));}
    else if (s->type=="VAR"){
        int k =s1->search(s->id);
        v1.push_back("PUSH mem["+ to_string(k)+"]" );
    }
    else{
        v1.push_back(s->type);
    }
}

vector<string> EPPCompiler::generate_targ_commands(){
    ExprTreeNode* e1= targ.expr_trees.back();
    vector<string> v1;
    generate(e1->right,v1,targ.symtable);
    if (e1->left->id!="RET"){
        if (targ.symtable->search(e1->left->id)==-2){
            targ.symtable->insert(e1->left->id);
            targ.symtable->assign_address(e1->left->id, mem_loc.back());
            int k =targ.symtable->search(e1->left->id);
            mem_loc.pop_back();
            v1.push_back("mem["+ to_string(k)+"] = POP");}
        else{
            int k=targ.symtable->search(e1->left->id);
            v1.push_back("mem["+ to_string(k)+"] = POP");
        }
    }
    else{
        v1.push_back("RET = POP");
    }
    return (v1);
}




void EPPCompiler::write_to_file(vector<string> commands) {
    ofstream outputFile(output_file);
    for (int i = 0; i < commands.size(); i++) {
        outputFile << commands[i] << endl;
    }
    outputFile.close();
}


EPPCompiler::~EPPCompiler(){
    
}
//
//int main(){
//    EPPCompiler* E =new EPPCompiler("/Users/deevyanshkhadria/Desktop/output.txt",7);
//    vector<std::string> v1 = {"ap1", ":=", "4"};
//    vector<std::string> v2= {"del", "=", "ap1"};
//    vector<std::string> v3 = {"ap2", ":=", "(", "56", "-", "(", "4", "/", "3", ")", ")"};
//    vector<std::string> v4 = {"ap2", ":=", "(", "ap2", "+", "(", "4", "/", "5", ")", ")"};
//    vector<std::string> v5 = {"ap4", ":=", "(", "ap2", "-", "(", "4", "/", "7", ")", ")"};
//    vector<std::string> v6 = {"ap5", ":=", "(", "ap4", "+", "(", "4", "/", "9", ")", ")"};
//    vector<std::string> v7 = {"ap6", ":=", "(", "ap5", "-", "(", "4", "/", "11", ")", ")"};
//    vector<std::string> v8 = {"ap7", ":=", "(", "ap6", "+", "(", "4", "/", "13", ")", ")"};
//    vector<std::string> v9={"ret","=","(","ap2","+","ap2",")"};
//    vector<vector<string>> n ={v1,v2,v3,v4,v5,v6,v7,v8,v9};
//    E->compile(n);
//    return 0;
//}
