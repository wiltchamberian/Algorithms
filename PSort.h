/*****************************************************************************
* @brief : ���߳������㷨�����ö��̣߳�ʹ�÷���ͬ���߳�����
* ������,��c++17�Ĳ��������ٶȻ�����ͬһ���������������ٶ��Կ�
* @author : acedtang
* @date : 2021/7/25
* @version : ver 1.0
* @inparam :
* @outparam :
*****************************************************************************/

#ifndef __PSORT_H 
#define __PSORT_H

#include <thread>
#include <future>
#include <algorithm>
#include <cassert>

namespace Sun {
//���������������ʵ����� ����Ҫ������������ʱֱ���ڵ�ǰ�߳�����
#define MINIMUM_FOR_MULTITHREAD 64  //must not be too small!  ֧�ֶ��̵߳���СԪ�ظ���

#define MINIMUM_FOR_ONE_FRAGMENT 2   //�����߳�Ƭ����С����������������õ��߳�)

	inline int find_neareset_higher_which_is_power_of_two(int val) {
		int n = val - 1;
		n = n | (n >> 1);
		n = n | (n >> 2);
		n = n | (n >> 4);
		n = n | (n >> 8);
		n = n | (n >> 16);
		return n + 1;
	}

	//threadNumΪ0������Զ���������ʵ��߳������������ָ�����߳���
	template<class _RandomIt,class _Compare>
	void parralled_sort(_RandomIt begin, _RandomIt end, _Compare compare,unsigned int threadNum = 0) {
		static int numCore = std::thread::hardware_concurrency();	
		int siz = std::distance(begin, end);
		if (threadNum ==1 || numCore <=1||siz< MINIMUM_FOR_MULTITHREAD) {
			std::sort(begin, end, compare);
			return;
		}
		int numThread = numCore;
		if (threadNum > 0) {
			numThread = threadNum;
		}
		else {
			bool ok = !(numCore&(numCore-1));
			if (!ok) {
				numThread = find_neareset_higher_which_is_power_of_two(numCore);
			}
			numThread *= 2;//this cof is a experience 
		}
		
		//��siz����ΪnumThread�����֣��ֱ�����
		int basicFragSiz = siz / numThread;
		if (basicFragSiz < MINIMUM_FOR_ONE_FRAGMENT) {
			std::sort(begin, end, compare); return;
		}
		//���resiude>0,�������ƽ̯��ǰresidue���߳���
		int residue = siz - basicFragSiz * numThread;
		
		//ȷ����ʼ���̴߳���
		//1 ��Ƭ;
		std::vector<std::pair<_RandomIt, _RandomIt>> prs(numThread);
		auto iter = begin;
		for (int i = 0; i < numThread -1 ; ++i) {
			prs[i].first = iter;
			int fragSiz = basicFragSiz + (residue > 0 ? 1 : 0);
			prs[i].second = iter + fragSiz;
			iter += fragSiz;
			residue--;
		}
		prs.back().first = iter;
		prs.back().second = end;

		//2���첽����
		std::vector<std::future<void>> futures(numThread);
		for (int i = 0; i < numThread; ++i) {
			futures[i] = std::async(std::launch::async, std::sort<_RandomIt, _Compare>, prs[i].first, prs[i].second,compare);
		}

		//�ȴ�Ƭ�ν���
		for (int i = 0; i < numThread; ++i) {
			futures[i].get();
		}

		//��ʼ���̹߳鲢
		int k = log2(numThread);
		int d = 2;
		for (int i = 0; i < k; ++i) {
			std::vector<std::future<void>> tmpfutures;
			for (int j = 0; j < numThread; j +=d) {
				auto start = prs[j].first;
				auto end = prs[j + d - 1].second;
				auto mid = prs[j + (d>>1)].first;
				auto fr = std::async(std::launch::async,std::inplace_merge<_RandomIt, _Compare>,start, mid, end, compare);
				tmpfutures.push_back(std::move(fr));
			}
			for (int j = 0; j < numThread / d; ++j) {
				tmpfutures[j].get();
			}
			d = d << 1;
		}
		
		return;
	}



}

#endif