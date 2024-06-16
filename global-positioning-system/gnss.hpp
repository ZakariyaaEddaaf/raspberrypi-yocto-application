#ifndef GNSS_HPP
#define GNSS_HPP

#include <string>
#include <vector>

class GNSS
{
    public:
        GNSS();
        ~GNSS();
        std::string catch_gpgga_gngga(const std::string& data);
        bool parse_gpgga_gngga(const std::string& sentence);
        double get_latitude() const;
        double get_longitude() const;
        int get_fix_quality() const;
        int get_num_satellites() const;
        double get_hdop() const;
        double get_altitude() const;
        double get_height_of_geoid() const;

    private:
        double latitude;
        double longitude;
        int fix_quality;
        int num_satellites;
        double hdop;
        double altitude;
        double height_of_geoid;
        std::vector<std::string> split(const std::string& s, char delimiter);
};

#endif // GNSS_HPP