#pragma once
#include<iostream>
#include<fstream>
#include<random>
#include<sstream>
#include<vector>
#include<stack>
#include<algorithm>
#include<assert.h>
#include<set>
#include<iomanip>

const std::vector<char> OPERATORS = { '+', '-', '*', '/' };
const int MIN_NUM = 1;
const int MAX_NUM = 100;

//输出min到max范围的一个整数
int randomInt(int min, int max);

//生成随机题目
std::vector<std::string> generateExercises(int num, int range);

//判断是否为运算符
bool isOperator(char c);

//获得符号的优先级
int getPrecedence(char op);

//中缀表达式转化为后缀表达式
std::string infixToPostfix(const std::string& infixExpression);

//将数组中的题目由中缀表达式转化为后缀表达式
std::vector<std::string> transform(const std::vector<std::string>& vec);

//根据不同符号计算结果
double performOperation(double operand1, double operand2, char op);

//计算后缀表达式
double evaluatePostfix(const std::string& postfixExpression);

//计算结果
std::vector<double> get_result(const std::vector<std::string>& vec);

//将题目写入文件,把文件名当参数传入
void write_to_text(const std::vector<std::string>& vec, std::string file_name);

//把结果写入文件,把文件名当参数传入
void write_result_to_file(const std::vector<double>& vec, std::string file_name);

//读取文件中的内容，并存入字符串数组中
std::vector<std::string> get_file_to_string(const std::string str);

//把string转化为double
std::vector<double>string_to_double(std::vector<std::string>v);

//通过判断两个数组是否相等，把相等下标存到correct数组中，其余的存到wrong数组中
void compareArrays(const std::vector<double>& array1, const std::vector<double>& array2, std::vector<int>& correct, std::vector<int>& wrong);

//把correct和wrong的内容存到Grade.txt中
void writeResultToFile(const std::vector<int>& correct, const std::vector<int>& wrong, std::string file_name);

//封装函数,随机生成题目，并把题目和答案分别输出到Exercises.txt，Answers.txt文件中
//参数num代表生成题目数量，range代表范围，即多大数字以内的运算，字符串exercises，answer分别代表两个文件名
void generte_topic_answer(int num, int range, const std::string exercises, const std::string answer);

//封装函数，输入question.txt，answer.txt就直接判断答案是否正确，并把内容输出到Grade.txt中
void judgment_que_ans(const std::string question, const std::string answer);



