#include <iostream>
#include <memory>
#include "rdma/rdma_config.h"

int main() {
    try {
        auto machines = parse_rdma_config("/home/hongkang/genesis/rdma_config.json");
        auto current = machines;
        while (current) {
            std::cout << "IP:" << current->ip << ", Device:" << current->device_name
                      << ", RDMA Port:" << current->rdma_port << ", Index:" << current->rdma_index << std::endl;
            current = current->next;
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
