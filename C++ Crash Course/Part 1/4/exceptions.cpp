#include <stdexcept>
#include <cstdio>

struct Groucho{
	void forget(int x)
	{
		if(x == 0xFACE)
		{
			throw std::runtime_error{"an exception"};
		}
		printf("Forgot 0x%x\n", x);
	}
};

int main()
{
	Groucho groucho{};
	try
	{
		groucho.forget(0xC0DE);
		groucho.forget(0xFACE);
		groucho.forget(0xC0FFEE);
	}
	catch(const std::runtime_error& e)
	{
		printf("Exception caught: %s\n", e.what());
	}
}
