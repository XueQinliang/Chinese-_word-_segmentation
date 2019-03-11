#include "sentence.h"
void Sentence::devide(file fp,bool paper){//全切分算法，找出一个句子中所有可能的值
    int deposition=0;
    while(deposition < len){
        for(int i=0;i<len-deposition;i+=2){
            string s;
            s.assign(sentence,deposition,len-deposition-i);
            pair<string, info> it = fp.Find(s);
            ArcNode* arc;
            arc = new ArcNode;
            if(it.first != "\0"){
                arc->word.assign(it.first);
                arc->weight = log(1.0*maxcount/it.second.count+1)/((int)arc->word.size());
                arc->part = it.second.part;
            }else if(it.first == "\0"&&s.size()<=2){
                arc->word = s;
                arc->weight = log(maxcount+1)/((int)arc->word.size());
                arc->part = "un";//词性未知
            }else {
                continue;
            }
            arc->nextarc = this->gra.vnodes[deposition].fristarc;
            this->gra.vnodes[deposition].fristarc = arc;
            this->gra.vnodes[deposition].degree++;
            arc->adjvex=(deposition + s.size());
        }
        deposition+=2;
    }
    if(paper == false){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0e);
        cout<<"DIJ:";
        cout<<ends<<gra.dij_search(0, this->gra.vexnum-1,true)<<endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x07);
        cout<<"please input a number bigger than zero:";
        int k;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0a);
        cin>>k;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x07);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0e);
        cout<<k<<"_shorter_path:\n";
        gra.k_search(0,k);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x07);
    }else gra.dij_search(0, this->gra.vexnum-1,true);
}

void Sentence::bigdevide(file fp){
    int length = sentence.size();
    int i = 0;
    int de = 0;
    while(de < length){
        if(sentence[de+i] >= 0){
            string sentence;
            sentence.assign(this->sentence,de,i);
            Sentence s(sentence);
            s.devide(fp,true);
            cout<<this->sentence[de+i];
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0d);
            cout<<"/";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x07);
            de += i+1;
            i=0;
        }
        else i++;
    }
    cout<<endl;
}
