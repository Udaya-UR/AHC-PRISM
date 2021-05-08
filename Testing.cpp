#include<jni.h>
#include <iostream>
//#include "agglomerativeClustering.h"
#include <Dense>
#include<cmath>
#include<vector>
#include<iostream>
#include<fstream>
#include <android/log.h>

using namespace std;
using namespace Eigen;
using Eigen::MatrixXd;
#include "Testing.h"

//extern "C" JNIEXPORT jint JNICALL
//static Testing::Java_com_example_ahc_MainActivity_Testing1(
//        JNIEnv* env,
//        jobject /* this */) {
//    return 10;
//}

int Testing::Testing1() {
    //int test= Testing::Testing2();
    MatrixXd data(200,200);
   data =Testing::openData("sample.csv");
   // data = Testing::Testing2();
   int s=data(0,0);
   string Str="raja";
    __android_log_print(ANDROID_LOG_ERROR, "TRACKERS", "%s", Str.c_str());
    return 6;


}

Eigen::MatrixXd Testing::Testing2() {
    MatrixXd check(2,2);
    check(0,0)=9;
    check(1,1)=3;
    check(0,1)=4;
    check(1,0)=7;
    return check;
}

Eigen::MatrixXd Testing::openData(const char *fileToOpen)
{

    // later on, this vector is mapped into the Eigen matrix format
    vector<double> matrixEntries;

    // in this object we store the data from the matrix
    ifstream matrixDataFile(reinterpret_cast<const char *>(fileToOpen));

    // this variable is used to store the row of the matrix that contains commas
    string matrixRowString;

    // this variable is used to store the matrix entry;
    string matrixEntry;

    // this variable is used to track the number of rows
    int matrixRowNumber = 0;


    while (getline(matrixDataFile, matrixRowString)) // here we read a row by row of matrixDataFile and store every line into the string variable matrixRowString
    {
        stringstream matrixRowStringStream(matrixRowString); //convert matrixRowString that is a string to a stream variable.

        while (getline(matrixRowStringStream, matrixEntry, ',')) // here we read pieces of the stream matrixRowStringStream until every comma, and store the resulting character into the matrixEntry
        {
            matrixEntries.push_back(stod(matrixEntry));   //here we convert the string to double and fill in the row vector storing all the matrix entries
        }
        matrixRowNumber++; //update the column numbers
    }

    return Eigen::Map<Matrix<double, Dynamic, Dynamic, RowMajor>>(matrixEntries.data(), matrixRowNumber, matrixEntries.size() / matrixRowNumber);

}
