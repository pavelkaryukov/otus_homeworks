#include <boost/format.hpp> 
#include <dlib/rand.h>
#include <fstream>
#include <algorithm>

int main() {
    std::ofstream file("stars.txt");
    if (!file || !file.is_open()) {
        std::cout << "cant open file stars.txt" << std::endl;
        return 1;
    }
    auto randomizer = dlib::rand();
    const double minCoord = -100;
    const double maxCoord = 100;

    for (int i = 0; i < 200; ++i) {
        const auto x = randomizer.get_double_in_range(minCoord, maxCoord);
        const auto y = randomizer.get_double_in_range(minCoord, maxCoord);
        file << boost::format("%1$.2f;%2$.2f") % x % y << std::endl;
    }
    return 0;
}