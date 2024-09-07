// JSON library
// header file
// Author: @someperson75
// Date: 07/09/2024
// Version: 1.0.1
// Description: json class for c++ with performs input and output on I/O stream

#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#ifndef JSON_lib
#define JSON_lib

class Object;
class Array;
class JSON;

class Json_error : public std::exception
{
    std::string msg;

public:
    Json_error(const char *msg);
    Json_error(const std::string msg);
    virtual const char *what() const noexcept;
};

class Object
{
    std::unordered_map<std::string, JSON> object;

public:
    void clear();
    JSON &operator[](const std::string key);
    JSON &operator[](const char *key);
    Object &operator=(const Object &other);
    std::list<std::pair<const std::string, JSON>, std::allocator<std::pair<const std::string, JSON>>>::const_iterator begin() const;
    std::list<std::pair<const std::string, JSON>, std::allocator<std::pair<const std::string, JSON>>>::const_iterator end() const;
    std::unordered_map<std::string, JSON> &values();
    Object();
};

class Array
{
    std::vector<JSON> array;

public:
    void clear();
    JSON &operator[](const long long id);
    Array &operator=(const Array &other);
    Array &push_back(const JSON &val);
    Array &operator+=(const JSON &val);
    std::vector<JSON> &values();
    std::vector<JSON>::const_iterator begin() const;
    std::vector<JSON>::const_iterator end() const;
    Array();
};

std::ostream &operator<<(std::ostream &os, const JSON &json);
JSON readJSON(std::istream &is);
std::istream &operator>>(std::istream &is, JSON &json);

class JSON
{
    unsigned short type;
    Object object;
    Array array;
    int num;
    std::string str;
    bool b;

public:
    void clear();
    JSON();
    JSON(const int num);
    JSON(const std::string str);
    JSON(const char *str);
    JSON(const bool b);
    JSON(const Object object);
    JSON(const Array array);
    JSON &operator[](const int id);
    JSON &operator[](const std::string &key);
    JSON &operator=(const JSON val);
    JSON &operator=(const Object val);
    JSON &operator=(const Array val);
    JSON &operator=(const int val);
    JSON &operator=(const std::string val);
    JSON &operator=(const char *val);
    JSON &operator=(const bool val);
    Object &getObject();
    Array &getArray();
    int &getInt();
    std::string &getString();
    bool &getBool();
    bool isNull() const;
    bool isObject() const;
    bool isArray() const;
    bool isInteger() const;
    bool isString() const;
    bool isBooleen() const;
    std::string strigify(bool preaty = false, int level = 0) const;
};
#endif