#include "apartment.h"
#include "trainer.h"
#include <exception>
#include <fstream>
#include <iostream>
#include <string>

void SaveClusteringAppartmentsInfo(const ClusterData& aData, const std::vector<Apartment>& aApartments, const std::string aFileName) {
    const auto len = std::min(std::min(aData.Samples.size(), aData.Labels.size()), aApartments.size());
    std::map<std::size_t, std::ofstream> fileStreams;
    for (std::size_t i = 0U; i < len; ++i) {
        const std::size_t label = aData.Labels[i];
        auto fileIter = fileStreams.find(label);
        if (fileIter == fileStreams.end()) {
            const std::string fileName = boost::str(boost::format("%1%.data.%2%") % aFileName % label);
            auto res = fileStreams.insert({ label, std::ofstream(fileName) });
            if (!res.second)
                continue;
            fileIter = res.first;
        }
        fileIter->second << aApartments[i].Serialize() << std::endl;
    }
}

int main(int argc, char** argv) {
    //std::locale::global(std::locale(""));
    //получили кол-во кластеров и имя файла 
    try {
        std::ifstream file("16.dataset-12995-8e405d.csv");
        if (!file || !file.is_open()) {
            std::cout << "не удается открыть файл" << std::endl;
            return 1;
        }
        std::string fileName = "model_set1";  //argc fill
        std::size_t clustersNumber = 100;     //argc fill
        auto apartments = GetApartments(file);//подать потов ввода
        file.close();
        const double maxCost = FindMaxCost(apartments);//max = 100, min = cost
        const double percentCost = maxCost / 100.00;//TODO:: DELETE
        ClusterData clusterData = MakeClassificator(apartments, maxCost, clustersNumber, fileName);
        SaveClusteringAppartmentsInfo(clusterData, apartments, fileName);
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}