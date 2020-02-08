/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-01-16 11:16:01
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/search/search.h
 * @Description: 
 */

namespace AlgoLibR{
namespace search{

template<typename T>
long long searchKernel(T arr[], T target, size_t n, enum SEARCH_METHOD method, bool ascending, bool isExist);

} // namespace search
} // namespace AlgoLibR