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
        int nr, nc;

    public:
        Matrix(int n, int c)// constructor of the matrix..
        {   
            if ( (n<1) || (c<1)) 
            {
                cout<<"Cannot construct a matrix of size "<<n<<" * "<<c<<endl;
                exit(1);
            }
            nr = n, nc = c;
            elem = new Datatype[n*c];
            for(int i=0; i<(n*c); ++i)  elem[i] = 0;
        }

        Datatype& operator() (int i, int j) { return elem[i*nc + j]; }
        const Datatype& operator() (int i, int j) const { return elem[i*nc + j]; }

        int nrow() const {return nr;}
        int ncol() const {return nc;}

        Matrix& operator*= (const double& d)
        {
            for(int i=0; i<(nr*nc); ++i)  elem[i] = elem[i] * d;
            return *this;
        }
        
        void print()
        {
            for(int i=0; i<nrow(); ++i)
            {
                for(int j=0; j<ncol(); ++j)
                {
                    cout<<elem[i*nc + j]<<" ";
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


        ~Matrix() { delete elem;}// a simple destructor..
        
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
