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
    void reverse();

    LinkedList(const LinkedList& list) {
        Node* root = list.head.get();

        std::unique_ptr<Node> new_head{nullptr};
        Node* ptr_on_new_head{nullptr};

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

    LinkedList(LinkedList&& list) noexcept {
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

void LinkedList::reverse() {
    LinkedList temp;
    Node* root = head.get();

    while (root) {
        temp.push(root->data);
        root = root->next.get();
    }

    clean();
    head = std::move(temp.head);
}

auto main() -> int {
    LinkedList list;

    for (size_t i = 0; i < 15; ++i) {
        list.push(static_cast<int>(i));
    }

    std::cout << "list with pushed data: " << list << std::endl;

    list.clean();
    std::cout << "cleaned list data: " << list << std::endl;

    list.push(-1);
    list.push(-2);
    list.push(-3);
    list.push(-4);
    list.push(-5);
    list.push(-6);
    std::cout << "list with pushed data: " << list << std::endl;

    LinkedList list1 = list;
    std::cout << "list1 (copy semantic): " << list1 << std::endl;

    LinkedList list2 = std::move(list1);
    std::cout << "list: " << list << std::endl;
    std::cout << "list2 (move semantic): " << list2 << std::endl;

    list2.reverse();
    std::cout << "reserved list2: " << list2 << std::endl;
}