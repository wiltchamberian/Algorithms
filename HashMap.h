/*****************************************************************************
* @brief : 一个简单而强大的hashmap实现
* @author : acedtang
* @date : 2021/2/19
* @version : ver 1.0
* @inparam : 
* @outparam : 
*****************************************************************************/
#ifndef __HASHMAP_H
#define __HASHMAP_H

#include <vector>
#include <functional>
#include <string>
#include "GeneralHashFunctions.h"

namespace ace
{
    template<class _Key,class _Value>
    class HashNode
    {
    public:
        HashNode(const _Key& key, const _Value& value)
            :_key(key)
            ,_value(value)
            ,_next(nullptr)
        {
        }
        _Key _key;
        _Value _value;
        HashNode<_Key,_Value>* _next;
    };

    template<class _Key>
    int myhash(const _Key& key)
    {
        static_assert(false, "use invalid hash function!");
    }
    template<>
    int myhash(const std::string& key) {
        return BKDRHash(key);
    }
    template<>
    int myhash(const int& key)
    {
        return key;
    }

    template<class _Key, class _Value>
    class HashMap
    {
    public:
        HashMap(std::function<unsigned int(const _Key&)> hash = myhash<_Key>);
        void insert(const _Key& key,const _Value& value);

        _Value& operator[] (const _Key& key);

    protected:
        //扩容
        void expansion();
        std::vector<HashNode<_Key,_Value>*> _vec;
        int _count = 0;
        std::function<unsigned int (const _Key&)> _hash;
    };

    template<class _Key, class _Value>
    void ace::HashMap<_Key, _Value>::expansion()
    {
        std::vector<HashNode<_Key, _Value>*> new_vec;
        int siz = _vec.size() * 2;
        new_vec.resize(siz, nullptr);
        for (int i = 0; i < _vec.size(); ++i) {
            HashNode<_Key, _Value>* rover = _vec[i];
            while (rover != nullptr) {
                HashNode<_Key, _Value>* nex = rover->_next;
                unsigned int index = _hash(rover->_key)& (siz-1);
                if (new_vec[index] == nullptr) {
                    new_vec[index] = rover;
                    new_vec[index]->_next = nullptr;
                }
                else {
                    rover->_next = new_vec[index];
                    new_vec[index] = rover;
                }
                rover = nex;
            }
        }
        std::swap(_vec, new_vec);
    }

    template<class _Key, class _Value>
    ace::HashMap<_Key, _Value>::HashMap(std::function<unsigned int(const _Key&)> hash_)
    {
        _hash = hash_;
        _vec.resize(16);
    }

    template<class _Key, class _Value>
    _Value& ace::HashMap<_Key, _Value>::operator[] (const _Key& key)
    {
        unsigned int index = _hash(key)&(_vec.size()-1);
        ace::HashNode<_Key, _Value>* node = _vec[index];
        while (node != nullptr) {
            if (node->_key == key) {
                return node->_value;
            }
            node = node->_next;
        }
        _Value val;
        insert(key, val);
        return operator[](key);
    }

    template<class _Key, class _Value>
    void ace::HashMap<_Key, _Value>::insert(const _Key& key, const _Value& value)
    {
        unsigned int index = _hash(key)&(_vec.size()-1);
        if (_vec[index] == nullptr) {
            _vec[index] = new ace::HashNode<_Key, _Value>(key, value);
            _count++;
        }
        else {
            if ((float)(_count + 1) / _vec.size() <= 0.75 /*expansion coffcient*/) {
                ace::HashNode<_Key, _Value>* node = new ace::HashNode<_Key, _Value>(key, value);
                node->_next = _vec[index];
                _vec[index] = node;
                _count++;
            }
            else {
                expansion();
                insert(key, value);      
            }
            
        }
    }

}



#endif