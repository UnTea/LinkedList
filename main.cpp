#include <iostream>
#include <memory>

struct Node {
    int data;
    std::unique_ptr<Node> next;

    Node(int data)
        : data{data}
        , next{nullptr} { }
};

class LinkedList {
public:
    LinkedList()
        : head{nullptr} { }

    void push(int data) {
        auto temp{std::make_unique<Node>(data)};

        if (head) {
            temp->next = std::move(head);
            head = std::move(temp);
        } else {
            head = std::move(temp);
        }
    }

    void clean() {
        while (head) {
            head = std::move(head->next);
        }
    }

    ~LinkedList() {
        clean();
    }

private:
    std::unique_ptr<Node> head;
};

int main() {
    LinkedList list;

    //    list.push(0);
    //    list.push(1);
    //    list.push(2);
    //    list.push(3);
    //    list.push(4);

    for (size_t i = 0; i < 1'000'000; ++i) {
        list.push(static_cast<int>(i));
    }
}