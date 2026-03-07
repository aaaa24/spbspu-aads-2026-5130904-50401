#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>

#include "liter.hpp"
#include "lciter.hpp"

namespace chernov {
  template< class T >
  class Node {
    T data;
    Node< T > * next;
  };

  template< class T >
  class List {
    Node< T > * fake_;
    size_t size_;
    Node< T > * createFake();
    void removeFake() noexcept;
  public:
    List();
    ~List() noexcept;
    List(const List< T > & list);
    List(List< T > && list);
    List< T > & operator=(const List< T > & list);
    List< T > & operator=(List< T > && list);
    
    LIter< T > before_begin() const noexcept;
    LCIter< T > cbefore_begin() const noexcept;
    LIter< T > begin() const noexcept;
    LCIter< T > cbegin() const noexcept;
    bool empty() const noexcept;
    size_t size() const noexcept;
    void clear() noexcept;
    LIter< T > insert_after(LIter< T > pos, const T & value);
    LIter< T > insert_after(LIter< T > pos, T && value);
  };
}

#endif
