#include "decoder.hpp"

namespace adaptive_huffman
{
using namespace std;

decoder::decoder(istream &is)
    : istream(this), is(is)
{
    setg(&buf, &buf + 1, &buf + 1);
}

streambuf::int_type decoder::underflow()
{
    int node;
    if (first_to_read)
    {
        node = tree.end;
        first_to_read = false;
    }
    else
    {
        node = read_node();
    }

    if (!is)
        return streambuf::traits_type::eof();

    int val;

    if (node == tree.end)
        val = read(9);
    else
        val = tree.nod[node].value;

    if (!is)
        return streambuf::traits_type::eof();
    tree.update(val);

    if (val != 256)
    {
        buf = val;
        setg(&buf, &buf, &buf + 1);
        return streambuf::traits_type::to_int_type(buf);
    }
    else
    {
        return underflow();
    }
}

int decoder::read_node()
{
    int res = 0;
    int node = tree.root;
    while (true)
    {
        if (!cur_bits)
            is.read(&cur_ch, sizeof(cur_ch));
        if (!is)
            return 0;
        if ((cur_ch >> (7 - cur_bits)) & 1)
        {
            node = tree.nod[node].left;
            res = res << 1 | 1;
        }
        else
        {
            node = tree.nod[node].right;
            res = res << 1;
        }
        cur_bits = (cur_bits + 1) % 8;
        if (!tree.nod[node].left && !tree.nod[node].right)
            return node;
    }
    return 0;
}

int decoder::read(int len)
{
    int ch = 0;
    for (int i = 0; i < len; ++i)
    {
        if (!cur_bits)
            is.read(&cur_ch, sizeof(cur_ch));
        if (!is)
            return EOF;
        ch = ch * 2 + (cur_ch >> (7 - cur_bits) & 1);
        cur_bits = (cur_bits + 1) % 8;
    }

    return ch;
}

} // namespace adaptive_huffman