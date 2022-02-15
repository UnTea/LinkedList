#include <memory>


struct Node {
    int data;
    std::unique_ptr<Node> next;

    Node(int data)
        : data{data}
        , next{nullptr}
    { }
};

int main() {
    auto first_node{std::make_unique<Node>(1)};

    auto second_node{std::make_unique<Node>(2)};
    second_node->next = std::move(first_node);

    auto third_node{std::make_unique<Node>(3)};
    third_node->next = std::move(second_node);
}