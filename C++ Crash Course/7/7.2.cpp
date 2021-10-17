#include <cstddef> 
#include <new>
#include <cstdio>

struct Bucket
{
    const static size_t data_size{4096};
    std::byte data[data_size];
};

struct LargeBucket
{
    const static size_t data_size{1048576};
    std::byte data[data_size];
};

struct Heap
{
    void* allocate(size_t bytes)
    {
        if(bytes <= Bucket::data_size)
        {
            for(size_t i{0}; i < n_heap_buckets; i++)
            {
                if(!bucket_used[i])
                {
                    bucket_used[i] = true;
                    return buckets[i].data;
                }
            }
        }
        else if(bytes <= LargeBucket::data_size)
        {
            for(size_t i{0}; i < n_heap_buckets; i++)
            {
                if(!largeBucket_used[i])
                {
                    largeBucket_used[i] = true;
                    return largeBuckets[i].data;
                }
            }
        }
        throw std::bad_alloc{};
        
    }

    void free(void* pointer)
    {
        for(size_t i{0}; i<n_heap_buckets; i++)
        {
            if(buckets[i].data == pointer)
            {
                bucket_used[i] = false;
                return;
            }
            if(largeBuckets[i].data == pointer)
            {
                largeBucket_used[i] = false;
                return;
            }
        }
    }
    static const size_t n_heap_buckets{10};
    Bucket buckets[n_heap_buckets]{};
    bool bucket_used[n_heap_buckets];
    LargeBucket largeBuckets[n_heap_buckets]{};
    bool largeBucket_used[n_heap_buckets];
};

Heap heap;

void* operator new(size_t n_bytes)
{
    return heap.allocate(n_bytes);
}

void operator delete(void* pointer)
{
    return heap.free(pointer);
}


int main()
{
    printf("Buckets: %p\n", heap.buckets);
    auto breakfast = new unsigned int{0xC0FFEE};
    auto dinner = new unsigned int{0xDEADBEEF};
    printf("Breakfast: %p 0x%x\n", breakfast, *breakfast);
    printf("Dinner: %p 0x%x\n", dinner, *dinner);
    delete breakfast;
    delete dinner;
    try
    {
        for(size_t i{1};;i++)
        {
            new char;
            printf("[%ld]Allocated a char\n", i);
            new LargeBucket;
            printf("[%ld]Allocated a large bucket\n", i);
        }
    }
    catch(const std::bad_alloc&)
    {
        printf("std::bad_alloc caught.\n");
    }
}




















