#pragma once
#include "apartment.h"
#include <vector> 
#include <dlib/clustering.h>

namespace trainer {
    using sample_type = dlib::matrix<double, 8, 1>;
    using kernel_type = dlib::radial_basis_kernel<sample_type>;
}

struct ClusterData {
    std::vector<trainer::sample_type> Samples;
    std::vector<unsigned long> Assignments;
};

trainer::sample_type ToSample(const Apartment& aApart, const std::size_t aMaxCost) {
    trainer::sample_type sample;
    sample(0) = aApart.Longitude    ();
    sample(1) = aApart.Latitude     ();
    sample(2) = aApart.Rooms        ();
    sample(3) = aApart.Cost         () / aMaxCost * 100.00;
    sample(4) = aApart.AreaAll      ();
    sample(5) = aApart.AreaKitchen  ();
    sample(6) = ((aApart.Floor() == aApart.NumberOfFloor()) || (aApart.Floor() <= 1)) ? 0 : 1;
    sample(7) = aApart.NumberOfFloor();
    return {};
}


ClusterData FindClusters(const std::vector<Apartment>& aApartments, const std::size_t aMaxCost, const std::size_t aNumberOfClusters) {
    if (aNumberOfClusters == 0)
        throw std::logic_error("Invalid number of clusters == 0");
    ClusterData  data;
    for (int i = 0; i < aApartments.size(); ++i) {
        const auto& apart = aApartments[i];
        data.Samples.push_back(ToSample(apart, aMaxCost));
    }

    dlib::kcentroid<trainer::kernel_type> kc(trainer::kernel_type(0.1), 0.01, 8);
    dlib::kkmeans<trainer::kernel_type> test(kc);

    std::vector<trainer::sample_type> initial_centers;
    test.set_number_of_centers(aNumberOfClusters);
    dlib::pick_initial_centers(aNumberOfClusters, initial_centers, data.Samples, test.get_kernel());
    data.Assignments = spectral_cluster(trainer::kernel_type(0.1), data.Samples, aNumberOfClusters);
    return data;
}
