#pragma once
#include <assert.h>
#include <cmath>
#include <atlstr.h>

class CMathTokenOperator
{
public:
    CMathTokenOperator(const CString& strToken)
        :m_eOperatorType(EMathOperatorType::MOT_LAST)
        ,m_eOperatorAssociativity(EMathOperatorAssociativity::MOA_LEFT)
        ,m_iOperatorPrecedence(-1)
    {
        switch (strToken[0])
        {
        case '(':
            m_eOperatorType = EMathOperatorType::MOT_BRACE_OPEN;
            m_iOperatorPrecedence = 0;
            break;
        case ')':
            m_eOperatorType = EMathOperatorType::MOT_BRACE_CLOSE;
            m_iOperatorPrecedence = 0;
            break;
        case '^':
            m_eOperatorType = EMathOperatorType::MOT_EXPONENT;
            m_iOperatorPrecedence = 3;
            m_eOperatorAssociativity = EMathOperatorAssociativity::MOA_RIGHT;
            break;
        case '*':
            m_eOperatorType = EMathOperatorType::MOT_MULTIPLY;
            m_iOperatorPrecedence = 2;
            break;
        case '/':
            m_eOperatorType = EMathOperatorType::MOT_DIVIDE;
            m_iOperatorPrecedence = 2;
            break;
        case '+':
            m_eOperatorType = EMathOperatorType::MOT_ADD;
            m_iOperatorPrecedence = 1;
            break;
        case '-':
            m_eOperatorType = EMathOperatorType::MOT_SUBTRACT;
            m_iOperatorPrecedence = 1;
            break;
        default:
            assert(false);
            break;
        }
    };

    inline friend bool operator< (const CMathTokenOperator& lhs, const CMathTokenOperator& rhs)
    { 
        if (lhs.m_iOperatorPrecedence == rhs.m_iOperatorPrecedence)
        {
            return rhs.m_eOperatorAssociativity == EMathOperatorAssociativity::MOA_LEFT;
        }
        else
        {
            return lhs.m_iOperatorPrecedence < rhs.m_iOperatorPrecedence;
        }
    }

    template<typename T>
    T ProcessOperator(const T First, const T Second) const
    {
        static_assert(std::is_arithmetic_v<T>, "Operators can only be applied on numerical types");
        static_assert(std::is_signed_v<T>, "Unsigned types are not supported due to the possibility of underflows");
        switch (m_eOperatorType)
        {
        case EMathOperatorType::MOT_EXPONENT:
            return static_cast<T>(std::pow(static_cast<double>(First), static_cast<double>(Second)));
        case EMathOperatorType::MOT_BRACE_OPEN:
        case EMathOperatorType::MOT_BRACE_CLOSE:
            break;
        case EMathOperatorType::MOT_MULTIPLY:
            return First * Second;
        case EMathOperatorType::MOT_DIVIDE:
            if (Second != 0.0)
            {
                return First / Second;
            }
            else
            {
                std::wcout << _T("A divide-by-zero is found, no valid answer is available");
                return T(0);
            }
        case EMathOperatorType::MOT_ADD:
            return First + Second;
        case EMathOperatorType::MOT_SUBTRACT:
            return First - Second;
        default:
            assert(false);
            break;
        }
        return T(0);
    }

    bool IsOpenBrace() const
    {
        return m_eOperatorType == EMathOperatorType::MOT_BRACE_OPEN;
    }

    bool IsCloseBrace() const
    {
        return m_eOperatorType == EMathOperatorType::MOT_BRACE_CLOSE;
    }

    bool IsMinus() const
    {
        return m_eOperatorType == EMathOperatorType::MOT_SUBTRACT;
    }


    CString GetStr() const
    {
        switch (m_eOperatorType)
        {
        case CMathTokenOperator::EMathOperatorType::MOT_EXPONENT:
            return _T("^");
        case CMathTokenOperator::EMathOperatorType::MOT_BRACE_OPEN:
            return _T("(");
        case CMathTokenOperator::EMathOperatorType::MOT_BRACE_CLOSE:
            return _T(")");
        case CMathTokenOperator::EMathOperatorType::MOT_MULTIPLY:
            return _T("*");
        case CMathTokenOperator::EMathOperatorType::MOT_DIVIDE:
            return _T("/");
        case CMathTokenOperator::EMathOperatorType::MOT_ADD:
            return _T("+");
        case CMathTokenOperator::EMathOperatorType::MOT_SUBTRACT:
            return _T("-");
        default:
            assert(false);
            return _T("Undefined Operator");
            break;
        }
    }

private:
    enum class EMathOperatorType
    {
        MOT_EXPONENT,
        MOT_BRACE_OPEN,
        MOT_BRACE_CLOSE,
        MOT_MULTIPLY,
        MOT_DIVIDE,
        MOT_ADD,
        MOT_SUBTRACT,
        MOT_LAST
    };

    enum class EMathOperatorAssociativity
    {
        MOA_LEFT,
        MOA_RIGHT
    };

    EMathOperatorType           m_eOperatorType;
    int                         m_iOperatorPrecedence;
    EMathOperatorAssociativity  m_eOperatorAssociativity;
};

