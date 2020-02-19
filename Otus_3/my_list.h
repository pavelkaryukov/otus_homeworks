#pragma once 
#include <memory>
//Перечитать move и форвард
////-----------------------------------------------------------------------------
template<class T>
struct TNode
{
    using value_type = T;
    //-----------------------------------------------------------------------------
    TNode<T>* Previos = nullptr;
    TNode<T>* Next    = nullptr;
    value_type Value = {};
    TNode() = default;
    //-----------------------------------------------------------------------------
    TNode(const T aNode)
    {
        Value = aNode;
        Previos = nullptr;
        Next = nullptr;
    }
    //-----------------------------------------------------------------------------
    TNode(const TNode<T>& aNode)
    {
        *this = aNode;
    }
    //-----------------------------------------------------------------------------
    TNode& operator=(T aNode)
    {
        auto temp(aNode);
        std::swap(*this, temp);
        return *this;
    }
    //-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
//Реализовать итераторы
//-----------------------------------------------------------------------------
template
<
    class T, 
    class _Alloc = std::allocator<TNode<T>>
>
struct MyList
{
    using Node   = TNode<T>;
    using NodePtr = Node*;
    //-----------------------------------------------------------------------------
    MyList() = default;
    //-----------------------------------------------------------------------------
    MyList(const MyList<T, _Alloc>& aList)
    {
        m_FirstNode = aList.m_FirstNode;
        m_TailNode = aList.m_TailNode;
        m_Allocator = aList.m_Allocator;
        m_Size = aList.m_Size;
    }
    //-----------------------------------------------------------------------------
    MyList& operator=(MyList<T, _Alloc> aList)
    {
        return MyList(aList);
    }
    //-----------------------------------------------------------------------------
    ~MyList()
    {
        auto node = m_FirstNode;
        do {
            auto currentNode = node;
            node = node->Next;
            FreeNode(currentNode);
        } while (node != nullptr);
    };
    //-----------------------------------------------------------------------------
    void Add(T&& aObj)
    {
        ++m_Size;
        auto ptr = m_Allocator.allocate(1);
        m_Allocator.construct(ptr, aObj);
        if (m_FirstNode == nullptr) {
            m_FirstNode = (NodePtr)ptr;
            m_TailNode = m_FirstNode;
            return;
        }
        BindNodes(m_TailNode, (NodePtr)ptr);
        m_TailNode = ptr;// TODO:: проверить
	};
    //-----------------------------------------------------------------------------
    std::size_t Size() const
    {
        return m_Size;
    }
    //-----------------------------------------------------------------------------
    std::vector<T> GetData() const
    {
        using DataVect =std::vector<T>; 
        if (m_FirstNode == nullptr)
            return DataVect();
        auto resVect = DataVect();
        auto node = m_FirstNode;
        do {
            resVect.emplace_back(node->Value);
            node = node->Next;
        } while (node != nullptr);
        return resVect;
    }
    //-----------------------------------------------------------------------------
private:
    NodePtr m_FirstNode = nullptr;
    NodePtr m_TailNode  = nullptr;
    _Alloc  m_Allocator = _Alloc();
    std::size_t m_Size = 0;
    //-----------------------------------------------------------------------------
    void BindNodes(NodePtr aPrevious, NodePtr aNext)
    {
        aNext->Previos = aPrevious;
        aPrevious->Next = aNext;
    }
    //-----------------------------------------------------------------------------
    void FreeNode(NodePtr aNode)
    {
        --m_Size;
        m_Allocator.destroy(aNode);
    }
    //-----------------------------------------------------------------------------
    
}; 
//-----------------------------------------------------------------------------
template<class T>
struct MyListIterator : public std::iterator<std::forward_iterator_tag,  MyList<T, class _Alloc>>
{
    friend MyList<T>;
    using List = MyList<T>;
    using ListPtr = List*;
    using ListRef = List&;
    using Node = TNode<T>;
    using NodePtr = TNode<T>;
    //-----------------------------------------------------------------------------
    MyListIterator()
    {
        CreateEnd();
        //m_Last = m_End;
        m_First = m_End;
    }
    //-----------------------------------------------------------------------------
    MyListIterator(ListPtr* aPtr) : m_First(aPtr->m_FirstNode), m_Last(aPtr->m_LastNode)
    {
        m_End = new TNode();
        m_End->Previos = m_Last;
    }
    //MyIterator(const MyIterator& aIter) : m_List(aIter.m_List) {}
    ~MyListIterator() { delete m_End; }
//     MyIterator& operator++() { ++p; return *this; }
//     MyIterator operator++(int) { MyIterator tmp(*this); operator++(); return tmp; }
//     bool operator==(const MyIterator& rhs) const { return p == rhs.p; }
//     bool operator!=(const MyIterator& rhs) const { return p != rhs.p; }
//     int& operator*() { return *p; }
private : 
    NodePtr m_First = nullptr;
    NodePtr m_Last  = nullptr;
    NodePtr m_End = nullptr;
    void CreateEnd()
    {
        m_End = new TNode();
        m_End->Previos = m_Last;
    }
};
//-----------------------------------------------------------------------------
//