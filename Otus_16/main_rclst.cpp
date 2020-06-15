#include "apartment.h"
#include "trainer.h"
#include <exception>
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

struct Arguments {
    std::size_t Clusters;
    std::string FileName;
};

Arguments GetArguments(int argc, char** argv) {
    if (argc < 3)
        throw std::invalid_argument("Invalid arguments number [<3]");

    std::size_t clusters = std::atoi(argv[1]);
    if (clusters == 0) 
        throw std::invalid_argument(boost::str(boost::format("Invalid clusters number = [%1%]")%argv[1]));

    std::string fileName = argv[2];
    return {clusters, fileName};
}

int main(int argc, char** argv) {
    try {
        const Arguments args = GetArguments(argc, argv);
        auto apartments = GetApartments(std::cin);//подать потов ввода
        const double maxCost = FindMaxCost(apartments);//max = 100, min = cost
        ClusterData clusterData = MakeClassificator(apartments, maxCost, args.Clusters, args.FileName);
        SaveClusteringAppartmentsInfo(clusterData, apartments, args.FileName);
        std::ofstream fileMaxCost(boost::str(boost::format("%1%.max_cost") % args.FileName));
        if (!fileMaxCost || !fileMaxCost.is_open()) {
            std::cout << "Cant open file for writing max cost" << std::endl;
            return 1;
        }
        fileMaxCost << maxCost;
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
		return 1;
    }
    return 0;
}