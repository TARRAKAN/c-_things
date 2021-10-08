#include <cstdio>
#include <utility>

template <typename T>
struct SimpleUniquePointer
{
    SimpleUniquePointer() = default;

    SimpleUniquePointer(T* pointer) :
        pointer{pointer}
    {
    }
    
    ~SimpleUniquePointer()
    {
        if(pointer) delete pointer;
    }
    
    SimpleUniquePointer(const SimpleUniquePointer&) = delete;
    SimpleUniquePointer& operator=(const SimpleUniquePointer&) = delete;

    SimpleUniquePointer(SimpleUniquePointer &&other) :
        pointer{other.pointer}
    {
        other.pointer = nullptr;
    }
    
    SimpleUniquePointer& operator=(SimpleUniquePointer &&other) noexcept
    {
        if(pointer) delete pointer;
        pointer = other.pointer;
        other.pointer = nullptr;
        return *this;
    }

    T* get()
    {
        return pointer;
    }

private:
    T* pointer;
};

struct Tracer
{
    Tracer(const char* name):
        str{name}
    {
        printf("Tracer: %s\n", str);
    }
    
    ~Tracer()
    {
        printf("~Tracer: %s\n", str);
    }
private:
    const char* const str;
};

void consumer(SimpleUniquePointer<Tracer> pConsumer)
{
    printf("(cons) ptr: %p\n", pConsumer.get());
}

int main()
{
    auto up = SimpleUniquePointer<Tracer>{ new Tracer{"(1)"}};
    printf("[main] ptr: %p\n", up.get());
    consumer(std::move(up));
    printf("[main] ptr: %p\n", up.get());
    return 0;
}
