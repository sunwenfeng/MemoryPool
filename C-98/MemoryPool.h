/*-
 * Copyright (c) 2013 Cosku Acay, http://www.coskuacay.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include <limits.h>
#include <stddef.h>
/*参考STL allocator实现的内存池，支持任意类型*/

template <typename T, size_t BlockSize = 4096>
class MemoryPool
{
  public:
    /* Member types */
    typedef T               value_type;         //元素类型
    typedef T*              pointer;            //指针
    typedef T&              reference;          //引用
    typedef const T*        const_pointer;      //const 指针
    typedef const T&        const_reference;    //const 引用
    typedef size_t          size_type;          //
    typedef ptrdiff_t       difference_type;

    template <typename U>
    struct rebind {
      typedef MemoryPool<U> other;              //重新绑定？？以U为参数
    };

    /* Member functions */
    MemoryPool() throw();                                       //构造函数
    MemoryPool(const MemoryPool& memoryPool) throw();           //拷贝构造，但没有指定参数？？
    template <class U>
    MemoryPool(const MemoryPool<U>& memoryPool) throw();        //拷贝构造

    ~MemoryPool() throw();                                      //析构函数

    pointer address(reference x) const throw();                 //返回指针
    const_pointer address(const_reference x) const throw();     //返回const 指针

    // Can only allocate one object at a time. n and hint are ignored
    pointer allocate(size_type n = 1, const_pointer hint = 0);     //分配内存空间
    void deallocate(pointer p, size_type n = 1);                    //释放内存空间

    size_type max_size() const throw();

    void construct(pointer p, const_reference val);                 //构造对象
    void destroy(pointer p);                                        //析构对象

    pointer newElement(const_reference val);
    void deleteElement(pointer p);

  private:
    union Slot_ {
      value_type element;
      Slot_* next;
    };//既能存放对象，又能构建链表，但同时只能存在一个

    typedef char* data_pointer_;            //指向内存池的首地址
    typedef Slot_ slot_type_;               //
    typedef Slot_* slot_pointer_;

    slot_pointer_ currentBlock_;            //block list头指针
    slot_pointer_ currentSlot_;             //当前可用的第一个slot的位置，即可以存放value_type数据的位置
    slot_pointer_ lastSlot_;                //最后一个slot的位置
    slot_pointer_ freeSlots_;               //空闲链表头指针

    size_type padPointer(data_pointer_ p, size_type align) const throw();
    void allocateBlock();                   //添加一个block
   /*
    static_assert(BlockSize >= 2 * sizeof(slot_type_), "BlockSize too small.");
    */
};

#include "MemoryPool.tcc"

#endif // MEMORY_POOL_H
