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
        printf("[database]Sum geted. id: %ld\n", id);
    }

    void setSum(double sum, long id) override
    {
        printf("[database]Sum seted. Id: %ld. Sum: %f\n", id, sum);
    }
};

struct IAccount
{
    virtual ~IAccount() = default;
    virtual double getSumm() const = 0;
    virtual void addToSumm(double summ) = 0;
    virtual long getId() const = 0;
};

struct CheckingAccount : public IAccount
{   
    CheckingAccount(long id) :
        id{id},
        summ{}
    {
    }

    double getSumm() const override
    {
        return summ;
    }

    void addToSumm(double summ) override
    {
        this->summ += summ;
    }
    
    long getId() const override
    {
        return id;
    }

private:
    const long id;
    double summ;
};

struct SavingsAccount : public IAccount
{
    SavingsAccount(long id) :
        id{id},
        summ{}
    {
    }

    double getSumm() const override
    {
        return this->summ;
    }

    void addToSumm(double summ) override
    {
        this->summ += summ;
    }
    
    long getId() const override
    {
        return this->id;
    }

private:
    const long id;
    double summ;
};

template <typename T>
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

    void make_transfer(T& from, T& to, double amount)
    {
        
        from.addToSumm(-amount);
        to.addToSumm(amount);
        database.getSum(from.getId());
        database.setSum(to.getSumm(), to.getId());
        logger->log_transfer(from.getId(), to.getId(), amount);
    }

private:
    Logger *logger;
    AccountDatabase &database;
};

int main()
{   
    CheckingAccount cA{1};
    SavingsAccount sA{2};
    cA.addToSumm(1000);
    InMemoryAccountDatabase database{};
    FileLogger fLogger{};
    ConsoleLogger cLogger{"Console message"};
    Bank<IAccount> bank(database, &fLogger);

    bank.make_transfer(cA,sA,100);
    bank.setLogger(&cLogger);
    bank.make_transfer(cA, sA, 50.5);
}
