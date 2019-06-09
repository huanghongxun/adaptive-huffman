#include "huffman_tree.hpp"

#define _par(x) nod[x].parent
#define _l(x) nod[x].left
#define _r(x) nod[x].right
#define _w(x) nod[x].weight
#define _val(x) nod[x].value
#define _hasval(x) nod[x].has_value

namespace adaptive_huffman
{
using namespace std;

node::node() : has_value(false) {}

node::node(int value) : value(value), has_value(true) {}

void tree::huffman_code(int node, int &code, int &len)
{
    if (!node || node == root)
        return;
    if (_l(_par(node)) == node)
        code += 1 << len;
    ++len;
    huffman_code(_par(node), code, len);
}

tree::tree()
{
    root = end = 2047;
    weighted[0].insert(root);
}

bool tree::exists(int byte) const
{
    return nodes.count(byte);
}

int tree::get(int byte) const
{
    return nodes.at(byte);
}

void tree::update(int byte)
{
    if (exists(byte))
    {
        int node = nodes[byte];
        update_node(node);
    }
    else
    {
        int n1 = end - 1;
        nod[n1] = node(byte);
        _par(n1) = end;
        _l(end) = n1;
        weighted[0].insert(n1);

        int n2 = end - 2;
        nod[n2] = node();
        _par(n2) = end;
        _r(end) = n2;
        weighted[0].insert(n2);

        update_node(n1);
        nodes[byte] = n1;

        end = n2;
    }
}

void tree::update_node(int node)
{
    while (true)
    {
        int weight = nod[node].weight;
        int to = *weighted[weight].rbegin();
        if (to != node && _par(node) != to)
        {
            swap(nod[node], nod[to]);
            swap(nod[node].parent, nod[to].parent);
#define update_child(par, cld) do{if(nod[par].cld)nod[nod[par].cld].parent=par;}while(0)
#define update_children(par) update_child(par, left); update_child(par, right)
            update_children(node);
            update_children(to);
            if (_hasval(node)) nodes[_val(node)] = node;
            if (_hasval(to)) nodes[_val(to)] = to;
            node = to;
        }

        weighted[weight].erase(node);
        if (weighted[weight].empty())
            weighted.erase(weight);
        ++weight;
        ++_w(node);
        weighted[weight].insert(node);
        if (node == root) return;
        node = _par(node);
    }
}

} // namespace adaptive_huffman