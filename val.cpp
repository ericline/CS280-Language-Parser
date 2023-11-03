/* Overloaded Methods for Parser */

#include <string>
#include <cmath>
#include <string>
#include <sstream>
#include "val.h"

using namespace std;

Value Value::operator+(const Value& op) const
{
    double oper1, oper2;
    if(IsString() && op.IsReal())
    {
        try 
        {
            oper1 = stod(GetString()); 
        }
        catch(invalid_argument& arg)
        {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        return Value(oper1 + op.GetReal());
    }
    else if(IsReal() && op.IsString())
    {
        try
        {
            oper1 = stod(op.GetString()); 
        }
        catch(invalid_argument& arg)
        {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }

        return Value(GetReal() + oper1);
    }
    else if(IsString() && op.IsString())
    {
        try
        {
            oper1 = stod(GetString());
            oper2 = stod(op.GetString()); 
        }
        catch(invalid_argument& arg)
        {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }

        return Value(oper1 + oper2);
    }
    else if(IsInt() && op.IsReal())
    {
        return Value(op.GetInt() + op.GetReal());
    }
    else if(IsReal() && op.IsInt())
    {
        return Value(GetReal() + op.GetInt());
    }
    else if(IsReal() && op.IsReal())
    {
        return Value(GetReal() + op.GetReal());
    }
    
    return Value();
}

Value Value::operator-(const Value& op) const
{
    double oper1, oper2;
    if(IsString() && op.IsReal())
    {
        try 
        {
            oper1 = stod(GetString()); 
        }
        catch(invalid_argument& arg)
        {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        return Value(oper1 - op.GetReal());
    }
    else if(IsReal() && op.IsString())
    {
        try
        {
            oper1 = stod(op.GetString()); 
        }
        catch(invalid_argument& arg)
        {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }

        return Value(GetReal() - oper1);
    }
    else if(IsString() && op.IsString())
    {
        try
        {
            oper1 = stod(GetString());
            oper2 = stod(op.GetString()); 
        }
        catch(invalid_argument& arg)
        {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }

        return Value(oper1 - oper2);
    }
    else if(IsInt() && op.IsReal())
    {
        return Value(GetInt() - op.GetReal());
    }
    else if(IsReal() && op.IsInt())
    {
        return Value(GetReal() - op.GetInt());
    }
    else if(IsReal() && op.IsReal())
    {
        return Value(GetReal() - op.GetReal());
    }
    
    return Value();
}

Value Value::operator*(const Value& op) const
{
    double oper1, oper2;
    if(IsString() && op.IsReal())
    {
        try 
        {
            oper1 = stod(GetString()); 
        }
        catch(invalid_argument& arg)
        {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        return Value(oper1 * op.GetReal());
    }
    else if(IsReal() && op.IsString())
    {
        try
        {
            oper1 = stod(op.GetString()); 
        }
        catch(invalid_argument& arg)
        {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }

        return Value(GetReal() * oper1);
    }
    else if(IsString() && op.IsString())
    {
        try
        {
            oper1 = stod(GetString());
            oper2 = stod(op.GetString()); 
        }
        catch(invalid_argument& arg)
        {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }

        return Value(oper1 * oper2);
    }
    else if(IsInt() && op.IsReal())
    {
        return Value(GetInt() * op.GetReal());
    }
    else if(IsReal() && op.IsInt())
    {
        return Value(GetReal() * op.GetInt());
    }
    else if(IsReal() && op.IsReal())
    {
        return Value(GetReal() * op.GetReal());
    }
    
    return Value();
}

Value Value::operator/(const Value& op) const
{
    double oper1, oper2;
    if(IsString() && op.IsReal())
    {
        try 
        {
            oper1 = stod(GetString()); 
        }
        catch(invalid_argument& arg)
        {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }

        if(op.GetReal() == 0)
        {
            cout << "Run-Time Error-Illegal Division by Zero." << endl;
            return Value();
        }
        return Value(oper1 / op.GetReal());
    }
    else if(IsReal() && op.IsString())
    {
        try
        {
            oper1 = stod(op.GetString()); 
        }
        catch(invalid_argument& arg)
        {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }

        if(oper1 == 0)
        {
            cout << "Run-Time Error-Illegal Division by Zero." << endl;
            return Value();
        }
        return Value(GetReal() / oper1);
    }
    else if(IsString() && op.IsString())
    {
        try
        {
            oper1 = stod(GetString());
            oper2 = stod(op.GetString()); 
        }
        catch(invalid_argument& arg)
        {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }

        if(oper2 == 0)
        {
            cout << "Run-Time Error-Illegal Division by Zero." << endl;
            return Value();
        }

        return Value(oper1 / oper2);
    }
    else if(IsInt() && op.IsReal())
    {
        if(op.GetReal() == 0)
        {
            cout << "Run-Time Error-Illegal Division by Zero." << endl;
            return Value();
        }

        return Value(GetInt() / op.GetReal());
    }
    else if(IsReal() && op.IsInt())
    {
        if(op.GetInt() == 0)
        {
            cout << "Run-Time Error-Illegal Division by Zero." << endl;
            return Value();
        }

        return Value(GetReal() / op.GetInt());
    }
    else if(IsReal() && op.IsReal())
    {
        if(op.GetReal() == 0)
        {
            cout << "Run-Time Error-Illegal Division by Zero." << endl;
            return Value();
        }

        return Value(GetReal() / op.GetReal());
    }
    
    return Value();
}

Value Value::operator==(const Value& op) const
{
    double oper1, oper2;
    if(IsString() && op.IsReal())
    {
        try 
        {
            oper1 = stod(GetString()); 
        }
        catch(invalid_argument& arg)
        {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }

        return Value(oper1 == op.GetReal());
    }
    else if(IsReal() && op.IsString())
    {
        try
        {
            oper1 = stod(op.GetString()); 
        }
        catch(invalid_argument& arg)
        {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }

        return Value(GetReal() == oper1);
    }
    else if(IsString() && op.IsString())
    {
        try
        {
            oper1 = stod(GetString());
            oper2 = stod(op.GetString()); 
        }
        catch(invalid_argument& arg)
        {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }

        return Value(oper1 == oper2);
    }
    else if(IsInt() && op.IsReal())
    {
        return Value(GetInt() == op.GetReal());
    }
    else if(IsReal() && op.IsInt())
    {
        return Value(GetReal() == op.GetInt());
    }
    else if(IsReal() && op.IsReal())
    {
        return Value(GetReal() == op.GetReal());
    }
    
    return Value();
}

Value Value::operator>(const Value& op) const
{
    double oper1, oper2;
    if(IsString() && op.IsReal())
    {
        try 
        {
            oper1 = stod(GetString()); 
        }
        catch(invalid_argument& arg)
        {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        return Value(oper1 > op.GetReal());
    }
    else if(IsReal() && op.IsString())
    {
        try
        {
            oper1 = stod(op.GetString()); 
        }
        catch(invalid_argument& arg)
        {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }

        return Value(GetReal() > oper1);
    }
    else if(IsString() && op.IsString())
    {
        try
        {
            oper1 = stod(GetString());
            oper2 = stod(op.GetString()); 
        }
        catch(invalid_argument& arg)
        {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }

        return Value(oper1 > oper2);
    }
    else if(IsInt() && op.IsReal())
    {
        return Value(GetInt() > op.GetReal());
    }
    else if(IsReal() && op.IsInt())
    {
        return Value(GetReal() > op.GetInt());
    }
    else if(IsReal() && op.IsReal())
    {
        return Value(GetReal() > op.GetReal());
    }
    
    return Value();
}

Value Value::operator<(const Value& op) const
{
    double oper1, oper2;
    if(IsString() && op.IsReal())
    {
        try 
        {
            oper1 = stod(GetString()); 
        }
        catch(invalid_argument& arg)
        {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        return Value(oper1 < op.GetReal());
    }
    else if(IsReal() && op.IsString())
    {
        try
        {
            oper1 = stod(op.GetString()); 
        }
        catch(invalid_argument& arg)
        {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }

        return Value(GetReal() < oper1);
    }
    else if(IsString() && op.IsString())
    {
        try
        {
            oper1 = stod(GetString());
            oper2 = stod(op.GetString()); 
        }
        catch(invalid_argument& arg)
        {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }

        return Value(oper1 < oper2);
    }
    else if(IsInt() && op.IsReal())
    {
        return Value(GetInt() < op.GetReal());
    }
    else if(IsReal() && op.IsInt())
    {
        return Value(GetReal() < op.GetInt());
    }
    else if(IsReal() && op.IsReal())
    {
        return Value(GetReal() < op.GetReal());
    }
    
    return Value();
}

Value Value::operator^(const Value& oper) const
{
    double oper1, oper2;
    if(IsString() && oper.IsReal())
    {
        try 
        {
            oper1 = stod(GetString()); 
        }
        catch(invalid_argument& arg)
        {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        return Value(pow(oper1, oper.GetReal()));
    }
    else if(IsReal() && oper.IsString())
    {
        try
        {
            oper1 = stod(oper.GetString()); 
        }
        catch(invalid_argument& arg)
        {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }

        return Value(pow(GetReal(), oper1));
    }
    else if(IsString() && oper.IsString())
    {
        try
        {
            oper1 = stod(GetString());
            oper2 = stod(oper.GetString()); 
        }
        catch(invalid_argument& arg)
        {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }

        return Value(pow(oper1, oper2));
    }
    if((IsReal() && oper.IsReal()))
    {
        return Value(pow(GetReal(), oper.GetReal()));
    }
    else if(IsReal() && oper.IsInt())
    {
        return Value(pow(GetReal(), oper.GetInt()));
    }
    else if(IsInt() && oper.IsReal())
    {
        return Value(pow(GetInt(), oper.GetReal()));
    }
    else if(IsInt() && oper.IsInt())
    {
        return Value(pow(GetInt(), oper.GetInt()));
    }

    return Value();
}

Value Value::Catenate(const Value& oper) const
{
    ostringstream outStr1, outStr2;
    string str1, str2;
    if(IsErr() || oper.IsErr())
    {
        return Value();
    }

    if(IsString() && !(oper.IsString()))
    {
        outStr1 << oper.GetReal();
        str1 = outStr1.str();
        return Value(GetString() + str1);
    }
    else if(!(IsString()) && oper.IsString())
    {
        outStr1 << GetReal();
        str1 = outStr1.str();
        return Value(str1 + oper.GetString());
    }
    else if(!IsString() && !oper.IsString())
    {
        outStr1 << GetReal();
        str1 = outStr1.str();
        outStr2 << oper.GetReal();
        str2 = outStr2.str();
        return Value(str1 + str2);
    }
    else if(IsString() && oper.IsString())
    {
        return Value(GetString() + oper.GetString());
    }

    return Value();
}

Value Value::Repeat(const Value& oper) const
{
    double times;
    if(IsString() && oper.IsString())
    {
        try
        {
            times = stod(oper.GetString()); 
        }
        catch(invalid_argument& arg)
        {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
    }
    else if(IsString() && oper.IsReal())
    {
        times = oper.GetReal();
    }
    else if(IsString() && oper.IsInt())
    {
        times = oper.GetInt();
    }
    else if(!IsString())
    {
        cout << "First argument of Repeat Statement is not of type string." << endl;
        return Value();
    }
    
    string newstr = "";
    string str = GetString();
    for(int i = 0; i < int(times); i++)
    {
        newstr += str;
    }

    return Value(newstr);
}

Value Value::SEqual(const Value& oper) const
{
    ostringstream outStr1, outStr2;
    string str1, str2;
    if(IsErr() || oper.IsErr())
    {
        return Value();
    }

    if(IsString() && !(oper.IsString()))
    {
        outStr1 << oper.GetReal();
        str1 = outStr1.str();

        return Value(GetString() == str1);
    }
    else if(!(IsString()) && oper.IsString())
    {
        outStr1 << GetReal();
        str1 = outStr1.str();
        return Value(str1 == oper.GetString());
    }
    else if(!IsString() && !oper.IsString())
    {
        outStr1 << GetReal();
        str1 = outStr1.str();
        outStr2 << oper.GetReal();
        str2 = outStr2.str();
        return Value(str1 == str2);
    }
    else if(IsString() && oper.IsString())
    {
        return Value(GetString() == oper.GetString());
    }

    return Value();
}

Value Value::SGthan(const Value& oper) const
{
    ostringstream outStr1, outStr2;
    string str1, str2;
    if(IsErr() || oper.IsErr())
    {
        return Value();
    }

    if(IsString() && !(oper.IsString()))
    {
        outStr1 << oper.GetReal();
        str1 = outStr1.str();
        return Value(GetString() > str1);
    }
    else if(!(IsString()) && oper.IsString())
    {
        outStr1 << GetReal();
        str1 = outStr1.str();
        return Value(str1 > oper.GetString());
    }
    else if(!IsString() && !oper.IsString())
    {
        outStr1 << GetReal();
        str1 = outStr1.str();
        outStr2 << oper.GetReal();
        str2 = outStr2.str();
        return Value(str1 > str2);
    }
    else if(IsString() && oper.IsString())
    {
        return Value(GetString() > oper.GetString());
    }

    return Value();
}

Value Value::SLthan(const Value& oper) const
{
    ostringstream outStr1, outStr2;
    string str1, str2;
    if(IsErr() || oper.IsErr())
    {
        return Value();
    }

    if(IsString() && !(oper.IsString()))
    {
        outStr1 << oper.GetReal();
        str1 = outStr1.str();
        return Value(GetString() < str1);
    }
    else if(!(IsString()) && oper.IsString())
    {
        outStr1 << GetReal();
        str1 = outStr1.str();
        return Value(str1 < oper.GetString());
    }
    else if(!IsString() && !oper.IsString())
    {
        outStr1 << GetReal();
        str1 = outStr1.str();
        outStr2 << oper.GetReal();
        str2 = outStr2.str();
        return Value(str1 < str2);
    }
    else if(IsString() && oper.IsString())
    {
        return Value(GetString() < oper.GetString());
    }

    return Value();
}
