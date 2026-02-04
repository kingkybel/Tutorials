#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct MultiplicativeType
{
    MultiplicativeType(double v = 0.0)
        : v_(v)
    {
    }
    friend MultiplicativeType operator*(const MultiplicativeType &lhs, const MultiplicativeType &rhs)
    {
        return (lhs.v_ + 2.0) * (rhs.v_ + 3.0);
    }

    friend ostream &operator<<(ostream &os, const MultiplicativeType &mt)
    {
        os << mt.v_;
        return os;
    }

    double v_;
};

#define OUT(var)                                                                                                                         \
    {                                                                                                                                    \
        cout << __LINE__ << " (" << __FUNCTION__ << "): " << #var << "=" << std::fixed << std::setprecision(16) << var << "\t " << endl; \
    }

constexpr double PI = 3.14159265;
template <typename ValType_>
ValType_ SQUARE(const ValType_ &value)
{
    return value * value;
}

template <typename ValueType_>
struct Complex
{
    ValueType_ real;
    ValueType_ imag;
    friend ostream &operator<<(ostream &os, const Complex &cplx)
    {
        os << "Complex"
           << "[" << cplx.real << "," << cplx.imag << "]";
        return os;
    }
};

int main()
{
    double d_pi = PI;
    float f_pi = PI;
    int64_t i64_pi = PI;

    OUT(d_pi);
    OUT(f_pi);
    OUT(i64_pi);

    auto d_pi2 = SQUARE(d_pi);
    auto f_pi2 = SQUARE(f_pi);
    auto i64_pi2 = SQUARE(i64_pi);
    OUT(d_pi2);
    OUT(f_pi2); 
    OUT(i64_pi2);

    auto d_pi_plus1 = PI + 1.0;
    OUT(SQUARE(d_pi_plus1));
    OUT(SQUARE(d_pi + 1.0));

    MultiplicativeType mt{5.5};
    OUT(mt);
    OUT(SQUARE(mt));

    Complex<double> cDbl{1.23,4.56};
    OUT(cDbl);

    Complex<int> cInt{7,8};
    OUT(cInt);

    Complex<MultiplicativeType> cMult{1.23, 4.56};
    OUT(cMult);

    return 0;
}