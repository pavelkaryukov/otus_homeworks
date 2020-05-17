#include "lib/bulk_async.h" 

int main() {
    auto handl1 = async::connect(3);
    std::string testCmd = "cmd1";
    async::receive(handl1, testCmd.data(), testCmd.size());
    async::receive(handl1, testCmd.data(), testCmd.size());
    async::receive(handl1, testCmd.data(), testCmd.size());
    async::receive(handl1, testCmd.data(), testCmd.size());
    async::disconnect(handl1);
    return 0;
}