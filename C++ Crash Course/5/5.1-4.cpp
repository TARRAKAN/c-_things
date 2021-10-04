#include <cstdio>

struct Logger
{
    virtual ~Logger() = deafult;
    virtual void log_transfer(long from, long to, double amount) = 0;
}

struct ConsoleLogger : Logger
{
    void log_transfer(long from, long to, double amount) override
    {
        printf("[Console] %ld -> %ld: %f\n", from, to, amount);    
    }
}

struct FileLogger : Logger 
{
    void log_transfer(long from, long to, double amount) override
    {
        printf("[File] %ld,%ld,%f\n", from, to, amount);
    }
}

struct Bank
{
    Bank(Logger *logger) :
        logger{logger}
    {
        
    }
    
        

    void make_transfer(long from, long to, double amount)
    {
        logger.log_transfer(from, to, amount);
    }

private:
    Logger *logger;
}
