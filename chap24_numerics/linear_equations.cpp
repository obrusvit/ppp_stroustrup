#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <random>

#include <cstdint>

#include "Matrix.h"
#include "MatrixIO.h"

using namespace std;

//------------------------------------------------------------------------------

using Matrix = Numeric_lib::Matrix<double, 2>;
using Vector = Numeric_lib::Matrix<double, 1>;
using Index = Numeric_lib::Index;

//------------------------------------------------------------------------------

Vector operator*(const Matrix& A, const Vector& b){
    const Index dim = A.dim1();
    Vector ret(dim);
    for(Index i = 0; i < dim; ++i){
        ret[i] = dot_product(A[i], b);
    }
    return ret;
}

//------------------------------------------------------------------------------

Matrix identity(int n = 2){
    Matrix m(n,n);
    for(int i = 0; i < n; ++i){
        m(i,i) = 1.0;
    }
    return m;
}

Vector ones(int n = 2){
    Vector v(n);
    for(int i = 0; i < n; ++i){
        v(i) = 1.0;
    }
    return v;
}

Matrix random_matrix(int dim){
    Matrix ret(dim, dim);
    std::default_random_engine dre{};
    std::mersenne_twister_engine<uint32_t, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10> mte{};
    std::uniform_real_distribution<double> urd{0,10};
    dre.seed(43);
    mte.seed(42);
    for(int i = 0; i < dim; ++i){
        for(int j = 0; j < dim; ++j){
            /* ret(i,j) = urd(dre); */
            ret(i,j) = urd(mte);
        }
    }
    return ret;
}

Vector random_vector(int dim){
    Vector ret(dim);
    std::default_random_engine dre{};
    std::uniform_real_distribution<double> urd{0,10};
    dre.seed(42);
    for(int i = 0; i < dim; ++i){
        cout << urd(dre) << "\n";
        ret[i] = urd(dre);
    }
    return ret;
}

//------------------------------------------------------------------------------

struct Gauss_elimination_error : public runtime_error {
    using runtime_error::runtime_error;
};

void elimination(Matrix& A, Vector& b){
    const Index n = A.dim1();

    //traverse from 1st columnt to the next to last
    //filling zeros into all elements under the diagonal
    for (Index j = 0; j<n-1; ++j){
        const double pivot = A(j,j);
        if (pivot == 0) 
            throw Gauss_elimination_error{"pivot 0"};
        //fill zeros into each element under the diagonal
        for (Index i = j+1; i<n; ++i){
            const double mult = A(i,j) / pivot;
            A[i].slice(j) = scale_and_add(A[j].slice(j), -mult, A[i].slice(j));
            b(i) -= mult*b(j); //make the corresponding change to b
        }
    }
}

struct Back_substitution_error : public runtime_error{
    using runtime_error::runtime_error;
};

Vector back_substitute(const Matrix& A, const Vector& b){
    const Index n = A.dim1();
    Vector ret{n};

    for(Index i = n-1; i >= 0; --i){
        ret[i] = b[i] - dot_product(A[i].slice(i+1), ret.slice(i+1)) ;
        auto diag_el = A(i,i);
        if(diag_el != 0)
            ret[i] /= diag_el;
        else
            throw Back_substitution_error{"zero on diag"};
    }
    return ret;
}

Vector classical_gauss_elimination(Matrix A, Vector b){
    elimination(A, b);
    return back_substitute(A, b);
}

//------------------------------------------------------------------------------

void test_matrix_working(){
    Matrix m1(3,2);
    m1(0,0) = 1.0;
    m1(1,1) = 1.0;
    cout << m1 << "\n";
    cout << "m1 dim1 (rows): " << m1.dim1() << "\n"; //rows
    cout << "m1 dim2 (cols): " << m1.dim2() << "\n"; //columns

    auto e4 = identity(4);
    cout << e4 << "\n";

}

void test_trivial_system(){
    auto A = identity(3);
    auto b = ones(3);

    auto x = classical_gauss_elimination(A, b);
    cout << "Simplest lin. eq.\n";
    cout << "A*x=";
    cout << x << "\n";
}

void test_random_system(){
    auto A = random_matrix(4);
    auto b = random_vector(4);
    cout << "Solving random system\n";
    cout << "A = " << A << "\n";
    cout << "b = " << b << "\n";

    try {
        auto x_sol = classical_gauss_elimination(A, b);
        auto b_test = A*x_sol;
        cout << "x = " << x_sol << "\n";
        cout << "A*x (should be b) =  " << b << "\n";
    }
    catch (const exception& e){
        cerr << e.what() << "\n";;
    }
}

int main(){
    try {

        /* test_trivial_system(); */
        test_random_system();


        return 0;
    }
    catch(exception& e){
        cerr << e.what() << "\n";
        return 1;
    }
    catch(...){
        cerr << "something went wrong\n";
        return 2;
    }
}

