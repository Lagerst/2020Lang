// ConsoleApplication2.cpp: 定义控制台应用程序的入口点。
// STL

#include "stdafx.h"
#define scanf scanf_s

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  // 1.定义和初始化
  vector<int> vec1;                           //默认初始化，vec1为空
  vector<int> vec2(vec1);                     //使用vec1初始化vec2
  vector<int> vec3(vec1.begin(), vec1.end()); //使用vec1初始化vec2
  vector<int> vec4(10);                       // 10个值为的元素
  vector<int> vec5(10, 4);                    // 10个值为的元素
                                              // 2.常用操作方法
  vec1.push_back(100);                        //添加元素
  int size = vec1.size();                     //元素个数
  bool isEmpty = vec1.empty();                //判断是否为空
  cout << vec1[0] << endl;                    //取得第一个元素
  vec1.insert(vec1.end(), 5, 3); //从vec1.back位置插入个值为的元素
  vec1.pop_back();               //删除末尾元素
  vec1.erase(vec1.begin(), vec1.end()); //删除之间的元素，其他元素前移
  cout << (vec1 == vec2) ? true : false; //判断是否相等==、！=、>=、<=...
  vector<int>::iterator iter = vec1.begin(); //获取迭代器首地址
  vec1.clear();                              //清空元素
                                             // 3.遍历
                                             //下标法
  vec1.push_back(100);
  vec1.push_back(10);
  int length = vec1.size();
  cout << endl << endl;
  for (int i = 0; i < length; i++) {
    cout << vec1[i] << ' ';
  }
  cout << endl << endl;
  //迭代器法
  vector<int>::const_iterator iterator = vec1.begin();
  for (; iterator != vec1.end(); iterator++) {
    cout << *iterator << ' ';
  }
  system("pause");
  vector<int> v;
  v.push_back(3); //数组尾部插入3
  v.push_back(2);
  v.push_back(1);
  v.push_back(0);
  cout << " 下标 " << v[3] << endl;
  cout << " 迭代器 " << endl;
  for (vector<int>::iterator i = v.begin(); i != v.end(); ++i) {
    cout << *i << " ";
  }
  cout << endl;
  //在第一个元素之前插入111  insert begin+n是在第n个元素之前插入
  v.insert(v.begin(), 111);
  //在最后一个元素之后插入222 insert end + n 是在n个元素之后插入
  v.insert(v.end(), 222);
  for (vector<int>::iterator i = v.begin(); i != v.end(); ++i) {
    cout << *i << " ";
  }
  cout << endl;

  vector<int> arr(10);
  for (int i = 0; i < 10; i++) {
    arr[i] = i;
  }
  for (vector<int>::iterator i = arr.begin(); i != arr.end(); ++i) {
    cout << *i << " ";
  }
  cout << endl;
  //删除 同insert
  arr.erase(arr.begin());
  for (vector<int>::iterator i = arr.begin(); i != arr.end(); ++i) {
    cout << *i << " ";
  }
  cout << endl;
  arr.erase(arr.begin(), arr.begin() + 5);
  for (vector<int>::iterator i = arr.begin(); i != arr.end(); ++i) {
    cout << *i << " ";
  }
  cout << endl;

  system("pause");
  reverse(v.begin(), v.end());
  for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
    cout << *it << " ";
  }
  system("pause");
}