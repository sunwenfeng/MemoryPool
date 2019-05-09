## MemoryPool C98注释
`实现时采用STL allocator的架构`  
`用union定义每个Slot`  
` placement new在已有内存上构造对象`  
`reinterpret_cast<>()进行指针间的类型转换（slot* 和 value_type* ）`  

详细分析在memory系统流程.docx
