#include <vector>
#include <iostream>

using std::vector;
using std::cout;

int main()
{
    vector<unsigned long> vec;
    cout << "Capacity 1:" << vec.capacity() << '\n';
    vec.reserve(10);
    vec.assign({1,1});
    for(size_t i{2}; i < 20; i++)
        vec.push_back(vec.at(i-2) +  vec.at(i-1));
    cout << "Capacity 2:" << vec.capacity() << '\n';
    for(auto n: vec)
        cout << n << " ";
    cout << '\n';
}
