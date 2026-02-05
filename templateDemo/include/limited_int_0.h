#ifndef LIMITED_INT_H_INCLUDED
#define LIMITED_INT_H_INCLUDED

#include <iostream>
#include <limits>
#include <exception>
#include <sstream>

using namespace std;

#define SHOW(expr, comment) {cout << "line("<< __LINE__ << "): " << boolalpha << (#expr)\
                                  << "=" << (expr) << "\t\t" << (comment) << endl; }

void execute()
{
    cout << "Step 0: Basic int32_t (no limited_int template)" << endl;
    cout << endl;

    cout << endl << "assign 270 to int32_t deg360" << endl;
    int32_t deg360 = 270; // ok
    SHOW(deg360, "valid");

    cout << endl << "assign -90 to int32_t deg180" << endl;
    int32_t deg180 = -90; // ok
    SHOW(deg180, "valid");

    cout << endl << "assign 1'234'567 to int32_t rad2Pi" << endl;
    int32_t rad2Pi = 1'234'567; // ok
    SHOW(rad2Pi, "valid");

    cout << endl << "assign 510 to int32_t deg360" << endl;
    deg360 = 510; // we don't want values like that!
    SHOW(deg360, "value >= 360");

    cout << endl << "assign 510 % 360 to int32_t deg360" << endl;
    deg360 = (510 % 360); // [0, 359]
    SHOW(deg360, "valid after modulo");

    cout << endl << "deg180 = deg360(359)" << endl;
    deg360 = 359;
    deg180 = deg360; // > 180!
    SHOW(deg180, "after assignment of 360 value to 180 value");
    deg180 = (deg360 > 179 ? ((deg360 % 360) - 360) : (deg360 % 360));

    SHOW(deg180, "after conversion");
    //...
}


#endif // LIMITED_INT_H_INCLUDED

