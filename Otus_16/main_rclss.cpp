#include "apartment.h"
#include "trainer.h"
#include <map>

std::multimap<double, std::string> GetClosedApartements(
    const std::string aFileName, 
    const trainer::sample_type& aSample,
    const double aMaxCost
) { 
    std::ifstream file(aFileName);
    if (!file || !file.is_open()) {
        std::cout << boost::format("Cant open file [%1%]") % aFileName << std::endl;
        return {};
    }
    std::multimap<double, std::string> apartments;
    std::string str;
    while (std::getline(file, str)) {
        const auto apartment = Apartment(str);
        const auto sample = ToSample(apartment, aMaxCost);
        const auto distance = GetDistance(aSample, sample);
        if (apartment.IsValid())
            apartments.insert({ distance, apartment.Serialize() });
    }
    return apartments;
}

void Process(std::istream& aStream, const std::string aFileName) {
    if (!aStream)
        throw std::logic_error("stream was corrupted");
    const double maxCost = FindMaxCost(aFileName);

    dlib::kcentroid<trainer::kernel_type> kc(trainer::kernel_type(0.000001), 0.01, 16);
    dlib::kkmeans<trainer::kernel_type> kktrainer(kc);
    dlib::deserialize(boost::str(boost::format("%1%.classificator") % aFileName)) >> kktrainer;
    
    std::string str;
    while (std::getline(aStream, str)) {
        const auto sample = ToSample(Apartment(str), maxCost); 
        const auto label = kktrainer(sample);                  
        const std::string lblFileName = boost::str(boost::format("%1%.data.%2%") % aFileName % label);
        auto apartments = GetClosedApartements(lblFileName, sample, maxCost);
        for (auto iter = apartments.cbegin(); iter != apartments.cend(); ++iter) {
                std::cout << iter->second << std::endl;
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 2){
        std::cout << "Invalid number of arguments" << std::endl;
        return 1;
    }
    std::string filename = std::string(argv[1]);
    
    try {
        Process(std::cin, filename);
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}