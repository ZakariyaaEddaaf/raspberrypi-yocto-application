#include "gnss.hpp"
#include <sstream>
#include <iostream>

GNSS::GNSS()
    : latitude(0), longitude(0), fix_quality(0), num_satellites(0), hdop(0), altitude(0), height_of_geoid(0)
{
}

GNSS::~GNSS()
{
}

std::vector<std::string> GNSS::split(const std::string& s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

std::string GNSS::catch_gpgga_gngga(const std::string& data)
{
    std::istringstream iss(data);
    std::string line;
    while (std::getline(iss, line, '\n'))
    {
        if (line.substr(0, 6) == "$GPGGA" || line.substr(0, 6) == "$GNGGA")
        {
            return line;
        }
    }
    return "";
}

bool GNSS::parse_gpgga_gngga(const std::string& sentence)
{
    auto tokens = split(sentence, ',');

    if (tokens.size() < 15 || (tokens[0] != "$GPGGA" && tokens[0] != "$GNGGA"))
    {
        return false;
    }

    try
    {
        if (!tokens[2].empty() && !tokens[3].empty())
        {
            latitude = std::stod(tokens[2].substr(0, 2)) + std::stod(tokens[2].substr(2)) / 60.0;
            if (tokens[3] == "S") latitude = -latitude;
        }

        if (!tokens[4].empty() && !tokens[5].empty())
        {
            longitude = std::stod(tokens[4].substr(0, 3)) + std::stod(tokens[4].substr(3)) / 60.0;
            if (tokens[5] == "W") longitude = -longitude;
        }

        if (!tokens[6].empty())
        {
            fix_quality = std::stoi(tokens[6]);
        }

        if (!tokens[7].empty())
        {
            num_satellites = std::stoi(tokens[7]);
        }

        if (!tokens[8].empty())
        {
            hdop = std::stod(tokens[8]);
        }

        if (!tokens[9].empty())
        {
            altitude = std::stod(tokens[9]);
        }

        if (!tokens[11].empty())
        {
            height_of_geoid = std::stod(tokens[11]);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error parsing GGA sentence: " << e.what() << std::endl;
        return false;
    }

    return true;
}

double GNSS::get_latitude() const
{
    return latitude;
}

double GNSS::get_longitude() const
{
    return longitude;
}

int GNSS::get_fix_quality() const
{
    return fix_quality;
}

int GNSS::get_num_satellites() const
{
    return num_satellites;
}

double GNSS::get_hdop() const
{
    return hdop;
}

double GNSS::get_altitude() const
{
    return altitude;
}

double GNSS::get_height_of_geoid() const
{
    return height_of_geoid;
}
