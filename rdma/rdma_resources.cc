class rdma_resources {
public:
    rdma_resources();
    ~rdma_resources();

    bool initialize();
    void cleanup();

private:
    // Add private member variables and methods as needed
};