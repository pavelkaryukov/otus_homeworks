#include "apartment.h"
#include "trainer.h"
#include <exception>
#include <fstream>
#include <iostream>
#include <string>


int main(int argc, char** argv) {
    //std::locale::global(std::locale(""));
    //получили кол-во кластеров и имя файла 
    try {
        std::ifstream file("16.dataset-12995-8e405d.csv");
        if (!file || !file.is_open()) {
            std::cout << "не удается открыть файл" << std::endl;
            return 1;
        }
        std::string fileName = "model_set1";
        std::size_t clustersNumber = 100;
        auto apartments = GetApartments(file);
        const double maxCost = FindMaxCost(apartments);//max = 100, min = cost
        const double percentCost = maxCost / 100.00;//TODO:: DELETE
        ClusterData clusterData = FindClusters(apartments, maxCost, clustersNumber);
        //Сделать кластеры
        //натренировать классификатор
        //сохранить классификатор
        //сохранить данные
        
        int stop1 = 0;
    }
    catch (std::exception& e) {

    }
    return 0;
}