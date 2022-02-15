#include <memory>
#include <iostream>


struct Node {
    int data;
    std::unique_ptr<Node> next;

    Node(int data)
        : data{data}
        , next{nullptr}
    { }

    //TODO delete this shit later
    ~Node() {
        std::cout << "Destroy Node with data: " << data << std::endl;
    }
};

class LinkedList {
public:
    LinkedList()
        : head{nullptr}
    { }

    void push(int data) {
        auto temp{std::make_unique<Node>(data)};

        if (head) {
            temp->next = std::move(head);
            head = std::move(temp);
        } else {
            head = std::move(temp);
        }
    }

private:
    std::unique_ptr<Node> head;
};


int main() {
    LinkedList list;

    list.push(0);
    list.push(1);
    list.push(2);
    list.push(3);
    list.push(4);
}