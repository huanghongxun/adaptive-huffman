#include "decoder.hpp"
#include <algorithm>

using namespace std;

int main(int argc, char **argv)
{
    adaptive_huffman::decoder decode(cin);
    copy(istreambuf_iterator<char>(decode),
         istreambuf_iterator<char>(),
         ostreambuf_iterator<char>(cout));
    return 0;
}