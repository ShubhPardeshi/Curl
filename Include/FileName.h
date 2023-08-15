#pragma once

#include <stdexcept>
#include <fstream>

class Geo {
public:
    Geo() = default;
    virtual ~Geo() = default;

private:
    std::string lat;
    std::string lng;

public:
    const std::string& get_lat() const { return lat; }
    void set_lat(const std::string& value) { this->lat = value; }

    const std::string& get_lng() const { return lng; }
    void set_lng(const std::string& value) { this->lng = value; }
};

class Address {
public:
    Address() = default;
    virtual ~Address() = default;

private:
    std::string street;
    std::string suite;
    std::string city;
    std::string zipcode;
    Geo geo;

public:
    const std::string& get_street() const { return street; }
    void set_street(const std::string& value) { this->street = value; }

    const std::string& get_suite() const { return suite; }
    void set_suite(const std::string& value) { this->suite = value; }

    const std::string& get_city() const { return city; }
    void set_city(const std::string& value) { this->city = value; }

    const std::string& get_zipcode() const { return zipcode; }
    void set_zipcode(const std::string& value) { this->zipcode = value; }

    const Geo& get_geo() const { return geo; }
    void set_geo(const Geo& value) { this->geo = value; }
};

class Company {
public:
    Company() = default;
    virtual ~Company() = default;

private:
    std::string name;
    std::string catch_phrase;
    std::string bs;

public:
    const std::string& get_name() const { return name; }
    void set_name(const std::string& value) { this->name = value; }

    const std::string& get_catch_phrase() const { return catch_phrase; }
    void set_catch_phrase(const std::string& value) { this->catch_phrase = value; }

    const std::string& get_bs() const { return bs; }
    void set_bs(const std::string& value) { this->bs = value; }
};

class metadata {
public:
    metadata() = default;
    virtual ~metadata() = default;

private:
    int64_t     id{ 0 };
    int64_t     user_id{ 0 };
    std::string title;
    std::string body;
    std::string name;
    std::string username;
    std::string email;
    std::string phone;
    std::string website;
    Address     address;
    Company     company;
   
public:
    const int64_t& get_id() const { return id; }
    void set_id(const int64_t& value) { this->id = value; }

    const std::string& get_name() const { return name; }
    void set_name(const std::string& value) { this->name = value; }

    const std::string& get_username() const { return username; }
    void set_username(const std::string& value) { this->username = value; }

    const std::string& get_email() const { return email; }
    void set_email(const std::string& value) { this->email = value; }

    const Address& get_address() const { return address; }
    void set_address(const Address& value) { this->address = value; }

    const std::string& get_phone() const { return phone; }
    void set_phone(const std::string& value) { this->phone = value; }

    const std::string& get_website() const { return website; }
    void set_website(const std::string& value) { this->website = value; }

    const Company& get_company() const { return company; }
    void set_company(const Company& value) { this->company = value; }

    const int64_t& get_user_id() const { return user_id; }
    void set_user_id(const int64_t& value) { this->user_id = value; }

    const std::string& get_title() const { return title; }
    void set_title(const std::string& value) { this->title = value; }

    const std::string& get_body() const { return body; }
    void set_body(const std::string& value) { this->body = value; }
};

void print(const metadata& data)
{
    std::ofstream OutputFile; //automatically has the ios::out flag set

    OutputFile.open("Output.txt", std::ios::app);
    if (!OutputFile.is_open()) {
        std::cout << "Unable to open output file!!" << std::endl;
    }

    OutputFile << "Data" << std::endl;
    OutputFile << "--------------------------------------------" << std::endl;
    OutputFile << "id:" << data.get_id() << std::endl;
    OutputFile << "user_id:" << data.get_user_id() << std::endl;
    OutputFile << "title:" << data.get_title() << std::endl;
    OutputFile << "body:" << data.get_body() << std::endl;
    OutputFile << "name:" << data.get_name() << std::endl;
    OutputFile << "username:" << data.get_username() << std::endl;
    OutputFile << "email:" << data.get_email() << std::endl;
    OutputFile << "address:" << std::endl;
    OutputFile << "street:" << data.get_address().get_street() << std::endl;
    OutputFile << "suit:" << data.get_address().get_suite() << std::endl;
    OutputFile << "city:" << data.get_address().get_city() << std::endl;
    OutputFile << "zipcode:" << data.get_address().get_zipcode() << std::endl;
    OutputFile << "geo:" << std::endl;
    OutputFile << "lat:" << data.get_address().get_geo().get_lat() << std::endl;
    OutputFile << "lng:" << data.get_address().get_geo().get_lng() << std::endl;
    OutputFile << "website:" << data.get_website() << std::endl;
    OutputFile << "phone:" << data.get_phone() << std::endl;
    OutputFile << "company" << std::endl;
    OutputFile << "name:" << data.get_company().get_name() << std::endl;
    OutputFile << "catch_phrase:" << data.get_company().get_catch_phrase() << std::endl;
    OutputFile << "bs:" << data.get_company().get_bs() << std::endl;
    OutputFile << "--------------------------------------------" << std::endl;
}
