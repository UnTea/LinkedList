#include <iostream>
#include <memory>

struct Node {
    int data;
    std::unique_ptr<Node> next;

    explicit Node(int data)
        : data{data}
        , next{nullptr} { }
};

class LinkedList {
public:
    LinkedList()
        : head{nullptr} { }

    void push(int data);
    void pop();
    void clean();

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

void LinkedList::push(int data) {
    auto temp{std::make_unique<Node>(data)};

    if (head) {
        temp->next = std::move(head);
        head = std::move(temp);
    } else {
        head = std::move(temp);
    }
}

void LinkedList::pop() {
    if (head == nullptr) {
        return;
    }

    std::unique_ptr<Node> temp = std::move(head);
    head = std::move(temp->next);
}

void LinkedList::clean() {
    while (head) {
        head = std::move(head->next);
    }
}

auto main() -> int {
    LinkedList list;

    list.push(-10);
    std::cout << list << std::endl;

    list.pop();
    std::cout << list << std::endl;

    for (size_t i = 0; i < 10; ++i) {
        list.push(static_cast<int>(i));
    }

    std::cout << list << std::endl;

    list.pop();
    list.pop();
    list.pop();

    std::cout << list << std::endl;
}