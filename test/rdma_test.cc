#include <iostream>
#include <memory>
#include "log/debug_info.h"
#include "rdma/rdma_config.h"

int main() {
    try {
        auto machines = rdma::parse_rdma_config("rdma_config.json");
        auto current = machines;
        while (current) {
            std::cout << "IP:" << current->ip << ", Device:" << current->device_name
                      << ", RDMA Port:" << current->ib_port << ", Index:" << current->gid_idx << std::endl;
            current = current->next;
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    genesis_log::debug("something\n", 0);
    return 0;
}
