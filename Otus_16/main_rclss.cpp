#include <string>
#include <exception>
#include <iostream>
#include "apartment.h"
#include "trainer.h"

void Process(std::istream& aStream, const std::string aFileName) {
    const std::size_t maxCost = 10000000;
    if (!aStream)
        throw std::logic_error("stream was corrupted");
    
    dlib::kcentroid<trainer::kernel_type> kc(trainer::kernel_type(0.000001), 0.01, 16);
    dlib::kkmeans<trainer::kernel_type> kktrainer(kc);
    dlib::deserialize(boost::str(boost::format("%1%.classificator") % aFileName)) >> kktrainer;
    std::string str;
    while (std::getline(aStream, str)) {
        auto apartment = Apartment(str);
        auto sample = ToSample(apartment, maxCost); //далее  работаем с sample
        auto label = kktrainer(sample);//maxCost хранить в первой строкой в .0
        int stop1 = 0;
    }
}

int main(int argc, char** argv) {
    try {
        std::string filename = "model_set1";
        std::ifstream file("c:\\my_programs\\otus\\otus_homeworks_all_2\\tasks\\perchik.csv");
        Process(file/*std::cin*/, filename);
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }


    return 0;
}