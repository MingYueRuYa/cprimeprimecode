/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Hewlett-Packard Company makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 *
 * Copyright (c) 1996
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

/* NOTE: This is an internal header file, included by other STL headers.
 *   You should not attempt to use it directly.
 */

#ifndef __SGI_STL_INTERNAL_VECTOR_H
#define __SGI_STL_INTERNAL_VECTOR_H

__STL_BEGIN_NAMESPACE 

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma set woff 1174
#endif

template <class T, class Alloc = alloc>  // 預設使用 alloc 為配置器
class vector {
public:
  // 以下標示 (1),(2),(3),(4),(5)，代表 iterator_traits<I> 所服務的5個型別。
  typedef T value_type;				// (1)
  typedef value_type* pointer; 			// (2)
  typedef const value_type* const_pointer;
  typedef const value_type* const_iterator;
  typedef value_type& reference; 		// (3)
  typedef const value_type& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type; 	// (4)
  // 以下，由於vector 所維護的是一個連續線性空間，所以不論其元素型別為何，
  // 原生指標都可以做為其迭代器而滿足所有需求。
  typedef value_type* iterator;
  /* 根據上述寫法，如果客端寫出這樣的碼：
      vector<Shape>::iterator is;
      is 的型別其實就是Shape*
      而STL 內部運用 iterator_traits<is>::reference 時，獲得 Shape&
                 運用iterator_traits<is>::iterator_category 時，獲得 
                      random_access_iterator_tag		(5)
      （此乃iterator_traits 針對原生指標的特化結果）
  */

#ifdef __STL_CLASS_PARTIAL_SPECIALIZATION
  typedef reverse_iterator<const_iterator> const_reverse_iterator;
  typedef reverse_iterator<iterator> reverse_iterator;
#else /* __STL_CLASS_PARTIAL_SPECIALIZATION */
  typedef reverse_iterator<const_iterator, value_type, const_reference, 
                           difference_type>  const_reverse_iterator;
  typedef reverse_iterator<iterator, value_type, reference, difference_type>
          _reverse_iterator;
#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */
protected:
  // 專屬之空間配置器，每次配置一個元素大小
  typedef simple_alloc<value_type, Alloc> data_allocator;

  // vector採用簡單的線性連續空間。以兩個迭代器start和end分別指向頭尾，
  // 並以迭代器end_of_storage指向容量尾端。容量可能比(尾-頭)還大，
  // 多餘即備用空間。
  iterator start;
  iterator finish;
  iterator end_of_storage;

  void insert_aux(iterator position, const T& x);
  void deallocate() {
    if (start)
         data_allocator::deallocate(start, end_of_storage - start);
  }

  void fill_initialize(size_type n, const T& value) {
    start = allocate_and_fill(n, value);  // 配置空間並設初值
    finish = start + n;				// 調整水位
    end_of_storage = finish; 			// 調整水位
  }
public:
  iterator begin() { return start; }
  const_iterator begin() const { return start; }
  iterator end() { return finish; }
  const_iterator end() const { return finish; }
  _reverse_iterator rbegin() { return _reverse_iterator(end()); }
  const_reverse_iterator rbegin() const { 
    return const_reverse_iterator(end()); 
  }
  _reverse_iterator rend() { return _reverse_iterator(begin()); }
  const_reverse_iterator rend() const { 
    return const_reverse_iterator(begin()); 
  }
  size_type size() const { return size_type(end() - begin()); }
  size_type max_size() const { return size_type(-1) / sizeof(T); }
  size_type capacity() const { return size_type(end_of_storage - begin()); }
  bool empty() const { return begin() == end(); }
  //这里的no-const版本调用const版本应该更好的 ---- liushixiong
  //reference operator[](size_type n) { return *(begin() + n); }
  reference operator[](size_type n) { 
	  return const_cast<reference>(static_cast<const vector<T>&>(*this)[n]);
  }
  const_reference operator[](size_type n) const { return *(begin() + n); }

  vector() : start(0), finish(0), end_of_storage(0) {}
  // 以下建構式，允許指定大小 n 和初值 value
  vector(size_type n, const T& value) { fill_initialize(n, value); }
  vector(int n, const T& value) { fill_initialize(n, value); }
  vector(long n, const T& value) { fill_initialize(n, value); }
  explicit vector(size_type n) { fill_initialize(n, T()); }

