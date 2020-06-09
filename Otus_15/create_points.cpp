#include <boost/format.hpp> 
#include <dlib/rand.h>
#include <fstream>


void MakeStars() {
    std::ofstream file("stars.txt");
    if (!file || !file.is_open()) {
        std::cout << "cant open file stars.txt" << std::endl;
    }
    auto randomizer = dlib::rand();
    const double minCoord = -100;
    const double maxCoord = 100;

    for (int i = 0; i < 200; ++i) {
        const auto x = randomizer.get_double_in_range(minCoord, maxCoord);
        const auto y = randomizer.get_double_in_range(minCoord, maxCoord);
        file << boost::format("%1$.2f;%2$.2f") % x % y << std::endl;
    }
}


void MakeKKmeans() {
    std::ofstream file("kkmeans_ex.txt");
    if (!file || !file.is_open()) {
        std::cout << "cant open file stars.txt" << std::endl;
    }
    auto randomizer = dlib::rand();
    
    for (int i = 0; i < 50; ++i) {
        const double xCentr = 22.0;
        const double yCentr = 30.0;
        const double radius = 5;
        const auto x = xCentr + randomizer.get_double_in_range(-radius, radius);
        const auto y = yCentr + randomizer.get_double_in_range(-radius, radius);
        file << boost::format("%1$.2f;%2$.2f") % x % y << std::endl;
    }


    for (int i = 0; i < 50; ++i) {
        const double xCentr = 120.0;
        const double yCentr = -40.0;
        const double radius = 10;
        const auto x = xCentr + randomizer.get_double_in_range(-radius, radius);
        const auto y = yCentr + randomizer.get_double_in_range(-radius, radius);
        file << boost::format("%1$.2f;%2$.2f") % x % y << std::endl;
    }

    for (int i = 0; i < 50; ++i) {
        const double xCentr = 0.0;
        const double yCentr = 0.0;
        const double radius = 3;
        const auto x = xCentr + randomizer.get_double_in_range(-radius, radius);
        const auto y = yCentr + randomizer.get_double_in_range(-radius, radius);
        file << boost::format("%1$.2f;%2$.2f") % x % y << std::endl;
    }

    for (int i = 0; i < 50; ++i) {
        const double xCentr = -90.0;
        const double yCentr = -80.0;
        const double radius = 10;
        const auto x = xCentr + randomizer.get_double_in_range(-radius, radius);
        const auto y = yCentr + randomizer.get_double_in_range(-radius, radius);
        file << boost::format("%1$.2f;%2$.2f") % x % y << std::endl;
    }

}

int main() {
    MakeStars();
    MakeKKmeans();
    return 0;
}