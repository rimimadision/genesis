#ifndef RDMA_CONFIG_H
#define RDMA_CONFIG_H

#include <memory>
#include <string>

struct Machine_Info {
    std::string ip;
    std::string device_name;
    int rdma_port;
    int rdma_index;
    std::shared_ptr<Machine_Info> next;
};

std::string read_file(const std::string& file_name);
std::string get_value(const std::string& json, const std::string& key);
std::shared_ptr<Machine_Info> parse_rdma_config(const std::string& file_name);

#endif // RDMA_CONFIG_H
