#ifndef FILE_H
#define FILE_H
#include <iostream>
#include <fstream>
#include <istream>
#include <ostream>
#include <map>
#include <string>
#include <string.h>
#include <utility>
using namespace std;
struct info{
    int count;//词频
    string part;//词性
};
typedef map<string, info>::iterator MyIterator;
class file{
public:
    void test_map_insert();
    pair<string, info> Find(string target);
private:
    map<string, info> direct;
};
#endif // FILE_H
