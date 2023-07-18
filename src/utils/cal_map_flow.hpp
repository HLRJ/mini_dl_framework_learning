#ifndef CAL_MAP_FLOW
#define CAL_MAP_FLOW

#include <exception>
#include <iostream>
#include <queue>
#include <vector>
#include "xtensor/xarray.hpp"
#include "xtensor/xio.hpp"
#include "xtensor/xview.hpp"
#include "../node/datatype.h"
#include "../node/node.hpp"

using namespace xt;

template<typename T>
class __CAL_MAP__{
public:
    std::vector<__DATA_NODE__<T>*> begin_node_list;
    std::vector<__DATA_NODE__<T>*> end_node_list;
    std::vector<__DATA_NODE__<T>*> data_node_list;
    std::vector<__DATA_NODE__<T>*> para_node_list;

    __CAL_MAP__(){}

    __CAL_MAP__(__DATA_NODE__<T> *begin_node, __DATA_NODE__<T> *end_node)
    {
        this->begin_node_list.push_back(begin_node);
        this->end_node_list.push_back(end_node);
    }

    __CAL_MAP__(std::vector<__DATA_NODE__<T> *> &begin_node_list, std::vector<__DATA_NODE__<T> *> &end_node_list)
    {
        this->begin_node_list = begin_node_list;
        this->end_node_list = end_node_list;
    }

    void AddBeginNode(__DATA_NODE__<T> *begin_node)
    {
        this->begin_node_list.push_back(begin_node);
    }

    void AddEndNode(__DATA_NODE__<T> *end_node)
    {
        this->end_node_list.push_back(end_node);
    }

    void AddDataNode(__DATA_NODE__<T> *data_node)
    {
        this->data_node_list.push_back(data_node);
    }

    void AddParaNode(__DATA_NODE__<T> *para_node)
    {
        this->para_node_list.push_back(para_node);
    }


    void Forward() {
        try
        {
            if (this->begin_node_list.empty() || this->end_node_list.empty())
                throw "Both the \"begin_node_list\" and \"end_node_list\" of the \"__CAL_MAP__\" can`t be empty!";
        }
        catch (const char *s)
        {
            std::cout << s << std::endl;
        }

        std::queue<__DATA_NODE__<T> *> q_data;
        std::queue<__CAL_NODE__<T> *> q_cal;
        // 将开始节点全部加入到数据节点
        for (auto iter = this->begin_node_list.begin(); iter != this->begin_node_list.end(); iter++)
            q_data.push(*iter);

        while (!q_data.empty() || !q_cal.empty()){
            if (!q_data.empty()){
                // 取出第一个节点
                auto tem_node = q_data.front();
                q_data.pop();
                // 如果节点后面没有节点，进行下一个循环。
                if (tem_node->back_node.size() == 0){
                    continue;
                } else{
                    // 如果数据节点后面有算子节点，就将算子节点的if_forward成员添加该数据节点，表示已经遍历过了
                    for (auto iter = tem_node->back_node.begin(); iter != tem_node->back_node.end(); iter++){
                        (*iter)->if_forward.insert(tem_node);

                        std::set<__DATA_NODE__<T> *> s;
                        // 考虑 x+x 这种算子节点前的两个数据节点是相同的情况
                        for (auto pre_node = (*iter)->pre_node.begin(); pre_node != (*iter)->pre_node.end(); pre_node++)
                            s.insert(*pre_node);
                        // 如果算子节点的遍历过的列表的长度 和 算子节点的数据节点列表的长度相同的话，将算子节点进队
                        if ((*iter)->if_forward.size() == s.size()){
                            q_cal.push(*iter);
                        }
                    }
                }
            } else{
                auto tem_node = q_cal.front();
                q_cal.pop();

                tem_node->Forward();
                q_data.push(tem_node->back_node);
            }
        }
    }
};











#endif