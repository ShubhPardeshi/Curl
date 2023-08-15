#include <iostream>
#include <sstream>
#include <memory>
#include "json.hpp"
#include "curl.h"
#include "FileName.h"

#pragma comment (lib, "libcurl.dll.a")

using std::stringstream;
using json = nlohmann::json;

static size_t WriteCallback(void* contents, size_t size, size_t membyte, void* userp)
{
    std::string data((const char*)contents, (size_t)size * membyte);
    *((stringstream*)userp) << data;
    return size * membyte;
}

int main(void)
{
    std::string                 strInput;
    std::vector<std::string>    vecInput;
    CURL*                       curlObject{nullptr};
    CURLcode                    curlResult;
    std::stringstream           readBuffer;
    json                        jsonObject;
    std::vector<metadata>       vecData;

    std::cout << "Enter website address:" << std::endl; 

    while (true) {
        getline(std::cin, strInput);
        if (strInput.empty()) { break; }
        vecInput.push_back(strInput.c_str());
        strInput.clear();
    }

    if (vecInput.empty()){ 
        std::cout << "Invalid Input!!" << std::endl;
        return -1;
    } 

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curlObject = curl_easy_init();
    
    if (nullptr == curlObject){
        std::cout << "Invalid Curl Object, failed to init" << std::endl;
        return -1;
    }

    for (auto& variable : vecInput)
    {
        readBuffer.str(std::string());
        jsonObject.clear();

        curl_easy_setopt(curlObject, CURLOPT_URL, variable.c_str());
        curl_easy_setopt(curlObject, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curlObject, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curlObject, CURLOPT_WRITEDATA, &readBuffer);

        Sleep(100); 

        curlResult = curl_easy_perform(curlObject);

        if (curlResult != CURLE_OK)
            std::cout << (stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(curlResult));

        if (readBuffer.str().empty()) {
            std::cout << "Unable to read the data!" << std::endl;
            return -1;
        }

        try {
            readBuffer >> jsonObject;

            if (jsonObject.is_array())
            {
                for (auto itr = jsonObject.begin(); itr != jsonObject.end(); ++itr)
                {
                    metadata data;

                    if (itr->is_object())
                    {
                        if (itr->contains("userId"))
                            data.set_user_id(itr.value()["userId"].get<int>());
                        if (itr->contains("id"))
                            data.set_id(itr.value()["id"].get<int>());
                        if (itr->contains("title"))
                            data.set_title(itr.value()["title"].get<std::string>());
                        if (itr->contains("body"))
                            data.set_body(itr.value()["body"].get<std::string>());
                        if (itr->contains("name"))
                            data.set_name(itr.value()["name"].get<std::string>());
                        if (itr->contains("username"))
                            data.set_username(itr.value()["username"].get<std::string>());
                        if (itr->contains("email"))
                            data.set_email(itr.value()["email"].get<std::string>());
                        if (itr->contains("phone"))
                            data.set_phone(itr.value()["phone"].get<std::string>());
                        if (itr->contains("website"))
                            data.set_website(itr.value()["website"].get<std::string>());
                        if (itr->contains("address"))
                        {
                            Address add;
                            Geo     geo;
                            for (auto& val : itr.value()["address"].items())
                            {
                                if (val.key() == "city")
                                    add.set_city(val.value().get<std::string>());

                                if (val.key() == ("street"))
                                    add.set_street(val.value().get<std::string>());

                                if (val.key() == ("suite"))
                                    add.set_suite(val.value().get<std::string>());

                                if (val.key() == ("zipcode"))
                                    add.set_zipcode(val.value().get<std::string>());

                                if (val.key() == ("geo")) {
                                    geo.set_lng(val.value()["lng"].get<std::string>());
                                    geo.set_lat(val.value()["lat"].get<std::string>());
                                }
                            }

                            add.set_geo(geo);
                            data.set_address(add);
                        }
                        if (itr->contains("company"))
                        {
                            Company com;
                            for (auto& val : itr.value()["company"].items())
                            {
                                if (val.key() == "name")
                                    com.set_name(val.value().get<std::string>());

                                if (val.key() == ("catchPhrase"))
                                    com.set_catch_phrase(val.value().get<std::string>());

                                if (val.key() == ("bs"))
                                    com.set_bs(val.value().get<std::string>());

                            }

                            data.set_company(com);
                        }
                    }
                    vecData.push_back(data);
                }
            }
        }
        catch (...)
        {
            std::cout << "Unable to parse the json data!" << std::endl;
        }
    }

    for (auto& var : vecData)
        print(var);

    curl_easy_cleanup(curlObject);
    curl_global_cleanup();
    return 0; 
}