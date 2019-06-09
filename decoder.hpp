#pragma once
#include "huffman_tree.hpp"
#include <iostream>

namespace adaptive_huffman
{
using namespace std;

/**
 * @brief 自适应哈夫曼编码解码流
 */
struct decoder : public istream, public streambuf
{
    decoder(istream &is);

protected:
    virtual streambuf::int_type underflow() override;

private:
    bool first_to_read = true; // 是否第一次解析输入数据
    int cur_bits = 0; // 从输入流内解析过的位数
    char cur_ch; // 当前从输入流读取的上一个字符
    char buf; // 缓冲区，为了方便，这里缓冲区只有一个字节
    adaptive_huffman::tree tree; // 哈夫曼树
    istream &is; // 输入流

    /**
     * @brief 不断读入的压缩后数据指到找到对应节点
     * @return 0 若输入流结束；否则为对应节点
     */
    int read_node();

    /**
     * @brief 根据指定读入长度读入相应的二进制位
     * @param len 读入二进制位数，比如 8 为读入一个字节
     * @return 如果成功解码，返回解码后的一个字节
     */
    int read(int len);
};
} // namespace adaptive_huffman