  vector(const vector<T, Alloc>& x) {
    start = allocate_and_copy(x.end() - x.begin(), x.begin(), x.end());
    finish = start + (x.end() - x.begin());
    end_of_storage = finish;
  }
#ifdef __STL_MEMBER_TEMPLATES
  template <class InputIterator>
  vector(InputIterator first, InputIterator last) :
    start(0), finish(0), end_of_storage(0)
  {
    range_initialize(first, last, iterator_category(first));
  }
#else /* __STL_MEMBER_TEMPLATES */
  vector(const_iterator first, const_iterator last) {
    size_type n = 0;
    distance(first, last, n);
    start = allocate_and_copy(n, first, last);
    finish = start + n;
    end_of_storage = finish;
  }
#endif /* __STL_MEMBER_TEMPLATES */
  ~vector() { 
    destroy(start, finish);  // 全域函式，建構/解構基本工具。
    deallocate();   // 先前定義好的成員函式
  }
  vector<T, Alloc>& operator=(const vector<T, Alloc>& x);
  void reserve(size_type n) {
    if (capacity() < n) {
      const size_type old_size = size();
      iterator tmp = allocate_and_copy(n, start, finish);
      destroy(start, finish);
      deallocate();
      start = tmp;
      finish = tmp + old_size;
      end_of_storage = start + n;
    }
  }

  // 取出第一個元素內容
  //同样的和operator[]一样的方式，non-const调用const版本的实现
  reference front() { return *begin(); }
  const_reference front() const { return *begin(); }
  // 取出最後一個元素內容
  //同样的和operator[]一样的方式，non-const调用const版本的实现
  reference back() { return *(end() - 1); }
  const_reference back() const { return *(end() - 1); }
  // 增加一個元素，做為最後元素
  void push_back(const T& x) {
    if (finish != end_of_storage) {  // 還有備用空間
      construct(finish, x);   		// 直接在備用空間中建構元素。
      ++finish;                          	// 調整水位高度
    }
    else                                  // 已無備用空間
      insert_aux(end(), x);			
  }
  //交换下vector的三个指针，所以效率不低的
  void swap(vector<T, Alloc>& x) {
    __STD::swap(start, x.start);
    __STD::swap(finish, x.finish);
    __STD::swap(end_of_storage, x.end_of_storage);
  }
  iterator insert(iterator position, const T& x) {
    size_type n = position - begin();
    if (finish != end_of_storage && position == end()) {
      construct(finish, x);		// 全域函式，建構/解構基本工具。
      ++finish;
    }
    else
      insert_aux(position, x);
    return begin() + n;
  }
  iterator insert(iterator position) { return insert(position, T()); }
#ifdef __STL_MEMBER_TEMPLATES
  template <class InputIterator>
  void insert(iterator position, InputIterator first, InputIterator last){
    range_insert(position, first, last, iterator_category(first));
  }
#else /* __STL_MEMBER_TEMPLATES */
  void insert(iterator position,
              const_iterator first, const_iterator last);
#endif /* __STL_MEMBER_TEMPLATES */

  void insert (iterator pos, size_type n, const T& x);
  void insert (iterator pos, int n, const T& x) {
    insert(pos, (size_type) n, x);
  }
  void insert (iterator pos, long n, const T& x) {
    insert(pos, (size_type) n, x);
  }

