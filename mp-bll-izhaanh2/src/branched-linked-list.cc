#include "branched-linked-list.hpp"

BLL::BLL(const BLL& to_copy) {
    Copy(to_copy);
}

BLL::~BLL() {
    Destruct();
}

BLL& BLL::operator=(const BLL& rhs) {
    if (this == &rhs) {
        return *this;
    }
    Destruct();
    Copy(rhs);
    return *this;
}

void BLL::Copy(const BLL& to_copy) {
    if (to_copy.head_ != nullptr) {
        head_ = new Node(to_copy.head_ -> data_);
    }
    CopyHelper(head_, to_copy.head_);
}

void BLL::CopyHelper(Node* current, Node* copy_current) {
    if (copy_current == nullptr) {
        return;
    }
    if (copy_current -> next_bll_ != nullptr) {
        current -> next_bll_ = new BLL();
        current -> next_bll_ -> head_ = new Node(copy_current -> next_bll_ -> head_ -> data_);
        CopyHelper(current -> next_bll_ -> head_, copy_current -> next_bll_ -> head_);
    }
    if (copy_current -> next_node_ != nullptr) {
        current -> next_node_ = new Node(copy_current -> next_node_ -> data_);
        CopyHelper(current -> next_node_, copy_current -> next_node_);
    }
}

void BLL::Destruct() {
    while (head_ != nullptr) {
        if (head_ -> next_bll_ != nullptr) {
            head_ -> next_bll_ -> Destruct();
        }
        Node* next = head_ -> next_node_;
        delete head_;
        head_ = next;
    }
}

Node* BLL::PushBack(char dat) {
    if (head_ == nullptr) {
        head_ = new Node(dat);
        return head_;
    } else {
        Node* current = head_;
        while (current -> next_node_ != nullptr) {
            current = current -> next_node_;
        }
        current -> next_node_ = new Node(dat);
        return current -> next_node_;
    }
}

size_t BLL::Size() const {
    size_t ret = 0;
    Node* current = head_;
    while (current != nullptr) {
        ret++;
        if (current -> next_bll_ != nullptr) {
            ret += current -> next_bll_ -> Size();
        } 
        current = current -> next_node_;
    }
    return ret;
}

char BLL::TestHead() {
    return NodeAtIndex(2) -> data_;
}

std::string BLL::ToString() const {
    std::string ret;
    Node* current = head_;
    while (current != nullptr) {
        ret += current -> data_;
        if (current -> next_bll_ != nullptr) {
            ret += current -> next_bll_ -> ToString();
        } 
        current = current -> next_node_;
    }
    return ret;
}

void BLL::Join(size_t idx, BLL* list) {
    if (idx < 0) {
        throw std::invalid_argument("");
    }
    Node* tmp = NodeAtIndex(idx);
    if (NodeAtIndex(idx) -> next_bll_ != nullptr) {
        throw std::invalid_argument("");
    }
    tmp -> next_bll_ = list;
    if (!IsBLLAcyclic()) {
        throw std::invalid_argument("");
    }
}

void BLL::SetAt(size_t idx, char dat) {
    if (idx < 0) {
        throw std::invalid_argument("");
    }
    Node* tmp = NodeAtIndex(idx);
    if (tmp == nullptr) {
        throw std::invalid_argument("");
    }
    tmp -> data_ = dat;
}

char BLL::GetAt(size_t idx) const {
    if (idx < 0) {
        throw std::invalid_argument("");
    }
    Node* tmp = NodeAtIndex(idx);
    if (tmp == nullptr) {
        throw std::invalid_argument("");
    }
    return tmp -> data_;
}

Node* BLL::NodeAtIndex(size_t index) const {
    Node* current = head_;
    size_t counter = 0;
    while (counter < index) {
        if (current -> next_bll_ != nullptr) {
            current = current -> next_bll_ -> head_;
            NodeAtIndex(index - counter);
        } else {
            current = current -> next_node_;
        }
        counter++;
    }
    return current;
}

bool BLL::IsBLLAcyclic() const {
    if (head_ == nullptr) {
        return true;
    }
    Node* tortoise = head_;
    Node* haire = head_ -> next_node_; 
    size_t position = 0;
    while (haire != nullptr) {
        position++;
        if (haire -> next_bll_ != nullptr) {
            haire = haire -> next_bll_ -> head_;
        } else {
            haire = haire -> next_node_;
        }
        if (position % 2 == 0) {
            if (tortoise -> next_bll_ != nullptr) {
                tortoise = tortoise -> next_bll_ -> head_;
            } else {
                tortoise = tortoise -> next_node_;
            }
        }
        if (tortoise == haire) {
            return false;
        }
    }
    return true;
}