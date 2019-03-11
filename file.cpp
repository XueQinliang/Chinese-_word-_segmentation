#include "file.h"
void file::test_map_insert( ){//从文件中读取构建字典结构
    ifstream in("dict.txt");
    if (! in.is_open()){
        cout << "Error opening file";
        exit (1);
    }
    while (!in.eof()){
        char buffer[100];
        in.getline (buffer,100);//按行读取
        char* temp = strtok(buffer," ");
        int num=0;
        info newinfo;
        string word;
        while(temp)//切分字符串
        {
            if(num == 0) word = temp;
            else if(num == 1) newinfo.count = stoi(temp,0,10);
            else if(num == 2) newinfo.part = temp;
            num++;
            temp = strtok(NULL," ");
        }
        pair<string, info> newpair=make_pair(word,newinfo);
        direct.insert(newpair);//插入map中
    }
    cout<<"dictionary input finished\n";
    in.close();
}
pair<string, info> file::Find(string target){//在字典中查找一个词
    MyIterator it;
    it = this->direct.find(target);
    if (it == this->direct.end()){
        pair<string, info> p;
        p.first = "\0";//如果没找到的话，返回空字符串
        return p;
    }
    return make_pair(it->first,it->second);//返回该词语和词频和词性
}
