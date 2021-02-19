/*****************************************************************************
* @brief : a implement of union find data struct  并查集数据结构的实现
* @author : acedtang
* @date : 2021/2/19
* @version : ver 1.0
* @inparam : 
* @outparam : 
* 并查集是一种数据结构，主要用于集合的等价类计算，这里提供了一种通用的并查集
* 模板实现，_T表征待导入的和比较的类别，如果_T本身拷贝成本较高，可以考虑输入
* 指针类型，使用方法为现将元素一个一个add到UnionFind对象，之后调用Union函数
* 合并类型，最后调用find查找每个对象所属的类型，返回的类型是个整数值，正确情形下
* >=0，如果返回-1表明是无效值；
*****************************************************************************/
#ifndef __UNIONFIND_H
#define __UNIONFIND_H

#include <unordered_map>

namespace ace
{
    template<class _T>
    class UnionFind
    {
    public:
        UnionFind();
        void add(_T obj);
        int find(_T obj);
        void Union(_T a, _T b);
        //输出不同类别的个数，类别值未必连续
        int typeNum() const;
    protected:
        //输入目标地址，返回其所属的类别
        _T internal_find(_T obj);
        std::unordered_map<_T, _T> _map;
        std::unordered_map<_T, int> _typeMap;
        int _count;
    };

    template<class _T>
    _T ace::UnionFind<_T>::internal_find(_T obj)
    {
        if (obj == _map[obj])
            return obj;
        _map[obj] = internal_find(_map[obj]);
        return _map[obj];
    }

    template<class _T>
    ace::UnionFind<_T>::UnionFind()
        :_count(0)
    {

    }

    template<class _T>
    void ace::UnionFind<_T>::add(_T obj)
    {
        if (_map.find(obj) != _map.end())
            return;

        _map[obj] = obj;
        _typeMap[obj] = _count;
        _count +=1;
    }

    template<class _T>
    int ace::UnionFind<_T>::typeNum() const
    {
        return _count;
    }

    template<class _T>
    void ace::UnionFind<_T>::Union(_T a, _T b)
    {
        if (_map.find(a) == _map.end() || _map.find(b) == _map.end())
            return;
        _T pa = internal_find(a);
        _T pb = internal_find(b);
        if (pa != pb) {
            _map[pb] = pa;
            _count -= 1;
        }
    }

    template<class _T>
    int ace::UnionFind<_T>::find(_T obj)
    {
        if (_map.find(obj) == _map.end())
            return -1;
        _T t = internal_find(obj);
        return _typeMap[t];
    }

}

#endif 