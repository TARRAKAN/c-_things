#include <ctime>
#include <cstdio>

struct TimerClass
{
	explicit TimerClass(const char* name) :
        timestamp{std::time(NULL)},
        timerName{name}
	{
    }
	
	TimerClass(const TimerClass &other) : 
		timestamp{other.timestamp}
	{
    }
	
	TimerClass& operator=(const TimerClass &other)
	{
		if(this == &other) return *this;
		timestamp = other.timestamp;
		return *this;
	}
    
    TimerClass(TimerClass&& other) noexcept :
        timestamp{other.timestamp}
    {
        other.timestamp = 0;
    }

	virtual ~TimerClass()
	{
		std::time_t temp{time(NULL)};
		printf("Timer \"%s\": %ld\n",timerName, temp - timestamp);
	}

	std::time_t getTime()
	{
		return timestamp;
	}

private:
	std::time_t timestamp;
	const char* timerName;
};

int main()
{
	TimerClass *tmr{new TimerClass{"1"}};
    while(std::clock() < CLOCKS_PER_SEC * 5)
    {
    }
	delete tmr;
}
