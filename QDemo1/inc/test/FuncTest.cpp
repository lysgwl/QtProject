#include "FuncTest.h"

#include <map>
#include <tuple>

#include <string>
#include <iostream>

#include <utility>
#include <functional>

#include <QMap>
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

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

        std::vector<std::tuple<std::string, std::string>> vecstr;
        vecstr.push_back(std::make_tuple("seq", std::to_string(0)));
        vecstr.push_back(std::make_tuple("lgtype", "PC"));
        vecstr.push_back(std::make_tuple("lgnum", "16104016001"));
        vecstr.push_back(std::make_tuple("lgpwd", "123456"));

        for (auto iter=vecstr.cbegin(); iter != vecstr.cend(); iter++)
        {
            std::string strKey = std::get<0>(*iter);
            std::string strValue = std::get<1>(*iter);
        }
    }

    //3
    {
    }
}

void CFuncTest::string_test()
{
    //1
    {
        QJsonObject json;
        json.insert("requestId", 1);
        json.insert("protocol", 0x1234abcd);
        json.insert("reserve", "this is a test!");

        if (!json.isEmpty() && json.contains("protocol"))
        {
            std::string seq = std::to_string(json.value("requestId").toInt());
            std::string reserve = json.value("reserve").toString().toStdString();

            //int value = std::stoi(seq);
            //int iseq = json.value("requestId").toInt();

            std::string str1 = std::string(QJsonDocument(json).toJson(QJsonDocument::Compact));
            //std::string str2 = str1.toStdString();
        }

        QJsonObject s1;
        s1.insert("test1", 123);
        json.insert("test", s1);
    }

    //2
    {
        std::string s1 = "{\"t1\":\"123\",\"t2\":321}";
        QJsonObject json = QJsonDocument::fromJson(s1.c_str()).object();
    }
}
