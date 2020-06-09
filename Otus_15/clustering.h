#pragma once
#include <boost/format.hpp>
#include <dlib/clustering.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

namespace cluster {
    using coord_t = std::pair<double, double>;
    using sample_t = dlib::matrix<double, 2, 1>;
    using kernel_t = dlib::radial_basis_kernel<sample_t>;

    void CalcClusters(std::vector<coord_t>& aCoords, const std::size_t aCentersNumber, std::ostream& aOstream) {
        if (aCoords.empty() || aCentersNumber == 0)
            return;
        dlib::kcentroid<kernel_t > kc(kernel_t(0.1), 0.01, 8);
        dlib::kkmeans<kernel_t> test(kc);

        std::vector<sample_t> samples;
        std::vector<sample_t> initial_centers;
        sample_t m;
        for (const auto& coord : aCoords) {
            m(0) = coord.first;
            m(1) = coord.second;
            samples.push_back(m);
        }
        test.set_number_of_centers(aCentersNumber);
        dlib::pick_initial_centers(aCentersNumber, initial_centers, samples, test.get_kernel());
        test.train(samples, initial_centers);
        for (std::size_t i = 0U; i < aCentersNumber; ++i) {
            std::cout << boost::format("centroid[%1%]; size[%2%];") % i % test.get_kcentroid(i).dictionary_size() << std::endl;
        }
        std::vector<unsigned long> assignments = spectral_cluster(kernel_t(0.1), samples, aCentersNumber);
        
        const auto size = std::min(assignments.size(), samples.size());
        for (auto i = 0U; i < size; ++i) {
            if (aOstream)
                aOstream << boost::format("%1%;%2%;%3%") % samples[i](0) % samples[i](1) % assignments[i] << std::endl;
            else 
                break;;
        }
    }
}