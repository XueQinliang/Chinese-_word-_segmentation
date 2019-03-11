#ifndef GRAPH_H
#define GRAPH_H
#define maxcount 3188252
#include <math.h>
#include <stack>
#include <queue>
#include <windows.h>
#include "file.h"
typedef struct ArcNode{
    int adjvex;
    struct ArcNode* nextarc;
    string word;
    string part;
    double weight;
}ArcNode;

double makescore( ArcNode* a,ArcNode* b);
class partscore{
public:
    int getscore(char a, char b){
        map<char, int>::iterator ita;
        ita = this->m.find(a);
        map<char, int>::iterator itb;
        itb = this->m.find(b);
        if (ita == this->m.end()||itb == this->m.end()){
            return 0;
        }else{
            return score[ita->second][itb->second];
        }
    }
    partscore(){
        m.insert(make_pair('a',0));
        m.insert(make_pair('d',1));
        m.insert(make_pair('n',2));
        m.insert(make_pair('p',3));
        m.insert(make_pair('r',4));
        m.insert(make_pair('v',5));
        score[0][0] = -1; score[0][1] = -1; score[0][2] = 1; score[0][3] = -1; score[0][4] = 1; score[0][5] = -1;
        score[1][0] = 1; score[1][1] = -1; score[1][2] = -1; score[1][3] = 1; score[1][4] = 1; score[1][5] = 1;
        score[2][0] = 1; score[2][1] = 1; score[2][2] = -1; score[2][3] = 1; score[2][4] = 1; score[2][5] = 1;
        score[3][0] = 1; score[3][1] = -1; score[3][2] = 1; score[3][3] = -1; score[3][4] = 1; score[3][5] = 1;
        score[4][0] = 1; score[4][1] = 1; score[4][2] = 1; score[4][3] = 1; score[4][4] = 1; score[4][5] = 1;
        score[5][0] = -1; score[5][1] = -1; score[5][2] = 1; score[5][3] = 1; score[5][4] = 1; score[5][5] = 1;
    }
private:
    map<char,int> m;
    int score[6][6];
};

typedef struct VNode{
    int num;
    int degree;//用邻接表存储，此处仅代表出度
    double distance;
    double restdistance;
    int *shortpath;
    VNode *pre;
    ArcNode *fristarc;
    friend bool operator < (VNode a, VNode b){//比较符号重载，便于优先队列排序
        return a.distance+a.restdistance > b.distance+b.restdistance;//结构体中，距离小的优先级高
    }
}VNode;

class graph{
public:
    void createnode(int vexnum);
    double dij_search(int start ,int target, bool show);
    void k_search(int start,int k);
    friend class Sentence;//Sentence可以随意调用graph的成员
private:
    VNode* vnodes;//结点数组
    int vexnum;//结点数
};

#endif // GRAPH_H
