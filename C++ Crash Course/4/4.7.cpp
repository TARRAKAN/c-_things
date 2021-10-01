#include <stdexcept>
#include <cstring>
#include <cstdio>

struct SimpleString
{
    SimpleString(size_t max_size) :
        max_size{max_size},
        length{}
    {
        if(max_size == 0)
        {
            throw std::runtime_error{"Max size must be at least 1."};   
        }
        buffer = new char[max_size];
        buffer[0] = '\0';
    }
    
    SimpleString(const SimpleString& other) :
        max_size{other.max_size},
        buffer{new char[other.max_size]},
        length{other.length},
        std::strcpy(buffer, other.buffer, max_size);
    {
    }    
    
//    SimpleString(const SimpleString&& other)    
    
    SimpleString& operator=(const SimpleString& other)
    {
        if(this == other)
            return *this;
        delete[] buffer;
        buffer = new char[other.max_size];
        length = other.length;
        max_size = other.max_size;
        std::strncpy(buffer, other.buffer, max_size);
        return *this;
    }    

    void print(const char* tag) const
    {
        printf("%s: %s", tag, buffer);
    }
    
    bool append_line(const char* x)
    {
        const auto x_len = strlen(x);
        if(x_len + length + 2 > max_size)
            return false;
        std::strncpy(buffer+length, x, max_size-length);
        length += x_len;
        buffer[length++] = '\n';
        buffer[length] = '\0';
        return true;
    }    

    ~SimpleString()
    {
        delete[] buffer;
    }

private:
    size_t max_size;
    char* buffer;
    size_t length;
};

int main()
{
    SimpleString str{115};
    str.append_line("Starbuck, whaddya hear?");
    str.append_line("Nothin' but the rain.");
    str.print("A");
    str.append_line("Grab your gun and bring the cat in.");
    str.append_line("Aye-aye sir, coming home.");
    str.print("B");
    if(!str.append_line("Galactica!"))
    {
        printf("String was not big enough to append another message.");
    }
    return 0;
}
