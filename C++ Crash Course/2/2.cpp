enum class Operation
{
	Add,
	Substract,
	Multiply,
	Devide
};

struct Calculator
{
	Calculator(Operation operation) : op{operation}
	{
	}
	
	int calc(int a, int b)
	{
		switch(op)
		{
        case Operation::Add: 
			return a+b;
        case Operation::Substract:
			return a-b;
		case Operation::Multiply:
			return a*b;
		case Operation::Devide:
			return a/b;
		}
		return 0;
	}
private:
	Operation op;
};

#include <iostream>
int main()
{
	Calculator calculatorAdd{Operation::Add};
	std::cout << calculatorAdd.calc(2,2) << "\n";
    
    Calculator calculatorSub{Operation::Substract};
    std::cout << calculatorAdd.calc(9,1) << "\n";
    
    Calculator calculatorMul{Operation::Substract};
    std::cout << calculatorMul.calc(10,3) << "\n";
    
    Calculator calculatorDev{Operation::Substract};
    std::cout << calculatorDev.calc(5,3) << "\n";
	return 0;
}
