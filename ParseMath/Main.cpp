#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <atlstr.h>
#include <tchar.h>

#include "CMathTokenOperator.h"
#include "ShuntingYard.h"



int main(int /*argc*/, char* /*/argv[] */ )
{
    // 0) Simpest equation
    CString strEquation("5 + 8 + 10");
    double dResult = ShuntingYard(strEquation);
    assert(dResult == 23);

    // 1) Simple equation
    strEquation = ("5 + 8 * 10");
    dResult = ShuntingYard(strEquation);
    assert(dResult == 85);

    // 2) Simple equation with and without spaces
    strEquation = ("5+8 *10");
    dResult = ShuntingYard(strEquation);
    assert(dResult == 85);

    // 3) Complexer equation
    strEquation = ("456*9+1385-12.5");
    dResult = ShuntingYard(strEquation);
    assert(dResult == 5476.5);

    // 4) Equation with power
    strEquation = ("5^3+8*7");
    dResult = ShuntingYard(strEquation);
    assert(dResult == 181);

    // 5) Equation with braces
    strEquation = ("(12+5)*8^2");
    dResult = ShuntingYard(strEquation);
    assert(dResult == 1088);

    // 5.2) Equation with double braces
    strEquation = ("(12+5*(3+3))*8^2");
    dResult = ShuntingYard(strEquation);
    assert(dResult == 2688);

    // 6) Equation with braces and missing operator
    strEquation = ("2(12+5)*8^2");
    dResult = ShuntingYard(strEquation);
    assert(dResult == 2176);

    // 7) Equation with negative numbers
    strEquation = ("-8*5+6 *-3");
    dResult = ShuntingYard(strEquation);
    assert(dResult == -58);

    // 8) Equation with negative numbers pt 2
    strEquation = ("-8*5--6*3");
    dResult = ShuntingYard(strEquation);
    assert(dResult == -58);

    // 8) Invalid equations and operators...
    strEquation = ("456&9");
    dResult = ShuntingYard(strEquation);
    // Operator not supported

    strEquation = ("456|9");
    dResult = ShuntingYard(strEquation);
    // Operator not supported

    strEquation = ("456**9");
    dResult = ShuntingYard(strEquation);
    // Double operator, ignored

    strEquation = ("456^(9+5");
    dResult = ShuntingYard(strEquation);
    // Missing closing brace

    return EXIT_SUCCESS; // optional return value
}