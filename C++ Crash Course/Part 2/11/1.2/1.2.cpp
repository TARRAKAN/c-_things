#include <cstdio>
#include <memory>

using FileGuard = std::shared_ptr<FILE>;

void say_hello(FileGuard file)
{
    fprintf(file.get(), "HI THERE");
}

int main()
{
    auto file{fopen("TextFile", "w")};
    if(!file) return errno;
    FileGuard file_guard{file, fclose};
    say_hello(std::move(file_guard));
}
