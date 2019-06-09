#include "encoder.hpp"
#include <algorithm>

using namespace std;

int main(int argc, char **argv)
{
    adaptive_huffman::encoder encode(cout);
    copy(istreambuf_iterator<char>(cin),
         istreambuf_iterator<char>(),
         ostreambuf_iterator<char>(encode));
    encode.flush();
    return 0;
}