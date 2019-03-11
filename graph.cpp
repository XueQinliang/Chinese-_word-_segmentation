#include "graph.h"
double makescore(ArcNode *a, ArcNode *b){//分数越低越好
    if(a == NULL || b == NULL) return 1;
    int alen = a->word.size();
    int blen = b->word.size();
    partscore p;
    int score = p.getscore(a->part[0],b->part[0]);
    return 0.1*((alen-blen)*(alen-blen)-10*score)+1;
}
void graph::createnode(int vexnum){//初始化结点
    this->vexnum=vexnum;
    this->vnodes = new VNode [vexnum];
    for(int i=0;i < this->vexnum; i++){
        this->vnodes[i].num=i;
        this->vnodes[i].degree = 0;
        this->vnodes[i].fristarc=NULL;
    }
}
double graph::dij_search(int start, int target, bool show){//返回值为最小路径的权值
    double routelen[target+1];//用一个数组存储所有结点和出发点的最短距离
    int shortpath[target+1];//用一个数组存储最短路径，每个位置的值表示这个结点的前驱结点的值
    for(int i=0; i<target+1; i++){
        routelen[i]=0x7fffffff;//先用一个很大的数字近似代表∞来初始化所有弧
        shortpath[i]=-1;//前驱结点均初始化为-1表示不存在
    }
    routelen[start] = 0;//第一个结点到第一个结点的距离为0
    for(int i=0; i<=target; i++){//用DIJ算法求所有结点的前驱结点和距出发点的距离
        ArcNode* arc = vnodes[i].fristarc;
        ArcNode* temp = NULL;
        if(shortpath[i] != -1){//如果该节点有前驱
            temp = vnodes[shortpath[i]].fristarc;
            for(int k = 0;k<vnodes[shortpath[i]].degree;k++){
                if(temp->adjvex == i)break;
                else temp = temp->nextarc;
            }
        }
        int j=0;
        while(j<vnodes[i].degree){
            if(routelen[i]+arc->weight<routelen[arc->adjvex]){
                shortpath[arc->adjvex]=i;     
                double score = makescore(temp, arc);
                double weight = (arc->weight);
                //weight *= score;
                routelen[arc->adjvex]=routelen[i]+weight;
            }
            arc = arc->nextarc;
            j++;
        }
    }
    if(show == true){//由于需要从头输出，利用栈的先进后出特点
        stack< pair<int,int> > Stack;
        for(int i=target; i>0;){
            Stack.push(make_pair(shortpath[i],i));
            i=shortpath[i];
        }
        while(!Stack.empty()){
            pair<int,int> p = Stack.top();
            Stack.pop();
            ArcNode* arc;
            arc = this->vnodes[p.first].fristarc;
            while(arc->adjvex != p.second){
                arc = arc->nextarc;
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0b);
            cout<<arc->word;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0d);
            cout<<"/";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0e);
        }
    }
    return routelen[target];//最短路径的值
}
void graph::k_search(int start,int k){//k最短路径算法
    int kc=1;
    priority_queue<VNode> Queue;//优先队列
    stack< pair<int,int> > Stack;
    this->vnodes[start].pre=NULL;
    this->vnodes[start].distance = 0;
    this->vnodes[start].restdistance = this->dij_search(start, this->vexnum-1, false);
    this->vnodes[start].shortpath = new int[this->vexnum];//起始节点初始化
    for(int i=0; i<vexnum; i++){
        this->vnodes[start].shortpath[i] = -1;
    }
    Queue.push(this->vnodes[start]);
    while((!Queue.empty())&&kc<=k){//求出k条最短路径
        VNode vn = Queue.top();//通过计算已有的距离和未走过的最短距离，出队列的一定是先到终点的结点
        Queue.pop();
        if(vn.num == this->vexnum-1){//如果发现出队列的是终点，说明这条路径已经到终点
            for(int i=vexnum-1; i>0;){
                Stack.push(make_pair(vn.shortpath[i],i));
                i=vn.shortpath[i];
            }
            cout<<kc<<" ";
            double weight=0;
            while(!Stack.empty()){//利用栈来从头输出句子的切分结果
                pair<int,int> p = Stack.top();
                Stack.pop();
                ArcNode* arc;
                arc = this->vnodes[p.first].fristarc;
                while(arc->adjvex != p.second){
                    arc = arc->nextarc;
                }
                weight+=arc->weight;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0b);
                cout<<arc->word;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0d);
                cout<<"/";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0e);
            }
            cout<<ends<<weight<<endl;
            kc++;
            continue;
        }
        ArcNode* temp = NULL;
        if(vn.shortpath[vn.num] != -1){//如果该节点有前驱
            temp = vnodes[vn.shortpath[vn.num]].fristarc;
            for(int k = 0;k<vnodes[vn.shortpath[vn.num]].degree;k++){
                if(temp->adjvex == vn.num)break;
                else temp = temp->nextarc;
            }
        }
        int c=0;
        for(ArcNode* arc = vn.fristarc;c < vn.degree; arc = arc->nextarc,c++){
            double score = makescore(temp, arc);
            double weight = (arc->weight);
            //weight *= score;
            vnodes[arc->adjvex].distance = vn.distance+weight;//计算照此路径距起始点的距离
            vnodes[arc->adjvex].restdistance = this->dij_search(arc->adjvex,this->vexnum-1,false);//计算当前结点距终点的最短距离
            VNode newnode = vnodes[arc->adjvex];//生成一个新的副本
            newnode.shortpath = new int[this->vexnum];//开辟空间
            memcpy(newnode.shortpath,vn.shortpath,this->vexnum*sizeof(int));//保存路径，以防有相同结点的路径之间互相干扰
            newnode.shortpath[arc->adjvex] = vn.num;//记录当前步骤
            Queue.push(newnode);
        }
    }
}
