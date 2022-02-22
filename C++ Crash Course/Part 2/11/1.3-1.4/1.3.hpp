#pragma once
#include <cstdio>
#include <memory>

using FileGuard = std::shared_ptr<FILE>;

class Hal
{
public:
    explicit Hal(FileGuard file);
    virtual ~Hal();
    void write_status();
private:
    FileGuard file;
};
