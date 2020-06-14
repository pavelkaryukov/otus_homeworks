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
    std::vector<std::size_t> Labels;
};

trainer::sample_type ToSample(const Apartment& aApart, const std::size_t aMaxCost) {
    trainer::sample_type sample;
    sample(0) = aApart.Longitude    ();
    sample(1) = aApart.Latitude     ();
    sample(2) = aApart.Rooms        ();
    sample(3) = (aApart.Cost        () / aMaxCost) * 100.00;
    sample(4) = aApart.AreaAll      ();
    sample(5) = aApart.AreaKitchen  ();
    sample(6) = ((aApart.Floor() == aApart.NumberOfFloor()) || (aApart.Floor() <= 1)) ? 0 : 1;
    sample(7) = aApart.NumberOfFloor();
    return sample;
}


ClusterData FindClusters(const std::vector<Apartment>& aApartments, const std::size_t aMaxCost, const std::size_t aNumberOfClusters) {
    if (aNumberOfClusters == 0)
        throw std::logic_error("Invalid number of clusters == 0");
    ClusterData  data;
    std::for_each(aApartments.cbegin(), aApartments.cend(), 
                  [&data, &aMaxCost](const auto& apart) { data.Samples.push_back(ToSample(apart, aMaxCost)); } );

    dlib::kcentroid<trainer::kernel_type> kc(trainer::kernel_type(0.000001), 0.01, 16);
    dlib::kkmeans<trainer::kernel_type> test(kc);

    std::vector<trainer::sample_type> initial_centers;
    test.set_number_of_centers(aNumberOfClusters);
    dlib::pick_initial_centers(aNumberOfClusters, initial_centers, data.Samples, test.get_kernel());
    test.train(data.Samples, initial_centers);

    //auto vec = dlib::spectral_cluster(trainer::kernel_type(0.1), std::vector<trainer::sample_type>{ data.Samples.begin(), data.Samples.begin() + 100 }, initial_centers.size());
    for (const auto& sample : data.Samples) {
        data.Labels.push_back(test(sample));
    }
    //auto vec = dlib::spectral_cluster(trainer::kernel_type(0.1), data.Samples, initial_centers.size());
    return data;
}
