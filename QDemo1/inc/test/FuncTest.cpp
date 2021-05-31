#include "FuncTest.h"

#include <map>
#include <tuple>

#include <string>
#include <iostream>

#include <utility>
#include <functional>

#include <QMap>
#include <QString>

CFuncTest::CFuncTest()
{
}

void CFuncTest::tuple_test()
{
    int s1;
    std::string str1;

    //1
    {
        auto key1 = std::make_tuple("123", 3);

        std::tuple_element<0, decltype(key1)>::type first = std::get<0>(key1);
        std::tuple_element<1, decltype(key1)>::type second = std::get<1>(key1);

        std::tuple<std::string, int> key2("123", 3);
        int value = std::tuple_size<decltype(key2)>::value;

        auto key3 = std::forward_as_tuple("123", 3);
        std::get<1>(key3) = 4;

        const int a = 0; int b[3];
        auto key4 = std::make_tuple(a, b);                  //tuple<int, int*>
        auto key5 = std::make_tuple(std::ref(a), "123");    //tuple<const int&, const char*>

        std::tuple<std::string, int> key6;
        key6 = std::make_tuple("123", 3);
        std::tie(str1, std::ignore) = key6;

        auto key7 = std::tuple_cat(key5, key6);
    }

    //2
    {
        QMap<std::string, std::tuple<std::string, int>> mapstr;
        mapstr["test1"] = std::make_tuple("123", 1);
        mapstr["test2"] = std::make_tuple("123", 2);

        if (mapstr.contains("test1"))
        {
            str1 = std::get<0>(mapstr["test1"]);
            s1 = std::get<1>(mapstr["test1"]);
        }
    }
}

void CFuncTest::string_test()
{
    //1
    {
    }
}
