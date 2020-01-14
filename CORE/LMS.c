//#include "LMS.h"

///* xn====ʵ�������ź�
// * itr===��������,[M<itr<sizeof(xn)]
// * en====�������(itr*1)
// * dn====����������Ӧ����
// * M=====�˲�������
// * mu====����(��������)
// * W=====�˲���Ȩֵ���󣬴�СΪM*itr
// * yn====ʵ���������*/


///*LMS�㷨����*/
//float * LMS_Filter(int itr, const float *xn, const float *dn, double mu, int length)
//{
//    static int i = 0;
//    static int k = 0;
//    static float y = 0.0;
//    static float en[F_COUNT];
//    static float W[M][F_COUNT];
//    static float x[M];
//    static float yn[F_COUNT];

//    /*����һ��enȫ�����,en(k)��ʾ��k�ε���ʱԤ�������ʵ����������*/
//    for (i=0; i<itr; i++)
//    {
//        en[i] = 0;
//    }

//    /*����һ��wȫ�����ûÿһ�д���һ����Ȩ���� ��ÿһ�д���һ�ε���*/
//    for (i=0; i<M; i++)
//        for (k=0; k<itr; k++)
//            W[i][k] = 0;

//    /*����һ��xȫ�����*/
//    for (i=0; i<M; i++)
//        x[i] = 0;

//    /*��������*/
//    for (k=M; k<=itr; k++)
//    {
//        /* �˲���M����ͷ������:��xn��k-1��ֵ����ȡ��M�������ֵ����x
//         * yΪ�˲������:W��K-2����x �Ļ��ĺ�*/
//        for (i=0; i<M; i++)
//        {
//            x[i] = xn[k-i-1];
//            y += W[i][k-2] * x[i];
//        }        

//        en[k-1] = dn[k-1] - y;  //��k�ε������

//        /*�˲���Ȩֵ����ĵ���ʽ*/
//        for (i=0; i<M; i++)
//        {
//            W[i][k-1] = W[i][k-2] + 2*mu*en[k-1]*x[i];
//        }

//        y = 0.0;
//    }

//    /*����һ��ynȫ��������λ����xnһ��*/
//    for (i=0; i<itr; i++)
//    {
//        yn[i] = 0.0;
//    }

//    /*���������˲������������*/
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
