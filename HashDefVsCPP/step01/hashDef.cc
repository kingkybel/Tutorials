#include <iomanip>
#include <iostream>
using namespace std;

struct MultiplicativeType
{
    MultiplicativeType(double v = 0.0) : v_(v)
    {
    }

    /**
     * @brief Global multiplication operator "*"
     *
     * @param lhs left-hand-side object
     * @param rhs right-hand-side object
     * @return MultiplicativeType some value depending the multiplication spec
     */
    friend MultiplicativeType operator*(const MultiplicativeType &lhs, const MultiplicativeType &rhs)
    {
        return (lhs.v_ + 2.0) * (rhs.v_ + 3.0);
    }

    /**
     * @brief Output stream operatoe of this class
     *
     * @param os the output stream
     * @param mt the object to stream
     * @return ostream& the modified output stream
     */
    friend ostream &operator<<(ostream &os, const MultiplicativeType &mt)
    {
        os << mt.v_;
        return os;
    }

    double v_;
};

/// Ill-advised short-cut for squaring a value
#define SQUARE(value) value *value

#define OUT(var)                                                                                                       \
    {                                                                                                                  \
        cout << __LINE__ << " (" << __FUNCTION__ << "): " << #var << "=" << std::fixed << std::setprecision(16) << var \
             << endl;                                                                                                  \
    }

#define PI 3.14159265

#define FUNCTION1(ret_type, name, par_type, parameter)                                                                \
    ret_type name(par_type parameter)                                                                                 \
    {                                                                                                                 \
        cout << "Entering " << #ret_type << " " << #name << "(" << #par_type << " " << #parameter << "(" << parameter \
             << ")"                                                                                                   \
             << ")" << endl;

#define END_FUNCTION1          \
    cout << "exiting" << endl; \
    }

FUNCTION1(void, myFunc, int, i)
int loc_i = 47;
cout << i << "," << loc_i << endl;
END_FUNCTION1

#define COMPLEX_CLASS(value_type)                                                           \
    struct Complex_##value_type                                                             \
    {                                                                                       \
        value_type      real;                                                               \
        value_type      imag;                                                               \
        friend ostream &operator<<(ostream &os, const Complex_##value_type &cplx)           \
        {                                                                                   \
            os << "Complex_" << #value_type << "[" << cplx.real << "," << cplx.imag << "]"; \
            return os;                                                                      \
        }                                                                                   \
    };

COMPLEX_CLASS(double);

COMPLEX_CLASS(int);

COMPLEX_CLASS(MultiplicativeType);

int main()
{
    double  d_pi   = PI;
    float   f_pi   = PI;
    int64_t i64_pi = PI;

    OUT(d_pi);
    OUT(f_pi);
    OUT(i64_pi);

    auto d_pi2   = SQUARE(d_pi);
    auto f_pi2   = SQUARE(f_pi);
    auto i64_pi2 = SQUARE(i64_pi);
    OUT(d_pi2);
    OUT(f_pi2);
    OUT(i64_pi2);

    // Strange behaviour below
    auto d_pi_plus1 = PI + 1.0;
    OUT(SQUARE(d_pi_plus1));
    OUT(SQUARE(d_pi + 1.0));

    MultiplicativeType mt{5.5};
    OUT(mt);
    OUT(SQUARE(mt));

    auto x = SQUARE('a');
    OUT(x);
    OUT(SQUARE(x + 1));
    myFunc(5);

    Complex_double cDbl{2.3, 4.5};
    OUT(cDbl);

    Complex_int cInt{7, 8};
    OUT(cInt);

    Complex_MultiplicativeType cMult{1.23, 4.56};
    OUT(cMult);

    return 0;
}
