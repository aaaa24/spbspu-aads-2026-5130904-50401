#include "lciter.hpp"

template< class T >
chernov::LCIter< T >::LCIter(const Node< T > * node, const Node< T > * fake):
  ptr(node),
  fake_(fake)
{}

template< class T >
chernov::LCIter< T >::LCIter():
  ptr(nullptr),
  fake_(nullptr)
{}

template< class T >
bool chernov::LCIter< T >::hasNext() const noexcept
{
  return ptr != nullptr && ptr != fake_;
}

template< class T >
chernov::LCIter< T > chernov::LCIter< T >::next() const
{
  Node< T > * next = ptr->next;
  if (next == fake_) {
    next = fake_->next;
  }
  return {next, fake_};
}

template< class T >
const T & chernov::LCIter< T >::value() const
{
  return ptr->data;
}

template< class T >
const T & chernov::LCIter< T >::operator*() const
{
  return ptr->data;
}

template< class T >
const T * chernov::LCIter< T >::operator->() const
{
  return &(ptr->data);
}

template< class T >
chernov::LCIter< T > & chernov::LCIter< T >::operator++()
{
  ptr = ptr->next;
  if (ptr == fake_) {
    ptr = fake_->next;
  }
  return *this;
}

template< class T >
chernov::LCIter< T > chernov::LCIter< T >::operator++(int)
{
  LCIter old = *this;
  ++(*this);
  return old;
}

template< class T >
bool chernov::LCIter< T >::operator==(const LCIter< T > & other) const noexcept
{
  return ptr == other.ptr;
}

template< class T >
bool chernov::LCIter< T >::operator!=(const LCIter< T > & other) const noexcept
{
  return !(*this == other);
}
