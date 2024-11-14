#ifndef RDMA_CONFIG_H
#define RDMA_CONFIG_H

#include <memory>
#include <string>

namespace rdma {

// Get from show_gids command
struct Node_Info {
    std::string ip;
    std::string device_name;
    int ib_port;
    int gid_idx;
    std::shared_ptr<Node_Info> next;
};

std::shared_ptr<Node_Info> parse_rdma_config(const std::string& file_name);

} // namespace rdma

#endif // RDMA_CONFIG_H
