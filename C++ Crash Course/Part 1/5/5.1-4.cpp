#include <cstdio>

struct Logger
{
    virtual ~Logger() = default;
    virtual void log_transfer(long from, long to, double amount) = 0;
};

struct ConsoleLogger : Logger
{   
    ConsoleLogger(const char* msg):
        message{msg}
    {
    }

    void log_transfer(long from, long to, double amount) override
    {
        printf("[Console] %ld -> %ld: %f \"%s\"\n", from, to, amount, message);    
    }
private:
    const char* message;
};

struct FileLogger : Logger 
{
    void log_transfer(long from, long to, double amount) override
    {
        printf("[File] %ld,%ld,%f\n", from, to, amount);
    }
};

struct AccountDatabase
{
    virtual ~AccountDatabase() = default;
    virtual void getSum(long id) = 0;
    virtual void setSum(double sum, long id) = 0;
};

struct InMemoryAccountDatabase : public AccountDatabase
{
    void getSum(long id) override
    {
        printf("Sum geted. id: %ld\n", id);
    }

    void setSum(double sum, long id) override
    {
        printf("Sum seted. Id: %ld. Sum: %f\n", id, sum);
    }
};

struct Bank
{
    Bank(AccountDatabase& database, Logger *logger) :
        logger{logger},
        database{database}
    {
    }
    
    void setLogger(Logger *newLogger)
    {
        logger = newLogger;
    }

    void make_transfer(long from, long to, double amount)
    {
        logger->log_transfer(from, to, amount);
    }

private:
    Logger *logger;
    
    AccountDatabase &database;
    
};

int main()
{
    InMemoryAccountDatabase database{};
    FileLogger fLogger{};
    ConsoleLogger cLogger{"Console message"};
    
    Bank bank(database, &fLogger);
    database.setSum(100.5,123);
    database.getSum(321);
    bank.make_transfer(1,2,100);
    bank.setLogger(&cLogger);
    bank.make_transfer(2,1,50.5);

}
