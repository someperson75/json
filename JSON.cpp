// JSON library
// source file
// Author: @someperson75
// Date: 07/09/2024
// Version: 3.0
// Description: json class for c++ with performs input and output on I/O stream

#include "JSON.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#ifndef JSON_lib_functions
#define JSON_lib_functions

////////////////////////////
//                        //
//  Json_error functions  //
//                        //
////////////////////////////

Json_error::Json_error(const char *msg)
{
    this->msg = msg;
}

Json_error::Json_error(const std::string msg)
{
    this->msg = msg;
}

const char *Json_error::what() const noexcept
{
    return msg.c_str();
}

////////////////////////////
//                        //
//    Object functions    //
//                        //
////////////////////////////

void Object::clear()
{
    for (auto it = object.begin(); it != object.end(); it++)
        it->second.clear();
}

JSON &Object::operator[](const std::string key)
{
    if (object.find(key) == object.end())
        object[key] = JSON();
    return object[key];
}

JSON &Object::operator[](const char *key)
{
    if (object.find(key) == object.end())
        object[key] = JSON();
    return object[key];
}

Object &Object::operator=(const Object &other)
{
    clear();
    object = other.object;
    return *this;
}

std::unordered_map<std::string, JSON> &Object::values()
{
    return object;
}

Object::Object()
{
    clear();
}

std::unordered_map<const std::string, JSON>::const_iterator Object::begin() const
{
    return object.begin();
}

std::unordered_map<const std::string, JSON>::const_iterator Object::end() const
{
    return object.end();
}

///////////////////////////
//                       //
//    Array functions    //
//                       //
///////////////////////////

void Array::clear()
{
    for (auto it = array.begin(); it != array.end(); it++)
        it->clear();
}

JSON &Array::operator[](const long long id)
{
    if (id < 0)
        throw Json_error("Out of bound error : index less than 0.\n");
    if (id >= (long long)array.size())
        array.resize(id + 1, JSON());
    return array[id];
}

Array &Array::operator=(const Array &other)
{
    clear();
    array = other.array;
    return *this;
}

Array &Array::push_back(const JSON &val)
{
    array.push_back(val);
    return *this;
}

Array &Array::operator+=(const JSON &val)
{
    array.push_back(val);
    return *this;
}

std::vector<JSON> &Array::values()
{
    return array;
}

Array::Array()
{
    clear();
}

std::vector<JSON>::const_iterator Array::begin() const
{
    return array.begin();
}

std::vector<JSON>::const_iterator Array::end() const
{
    return array.end();
}

////////////////////////////
//                        //
//     JSON functions     //
//                        //
////////////////////////////

void JSON::clear()
{
    object.clear();
    array.clear();
    num = 0;
    d = 0.;
    str = "";
    b = false;
    type = Type::null;
}

JSON::JSON()
{
    clear();
}

JSON::JSON(const Object object)
{
    clear();
    this->object = object;
    type = Type::obj;
}

JSON::JSON(const Array array)
{
    clear();
    this->array = array;
    type = Type::arr;
}

JSON::JSON(const int num)
{
    clear();
    this->num = num;
    type = Type::integer;
}

JSON::JSON(const double num)
{
    clear();
    this->d = d;
    type = Type::floatNum;
}

JSON::JSON(const std::string str)
{
    clear();
    this->str = str;
    type = Type::string;
}

JSON::JSON(const char *str)
{
    clear();
    this->str = str;
    type = Type::string;
}

JSON::JSON(const bool b)
{
    clear();
    this->b = b;
    type = Type::boolean;
}

JSON &JSON::operator[](const int id)
{
    if (type == Type::arr)
        return array[id];
    else
        throw Json_error("Type error : not an Array.\n");
}

JSON &JSON::operator[](const std::string &key)
{
    if (type == Type::obj)
        return object[key];
    else
        throw Json_error("Type error : not an Object.\n");
}

