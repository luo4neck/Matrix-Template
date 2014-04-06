#include<stdlib.h>
#include<iostream>
#include<fstream>
#include"matrix.h"

using namespace std;

int main()
{
    int nr=7, nc=7;
    
    int **Mati1 = new int*[nr];
    int **Mati2 = new int*[nr];
    int **Mati3 = new int*[nr];
    for(int i=0; i<nr; ++i)
    {
        Mati1[i] = new int[nc];
        Mati2[i] = new int[nc];
        Mati3[i] = new int[nc];
    } 
   
    for(int i=0; i<nr; ++i)
    {
        for(int j=0; j<nc; ++j)
        {
            if( i%2==0 || i%3 == 0 || j%2==0 || j%3==0 )
            {
                Mati1[i][j] = 0;
                Mati2[i][j] = 0;
                Mati3[i][j] = 0;
            }
            else 
            {
                Mati1[i][j] = rand()%nc;
                Mati2[i][j] = rand()%nc;
                Mati3[i][j] = rand()%nc;
            }
        }
    }
    
    Matrix <int> mati1(Mati1, nr, nc);
    Matrix <int> mati2(Mati2, nr, nc);
    Matrix <int> mati3(Mati3, nr, nc);
/*
    Matrix <int> mati1(Mati1, nr, nc);
    Matrix <int> mati2(Mati2, nr, nc);
    Matrix <int> mati3(Mati3, nr, nc);
    
    Matrix <bool> mati1(Mati1, nr, nc);
    Matrix <bool> mati2(Mati2, nr, nc);
    Matrix <bool> mati3(Mati3, nr, nc);
*/
    cout<<"mati1 is a "<<mati1.nrow()<<" * "<<mati1.ncol()<<" matrix."<<endl;
    mati1.print();
    cout<<"mati1 *= 4.0"<<endl;
    mati1 = mati1 *= 4.0;
    mati1.print();

    cout<<"mati2 is a "<<mati2.nrow()<<" * "<<mati2.ncol()<<" matrix."<<endl;
    mati2.print();
    cout<<"mati3 is a "<<mati3.nrow()<<" * "<<mati3.ncol()<<" matrix."<<endl;
    mati3.print();
    
    if(mati2 == mati3) cout<<"mati2 == mati3"<<endl<<endl;
    if(mati2 != mati3) cout<<"mati2 != mati3"<<endl<<endl;

    cout<<"mati2 + mati3 = mati1"<<endl<<"New mati1 is:"<<endl;
    mati1.add(mati1, mati2, mati3);
    mati1.print();
    
    cout<<"mati2 * mati3 = mati1"<<endl<<"New mati1 is:"<<endl;
    mati1.mult(mati1, mati2, mati3);
    mati1.print();
   
    cout<<"Write mati1 into a file: mat.dat"<<endl;
    fstream fp("mat.dat", fstream::out);
    fp<<mati1;
    fp.close();
    cout<<"...."<<endl<<endl<<"Writting finished."<<endl<<endl;
  
    cout<<"Read mat.dat into mati2"<<endl;
    fstream fin("mat.dat", fstream::in);
    fin>>mati2;
    fin.close();
    mati2.print();

    for(int i=0; i<nr; ++i)
    {
        delete[] Mati1[i];
        delete[] Mati2[i];
        delete[] Mati3[i];
    }
    delete[] Mati1;
    delete[] Mati2;
    delete[] Mati3;

    return 0;
}
