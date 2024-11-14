#include <cstdio>
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <sstream>
#include "rdma/rdma_config.h"


std::string read_file(const std::string& file_name) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::string get_value(const std::string& json, const std::string& key) {
    auto start = json.find("\"" + key + "\":");
    if (start == std::string::npos) return "";
    start = json.find(":", start) + 1;
    auto end = json.find_first_of(",}", start);
    auto value = json.substr(start, end - start);
    std::string cleaned_value;
    for (char c : value) {
        if (c != '\"') {
            cleaned_value += c;
        }
    }
    value = cleaned_value;
    return value;
}

std::shared_ptr<Machine_Info> parse_rdma_config(const std::string& file_name) {
    std::string json = read_file(file_name);

    std::shared_ptr<Machine_Info> head = nullptr;
    std::shared_ptr<Machine_Info> current = nullptr;

    auto machines_start = json.find("\"machines\": [");
    if (machines_start == std::string::npos) return nullptr;
    machines_start = json.find("[", machines_start) + 1;
    auto machines_end = json.find("]", machines_start);

    std::string machines_json = json.substr(machines_start, machines_end - machines_start);
    std::stringstream ss(machines_json);
    std::string machine_json;

    while (std::getline(ss, machine_json, '{')) {
        if (machine_json.find("}") == std::string::npos) continue;
        machine_json = machine_json.substr(0, machine_json.find("}") + 1);

        auto machine_info = std::make_shared<Machine_Info>();
        machine_info->ip = get_value(machine_json, "ip");
        machine_info->device_name = get_value(machine_json, "device_name");
        machine_info->rdma_port = std::stoi(get_value(machine_json, "rdma_port"));
        machine_info->rdma_index = std::stoi(get_value(machine_json, "index"));
        machine_info->next = nullptr;

        if (!head) {
            head = machine_info;
            current = machine_info;
        } else {
            current->next = machine_info;
            current = machine_info;
        }
    }

    return head;
}
