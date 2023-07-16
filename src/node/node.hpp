#ifndef NODE
#define NODE

#include "xtensor/xarray.hpp"
#include "../datatype.h"

using namespace xt;
#define DATA_NODE_FLOAT32 __DATA_NODE__<FLOAT32>
#define CAL_NODE_FLOAT32 __CAL_NODE__<FLOAT32>


// 算子节点
template<typename T>
class __CAL_NODE__;

// 数据节点
template<typename T>
class __DATA_NODE__{
public: // 为了方便调试，将成员都设置成公共的
    __CAL_NODE__<T>* pre_node;
    std::vector<__CAL_NODE__<T>*> back_node;
    xarray<T> data;
    xarray<T> grad;

    // 构造函数
    __DATA_NODE__(){
        this->pre_node = nullptr;
        this->data = DEFAULT_TENSOR_FLOAT32;
        this->grad = DEFAULT_TENSOR_FLOAT32;
    }
    __DATA_NODE__(xarray<T> &data){
        this->pre_node = nullptr;
        this->data = data;
        this->grad = DEFAULT_TENSOR_FLOAT32;
    }

    __DATA_NODE__(const xarray<T> &data){
        this->pre_node = nullptr;
        this->data = data;
        this->grad = DEFAULT_TENSOR_FLOAT32;
    }

    // 添加前向节点
    void SetPreNode(__CAL_NODE__<T>* pre_node){
        this->pre_node = pre_node;
    }
    // 添加后向节点
    void AddBackNode(__CAL_NODE__<T>* back_node){
        this->back_node.push_back(back_node)
    }
    // 设置data
    void SetData(xarray<T>& data){
        this->data = data;
    }

    void SetData(const xarray<T>& data){
        this->data = data;
    }
    // 设置grad
    void SetGrad(xarry<T>& grad){
        this->grad = grad;
    }

    void SetGrad(const xarry<T>& grad){
        this->grad = grad;
    }
    // 前向传播

    // 后(反)向传播

};

template<typename T>
class __CAL_NODE__{
public:
    std::vector<__DATA_NODE__<T>*> pre_node;
    __DATA_NODE__<T>* back_node;

    __CAL_NODE__(){
        this->back_node = nullptr;
    }
    AddPreNode(__DATA_NODE__<T>* pre_node){
        this->pre_node = pre_node;
    }
    SetBackNode(__DATA_NODE__<T>* back_node){
        this->back_node = back_node;
    }
    // 前向传播和返乡传播虚函数 算子
    virtual void Forward() = 0;
    virtual void Backward() = 0;

    virtual void ZeroGrad(){}
    virtual void UpdatePara(T eta){}
};

#endif