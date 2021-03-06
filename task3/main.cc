#include<stdlib.h>
#include<iostream>
#include"matrix.h"

using namespace std;

int main()
{
    Matrix <double> matd(3,3);
    Matrix <int> mati0(3,3);
    Matrix <int> mati1(3,3);
    Matrix <bool> matb(3,3);
   
    for(int i=0; i<3; ++i)
    {
        for(int j=0; j<3; ++j)
        {
            matd(i, j) = i+0.3;
            mati0(i, j) = i+0.3;
            mati1(i, j) = i+0.3;
            matb(i, j) = i+0.3;
        }
    }
    
    cout<<"matd is a "<<matd.nrow()<<" * "<<matd.ncol()<<" matrix."<<endl;
    matd.print();
    cout<<"matd *= 3.5"<<endl;
    matd = matd *= 3.5;
    cout<<"Trace of the matrix is: "<<matd.ntrace()<<endl;
    cout<<"Det of the matrix is: "<<matd.ndet()<<endl;
    matd.print();
    
    cout<<"mati0 is a "<<mati0.nrow()<<" * "<<mati0.ncol()<<" matrix."<<endl;
    cout<<"Trace of the matrix is: "<<mati0.ntrace()<<endl;
    cout<<"Det of the matrix is: "<<mati0.ndet()<<endl;
    mati0.print();
    
    cout<<"mati1 is a "<<mati1.nrow()<<" * "<<mati1.ncol()<<" matrix."<<endl;
    cout<<"Trace of the matrix is: "<<mati1.ntrace()<<endl;
    cout<<"Det of the matrix is: "<<mati1.ndet()<<endl;
    mati1.print();
    
    cout<<"matb is a "<<matb.nrow()<<" * "<<matb.ncol()<<" matrix."<<endl;
    cout<<"Trace of the matrix is: "<<matb.ntrace()<<endl;
    cout<<"Det of the matrix is: "<<matb.ndet()<<endl;
    matb.print();
    
    if(mati0 == mati1) cout<<"mati0 == mati1"<<endl<<endl;
    if(mati0 != mati1) cout<<"mati0 != mati1"<<endl<<endl;

    return 0;
}
