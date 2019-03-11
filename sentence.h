#ifndef SENTENCE_H
#define SENTENCE_H
#include "file.h"
#include "graph.h"
class Sentence{
public:
    Sentence(){}
    Sentence(string s){
        sentence = s;
        len = s.size();
        gra.createnode(len+1);
    }
    void input(ifstream& in,file fp){
        while(in>>this->sentence){
            bigdevide(fp);
        }
    }
    void devide(file fp,bool whole);//whole代表是否是作为全文分词函数内部的调用
    void bigdevide(file fp);
private:
    string sentence;
    int len;
    graph gra;
};

#endif // SENTENCE_H
