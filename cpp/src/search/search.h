/*
 * @Author: raoqiyu@mail.com
 * @Date: 2020-01-16 11:16:01
 * @FilePath: /AlgoLibR/cpp/src/search/search.h
 * @Description: 
 */

namespace SEARCH{

    template<typename T>
    long long searchKernel(T arr[], T target, size_t n, enum SEARCH_METHOD method, bool ascending, bool isExist);

}