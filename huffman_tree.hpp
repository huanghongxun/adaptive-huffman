#pragma once
#include <memory>
#include <unordered_map>
#include <set>

namespace adaptive_huffman
{
using namespace std;

/**
 * @brief 自适应哈夫曼树的节点
 */
struct node
{
    int weight = 0;
    int value;
    bool has_value;

    int left = 0, right = 0, parent = 0;

    node();
    node(int value);
};

/**
 * @brief 自适应哈夫曼树
 */
struct tree
{
    node nod[2048];

    /**
     * @brief 哈夫曼树根节点编号
     */
    int root;
    
    /**
     * @brief 最近一个新字符节点
     */
    int end;

    /**
     * @brief 存储字符与节点的对应关系
     */
    unordered_map<int, int> nodes;

    /**
     * @brief 存储
     */
    unordered_map<int, set<int>> weighted;

    /**
     * @brief 初始化哈夫曼树
     */
    tree();

    /**
     * @brief 判断是否存在字符为 byte 的节点
     * @param byte 所求节点表示的字符
     * @return 布尔值表示是否存在字符为 byte 的节点
     */
    bool exists(int byte) const;

    /**
     * @brief 求字符为 byte 的节点编号
     * @param byte 所求节点表示的字符
     * @return 表示字符为 byte 的节点编号
     */
    int get(int byte) const;

    /**
     * @brief 计算该节点的哈夫曼编码
     * @param code 计算的哈夫曼编码结果
     * @param len 计算的哈夫曼编码的二进制位长度
     */
    void huffman_code(int node_id, int &code, int &len);

    void update(int byte);

private:
    void update_node(int node);
};

} // namespace adaptive_huffman