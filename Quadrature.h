/*****************************************************************************
* @brief : GaussQuadrature.h
* 高斯求积法实现（数值积分)
* @author : acedtang
* @date : 2021/5/18
* @version : ver 1.0
* @inparam :
* @outparam :
*****************************************************************************/
#ifndef __GAUSS_QUADRATURE_H
#define __GAUSS_QUADRATURE_H

#include <functional>
#include <cassert>

namespace Sun {
    //输入函数
    typedef float (*PFN_Function)(float);
    class GaussQuadrature {
    public:
        //当前只支持n<=5的情形
        //数值计算 [a,b]上f(x)的定积分
        template<class _T>
        static _T quadrature2(std::function<_T(_T)> f,_T a, _T b) {
            assert(a <= b);
            if (a > b) return 0;
            _T res = 0.0;
            _T d = (b - a) * 0.5;
            for (int i = 0; i < 2; ++i) {
                _T x = (roots_2[i] * (b - a) + b + a) * 0.5;
                res += f(x) * d * cofs_2[i];
            }
           
            return res;
        }
        template<class _T>
        static _T quadrature3(std::function<_T(_T)> f, _T a, _T b) {
            assert(a <= b);
            if (a > b) return 0;
            _T res = 0.0;
            _T d = (b - a) * 0.5;
            for (int i = 0; i < 3; ++i) {
                _T x = (roots_3[i] * (b - a) + b + a) * 0.5;
                res += f(x) * d * cofs_3[i];
            }

            return res;
        }
        template<class _T>
        static _T quadrature4(std::function<_T(_T)> f, _T a, _T b) {
            assert(a <= b);
            if (a > b) return 0;
            _T res = 0.0;
            _T d = (b - a) * 0.5;
            for (int i = 0; i < 4; ++i) {
                _T x = (roots_4[i] * (b - a) + b + a) * 0.5;
                res += f(x) * d * cofs_4[i];
            }

            return res;
        }
        template<class _T>
        static _T quadrature5(std::function<_T(_T)> f, _T a, _T b) {
            assert(a <= b);
            if (a > b) return 0;
            _T res = 0.0;
            _T d = (b - a) * 0.5;
            for (int i = 0; i < 5; ++i) {
                _T x = (roots_5[i] * (b - a) + b + a) * 0.5;
                res += f(x) * d * cofs_5[i];
            }

            return res;
        }
        template<class _T>
        static _T quadrature(std::function<_T(_T)> f, _T a, _T b) {
            return quadrature5(f, a, b);
        }
    protected:
        
        static double roots_2[2];
        static double cofs_2[2];
        static double roots_3[3];
        static double cofs_3[3];
        static double roots_4[4];
        static double cofs_4[4];
        static double roots_5[5];
        static double cofs_5[5];
    };
    
}



#endif