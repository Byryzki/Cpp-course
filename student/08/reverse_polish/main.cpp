#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <stack>

using namespace std;


bool isInteger(const std::string & s)
{
   if(s.empty() || ((!isdigit(s[0])))){

       return false;
}
   else{
       return true;
   }
}


int calculate(int a, int b, const std::string &operation)
{
    if (operation == "+")
        return a + b;
    if (operation == "-")
        return a - b;
    if (operation == "*")
        return a * b;
    if (operation == "/"){
        if(b == 0){
            cout << "Error: Division by zero" << endl;
            return EXIT_FAILURE;
        }
        else{

        return a / b;
        }
    }
    return -1;
}

bool isOperation(const std::string& op)
{
   if(op == "+" || op == "-" || op == "*" || op == "/"){
       return true;
   }
   else{
       return false;
   }
}

int RPN(std::vector<std::string> &notation) {

    std::stack<int> numbers;
    for (const auto& str : notation)
    {
        if (isOperation(str))
        {
            if(numbers.size() > 1){
            int n2 = numbers.top(); numbers.pop();
            int n1 = numbers.top(); numbers.pop();
            int result = calculate(n1, n2, str);
            if(result == EXIT_FAILURE){
                return EXIT_FAILURE;
            }
            else{
                numbers.push(result);
            }
        }
            else{
                cout << "Error: Too few operands" << endl;
                return EXIT_FAILURE;
            }

        }

        else if(isInteger(str) == true){
            numbers.push(std::stoi(str));
    }
        else{
            cout << "Error: Unknown character" << endl;
            return EXIT_FAILURE;
        }
        }
    if(numbers.size() > 1){
        cout << "Error: Too few operators" << endl;
        return EXIT_FAILURE;
    }

    return numbers.top();
}


std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }

    return result;
}

int main()
{
    cout << "Input an expression in reverse Polish notation (end with #):" << endl;
    std::string rivi;
    std::vector<std::string> input_palasina;

    std::cout << "EXPR> ";
    getline(cin, rivi);
    input_palasina = split(rivi, ' ', true);

    input_palasina.pop_back();

    if(isInteger(input_palasina.at(0)) == false){
        cout << "Error: Expression must start with a number" << endl;
        return EXIT_FAILURE;
    }
    else{

    if(RPN(input_palasina) == EXIT_FAILURE){
        return EXIT_FAILURE;
    }
    else{
    cout << "Correct: " << RPN(input_palasina) << " is the result" << endl;
}
}


}
