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

    LinkedList(const LinkedList &list) {
        Node *root = list.head.get();

        std::unique_ptr<Node> new_head{nullptr};
        Node *ptr_on_new_head{nullptr};

        while (root) {
            auto temp{std::make_unique<Node>(root->data)};

            if (new_head == nullptr) {
                new_head = std::move(temp);
                ptr_on_new_head = new_head.get();
            } else {
                ptr_on_new_head->next = std::move(temp);
                ptr_on_new_head = ptr_on_new_head->next.get();
            }

            root = root->next.get();
        }

        head = std::move(new_head);
    }

    LinkedList(LinkedList &&list) noexcept {
        head = std::move(list.head);
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