  void pop_back() {
    --finish;
    destroy(finish);	// 全域函式，建構/解構基本工具。
  }
  // 將迭代器 position 所指之元素移除
  iterator erase(iterator position) {
    //先要释放准备释放的对象
    destroy(position);	// 全域函式，建構/解構基本工具。
    if (position + 1 != end()) {// 如果 p 不是指向最後一個元素
      // 將 p 之後的元素一一向前遞移
	  // 这里将要准备释放的对象给覆盖
      copy(position + 1, finish, position); 
	}

    --finish;  // 調整水位
	//TODO: bug 这里每次都是析构最后对象而不是指定位置的对象----liushixiong
    //destroy(finish);	// 全域函式，建構/解構基本工具。
    return position; 	// 返回的迭代器指向下一个元素的位置，迭代器本身不变
  }
  iterator erase(iterator first, iterator last) {
    destroy(first, last);	// 全域函式，建構/解構基本工具。
    iterator i = copy(last, finish, first);
	//TODO: bug释放的对象是不该释放的对象，放到上面去先调用析构函数
    //destroy(i, finish);	// 全域函式，建構/解構基本工具。
    finish = finish - (last - first);
    return first;
  }
  void resize(size_type new_size, const T& x) {
    if (new_size < size()) 
      erase(begin() + new_size, end());
    else
      insert(end(), new_size - size(), x);
  }
  void resize(size_type new_size) { resize(new_size, T()); }
  // 清除全部元素。注意，並未釋放空間，以備可能未來還會新加入元素。
  void clear() { erase(begin(), end()); }

protected:
  iterator allocate_and_fill(size_type n, const T& x) {
    iterator result = data_allocator::allocate(n); // 配置n個元素空間
    __STL_TRY {
      // 全域函式，記憶體低階工具，將result所指之未初始化空間設定初值為 x，n個
      // 定義於 <stl_uninitialized.h>。
      uninitialized_fill_n(result, n, x);  
      return result;
    }
     // "commit or rollback" 語意：若非全部成功，就一個不留。
    __STL_UNWIND(data_allocator::deallocate(result, n));
  }

#ifdef __STL_MEMBER_TEMPLATES
  template <class ForwardIterator>
  iterator allocate_and_copy(size_type n,
                             ForwardIterator first, ForwardIterator last) {
    iterator result = data_allocator::allocate(n);
    __STL_TRY {
      uninitialized_copy(first, last, result);
      return result;
    }
    __STL_UNWIND(data_allocator::deallocate(result, n));
  }
#else /* __STL_MEMBER_TEMPLATES */
  iterator allocate_and_copy(size_type n,
                             const_iterator first, const_iterator last) {
    iterator result = data_allocator::allocate(n);
    __STL_TRY {
      uninitialized_copy(first, last, result);
      return result;
    }
    __STL_UNWIND(data_allocator::deallocate(result, n));
  }
#endif /* __STL_MEMBER_TEMPLATES */


#ifdef __STL_MEMBER_TEMPLATES
  template <class InputIterator>
  void range_initialize(InputIterator first, InputIterator last,
                        input_iterator_tag) {
    for ( ; first != last; ++first)
      push_back(*first);
  }

  // This function is only called by the constructor.  We have to worry
  //  about resource leaks, but not about maintaining invariants.
  template <class ForwardIterator>
  void range_initialize(ForwardIterator first, ForwardIterator last,
                        forward_iterator_tag) {
    size_type n = 0;
    distance(first, last, n);
    start = allocate_and_copy(n, first, last);
    finish = start + n;
    end_of_storage = finish;
  }

  template <class InputIterator>
  void range_insert(iterator pos,
                    InputIterator first, InputIterator last,
                    input_iterator_tag);

  template <class ForwardIterator>
  void range_insert(iterator pos,
                    ForwardIterator first, ForwardIterator last,
                    forward_iterator_tag);

#endif /* __STL_MEMBER_TEMPLATES */
};

template <class T, class Alloc>
inline bool operator==(const vector<T, Alloc>& x, const vector<T, Alloc>& y) {
  return x.size() == y.size() && equal(x.begin(), x.end(), y.begin());
}

