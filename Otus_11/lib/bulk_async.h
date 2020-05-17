#pragma once
#include <cctype>
#include <iostream>

namespace async {

    using handle_t = std::uint64_t;

    handle_t connect(std::size_t bulk, std::ostream& aOutStream = std::cout);
    void receive(handle_t handle, const char *data, std::size_t size);
    void disconnect(handle_t handle);

}