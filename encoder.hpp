#pragma once
#include "huffman_tree.hpp"
#include <iostream>

namespace adaptive_huffman
{
using namespace std;

/**
 * @brief 自适应哈夫曼编码编码流
 */
struct encoder : public ostream, public streambuf
{

    encoder(ostream &os);

protected:
    virtual streambuf::int_type overflow(streambuf::int_type c  = streambuf::traits_type::eof()) override;
    virtual streambuf::int_type sync() override;

private:
    int character = 0; // 当前从输出流读取的上一个字符
    int step = 0; // 根据输出流导出的哈夫曼编码位数
    bool flushed;
    ostream &os; // 输出流
    adaptive_huffman::tree tree; // 哈夫曼树

    /**
     * @brief 将节点所表示的哈夫曼编码写入到输出流中
     * @param node 要写入其哈夫曼编码的节点
     */
    void write_node(int node);

    /**
     * @brief 将二进制数据写入到输出流中
     * @param code 二进制数据
     * @param len 二进制数据位数
     */
    void write(int code, int len);
};

} // namespace adaptive_huffman