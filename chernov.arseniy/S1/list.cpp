#include "list.hpp"

template< class T >
chernov::Node< T > * chernov::List< T >::createFake()
{
  fake_ = static_cast< Node< T > * >(::operator new (sizeof(Node< T > *)));
  return fake_;
}

template< class T >
void chernov::List< T >::removeFake() noexcept
{
  ::operator delete(fake_);
}

template< class T >
chernov::List< T >::List():
  fake_(nullptr),
  size_(0)
{
  createFake();
}

template< class T >
chernov::List< T >::~List() noexcept
{
  clear();
  removeFake();
}

template< class T >
chernov::List< T >::List(const List< T > & list):
  fake_(nullptr),
  size_(list.size_)
{
  createFake();
  // ...
}

template< class T >
chernov::List< T >::List(List< T > && list) noexcept:
  fake_(list.fake_),
  size_(list.size_)
{
  list.fake_ = nullptr;
}

template< class T >
chernov::List< T > & chernov::List< T >::operator=(const List< T > & list)
{
  if (this == &list) {
    return *this;
  }
  // ...
  clear();
  removeFake();
  // ...
  size_ = list.size_;
  return *this;
}

template< class T >
chernov::List< T > & chernov::List< T >::operator=(List< T > && list) noexcept
{
  if (this == &list) {
    return *this;
  }
  clear();
  removeFake();
  fake_ = list.fake_;
  size_ = list.size_;
  list.fake_ = nullptr;
  return *this;
}

template< class T >
chernov::LIter< T > chernov::List< T >::before_begin() const noexcept
{
  return {fake_};
}

template< class T >
chernov::LCIter< T > chernov::List< T >::cbefore_begin() const noexcept
{
  return {fake_};
}

template< class T >
chernov::LIter< T > chernov::List< T >::begin() const noexcept
{
  return {fake_->next};
}

template< class T >
chernov::LCIter< T > chernov::List< T >::cbegin() const noexcept
{
  return {fake_->next};
}

template< class T >
bool chernov::List< T >::empty() const noexcept
{
  return size_ != 0;
}

template< class T >
size_t chernov::List< T >::size() const noexcept
{
  return size_;
}


template< class T >
void chernov::List< T >::clear() noexcept
{
  Node< T > * node = fake_;
  while (node != fake->next) {
    Node< T > * next = node->next;
    delete node;
    node = next;
  }
  size_ = 0;
  fake_->next = nullptr;
}

template< class T >
chernov::LIter< T > chernov::List< T >::insert_after(LIter< T > pos, const T & value)
{
  Node< T > * node = new Node< T >(value, pos.ptr->next);
  if (node->next == nullptr) {
    node->next = node;
  }
  pos.ptr->next = node;
  ++size_;
  return {node};
}

template< class T >
chernov::LIter< T > chernov::List< T >::insert_after(LIter< T > pos, T && value)
{
  Node< T > * node = new Node< T >(std::move(value), pos.ptr->next);
  if (node->next == nullptr) {
    node->next = node;
  }
  pos.ptr->next = node;
  ++size_;
  return {node};
}

template< class T >
chernov::LIter< T > chernov::List< T >::erase_after(LIter< T > pos)
{
  if (pos.ptr == nullptr || pos.ptr->next == nullptr) {
    return {nullptr};
  }
  Node< T > * del_node = pos.ptr->next;
  Node< T > * next = del_node->next;
  pos.ptr->next = del_node == next ? nullptr : next;
  delete del_node;
  --size_;
  return {pos.ptr->next};
}

template< class T >
chernov::LIter< T > chernov::List< T >::erase_after(LIter< T > first, LIter< T > last)
{
  while (first.ptr->next != nullptr && first.ptr->next != last.ptr) {
    erase_after(first);
  }
  return last;
}
