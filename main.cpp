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

    friend std::ostream& operator<<(std::ostream& ostream, const LinkedList& list);

private:
    std::unique_ptr<Node> head;
};

std::ostream& operator<<(std::ostream& ostream, const LinkedList& list) {
    Node* head = list.head.get();

    while (head) {
        ostream << head->data << ' ';
        head = head->next.get();
    }

    return ostream;
}

int main() {
    LinkedList list;

    std::cout << "empty list" << std::endl;
    std::cout << list << std::endl;
    std::cout << "==========" << std::endl;

    for (size_t i = 0; i < 10; ++i) {
        list.push(static_cast<int>(i));
    }

    std::cout << "filled list" << std::endl;
    std::cout << list << std::endl;
    std::cout << "==========" << std::endl;

    list.clean();

    std::cout << "empty list" << std::endl;
    std::cout << list << std::endl;
    std::cout << "==========" << std::endl;
}