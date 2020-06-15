#pragma once
#include "apartment.h"
#include <vector> 
#include <dlib/clustering.h>        
//#include <dlib/svm_threaded.h>
#include <boost/format.hpp>

namespace trainer {
    using sample_type = dlib::matrix<double, 8, 1>;
    using kernel_type = dlib::radial_basis_kernel<sample_type>;
    //using ovo_trainer = dlib::one_vs_one_trainer<dlib::any_trainer<sample_type>>;
    //using poly_kernel =  dlib::polynomial_kernel<sample_type>;
    //using rbf_kernel  = dlib::radial_basis_kernel<sample_type>;
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



//TODO::DELETE
bool CheckDeserialize(ClusterData& aData) {
    dlib::kcentroid<trainer::kernel_type> kc(trainer::kernel_type(0.000001), 0.01, 16);
    dlib::kkmeans<trainer::kernel_type> test(kc);
    dlib::deserialize("mega_model.class") >> test;

    for (int i = 0; i < std::min(aData.Samples.size(), aData.Labels.size()); ++i) {
        aData.Samples[i](0) += 0.001;
        aData.Samples[i](1) -= 0.001;
        auto label = test(aData.Samples[i]);
        if (label != aData.Labels[i])
            continue;;
    }
    return true;
}

////dlib::one_vs_one_decision_function<trainer::ovo_trainer> 
//bool GetDecissionFunc(ClusterData& aData) {
//    std::for_each(aData.Labels.begin(), aData.Labels.end(), [](auto& a) {++a; });
////     for (auto& ll : aData.Labels) {
////         //ll += 1;
////         if (ll < 1.00)
////             std::cout << "label < 1" << std::endl;
////     }
//    trainer::ovo_trainer trainer;
//    
//    dlib::krr_trainer<trainer::rbf_kernel> rbf_trainer;
//    dlib::svm_nu_trainer<trainer::poly_kernel> poly_trainer;
//    poly_trainer.set_kernel(trainer::poly_kernel(0.1, 1, 8));
//    rbf_trainer.set_kernel(trainer::rbf_kernel(0.1));
//    trainer.set_trainer(rbf_trainer);
//    //trainer.set_trainer(poly_trainer, 1, 8);
//    try
//    {
//        std::cout << cross_validate_multiclass_trainer(trainer, aData.Samples, aData.Labels, 1) << std::endl;
//    }
//    catch (std::exception& e)
//    {
//        std::cout << e.what() << std::endl;
//    	
//    }
//    dlib::one_vs_one_decision_function<trainer::ovo_trainer> df = trainer.train(aData.Samples, aData.Labels);
//    std::cout << "Decission Function was trained" << std::endl;
//    return {};
//}