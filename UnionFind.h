/*****************************************************************************
* @brief : a implement of union find data struct  ���鼯���ݽṹ��ʵ��
* @author : acedtang
* @date : 2021/2/19
* @version : ver 1.0
* @inparam : 
* @outparam : 
* ���鼯��һ�����ݽṹ����Ҫ���ڼ��ϵĵȼ�����㣬�����ṩ��һ��ͨ�õĲ��鼯
* ģ��ʵ�֣�_T����������ĺͱȽϵ�������_T�������ɱ��ϸߣ����Կ�������
* ָ�����ͣ�ʹ�÷���Ϊ�ֽ�Ԫ��һ��һ��add��UnionFind����֮�����Union����
* �ϲ����ͣ�������find����ÿ���������������ͣ����ص������Ǹ�����ֵ����ȷ������
* >=0���������-1��������Чֵ��
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
        //�����ͬ���ĸ��������ֵδ������
        int typeNum() const;
    protected:
        //����Ŀ���ַ�����������������
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