template <class T, class Alloc>
inline bool operator<(const vector<T, Alloc>& x, const vector<T, Alloc>& y) {
  return lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER

template <class T, class Alloc>
inline void swap(vector<T, Alloc>& x, vector<T, Alloc>& y) {
  x.swap(y);
}

#endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */

template <class T, class Alloc>
vector<T, Alloc>& vector<T, Alloc>::operator=(const vector<T, Alloc>& x) {
  if (&x != this) {	// 判斷是否 self-assignment
    if (x.size() > capacity()) {		// 如果標的物比我本身的容量還大
      iterator tmp = allocate_and_copy(x.end() - x.begin(),
                                       x.begin(), x.end());
      destroy(start, finish);	// 把整個舊的vector 摧毀
      deallocate();			// 釋放舊空間
      start = tmp;				// 設定指向新空間
      end_of_storage = start + (x.end() - x.begin());
    }
    else if (size() >= x.size()) {	// 如果標的物大小 <= 我的大小
      iterator i = copy(x.begin(), x.end(), begin());
      destroy(i, finish);
    }
    else { //如果目标的size() <= this->capacity()
      copy(x.begin(), x.begin() + size(), start);
	  //将后面的数据都清空
      uninitialized_copy(x.begin() + size(), x.end(), finish);
    }
    finish = start + x.size();
  }
  return *this;
}

template <class T, class Alloc>
void vector<T, Alloc>::insert_aux(iterator position, const T& x) {
  if (finish != end_of_storage) {  // 還有備用空間
    // 在備用空間起始處建構一個元素，並以vector 最後一個元素值為其初值。    
	// 复制最后一个元素
    construct(finish, *(finish - 1));
    // 調整水位。
    ++finish;
    // 以下做啥用？好像是做了转型操作
    T x_copy = x;
	//从position开始到finish-2个位置，向后移动一个位置
    copy_backward(position, finish - 2, finish - 1);
	//copy_backward最终采用的算法如下：
  	//while (first != last) *--result = *--last;
	//再将插入的元素位置，赋值给position位置
    *position = x_copy;
  }
  else {		// 已無備用空間
    const size_type old_size = size();
    const size_type len = old_size != 0 ? 2 * old_size : 1;
    // 以上配置原則：如果原大小為0，則配置 1（個元素大小）；
    // 如果原大小不為0，則配置原大小的兩倍，
    // 前半段用來放置原資料，後半段準備用來放置新資料。

    iterator new_start = data_allocator::allocate(len); // 實際配置
    iterator new_finish = new_start;
    __STL_TRY {
      // 將原vector 的內容拷貝到新 vector。
      new_finish = uninitialized_copy(start, position, new_start);
      // 為新元素設定初值x
      construct(new_finish, x);
      // 調整水位。
      ++new_finish;
      // 將原vector 的備用空間中的內容也忠實拷貝過來（啥用途？）
      new_finish = uninitialized_copy(position, finish, new_finish);
    }

#       ifdef  __STL_USE_EXCEPTIONS 
    catch(...) {
      // "commit or rollback" 語意：若非全部成功，就一個不留。
      destroy(new_start, new_finish); 
      data_allocator::deallocate(new_start, len);
      throw;
    }
#       endif /* __STL_USE_EXCEPTIONS */

    // 解構並釋放原 vector
    destroy(begin(), end());
    deallocate();

    // 調整迭代器，指向新vector
    start = new_start;
    finish = new_finish;
    end_of_storage = new_start + len;
  }
}

// 從 position 開始，安插 n 個元素，元素初值為 x
template <class T, class Alloc>
void vector<T, Alloc>::insert(iterator position, size_type n, const T& x) {
  if (n != 0) { // 當 n != 0  才進行以下所有動作
    if (size_type(end_of_storage - finish) >= n) { 
      // 備用空間大於等於「新增元素個數」
      T x_copy = x;
      // 以下計算安插點之後的現有元素個數
      const size_type elems_after = finish - position;	
      iterator old_finish = finish;
      if (elems_after > n) { 
        // 「安插點之後的現有元素個數」大於「新增元素個數」
        uninitialized_copy(finish - n, finish, finish);
        finish += n;	// 將vector 尾端標記後移
        copy_backward(position, old_finish - n, old_finish);
        fill(position, position + n, x_copy);	// 從安插點開始填入新值
      }
      else {	
        // 「安插點之後的現有元素個數」小於等於「新增元素個數」
        uninitialized_fill_n(finish, n - elems_after, x_copy);
        finish += n - elems_after;
        uninitialized_copy(position, old_finish, finish);
        finish += elems_after;
        fill(position, old_finish, x_copy);
      }
    }
    else {
      // 備用空間小於「新增元素個數」（那就必須配置額外的記憶體）
      // 首先決定新長度：舊長度的兩倍，或舊長度+新增元素個數。
      const size_type old_size = size();        
      const size_type len = old_size + max(old_size, n);
      // 以下配置新的vector 空間
      iterator new_start = data_allocator::allocate(len);
      iterator new_finish = new_start;
      __STL_TRY {
        // 以下首先將舊vector 的安插點之前的元素複製到新空間。
        new_finish = uninitialized_copy(start, position, new_start);
        // 以下再將新增元素（初值皆為 n）填入新空間。
        new_finish = uninitialized_fill_n(new_finish, n, x);
        // 以下再將舊vector 的安插點之後的元素複製到新空間。
        new_finish = uninitialized_copy(position, finish, new_finish);
      }
#         ifdef  __STL_USE_EXCEPTIONS 
      catch(...) {
        // 如有異常發生，實現 "commit or rollback" semantics.
        destroy(new_start, new_finish);
        data_allocator::deallocate(new_start, len);
        throw;
      }
#         endif /* __STL_USE_EXCEPTIONS */
      // 以下清除並釋放舊的 vector 
      destroy(start, finish);
      deallocate();
      // 以下調整水位標記
      start = new_start;
      finish = new_finish;
      end_of_storage = new_start + len;
    }
  }
}

#ifdef __STL_MEMBER_TEMPLATES

template <class T, class Alloc> template <class InputIterator>
void vector<T, Alloc>::range_insert(iterator pos,
                                    InputIterator first, InputIterator last,
                                    input_iterator_tag) {
  for ( ; first != last; ++first) {
    pos = insert(pos, *first);
    ++pos;
  }
}

template <class T, class Alloc> template <class ForwardIterator>
void vector<T, Alloc>::range_insert(iterator position,
                                    ForwardIterator first,
                                    ForwardIterator last,
                                    forward_iterator_tag) {
  if (first != last) {
    size_type n = 0;
    distance(first, last, n);
    if (size_type(end_of_storage - finish) >= n) {
      const size_type elems_after = finish - position;
      iterator old_finish = finish;
      if (elems_after > n) {
        uninitialized_copy(finish - n, finish, finish);
        finish += n;
        copy_backward(position, old_finish - n, old_finish);
        copy(first, last, position);
      }
      else {
        ForwardIterator mid = first;
        advance(mid, elems_after);
        uninitialized_copy(mid, last, finish);
        finish += n - elems_after;
        uninitialized_copy(position, old_finish, finish);
        finish += elems_after;
        copy(first, mid, position);
      }
    }
    else {
      const size_type old_size = size();
      const size_type len = old_size + max(old_size, n);
      iterator new_start = data_allocator::allocate(len);
      iterator new_finish = new_start;
      __STL_TRY {
        new_finish = uninitialized_copy(start, position, new_start);
        new_finish = uninitialized_copy(first, last, new_finish);
        new_finish = uninitialized_copy(position, finish, new_finish);
      }
#         ifdef __STL_USE_EXCEPTIONS
      catch(...) {
        destroy(new_start, new_finish);
        data_allocator::deallocate(new_start, len);
        throw;
      }
#         endif /* __STL_USE_EXCEPTIONS */
      destroy(start, finish);
      deallocate();
      start = new_start;
      finish = new_finish;
      end_of_storage = new_start + len;
    }
  }
}

#else /* __STL_MEMBER_TEMPLATES */

template <class T, class Alloc>
void vector<T, Alloc>::insert(iterator position, 
                              const_iterator first, 
                              const_iterator last) {
  if (first != last) {
    size_type n = 0;
    distance(first, last, n);
    if (size_type(end_of_storage - finish) >= n) {
      const size_type elems_after = finish - position;
      iterator old_finish = finish;
      if (elems_after > n) {
        uninitialized_copy(finish - n, finish, finish);
        finish += n;
        copy_backward(position, old_finish - n, old_finish);
        copy(first, last, position);
      }
      else {
        uninitialized_copy(first + elems_after, last, finish);
        finish += n - elems_after;
        uninitialized_copy(position, old_finish, finish);
        finish += elems_after;
        copy(first, first + elems_after, position);
      }
    }
    else {
      const size_type old_size = size();
      const size_type len = old_size + max(old_size, n);
      iterator new_start = data_allocator::allocate(len);
      iterator new_finish = new_start;
      __STL_TRY {
        new_finish = uninitialized_copy(start, position, new_start);
        new_finish = uninitialized_copy(first, last, new_finish);
        new_finish = uninitialized_copy(position, finish, new_finish);
      }
#         ifdef __STL_USE_EXCEPTIONS
      catch(...) {
        destroy(new_start, new_finish);
        data_allocator::deallocate(new_start, len);
        throw;
      }
#         endif /* __STL_USE_EXCEPTIONS */
      destroy(start, finish);
      deallocate();
      start = new_start;
      finish = new_finish;
      end_of_storage = new_start + len;
    }
  }
}

#endif /* __STL_MEMBER_TEMPLATES */

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma reset woff 1174
#endif

__STL_END_NAMESPACE 

#endif /* __SGI_STL_INTERNAL_VECTOR_H */

// Local Variables:
// mode:C++
// End:


