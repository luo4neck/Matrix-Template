#include<iostream>
#include<limits>
#include<cmath>

using namespace std;

template <typename Datatype>
bool not_equal(const Datatype& a, const Datatype& b) 
{
    return abs(a-b)>(abs(min(a,b)) * numeric_limits<double>::epsilon()*20.0); 
}

template <typename Datatype>
class Matrix
{
    private:
        Datatype *elem;
        Datatype Zero;
        int nr, nc, count;
        int *axr, *axc;// axr/axc store the row/col index of each non-zero element in the matrix..
    
    public:
        Matrix(Datatype **mat, int n, int c): Zero(0)// constructor of the matrix..
        {   
            if ( (n<1) || (c<1)) 
            {
                cout<<"Cannot construct a matrix of size "<<n<<" * "<<c<<endl;
                exit(1);
            }
            nr = n, nc = c;
            count=0;
            for(int i=0; i<nr; ++i)// this loop detect the size of elem[]..
            {
                for(int j=0; j<nc; ++j)
                {
                    if(mat[i][j] != 0) count++;
                }
            }
//            cout<<"This sparse matrix has "<<count<<" non-zero elements."<<endl;
            elem = new Datatype[count];
            axr = new int[count];
            axc = new int[count];

            count = 0;
            for(int i=0; i<nr; ++i)// this loop give exact value of elem[]..
            {
                for(int j=0; j<nc; ++j)
                {
                    if(mat[i][j] != 0) 
                    {
                        elem[count] = mat[i][j];
                        axr[count] = i;
                        axc[count] = j;
                        count++;
                    }
                }
            }
        }

        Datatype& operator() (int i, int j) // if input i and j exactly fit the element's i and j index, return the element value, else return zero..
        {
        bool check =0;
        int k=0;
            for(k=0; k<ncount(); ++k)
            {
                if( i == axr[k] && j == axc[k] )
                {
                    return elem[k];
                    check = 1;
                    break;
                }
            }
            if(check) return elem[k];
            else return Zero; 
        }

        const Datatype& operator() (int i, int j) const// same as above function.. 
        {
        bool check =0;
        int k=0;
            for(k=0; k<ncount(); ++k)
            {
                if( i == axr[k] && j == axc[k] )
                {
                    return elem[k];
                    check = 1;
                    break;
                }
            }
            if(check) return elem[k];
            else return Zero; 
        }

        int ncount() const {return count;}
        int nrow()  const {return nr;}
        int ncol()  const {return nc;}

        Matrix& operator*= (const double& d)
        {
            for(int i=0; i<ncount(); ++i)  elem[i] = elem[i] * d;
            return *this;
        }
        
        void print()// just print the matrix out..
        {
            int k=0;
            for(int i=0; i<nrow(); ++i)
            {
                for(int j=0; j<ncol(); ++j)
                {
                    if(i==axr[k] && j==axc[k])
                    {
                        cout<<elem[k]<<" ";
                        k++;
                    }
                    else  cout<<Zero<<" ";
                }
                cout<<endl;
            }
            cout<<endl;
        }

        void mult(Matrix& a, const Matrix& b, const Matrix& c)
        {
            if ((b.ncol()!=c.nrow())||(a.nrow()!=b.nrow())||(a.ncol()!=c.ncol()))
            {
                cout<<"Cannot multiply the two matrices"<<endl;
                exit(1);
            }
            for (int i=0; i<a.nrow(); i++) 
            {
                for (int j=0; j<a.ncol(); j++) 
                {
                    a(i,j) = 0.0; 
                    for (int k=0; k<b.ncol(); k++)  a(i,j) += b(i,k)*c(k,j);
                }
            }
        }

        void add(Matrix& a, const Matrix& b, const Matrix& c)
        {
            if ((a.nrow()!=b.nrow())||(a.ncol()!=b.ncol())||(a.nrow()!=c.nrow()))
            {
                cout<<"Cannot add the two matrices"<<endl;
                exit(1);
            }
            for (int i=0; i<a.nrow(); i++) 
            {
                for (int j=0; j<a.ncol(); j++)  a(i,j) = b(i,j) + c(i,j); 
            }
        }

        ~Matrix() // a simple destructor..
        { 
            delete elem;
            delete axr;
            delete axc;
        }
        
        friend ostream& operator<<(ostream& strm, const Matrix<Datatype>& mat)
        {
            strm << mat.nrow() << "  "<< mat.ncol() << endl; 
            for (int i=0 ; i < mat.nrow() ; i++)
            {
                for (int j=0 ; j < mat.ncol() ; j++)
                strm << mat(i,j) << "  ";
                strm << endl;
            }
        }

        friend istream& operator>>(istream& strm, Matrix<Datatype>& mat)
        {
            int nr,nc;
            strm >> nr >> nc; 
            if ((nr!=mat.nrow())||(nc!=mat.ncol()))
            {
                cout<<"Cannot read the matrix"<<endl;
                exit(1);
            }
            for (int i=0; i<mat.nrow(); i++) 
            {
                for (int j=0; j<mat.ncol(); j++)  strm >> mat(i,j);
            }
        }

        friend bool operator != (const Matrix& a, const Matrix& b) 
        {
            bool temp = 0; 
            temp |= ((a.nrow()!=b.nrow())||(a.ncol()!=b.ncol()));

            if (!temp) 
            { 
                for (int i=0; i<a.nrow(); i++)
                {
                    for (int j=0; j<a.ncol(); j++) 
                    {
                        temp |= not_equal(a(i,j), b(i,j));  
                    }
                }
            }
            return temp;
        }
        
        friend bool operator==(const Matrix& a, const Matrix& b) {return (!(a!=b));}
};
