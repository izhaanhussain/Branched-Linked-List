#ifndef BRANCHED_LINKED_LIST_HPP
#define BRANCHED_LINKED_LIST_HPP

#include <cstddef>
#include <stdexcept>
#include <string>

#include "node.hpp"

class BLL {
public:
  BLL() = default;
  BLL(const BLL& to_copy);
  ~BLL();

  BLL& operator=(const BLL& rhs);
  Node* PushBack(char dat);
  char GetAt(size_t idx) const;
  void SetAt(size_t idx, char dat);
  void Join(size_t idx, BLL* list);
  std::string ToString() const;
  size_t Size() const;
  void CopyHelper(Node* current, Node* copy_current);
  void Copy(const BLL& to_copy);
  void Destruct();
  char TestHead();
  Node* NodeAtIndex(size_t index) const;

private:
  Node* head_ = nullptr;
  bool IsBLLAcyclic() const;
};

#endif
