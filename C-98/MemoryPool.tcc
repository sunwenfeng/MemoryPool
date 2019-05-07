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

#ifndef MEMORY_BLOCK_TCC
#define MEMORY_BLOCK_TCC

#include <iostream>

template <typename T, size_t BlockSize>
inline typename MemoryPool<T, BlockSize>::size_type                   //嵌套从属类型，用typename声明
MemoryPool<T, BlockSize>::padPointer(data_pointer_ p, size_type align)//计算内存对齐空间
const throw()
//以slot_type的长度，对齐block中除block list指针之外的空间
//size_type bodyPadding = padPointer(body, sizeof(slot_type_));
{
  size_t result = reinterpret_cast<size_t>(p);  //reinterpret_cast用于底层的类型转换，如void*和int之间的转换
  return ((align - result) % align);
    //需要的对齐长度为align，block第一个元素放slot*指针，此时指针位置为，补齐长度为（align-result）%align，result为将p强制转换
    //成int的结果，经验证，补齐长度正确，但未找到出处。
    //如slot的长度是8，此时slot*只占用了4，需要补齐4，padPointer返回4
}



template <typename T, size_t BlockSize>
MemoryPool<T, BlockSize>::MemoryPool()
throw()
//函数名后加throw,对函数的异常安全性进行线程，throw()没有参数时，不允许抛出异常，表明异常安全
{
  currentBlock_ = 0;
  currentSlot_ = 0;
  lastSlot_ = 0;
  freeSlots_ = 0;
}



template <typename T, size_t BlockSize>
MemoryPool<T, BlockSize>::MemoryPool(const MemoryPool& memoryPool)
throw()
{
    std::cout<<"cpoy1"<<std::endl;
  MemoryPool();
}



template <typename T, size_t BlockSize>
template<class U>
MemoryPool<T, BlockSize>::MemoryPool(const MemoryPool<U>& memoryPool)
throw()
{
    std::cout<<"copy2"<<std::endl;
  MemoryPool();
}



template <typename T, size_t BlockSize>
MemoryPool<T, BlockSize>::~MemoryPool()
throw()
{
  slot_pointer_ curr = currentBlock_;
  while (curr != 0) {   //block以链表存储，依次删除每一个block
    slot_pointer_ prev = curr->next;
    operator delete(reinterpret_cast<void*>(curr));//转换成void*，不需要析构，直接delete
    curr = prev;
  }
}



template <typename T, size_t BlockSize>
inline typename MemoryPool<T, BlockSize>::pointer
MemoryPool<T, BlockSize>::address(reference x)//返回指针
const throw()
{
  return &x;
}



template <typename T, size_t BlockSize>
inline typename MemoryPool<T, BlockSize>::const_pointer
MemoryPool<T, BlockSize>::address(const_reference x)//const指针
const throw()
{
  return &x;
}



template <typename T, size_t BlockSize>
void
MemoryPool<T, BlockSize>::allocateBlock()
{
  // Allocate space for the new block and store a pointer to the previous one
    //operator new进行内存分配，返回void*
  data_pointer_ newBlock = reinterpret_cast<data_pointer_>
                           (operator new(BlockSize));
    //新分配的内存用char*指针data_pointer指向

  reinterpret_cast<slot_pointer_>(newBlock)->next = currentBlock_;//newBlock是新block的指针，转换成slot*,然后插入到block list

  currentBlock_ = reinterpret_cast<slot_pointer_>(newBlock);//用currentBlock记录当前block list头指针
  // Pad block body to staisfy the alignment requirements for elements

  data_pointer_ body = newBlock + sizeof(slot_pointer_);    //block开始的位置为什么加一个sizeof(),即加4，所以在第一个位置存储slot*(长度为4),之后再存储value_type

  size_type bodyPadding = padPointer(body, sizeof(slot_type_));

    //由于value_type类型的长度可能大于slot_pointer_即slot指针的长度，即sizeof(slot_type)的长度可能大于sizeof(char*)
    // 而在block中存储的每个元素都需要对齐，也就是长度都是sizeof(slot_type),不足的空间需要补齐。

  currentSlot_ = reinterpret_cast<slot_pointer_>(body + bodyPadding);    //currentSlot为block开始的位置加上bodypadding个char*空间，对齐之后存储第一个value_type

  lastSlot_ = reinterpret_cast<slot_pointer_>
              (newBlock + BlockSize - sizeof(slot_type_) + 1);//+1有点不明白
}



template <typename T, size_t BlockSize>
inline typename MemoryPool<T, BlockSize>::pointer
MemoryPool<T, BlockSize>::allocate(size_type, const_pointer)
{
  if (freeSlots_ != 0) {//空闲链表不为空
    pointer result = reinterpret_cast<pointer>(freeSlots_);//转换成value_type指针，然后构造对象
    freeSlots_ = freeSlots_->next;//更新空闲链表头指针
    return result;
  }
  else {//空闲链表为空时
    if (currentSlot_ >= lastSlot_)//新分配的block不可用，则重新分配block
      allocateBlock();
    return reinterpret_cast<pointer>(currentSlot_++);//返回当前block中的空闲slot。
  }
}

template <typename T, size_t BlockSize>
inline void
MemoryPool<T, BlockSize>::deallocate(pointer p, size_type)//释放内存，然后将其加入freeSlot即空闲链表中，加入头部
//与其说是释放内存，不如说是将p所指内存加入freeslot链表，表明这部分内存不用了，可以在上面用placement new创建新对象。
{
  if (p != 0) {
    reinterpret_cast<slot_pointer_>(p)->next = freeSlots_;//将p转换成Slot_*，Slot*中只有next指针。
    freeSlots_ = reinterpret_cast<slot_pointer_>(p);
  }
}



template <typename T, size_t BlockSize>
inline typename MemoryPool<T, BlockSize>::size_type
MemoryPool<T, BlockSize>::max_size()//计算可达到的最大元素上限
const throw()
{
  size_type maxBlocks = -1 / BlockSize;
  return (BlockSize - sizeof(data_pointer_)) / sizeof(slot_type_) * maxBlocks;
}



template <typename T, size_t BlockSize>
inline void
MemoryPool<T, BlockSize>::construct(pointer p, const_reference val)
{
  new (p) value_type (val);//placement new用法，创建对象但是不分配内存，在已有的内存块上创建对象。
}



template <typename T, size_t BlockSize>
inline void
MemoryPool<T, BlockSize>::destroy(pointer p)
{
  p->~value_type();
}



template <typename T, size_t BlockSize>
inline typename MemoryPool<T, BlockSize>::pointer
MemoryPool<T, BlockSize>::newElement(const_reference val)
{
  pointer result = allocate();      //申请内存
  construct(result, val);           //构造对象
  return result;
}



template <typename T, size_t BlockSize>
inline void
MemoryPool<T, BlockSize>::deleteElement(pointer p)
{
  if (p != 0) {
    p->~value_type();
    deallocate(p);
  }
}



#endif // MEMORY_BLOCK_TCC
