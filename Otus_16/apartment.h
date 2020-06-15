#pragma once
#include <boost/algorithm/algorithm.hpp>      
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <fstream>
#include <iostream>
#include <cstddef>
#include <string>
#include <vector>
//долгота;широта;комнат;цена;метраж;кухня;этаж;этажность\n
//86.116781;55.335492;2;4326901.00;54.00;7.00;5;5\n


class Apartment {
public:
    Apartment() = default;
    Apartment(const std::string aStr) : m_Serialized(aStr) {

        auto tokens = GetTokens(aStr);
        const std::size_t minTokensNumber = 8;
        if (tokens.size() < minTokensNumber) 
            return;
        try {
            m_Longitude     = (tokens[0]!= "") ? std::stod(tokens[0]) : 0;
            m_Latitude      = (tokens[1]!= "") ? std::stod(tokens[1]) : 0;
            m_Rooms         = (tokens[2]!= "") ? std::stoi(tokens[2]) : 0;
            m_Cost          = (tokens[3]!= "") ? std::stod(tokens[3]) : 0;
            m_AreaAll       = (tokens[4]!= "") ? std::stod(tokens[4]) : 0;
            m_AreaKitchen   = (tokens[5]!= "") ? std::stod(tokens[5]) : 0;
            m_Floor         = (tokens[6]!= "") ? std::stoi(tokens[6]) : 0;
            m_NumberOfFloor = (tokens[7]!= "") ? std::stoi(tokens[7]) : 0;
            m_Valid = true;
        } 
        catch (std::exception& e) {
            m_Valid = false;
        }
    }

    std::string Serialize() const {
        return m_Serialized;
    }

    bool IsValid() const {
        return m_Valid;
    }

    double Longitude          () const {
        return m_Longitude;
    }

    double Latitude           () const {
        return m_Latitude;
    }
    
    std::size_t Rooms         () const {
        return m_Rooms;
    }

    double Cost               () const {
        return m_Cost;
    }

    double AreaAll            () const {
        return m_AreaAll;
    }

    double AreaKitchen        () const {
        return m_AreaKitchen;
    }

    std::size_t  Floor        () const {
        return m_Floor;
    }
    
    std::size_t  NumberOfFloor() const {
        return m_NumberOfFloor;
    }
private:    
    double      m_Longitude     = 0;
    double      m_Latitude      = 0;
    std::size_t m_Rooms         = 0;
    double      m_Cost          = 0;
    double      m_AreaAll       = 0;
    double      m_AreaKitchen   = 0;
    std::size_t m_Floor         = 0;
    std::size_t m_NumberOfFloor = 0;

    bool m_Valid = false;
    const std::string m_Serialized = "";

    std::vector<std::string> GetTokens(const std::string& aStr) {
        std::vector<std::string> vec;
        boost::algorithm::split(vec, aStr, boost::is_any_of(";\r\n"));
        return vec;
    }
};

std::vector<Apartment> GetApartments(std::istream& aStream) {
    if (!aStream) {
        throw std::logic_error("std::ifstream aStream was corrupted");
    }

    std::vector<Apartment> apartments;
    std::string str;
    while (std::getline(aStream, str)) {
        Apartment apartment(str);
        if (!apartment.IsValid())
            continue;
        apartments.push_back(apartment);
    }
    return apartments;
}

struct ApartmentsBorders {
    Apartment Min;
    Apartment Max;
};

ApartmentsBorders FindBorders(const std::vector<Apartment>& aApartments) {
    return {};
}

double FindMaxCost(const std::vector<Apartment>& aApartments) {
    double maxCost = 0;
    std::for_each(aApartments.cbegin(), aApartments.cend(), [&maxCost](const auto& apart) { maxCost = std::max(maxCost, apart.Cost()); });
    return maxCost;
}

double FindMaxCost(const std::string aFileName) {
    double maxCost = 0;
    std::ifstream file(boost::str(boost::format("%1$.2f.max_cost") % aFileName));
    std::string str;
    std::getline(file, str);
    maxCost = std::atof(str.c_str());
    return maxCost ? maxCost : 1;
}
