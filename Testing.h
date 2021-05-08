#ifndef AHC_H
#define AHC_H
#include<string.h>
#include<Dense>
#include<cmath>
#include<vector>
#include<iostream>
extern "C"
class Testing{
public:
//    extern "C" static int Java_com_example_ahc_MainActivity_Testing1(JNIEnv *env, jobject thiz);

    static int Testing1();

    static Eigen::MatrixXd Testing2();

    static Eigen::MatrixXd openData(const char *fileToOpen);
};
#endif