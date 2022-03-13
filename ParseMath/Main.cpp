#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <deque>
#include <atlstr.h>
#include <tchar.h>

#include "IMathToken.h"
#include "CMathTokenValue.h"
#include "CMathTokenOperator.h"
#include "ShuntingYard.h"



int main(int /*argc*/, char* /*/argv[] */ )
{
    std::cout << "Welcome, please enter your space separated math equation below:\n";
    const CString strEquation("5 + 8 * 10");

    std::deque<IMathToken*> dq = ShuntingYard(strEquation);

    dq;
    /*std::deque<IMathToken*> LineOfMath;

    CMathTokenValue     FirstValue (8);
    CMathTokenValue     SecondValue(10);
    CMathTokenOperator  Operator   (CMathTokenOperator::EMathOperatorType::MOT_MULTIPLY);
    LineOfMath.push_back(&FirstValue);
    LineOfMath.push_back(&SecondValue);
    LineOfMath.push_back(&Operator);

    auto itOperator = std::find_if(LineOfMath.begin(), LineOfMath.end(), [](const IMathToken* pToken)
        {
            return pToken->IsOperator();
        });

    if (itOperator != LineOfMath.end())
    {
        // TODO Check availability of (itOperator-1) and (itOperator - 2)

        const CMathTokenOperator* const pMathOperator = dynamic_cast<CMathTokenOperator*>(*itOperator    );
              CMathTokenValue* const    pFirstValue   = dynamic_cast<CMathTokenValue*>   (*(itOperator-2));
        const CMathTokenValue* const    pSecondValue  = dynamic_cast<CMathTokenValue*>   (*(itOperator-1));
        if (pMathOperator && pFirstValue && pSecondValue)
        {
            const double dResult = pMathOperator->ProcessOperator(pFirstValue->GetValue(), pSecondValue->GetValue());
            pFirstValue->SetValue(dResult);
            auto itSecondValue = (itOperator - 1);
            LineOfMath.erase(itSecondValue);
            LineOfMath.erase(itOperator);
            std::cout << "The computed value is: " << pFirstValue->GetValue();
        }
    }*/


    return EXIT_SUCCESS; // optional return value
}