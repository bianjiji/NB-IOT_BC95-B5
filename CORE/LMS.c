//#include "LMS.h"

///* xn====实际输入信号
// * itr===迭代次数,[M<itr<sizeof(xn)]
// * en====误差序列(itr*1)
// * dn====所期望的响应序列
// * M=====滤波器阶数
// * mu====步长(收敛因子)
// * W=====滤波器权值矩阵，大小为M*itr
// * yn====实际输出序列*/


///*LMS算法过程*/
//float * LMS_Filter(int itr, const float *xn, const float *dn, double mu, int length)
//{
//    static int i = 0;
//    static int k = 0;
//    static float y = 0.0;
//    static float en[F_COUNT];
//    static float W[M][F_COUNT];
//    static float x[M];
//    static float yn[F_COUNT];

//    /*创建一个en全零矩阵,en(k)表示第k次迭代时预期输出与实际输入的误差*/
//    for (i=0; i<itr; i++)
//    {
//        en[i] = 0;
//    }

//    /*创建一个w全零矩阵，没每一行代表一个加权参量 ，每一列代表一次迭代*/
//    for (i=0; i<M; i++)
//        for (k=0; k<itr; k++)
//            W[i][k] = 0;

//    /*创建一个x全零矩阵*/
//    for (i=0; i<M; i++)
//        x[i] = 0;

//    /*迭代计算*/
//    for (k=M; k<=itr; k++)
//    {
//        /* 滤波器M个抽头的输入:从xn第k-1个值倒序取出M个样点的值放入x
//         * y为滤波器输出:W的K-2列与x 的积的和*/
//        for (i=0; i<M; i++)
//        {
//            x[i] = xn[k-i-1];
//            y += W[i][k-2] * x[i];
//        }        

//        en[k-1] = dn[k-1] - y;  //第k次迭代误差

//        /*滤波器权值计算的迭代式*/
//        for (i=0; i<M; i++)
//        {
//            W[i][k-1] = W[i][k-2] + 2*mu*en[k-1]*x[i];
//        }

//        y = 0.0;
//    }

//    /*创建一个yn全无穷大矩阵，位数与xn一样*/
//    for (i=0; i<itr; i++)
//    {
//        yn[i] = 0.0;
//    }

//    /*求最优是滤波器的输出序列*/
//    for (k=M; k<=length; k++)
//    {
//        for (i=0; i<M; i++)
//        {
//            x[i] = xn[k-i-1];
//            y += W[i][itr-1]*x[i];
//        }

//        yn[k-1] = y;
//        y = 0.0;

//    }

//    return yn;
//}
