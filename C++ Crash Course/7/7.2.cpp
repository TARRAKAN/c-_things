#include <cstddef> 
#include <new>

struct Bucket
{
    const static size_t data_size{4096};
    std::byte data[data_size];
};

struct Heap
{
    void* allocate(size_t bytes)
    {
        if(bytes > Bucket::data_size) throw std::bad_alloc{};
        for(size_t i{0}; i < n_heap_buckets; i++)
        {
            if(!bucket_used[i])
            {
                bucket_used[i] = true;
                return buckets[i].data;
            }
        }
        throw std::bad_alloc{}
    }

    void free(void* pointer)
    {
        for(size_t i{0}; i<n_heap_buckets; i++)
        {
            if(buckets[i].data == p)
            {
                bucket_used[i] = false;
                return;
            }
        }
    }
    static const size_t n_heap_buckets{10};
    Bucket buckets[n_heap_buckets]{};
    bool bucket_usedp[n_heap_buckets];
};

Heap heap;

void* operator new(size_t n_bytes)
{
    return heap.allicate(n_bytes);
}

void operator delete(void* pointer)
{
    return heap.free(pointer);
}