JSON &JSON::operator=(const JSON val)
{
    clear();
    type = val.type;
    switch (type)
    {
    case Type::obj:
        object = val.object;
        break;
    case Type::arr:
        array = val.array;
        break;
    case Type::integer:
        num = val.num;
        break;
    case Type::floatNum:
        d = val.d;
        break;
    case Type::string:
        str = val.str;
        break;
    case Type::boolean:
        b = val.b;
        break;
    default:
        break;
    }
    return *this;
}

JSON &JSON::operator=(const Object val)
{
    clear();
    object = val;
    type = Type::obj;
    return *this;
}

JSON &JSON::operator=(const Array val)
{
    clear();
    array = val;
    type = Type::arr;
    return *this;
}

JSON &JSON::operator=(const int val)
{
    clear();
    num = val;
    type = Type::integer;
    return *this;
}

JSON &JSON::operator=(const double val)
{
    clear();
    d = val;
    type = Type::floatNum;
    return *this;
}

JSON &JSON::operator=(const std::string val)
{
    clear();
    str = val;
    type = Type::string;
    return *this;
}

JSON &JSON::operator=(const char *val)
{
    clear();
    str = val;
    type = Type::string;
    return *this;
}

JSON &JSON::operator=(const bool val)
{
    clear();
    b = val;
    type = Type::boolean;
    return *this;
}

template <typename T>
T &JSON::get(T n)
{
    throw Json_error((std::string) "Error : type " + typeid(T).name() + " is not allowed here.\n");
    return T();
}

template <>
Object &JSON::get<Object>(Object n)
{
    if (type == Type::obj)
        return object;
    else
        throw Json_error("Type error : not an Object.\n");
}

template <>
Array &JSON::get<Array>(Array n)
{
    if (type == Type::arr)
        return array;
    else
        throw Json_error("Type error : not an Array.\n");
}

template <>
int &JSON::get<int>(int n)
{
    if (type == Type::integer)
        return num;
    else
        throw Json_error("Type error : not an Integer.\n");
}

template <>
double &JSON::get<double>(double n)
{
    if (type == Type::floatNum)
        return d;
    else
        throw Json_error("Type error : not an Double.\n");
}

template <>
bool &JSON::get<bool>(bool n)
{
    if (type == Type::boolean)
        return b;
    else
        throw Json_error("Type error : not a Boolean.\n");
}

template <>
std::string &JSON::get<std::string>(std::string n)
{
    if (type == Type::string)
        return str;
    else
        throw Json_error("Type error : not a String.\n");
}

bool JSON::isNull() const
{
    return type == Type::null;
}

bool JSON::isObject() const
{
    return type == Type::obj;
}

bool JSON::isArray() const
{
    return type == Type::arr;
}

bool JSON::isInteger() const
{
    return type == Type::integer;
}

bool JSON::isDouble() const
{
    return type == Type::floatNum;
}

bool JSON::isString() const
{
    return type == Type::string;
}

bool JSON::isBoolean() const
{
    return type == Type::boolean;
}

///////////////////////////
//                       //
//     I/O functions     //
//                       //
///////////////////////////

std::string JSON::strigify(bool preaty, int level) const
{
    std::string line = " ";
    if (preaty)
    {
        line = "\n";
        for (int i = 0; i <= level; i++)
            line += "\t";
    }
    std::string out = "";
    switch (type)
    {
    case Type::null:
        out = "null";
        break;

    case Type::obj:
        out += '{';
        out += line;
        for (auto iter = object.begin(); iter != object.end();)
        {
            out += "\"" + iter->first + "\": " + iter->second.strigify(preaty, level + 1);
            if (++iter != object.end())
                out += ',';
            out += line;
        }
        if (preaty)
            out.pop_back();
        out += '}';
        break;

    case Type::arr:
        out += '[';
        out += line;
        for (auto iter = array.begin(); iter != array.end();)
        {
            out += iter->strigify(preaty, level + 1);
            if (++iter != array.end())
                out += ',';
            out += line;
        }
        if (preaty)
            out.pop_back();
        out += ']';
        break;

    case Type::integer:
        out = std::to_string(num);
        break;

    case Type::floatNum:
        out = std::to_string(d);
        break;

    case Type::string:
        out = "\"" + str + "\"";
        break;

    case Type::boolean:
        out = b ? "true" : "false";
        break;

    default:
        break;
    }
    return out;
}

