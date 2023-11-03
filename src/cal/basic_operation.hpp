#ifndef BASIC_OPERATION
#define BASIC_OPERATION
#include <exception>
#include <iostream>
#include <vector>
#include "xtensor/xarray.hpp"
#include "xtensor/xio.hpp"
#include "xtensor/xview.hpp"
#include "../node/datatype.h"
#include "../node/node.hpp"


template<typename T>
class __ADD_NODE__ : public __CAL_NODE__<T>{
public:
    void AddPreNode(__DATA_NODE__<T>* pre_node){
        // 算子节点的入度最多等于2，添加多了就超了
        try {
            if (this->pre_node.size() >=2)
                throw "The \" pre_node \" of \"ADD_NODE\" has been overflowed!!"
        }
        catch (const char* s){
            std::cout << s << std::endl;
        }
        this->pre_node = pre_node;
    }

    void Forward() override{
        // 算子节点的入度等于2
        try {
            if (this->pre_node.size() <2)
                throw "The  length of \"ADD_NODE\" need to be 2!"
        }
        catch (const char* s){
            std::cout << s << std::endl;
        }
        // 算子节点的出度不能为空
        try {
            if (this->back_node == nullptr)
                throw "The \" back_node \" of \"ADD_NODE\" is nullptr!!"
        }
        catch (const char* s){
            std::cout << s << std::endl;
        }
        // 执行前向传播
        try {
            this->back_node->data = this->pre_node[0]->data + this->pre_node[1]->data;
            // 记录当前算子节点是否正向传播过
            this->if_forward.clear();
        }
        catch (const std::exception& e){
            std::cout << "__ADD_NODE__Forward:" << e.what() << std::endl;
        }

    }

    void Backward() override{
        this->pre_node[0]->grad += this->back_node->grad;
        this->pre_node[1]->grad += this->back_node->grad;
    }
};

template <typename T>
class __SUB_NODE__ : public __CAL_NODE__<T>
{
public:
    void AddPreNode(__DATA_NODE__<T> *pre_node)
    {
        try
        {
            if (this->pre_node.size() >= 2)
                throw "The \"pre_node\" of \"__SUB_NODE__\" has been overflowed!!";
        }
        catch (const char *s)
        {
            std::cout << s << '\n';
        }

        this->pre_node.push_back(pre_node);
        // this->if_forward.push_back(false);
    }

    void Forward()
    {
        try
        {
            if (this->pre_node.size() < 2)
                throw "The value of length of the \"__SUB_NODE__\" need to be 2,but the actual value of it is not enough!";
        }
        catch (const char *s)
        {
            std::cout << s << '\n';
        }

        try
        {
            if (this->back_node == nullptr)
                throw "The \"baak_node\" of \"__SUB_NODE__\" is nullptr!";
        }
        catch (const char *s)
        {
            std::cout << s << '\n';
        }

        try
        {
            this->back_node->data = this->pre_node[0]->data - this->pre_node[1]->data;

            this->if_forward.clear();
        }
        catch (std::exception &e)
        {
            std::cout << "__SUB_NODE__Forward:" << e.what() << std::endl;
        }
    }

    void Backward()
    {
        this->pre_node[0]->grad += this->back_node->grad;

        this->pre_node[1]->grad += -this->back_node->grad;
    }
};

template <typename T>
class __MUL_NODE__ : public __CAL_NODE__<T>
{
public:
    void AddPreNode(__DATA_NODE__<T> *pre_node)
    {
        try
        {
            if (this->pre_node.size() >= 2)
                throw "The \"pre_node\" of \"__MUL_NODE__\" has been overflowed!!";
        }
        catch (const char *s)
        {
            std::cout << s << '\n';
        }

        this->pre_node.push_back(pre_node);
        // this->if_forward.push_back(false);
    }

    void Forward()
    {
        try
        {
            if (this->pre_node.size() < 2)
                throw "The value of length of the \"__MUL_NODE__\" need to be 2,but the actual value of it is not enough!";
        }
        catch (const char *s)
        {
            std::cout << s << '\n';
        }

        try
        {
            if (this->back_node == nullptr)
                throw "The \"baak_node\" of \"__MUL_NODE__\" is nullptr!";
        }
        catch (const char *s)
        {
            std::cout << s << '\n';
        }

        try
        {
            this->back_node->data = this->pre_node[0]->data * this->pre_node[1]->data;

            this->if_forward.clear();
        }
        catch (std::exception &e)
        {
            std::cout << "__MUL_NODE__Forward:" << e.what() << std::endl;
        }
    }

    void Backward()
    {
        xarray<T> tem = this->pre_node[0]->data;

        this->pre_node[0]->grad += this->pre_node[1]->data * this->back_node->grad;

        this->pre_node[1]->grad += tem * this->back_node->grad;
    }
};

template <typename T>
class __DIV_NODE__ : public __CAL_NODE__<T>
{
public:
    void AddPreNode(__DATA_NODE__<T> *pre_node)
    {
        try
        {
            if (this->pre_node.size() >= 2)
                throw "The \"pre_node\" of \"__DIV_NODE__\" has been overflowed!!";
        }
        catch (const char *s)
        {
            std::cout << s << '\n';
        }

        this->pre_node.push_back(pre_node);
        // this->if_forward.push_back(false);
    }

    void Forward()
    {
        try
        {
            if (this->pre_node.size() < 2)
                throw "The value of length of the \"__DIV_NODE__\" need to be 2,but the actual value of it is not enough!";
        }
        catch (const char *s)
        {
            std::cout << s << '\n';
        }

        try
        {
            if (this->back_node == nullptr)
                throw "The \"baak_node\" of \"__DIV_NODE__\" is nullptr!";
        }
        catch (const char *s)
        {
            std::cout << s << '\n';
        }

        try
        {
            this->back_node->data = this->pre_node[0]->data / this->pre_node[1]->data;

            this->if_forward.clear();
        }
        catch (std::exception &e)
        {
            std::cout << "__DIV_NODE__Forward:" << e.what() << std::endl;
        }
    }

    void Backward()
    {
        /*
            a / b = c
            1/b
            -a/b^2
        */
        xarray<T> tem = this->pre_node[0]->data;
        // data.shape 获取一个和data1 形状相同的全1矩阵
        this->pre_node[0]->grad += (ones<T>(this->pre_node[1]->data.shape()) / this->pre_node[1]->data) * this->back_node->grad;

        this->pre_node[1]->grad += -(tem * ((ones<T>(this->pre_node[1]->data.shape()) / this->pre_node[1]->data) * (ones<T>(this->pre_node[1]->data.shape()) / this->pre_node[1]->data)) * this->back_node->grad);
    }
};

#endif