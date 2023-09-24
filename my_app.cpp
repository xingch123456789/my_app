#include"my_app.h"

//输出min到max范围的一个整数
int randomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

//void func(std::string n)
//{
//    std::cout << n <<" ";
//}
//void func1(double n)
//{
//    std::cout << n << " ";
//}


////输出随机真分数
//std::string randomFraction(int min, int max) {
//    int numerator = randomInt(min, max);
//    int denominator = randomInt(min, max);
//    int integer = numerator / denominator;
//    //std::cout << numerator << " " << denominator << std::endl;
//    //numerator %= denominator;
//    std::stringstream ss;
//    if (integer > 0) {
//        numerator %= denominator;
//        if (numerator == 0)ss << integer;//分子分母相等
//        else ss << integer << "'"<< numerator << "/" << denominator;
//    }
//    else ss << numerator << "/" << denominator;
//    return ss.str();
//}

//生成随机题目
std::vector<std::string> generateExercises(int num, int range) {//num控制生成题目的数量，range控制数字的大小
    std::string expression;
    std::vector<std::string>vec;
    //vec.reserve(num);
    for (int i = 0; i < num; i++) {
        // 随机生成算术表达式
        std::stringstream ss;
        int operatorCount = randomInt(2, 4);//控制运算符的数量不超过3个
        for (int j = 0; j < operatorCount; j++) {
            if (j > 0) {//保证第一个字符不是操作符
                ss << OPERATORS[randomInt(0, OPERATORS.size() - 1)];
            }
            ss << randomInt(MIN_NUM, range);
        }
        expression = ss.str();
        vec.push_back(expression);
        // std::cout << expression << std::endl;
    }
    //std::cout << expression << std::endl;
    return vec;
}

//判断是否为运算符
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

//获得符号的优先级
int getPrecedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/') {
        return 2;
    }
    else {
        return 0;
    }
}

//中缀表达式转化为后缀表达式
std::string infixToPostfix(const std::string& infixExpression) {
    std::stack<char> operators;//暂存string中的操作符，用于优先级的判断
    std::string postfixExpression;//存放转化后的结果

    for (char c : infixExpression) {
        if (c == ' ') {
            continue;
        }

        if (isdigit(c)) {//如果是数字就直接加入string中
            postfixExpression += c;
        }
        else if (isOperator(c)) {
            //符号优先级高的先操作
            while (!operators.empty() && operators.top() != '(' && getPrecedence(operators.top()) >= getPrecedence(c)) {
                postfixExpression += operators.top();
                operators.pop();
            }
            operators.push(c);
        }
    }

    //如果string已经遍历完了，存放操作符的栈还有元素，就直接加到string中
    while (!operators.empty()) {
        postfixExpression += operators.top();
        operators.pop();
    }

    return postfixExpression;
}

//将数组中的题目由中缀表达式转化为后缀表达式
std::vector<std::string> transform(const std::vector<std::string>& vec)
{
    std::vector<std::string>tmp;
    for (int i = 0; i<vec.size(); i++)
    {
        std::string str = infixToPostfix(vec[i]);
        tmp.push_back(str);
    }
    return tmp;
}

//根据不同符号计算结果
double performOperation(double operand1, double operand2, char op) {
    switch (op) {
    case '+':
        return operand1 + operand2;
    case '-':
        return operand1 - operand2;
    case '*':
        return operand1 * operand2;
    case '/':
        return operand1 / operand2;
    default:
        return 0;
    }
}

//计算后缀表达式
double evaluatePostfix(const std::string& postfixExpression) {
    std::stack<double> operands;

    for (char c : postfixExpression) {
        if (isdigit(c)) {
            operands.push(c - '0');//将字符转化为数字
        }
        else if (isOperator(c)) {
            double operand2 = operands.top();
            operands.pop();
            double operand1 = operands.top();
            operands.pop();
            double result = performOperation(operand1, operand2, c);
            operands.push(result);
        }
    }
    return operands.top();
}

//计算结果
std::vector<double> get_result(const std::vector<std::string>& vec)
{
    std::vector<double>res;
    for (int i = 0; i < vec.size(); i++)
    {
        double x = abs(evaluatePostfix(vec[i]));//加上绝对值，得到的结果一定为正数，取巧了
        res.push_back(x);
    }
    return res;
}

