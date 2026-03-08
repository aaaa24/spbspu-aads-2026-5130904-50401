#include "liter.hpp"

template< class T >
chernov::LIter< T >::LIter(Node< T > * node, Node< T > * fake):
  ptr(node),
  fake_(fake)
{}

template< class T >
chernov::LIter< T >::LIter():
  ptr(nullptr),
  fake_(nullptr)
{}

template< class T >
bool chernov::LIter< T >::hasNext() const noexcept
{
  return ptr != nullptr && ptr != fake_;
}

template< class T >
chernov::LIter< T > chernov::LIter< T >::next() const
{
  Node< T > * next = ptr->next;
  if (next == fake_) {
    next = fake_->next;
  }
  return {next, fake_};
}

template< class T >
T & chernov::LIter< T >::value() const
{
  return ptr->data;
}

template< class T >
T & chernov::LIter< T >::operator*() const
{
  return ptr->data;
}

template< class T >
T * chernov::LIter< T >::operator->() const
{
  return &(ptr->data);
}

template< class T >
chernov::LIter< T > & chernov::LIter< T >::operator++()
{
  ptr = ptr->next;
  if (ptr == fake_) {
    ptr = fake_->next;
  }
  return *this;
}

template< class T >
chernov::LIter< T > chernov::LIter< T >::operator++(int)
{
  LIter old = *this;
  ++(*this);
  return old;
}

template< class T >
bool chernov::LIter< T >::operator==(const LIter< T > & other) const noexcept
{
  return ptr == other.ptr;
}

template< class T >
bool chernov::LIter< T >::operator!=(const LIter< T > & other) const noexcept
{
  return !(*this == other);
}
