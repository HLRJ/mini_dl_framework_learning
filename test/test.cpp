//
// Created by zhenxiang on 23-7-16.
//
#include <iostream>
#include "../extern/xtensor/include/xtensor/xarray.hpp"
#include "../extern/xtensor/include/xtensor/xio.hpp"

using namespace xt;

int main(){
    auto a = xarray<float>({1,2,3});
    std::cout << a << std::endl;
}