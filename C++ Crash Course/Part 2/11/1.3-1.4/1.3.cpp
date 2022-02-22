#include <cstdio>
#include <memory>
#include "1.3.hpp"

using FileGuard = std::shared_ptr<FILE>;

Hal::Hal(FileGuard file):
    file{file}
{
        
}
    
Hal::~Hal()
{
    fprintf(file.get(), "Stop Dave\n");
}
    
void Hal::write_status()
{
    fprintf(file.get(), "I'm completely operational\n");
}