std::ostream &operator<<(std::ostream &os, const JSON &json)
{
    os << json.strigify(true);
    return os;
}

void ExtractNotInterestingChar(std::istream &is)
{
    char next = is.eof() ? ' ' : is.peek();
    while (next == ' ' || next == '\n' || next == '\t')
        is.get(), next = is.peek();
}

JSON readJSON(std::istream &is)
{
    ExtractNotInterestingChar(is);
    char c = is.get();
    if (c == '\"')
    {
        // string
        std::string str = "";
        char last = '"';
        char current = is.get();
        while (current != '"' || last == '\\')
        {
            if (last == '\\')
            {
                switch (current)
                {
                case '\\':
                    str += '\\';
                    break;

                case 'n':
                    str += '\n';
                    break;

                case 't':
                    str += '\t';
                    break;

                case '"':
                    str += '"';
                    break;

                default:
                    break;
                }
                current = '\0';
            }
            if (current != '\\' && current != '\0')
                str += current;
            last = current, current = is.get();
        }
        return JSON(str);
    }
    else if (c == '-' || c == '+' || (c >= '0' && c <= '9'))
    {
        // integer
        int num = 0;
        int divide = 0;
        bool signe = (c == '-');
        char current = c < '0' ? is.get() : c;
        while ((current >= '0' && current <= '9') || current == '.')
        {
            num *= 10;
            divide *= 10;
            if (current == '.' && divide != 0)
                throw Json_error("Syntax error: there can't be two or more decimal point.\n");
            if (current == '.')
                divide = 1;
            num += (current - '0');
            current = is.get();
        }
        is.unget();
        if (divide != 0)
            return JSON((double)(num * (signe ? -1 : 1)) / (double)divide);
        return JSON(num * (signe ? -1 : 1));
    }
    else if (c == 't' || c == 'f')
    {
        // boolean
        bool result = (c == 't');
        char null[5] = "\0\0\0\0";
        if (result)
            is.read(null, 3);
        else
            is.read(null, 4);
        if ((std::string)null != (std::string) "alse" && (std::string)null != (std::string) "rue")
            throw Json_error((std::string) "Syntax error : Unknow symbol '" + c + null + "'.\n");
        return JSON(result);
    }
    else if (c == '{')
    {
        // Object
        Object o;
        while (true)
        {
            ExtractNotInterestingChar(is);
            std::string str = "";
            char last = is.get();
            char current = is.get();
            while (current != '"' || last == '\\')
            {
                if (last == '\\')
                {
                    switch (current)
                    {
                    case '\\':
                        str += '\\';
                        break;

                    case 'n':
                        str += '\n';
                        break;

                    case 't':
                        str += '\t';
                        break;

                    case '"':
                        str += '"';
                        break;

                    default:
                        break;
                    }
                    current = '\0';
                }
                if (current != '\\' && current != '\0')
                    str += current;
                last = current, current = is.get();
            }
            ExtractNotInterestingChar(is);
            char c = is.get();
            if (c != ':')
                throw Json_error((std::string) "Syntax error : Unknow symbol '" + c + "'.\n");
            JSON obj = readJSON(is);
            o[str] = obj;
            ExtractNotInterestingChar(is);
            char end = is.get();
            if (end == '}')
                break;
            else if (end != ',')
                throw Json_error((std::string) "Syntax error : Unknow symbol '" + end + "'.\n");
        }
        return JSON(o);
    }
    else if (c == '[')
    {
        // Array
        Array a;
        while (true)
        {
            JSON obj = readJSON(is);
            a += obj;
            ExtractNotInterestingChar(is);
            char end = is.get();
            if (end == ']')
                break;
            else if (end != ',')
                throw Json_error((std::string) "Syntax error : Unknow symbol '" + end + "'.\n");
        }
        return JSON(a);
    }
    else
        throw Json_error((std::string) "Syntax error : Unknow symbol '" + c + "'.\n");
}

std::istream &operator>>(std::istream &is, JSON &json)
{
    json = readJSON(is);
    return is;
}
#endif