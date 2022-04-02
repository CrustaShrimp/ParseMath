#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <atlstr.h>
#include <tchar.h>

#include "CMathTokenOperator.h"
#include "ShuntingYard.h"



int main(int /*argc*/, char* /*/argv[] */ )
{
    CShuntingYard<> Algorithm;
    // 0) Simpest equation
    CString strEquation("5 + 8 + 10");
    double dResult = Algorithm.Compute(strEquation);
    assert(dResult == 23);

    // 1) Simple equation
    strEquation = ("5 + 8 * 10");
    dResult = Algorithm.Compute(strEquation);
    assert(dResult == 85);

    // 2) Simple equation with and without spaces
    strEquation = ("5+8 *10");
    dResult = Algorithm.Compute(strEquation);
    assert(dResult == 85);

    // 3) Complexer equation
    strEquation = ("456*9+1385-12.5");
    dResult = Algorithm.Compute(strEquation);
    assert(dResult == 5476.5);

    // 4) Equation with power
    strEquation = ("5^3+8*7");
    dResult = Algorithm.Compute(strEquation);
    assert(dResult == 181);

    // 4.1) Equation with double power
    strEquation = ("5^3^2");
    dResult = Algorithm.Compute(strEquation);
    assert(dResult == 1953125);

    // 5) Equation with braces
    strEquation = ("(12+5)*8^2");
    dResult = Algorithm.Compute(strEquation);
    assert(dResult == 1088);

    // 5.2) Equation with double braces
    strEquation = ("(12+5*(3+3))*8^2");
    dResult = Algorithm.Compute(strEquation);
    assert(dResult == 2688);

    // 6) Equation with braces and missing operator
    strEquation = ("2(12+5)*8^2");
    dResult = Algorithm.Compute(strEquation);
    assert(dResult == 2176);

    // 7) Equation with negative numbers
    strEquation = ("-8*5+6 *-3");
    dResult = Algorithm.Compute(strEquation);
    assert(dResult == -58);

    // 8) Equation with negative numbers pt 2
    strEquation = ("-8*5--6*-3");
    dResult = Algorithm.Compute(strEquation);
    assert(dResult == -58);

    //// 8) Invalid equations and operators...
    //strEquation = ("456&9");
    //dResult = ShuntingYard(strEquation);
    //// Operator not supported
    //
    //strEquation = ("456|9");
    //dResult = ShuntingYard(strEquation);
    //// Operator not supported

    CShuntingYard<int> AlgorithmInt;
    int iResult = AlgorithmInt.Compute(_T("1 + 2 / 3"));
    assert(iResult == 1);

//     CShuntingYard<unsigned long> AlgorithmUnsigned;
//     unsigned long uiResult = AlgorithmUnsigned.Compute(_T("2 + 1 / 3"));
//     assert(uiResult == 2);

//     uiResult = AlgorithmUnsigned.Compute(_T("2 - 1 / 3"));
//     assert(uiResult == 2);
// 
//     uiResult = AlgorithmUnsigned.Compute(_T("2 + -9"));
//     assert(uiResult == 2);
// 
//     uiResult = AlgorithmUnsigned.Compute(_T("2 - 9 / 3"));
//     assert(uiResult == 2);

    strEquation = ("456**9");
    dResult = Algorithm.Compute(strEquation);
    assert(dResult == 4104);
    // Double operator, ignored

    strEquation = ("456^(9+5");
    dResult = Algorithm.Compute(strEquation);
    // Missing closing brace

    return EXIT_SUCCESS; // optional return value
}