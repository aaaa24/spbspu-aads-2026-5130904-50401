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
  fake_->next = fake_;
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
  size_(0)
{
  createFake();
  fake_->next = fake_;
  LIter< T > pos = before_begin();
  for (LIter< T > iter = list.begin(); iter != list.end(); ++iter) {
    insert_after(pos, *iter);
  }
}

template< class T >
chernov::List< T >::List(List< T > && list) noexcept:
  fake_(list.fake_),
  size_(list.size_)
{
  list.fake_ = nullptr;
  list.size_ = 0;
}

template< class T >
chernov::List< T > & chernov::List< T >::operator=(const List< T > & list)
{
  if (this == &list) {
    return *this;
  }
  clear();
  LIter< T > pos = before_begin();
  for (LIter< T > iter = list.begin(); iter != list.end(); ++iter) {
    insert_after(pos, *iter);
  }
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
  list.size_ = 0;
  return *this;
}

template< class T >
chernov::LIter< T > chernov::List< T >::before_begin() const noexcept
{
  return {fake_, fake_};
}

template< class T >
chernov::LCIter< T > chernov::List< T >::cbefore_begin() const noexcept
{
  return {fake_, fake_};
}

template< class T >
chernov::LIter< T > chernov::List< T >::begin() const noexcept
{
  return {fake_->next, fake_};
}

template< class T >
chernov::LCIter< T > chernov::List< T >::cbegin() const noexcept
{
  return {fake_->next, fake_};
}

template< class T >
chernov::LIter< T > chernov::List< T >::end() const noexcept
{
  return {fake_, fake_};
}

template< class T >
chernov::LCIter< T > chernov::List< T >::cend() const noexcept
{
  return {fake_, fake_};
}

template< class T >
bool chernov::List< T >::empty() const noexcept
{
  return size_ == 0;
}

template< class T >
size_t chernov::List< T >::size() const noexcept
{
  return size_;
}

template< class T >
void chernov::List< T >::clear() noexcept
{
  Node< T > * node = fake_->next;
  while (node != fake_) {
    Node< T > * next = node->next;
    delete node;
    node = next;
  }
  fake_->next = fake_;
  size_ = 0;
}

template< class T >
chernov::LIter< T > chernov::List< T >::insert_after(LIter< T > pos, const T & value)
{
  Node< T > * node = new Node< T >(value, pos.ptr->next);
  pos.ptr->next = node;
  ++size_;
  return {node, fake_};
}

template< class T >
chernov::LIter< T > chernov::List< T >::insert_after(LIter< T > pos, T && value)
{
  Node< T > * node = new Node< T >(std::move(value), pos.ptr->next);
  pos.ptr->next = node;
  ++size_;
  return {node, fake_};
}

template< class T >
chernov::LIter< T > chernov::List< T >::erase_after(LIter< T > pos)
{
  if (pos.ptr == nullptr || pos.ptr == fake_ && fake_->next == fake_) {
    return end();
  }
  Node< T > * del_node = pos.ptr->next;
  if (del_node == fake_) {
    pos.ptr = fake_;
    del_node = fake_->next;
    if (del_node == fake_) {
      return end();
    }
  }
  pos.ptr->next = del_node->next;
  delete del_node;
  --size_;
  return {pos.ptr->next, fake_};
}

template< class T >
chernov::LIter< T > chernov::List< T >::erase_after(LIter< T > first, LIter< T > last)
{
  while (!empty() && first.ptr->next != last.ptr) {
    erase_after(first);
  }
  return last;
}

template< class T >
void chernov::List< T >::push_front(const T & value)
{
  insert_after(fake_, value);
}

template< class T >
void chernov::List< T >::push_front(T && value)
{
  insert_after(fake_, std::move(value));
}
