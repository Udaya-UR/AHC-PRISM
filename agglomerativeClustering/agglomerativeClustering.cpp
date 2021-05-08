#include "agglomerativeClustering.h"

agglomerativeClustering::agglomerativeClustering()
{
    //ctor
    cout<<"Object Created"<<endl;
}

double agglomerativeClustering::findDistance(Eigen::VectorXd data1,Eigen::VectorXd data2,string affinity){

    if(affinity == "manhattan"){
    return (data1-data2).array().abs().sum();
    }

    if(affinity == "euclidean"){
    return sqrt((data1-data2).array().square().sum());
    }
    return 1000 ;
}

Eigen::MatrixXd agglomerativeClustering::createArray_dist(Eigen::MatrixXd data){

   for(int i = 0; i < rows-1;i++){
    data1 = data.row(i);
    for (int j = i+1 ; j < rows ; j++){
        data2 = data.row(j);
        distMatrix(i,j) = findDistance(data1,data2,affinity);
    }
   }
   return distMatrix;
}


void agglomerativeClustering::removeRow(Eigen::MatrixXd &matrix, unsigned int rowToRemove)
{
    unsigned int numRows = matrix.rows()-1;
    unsigned int numCols = matrix.cols();
    if( rowToRemove < numRows )
        matrix.block(rowToRemove,0,numRows-rowToRemove,numCols) = matrix.block(rowToRemove+1,0,numRows-rowToRemove,numCols);
    matrix.conservativeResize(numRows,numCols);
}

void agglomerativeClustering::removeColumn(Eigen::MatrixXd &matrix, unsigned int colToRemove)
{
    unsigned int numRows = matrix.rows();
    unsigned int numCols = matrix.cols()-1;
    if( colToRemove < numCols )
        matrix.block(0,colToRemove,numRows,numCols-colToRemove) = matrix.block(0,colToRemove+1,numRows,numCols-colToRemove);
    matrix.conservativeResize(numRows,numCols);
}

Eigen::VectorXd agglomerativeClustering::findmin(Eigen::MatrixXd distMatrix){

  double mini = distMatrix.minCoeff() ;

  int miniIndex,minjindex;

  int flag=0;

  for(int i=0;i<distDim-1;i++){

    if(flag == 1){
        break;
    }

    for(int j=i+1;j<distDim;j++){

        if (distMatrix(i,j) == mini){

            miniIndex = i;
            minjindex = j;
            flag = 1;
            break;
        }
    }
  }

  Eigen::VectorXd a(3);
  a << mini,miniIndex,minjindex;
  return a;
}


void agglomerativeClustering::tracker(int loc1,int loc2){

for (int i=0;i<rows;i++){

    if(trackerMatrix(i,1)== loc2){

        trackerMatrix(i,1)=loc1;
    }
    if(trackerMatrix(i,1)>loc2){

        trackerMatrix(i,1)=trackerMatrix(i,1)-1;
    }
}
}



void agglomerativeClustering::updateDistance(Eigen::MatrixXd &distMatrix,string method){

minVec = findmin(distMatrix);

if (method == "singleLink"){


    for(int i=minVec(2);i<distDim;i++){

    if(distMatrix(minVec(1),i) > distMatrix(minVec(2),i)){

        distMatrix(minVec(1),i) = distMatrix(minVec(2),i);
    }
}
}
else if (method == "completeLink"){


    for(int i=minVec(2);i<distDim;i++){

    if(distMatrix(minVec(1),i) < distMatrix(minVec(2),i)){

        distMatrix(minVec(1),i) = distMatrix(minVec(2),i);
    }

}

}
else if (method == "averageLink"){

    for(int i=minVec(2);i<distDim;i++){

        distMatrix(minVec(1),i) = (distMatrix(minVec(1),i)+distMatrix(minVec(2),i))/2.0;
    }
}

else{

    cout<<"Couldn't find the [method] parameter to proceed"<<endl;
    exit(0);
}


removeColumn(distMatrix,minVec(2));
removeRow(distMatrix,minVec(2));
distDim--;

tracker(minVec(1),minVec(2));

}





Eigen::MatrixXd agglomerativeClustering::fit(Eigen::MatrixXd data_,unsigned int numOfClusters_,string method_,string affinity_){

method = method_;
affinity = affinity_;
numOfClusters = numOfClusters_;
data = data_;
rows=data.rows();
columns=data.cols();
distDim=data.rows();
distMatrix =Eigen::MatrixXd::Constant(rows,rows,10000);
distMatrix = createArray_dist(data);
trackerMatrix = Eigen::MatrixXd(rows,2);

for(int i=0;i<rows;i++){

    trackerMatrix(i,0) = i;
    trackerMatrix(i,1) = i;

}

for (int i = 0 ; i<(rows-numOfClusters) ; i++){

    updateDistance(distMatrix,method);
}



return trackerMatrix;
}

