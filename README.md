# adaptive huffman
A C++ implementation.

## Example
```cpp
// consider s as a tcp_stream
stringstream s;
adaptive_huffman::encoder encode(s);
adaptive_huffman::decoder decode(s);
encode << "123" << 456 << endl << "abc" << flush;
int a; string b;
decode >> a >> b;
cout << a << ' ' << b; // 123456 abc
```