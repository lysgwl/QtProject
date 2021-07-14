#include "FuncTest.h"

#include <internal.h>

CFuncTest::CFuncTest()
{
}

//tuple
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

//string
void CFuncTest::string_test()
{
    //1
    {
        QJsonObject jsonObject;
        jsonObject.insert("test1", 123);
        jsonObject.insert("test2", 213);
        jsonObject.insert("test3", "321");
        jsonObject.insert("test4", false);
        if (!jsonObject.isEmpty())
        {
            if (jsonObject.contains("test3"))
            {
                std::string s1 = jsonObject.value("test3").toString().toStdString();
                if (jsonObject.value("test3").toString() == ("") || jsonObject.value("test3").toString().isEmpty())
                {
                    jsonObject.remove("test3");
                }

                bool bFlag = jsonObject.value("test4").toBool();
                std::cout << bFlag;
            }
        }

        QJsonObject json;
        json.insert("requestId", 1);
        json.insert("protocol", 0x1234abcd);
        json.insert("reserve", "this is a test!");
        json.insert("data", jsonObject);    //QJsonValue(jsonObject)
        if (!json.isEmpty())
        {
            if (json.contains("protocol"))
            {
                std::string seq = std::to_string(json.value("requestId").toInt());
                std::string reserve = json.value("reserve").toString().toStdString();

                //int value = std::stoi(seq);
                //int iseq = json.value("requestId").toInt();

                std::string s1 = std::string(QJsonDocument(json).toJson(QJsonDocument::Compact));
                //std::string s2 = str1.toStdString();
            }

            if (json.contains("data"))
            {
                {
                    QJsonValueRef RefPage = json.find("data").value();
                    QJsonObject obj = RefPage.toObject();

                    std::string s1 = std::to_string(obj.value("test1").toInt());
                    std::string s2 = std::to_string(json["test"].toObject().value("test1").toInt());
                }

                {
                    QJsonObject obj = json["data"].toObject();
                    std::string s1 = std::to_string(obj["test1"].toInt());
                }
            }
        }
    }

    //2
    {
        QJsonArray array;
        qint64 iNum = 16104016000;

        for (int i=0; i<2; i++)
        {
            QJsonObject jsonData;
            jsonData.insert("id", i);
            jsonData.insert("status", 0);
            jsonData.insert("user", iNum+i);
            array.insert(i, jsonData);
        }

        QJsonObject json;
        json.insert("count", array.size());
        json.insert("data", array);

        QJsonArray membArray = json["data"].toArray();
        if (!membArray.isEmpty())
        {
            const QJsonValue jsonValue = membArray.at(0);
            QJsonObject object = jsonValue.toObject();
            if (object.isEmpty())
            {
                return;
            }
        }

        for (QJsonArray::Iterator iter = membArray.begin(); iter != membArray.end(); iter++)
        {
            QJsonObject object = iter[0].toObject();
            if (object.isEmpty())
            {
                continue;
            }
        }

        foreach(QJsonValue value, membArray)
        {
            QJsonObject object = value.toObject();
            if (object.isEmpty())
            {
                continue;
            }
        }

        if (0)
        {
            /*QJsonArray::iterator arrayIter = membArray.begin();
            QJsonValueRef ElementOneValueRef = arrayIter[0];
            QJsonObject ElementOneObject = ElementOneValueRef.toObject();

            QByteArray byte_array = QJsonDocument(membArray).toJson();
            QJsonObject object = QJsonDocument::fromJson(byte_array).object();*/
        }
    }

    //3
    {
        std::string s1 = "{\"t1\":\"123\",\"t2\":321}";
        QJsonObject json = QJsonDocument::fromJson(s1.c_str()).object();

        std::stringstream stream;
        stream << "http://" << "192.168.0.1" << 80;
        std::string s2 = stream.str();

        std::ostringstream  strss;
        strss << "http://" << "192.168.0.1" << 80 << "/" << s1;
        std::string s3 = strss.str();

        int pos = s3.compare(s2);

        stream.str("");
        stream << 1 << 2 << 3;

        std::string s4 = stream.str();
        QString qs4 = s4.c_str();
    }

    //4
    {
       QString s1 = "16104016001h";

       QRegExp rx("(.*)[h|H]$");  //(.*?)[h|H]$ //^[A-Za-z]+$
       int index = s1.indexOf(rx);
       if (index == 0)
       {
       }
    }
}
