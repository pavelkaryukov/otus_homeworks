#pragma once 
#include <memory>
#include <vector>
////-----------------------------------------------------------------------------
template<class T>
struct TNode
{
    using value_type = T;
    //-----------------------------------------------------------------------------
    TNode<T>* Previous = nullptr;
    TNode<T>* Next    = nullptr;
    value_type Value = {};
    TNode() = default;
    //-----------------------------------------------------------------------------
    TNode(const T aNode)
    {
        Value = aNode;
        Previous = nullptr;
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
private:
    NodePtr m_FirstNode = nullptr;
    NodePtr m_LastNode = nullptr;
    _Alloc  m_Allocator = _Alloc();
    std::size_t m_Size = 0;
    //-----------------------------------------------------------------------------
    void BindNodes(NodePtr aPrevious, NodePtr aNext)
    {
        aNext->Previous = aPrevious;
        aPrevious->Next = aNext;
    }
    //-----------------------------------------------------------------------------
    void FreeNode(NodePtr aNode)
    {
        --m_Size;
        m_Allocator.destroy(aNode);
    }
    //-----------------------------------------------------------------------------
    NodePtr GetFirstNode() const
    {
        return m_FirstNode;
    }
    //-----------------------------------------------------------------------------
    NodePtr GetLastNode() const
    {
        return m_LastNode;
    }
#pragma region Iterator
    //-----------------------------------------------------------------------------
    class MyListIterator : public std::iterator<
        std::forward_iterator_tag,   // iterator_category
        T,                           // value_type
        T,                           // difference_type
        T*,                          // pointer
        T&                           // reference
    >
    {
        NodePtr m_Value = nullptr;
    public:
        explicit MyListIterator(NodePtr aValue = nullptr) : m_Value(aValue) {}
        //-----------------------------------------------------------------------------
        MyListIterator& operator++()
        {
            if (m_Value == nullptr)
                throw std::runtime_error("Wrong Iterator (== nullptr)");//TODO::Сделать нормальные исключения
            m_Value = (m_Value->Next != nullptr) ? m_Value->Next : nullptr;
            return *this;
        }
        //-----------------------------------------------------------------------------
        MyListIterator& operator--()
        {
            if (m_Value == nullptr)
                throw std::runtime_error("Wrong Iterator (== nullptr)");//TODO::Сделать нормальные исключения
            m_Value = (m_Value->Previous != nullptr) ? m_Value->Previous : nullptr;
            return *this;
        }        
        //-----------------------------------------------------------------------------
        MyListIterator operator++(int)
        {
            auto tmp = *this;
            operator++();
            return tmp;
        }
        //-----------------------------------------------------------------------------
        MyListIterator operator--(int)
        {
            auto tmp = *this;
            operator--();
            return tmp;
        }
        //-----------------------------------------------------------------------------
        bool operator==(MyListIterator aRhs) const { 
            return m_Value == aRhs.m_Value;
        }
        //-----------------------------------------------------------------------------
        bool operator!=(MyListIterator aRhs) const { 
            return !(*this == aRhs); 
        }
        //-----------------------------------------------------------------------------
        T* operator->() const
        {
            return addressof(operator*());
        }
        //-----------------------------------------------------------------------------
        T& operator*() const { return m_Value->Value; }
        //-----------------------------------------------------------------------------
    };
    //-----------------------------------------------------------------------------
#pragma endregion
    //-----------------------------------------------------------------------------
public:
    //-----------------------------------------------------------------------------
    MyList() = default;
    //-----------------------------------------------------------------------------
    MyList(const MyList<T, _Alloc>& aList)
    {
        m_FirstNode = aList.m_FirstNode;
        m_LastNode = aList.m_LastNode;
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
    void Add(T aObj)
    {
        ++m_Size;
        auto ptr = m_Allocator.allocate(1);
        m_Allocator.construct(ptr, aObj);
        if (m_FirstNode == nullptr) {
            m_FirstNode = (NodePtr)ptr;
            m_LastNode = m_FirstNode;
            m_Allocator.deallocate(ptr, 1);
            return;
        }
        BindNodes(m_LastNode, (NodePtr)ptr);
        m_LastNode = ptr;// TODO:: проверить
	};
    //-----------------------------------------------------------------------------
    std::size_t size() const
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
    MyListIterator begin()
    {
        return MyListIterator(m_FirstNode);
    }
    //-----------------------------------------------------------------------------
    MyListIterator rbegin()
    {
        return MyListIterator(m_LastNode);
    }
    //-----------------------------------------------------------------------------
    MyListIterator rend()
    {
        return MyListIterator( );
    }
    //-----------------------------------------------------------------------------
    MyListIterator end()
    {
        return MyListIterator();
    }
    //-----------------------------------------------------------------------------
}; 