//将题目写入文件,把文件名当参数传入
void write_to_text(const std::vector<std::string>&vec, std::string file_name)
{
    //打开文件前向先把文件内容清空
    std::fstream ofs1(file_name, std::ios::in | std::ios::out| std::ios::trunc);
    if (!ofs1.is_open()) { std::cout << "file is open failure" << std::endl; }

    int a = 1;
    for (int i = 0; i < vec.size(); i++)
    {
        ofs1 << a << ". " << "e= " << vec[i] << std::endl;
        a++;
    }
    ofs1.close();
    
}

//把结果写入文件,把文件名当参数传入
void write_result_to_file(const std::vector<double>&vec, std::string file_name)
{
    std::fstream ofs1(file_name, std::ios::in | std::ios::out|std::ios::trunc);
    if (!ofs1.is_open()) { std::cout << "file is open failure" << std::endl; }

    int a = 1;
    for (int i = 0; i < vec.size(); i++)
    {
        ofs1 << a << ". " << vec[i] << std::endl;
        a++;
    }
    ofs1.close();
}

//读取文件中的内容，并存入字符串数组中
std::vector<std::string> get_file_to_string(const std::string str)
{
    std::ifstream filename(str);
    assert(filename.is_open());
    std::vector<std::string> lines;
    std::string line;
    while (filename>>line) {
        lines.push_back(line);
        //std::cout << line << std::endl;
    }
    filename.close();
    return lines;
}


//把string转化为double
std::vector<double>string_to_double( std::vector<std::string>v)
{
    std::vector<double>vec;
    for (std::string num : v)
    {
        vec.push_back(std::stod(num));
    }
    return vec;
}

//通过两个数组相等，把相等下标存到correct数组中，其余的存到wrong数组中
void compareArrays(const std::vector<double>& array1, const std::vector<double>& array2, std::vector<int>& correct, std::vector<int>& wrong) {
    for (int i = 0; i < array1.size(); i++) {
        if (array1[i] == array2[i]) {
            correct.push_back(i);
        }
        else {
            wrong.push_back(i);
        }
    }
}

//把correct和wrong的内容存到Grade.txt中
void writeResultToFile(const std::vector<int>& correct, const std::vector<int>& wrong, std::string file_name) {
    std::ofstream outputFile(file_name);
    if (outputFile.is_open()) {
        outputFile << "Correct: " << correct.size() << " (";
        for (int i = 0; i < correct.size(); i++) {
            outputFile << correct[i];
            if (i != correct.size() - 1) {
                outputFile << ", ";
            }
        }
        outputFile << ")" << std::endl;

        outputFile << "Wrong: " << wrong.size() << " (";
        for (int i = 0; i < wrong.size(); i++) {
            outputFile << wrong[i];
            if (i != wrong.size() - 1) {
                outputFile << ", ";
            }
        }
        outputFile << ")" << std::endl;

        outputFile.close();
    }
    else {
        std::cout << "Failed to open file." << std::endl;
    }
}

//封装函数,随机生成题目，并把题目和答案分别输出到Exercises.txt，Answers.txt文件中
//参数num代表生成题目数量，range代表范围，即多大数字以内的运算，字符串exercises，answer分别代表两个文件名
void generte_topic_answer(int num, int range, const std::string exercises, const std::string answer)
{
    std::vector<std::string> v;
    v = generateExercises(num, range);//生成num多个题目
    std::vector<std::string>v1 = transform(v);//由中缀转化为后缀
    std::vector<double>v2 = get_result(v1);//得到算出的结果
    write_to_text(v, exercises);//写入文件Exercises.txt
    write_result_to_file(v2, answer);//写入文件Answers.txt
}


//封装函数，输入question.txt，answer.txt就直接判断答案是否正确，并把内容输出到Grade.txt中
void judgment_que_ans(const std::string question, const std::string answer)
{
    //首先将两个文件里的内容读取到字符串数组中
    std::vector<std::string>v = get_file_to_string(question);
    std::vector<std::string>v3 = get_file_to_string(answer);

    std::vector<std::string>v1 = transform(v);//由中缀转化为后缀
    std::vector<double>v2 = get_result(v1);//得到算出的结果

    std::vector<double>v4 = string_to_double(v3);//answer.txt的内容，转化为double
    std::vector<int> correct;
    std::vector<int> wrong;
    compareArrays(v2, v4, correct, wrong);
    writeResultToFile(correct, wrong, "Grade.txt");//结果输出到Grade.txt
}

//int main()
//{
//    generte_topic_answer(5, 5, "Exercises.txt", "Answers.txt");
//    judgment_que_ans("question.txt", "answer.txt");
//    return 0;
//}