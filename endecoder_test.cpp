#include "encoder.hpp"
#include "decoder.hpp"
#include <algorithm>
#include <sstream>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    // consider s as a tcp_stream
    stringstream s;
    adaptive_huffman::encoder encode(s);
    adaptive_huffman::decoder decode(s);
    encode << "123" << 456 << endl << "abc" << flush;
    int a; string b;
    decode >> a >> b;
    cout << a << ' ' << b; // 123456 abc
    return 0;
}