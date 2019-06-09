#include "encoder.hpp"

namespace adaptive_huffman
{
using namespace std;

encoder::encoder(ostream &os)
    : ostream(this), os(os), tree()
{
}

streambuf::int_type encoder::overflow(streambuf::int_type c)
{
    if (tree.exists(c))
    {
        write_node(tree.get(c));
    }
    else
    {
        write_node(tree.end);
        write(c, 9);
    }
    tree.update(c);

    return streambuf::traits_type::not_eof(c);
}

streambuf::int_type encoder::sync()
{
    flushed = false;
    while (!flushed)
        overflow(256);
    return 0;
}

void encoder::write_node(int node)
{
    int code = 0, len = 0;
    tree.huffman_code(node, code, len);
    write(code, len);
}

void encoder::write(int code, int len)
{
    for (int i = len - 1; i >= 0; --i)
    {
        character = character * 2 + (code >> i & 1);
        step = (step + 1) % 8;
        if (!step)
        {
            char buf[] = {(char)character};
            os.write(buf, sizeof(buf));
            character = 0;
            flushed = true;
        }
    }
}

} // namespace adaptive_huffman