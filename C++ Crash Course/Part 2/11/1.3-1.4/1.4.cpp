#include "1.3.hpp"

int main()
{
    auto file{fopen("TextFile", "w")};
    if(!file) return errno;
    FileGuard file_guard{file, fclose};
    auto hal1{Hal(file_guard)};
    auto hal2{Hal(file_guard)};
    auto hal3{Hal(file_guard)};
    hal1.write_status();
    hal2.write_status();
    hal3.write_status();
}
