#pragma once
#include "apartment.h"
#include <dlib/clustering.h>       
#include <boost/format.hpp>

namespace trainer {
    using sample_type = dlib::matrix<double, 8, 1>;
    using kernel_type = dlib::radial_basis_kernel<sample_type>;
}

double GetDistance(const trainer::sample_type& aSample1, const trainer::sample_type& aSample2) {
    double res = 0; 
    for (int i = 0; i < 8; ++i) {
        res += std::abs(aSample1(i) * aSample1(i) - aSample2(i) * aSample2(i));
    }

    return std::sqrt(res);
}

struct ClusterData {
    std::vector<trainer::sample_type> Samples;
    std::vector<unsigned long> Labels;
};

trainer::sample_type ToSample(const Apartment& aApart, const double aMaxCost) {
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


ClusterData MakeClassificator(
    const std::vector<Apartment>& aApartments, 
    const std::size_t aMaxCost, 
    const std::size_t aNumberOfClusters, 
    const std::string aFileName
) {
    if (aNumberOfClusters == 0)
        throw std::logic_error("Invalid number of clusters == 0");
    ClusterData  data;
    std::for_each(aApartments.cbegin(), aApartments.cend(), 
                  [&data, &aMaxCost](const auto& apart) { data.Samples.push_back(ToSample(apart, aMaxCost)); } );

    dlib::kcentroid<trainer::kernel_type> kc(trainer::kernel_type(0.000001), 0.01, 16);
    dlib::kkmeans<trainer::kernel_type> kktrainer(kc);

    std::vector<trainer::sample_type> initial_centers;
    kktrainer.set_number_of_centers(aNumberOfClusters);
    dlib::pick_initial_centers(aNumberOfClusters, initial_centers, data.Samples, kktrainer.get_kernel());
    kktrainer.train(data.Samples, initial_centers);
    dlib::serialize(boost::str(boost::format("%1%.classificator") % aFileName)) << kktrainer;
    for (const auto& sample : data.Samples) {
        data.Labels.push_back(kktrainer(sample));
    }
    return data;
}