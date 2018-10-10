#include <iostream>
#include <assert.h>
#include "List.h"

using namespace std;

//节点类构造函数*
LinkNode::LinkNode(const DataType x)
        :_data(x)
        , _next(nullptr)
        , _prev(nullptr)
{}

//链表类*
List::List()         //构造函数
        : _head(nullptr)
        , _tail(nullptr)
{}

List::List(const List& s)          //拷贝构造
        : _head(nullptr)
        , _tail(nullptr)
{
    if (s._head == nullptr)
    {
        return;
    }
    LinkNode* tmp = s._head;
    while (tmp)
    {
        PushBack(tmp->_data);
        tmp = tmp->_next;
    }

}

//赋值运算符的重载再优化(推荐写法)
List&  List::operator=(List &s)
{
    if (this != &s)
    {
        swap(_head, s._head);
        swap(_tail, s._tail);
    }
    return *this;
}
List::~List()    //析构
{
    Clear();
}

void List::Reverse()   //链表逆置（利用头插新节点的方法）
{
    if (_head == nullptr || _head== _tail)
    {
        return;
    }
    int ret = Amount();

    //  方法二（只是交换对称位置节点的数据）**（高效）
    LinkNode* begin = _head;
    LinkNode* end = _tail;
    while (ret)
    {
        if (end->_next == begin)
            break;
        ret /= 2;
        swap(begin->_data, end->_data);
        begin = begin->_next;
        end = end->_prev;
    }

}

//打印链表*
void List::PrintSList()
{
    //头结点为空时，无需打印链表
    if (_head == nullptr)
    {
        cout << "This SList is Empty !" << endl;
        return;
    }
    else
    {
        LinkNode* tmp = _head;
        while (tmp)
        {
            cout << tmp->_data << "-->";
            tmp = tmp->_next;
        }
        cout <<"nullptr"<< endl;
    }
}

void List::PushBack(const DataType& x)    //在尾部插入一个节点*
{
    //如果链表为空，插入节点后只有一个节点，此时_head=_tail
    if (_head == nullptr)
    {
        _head = new LinkNode(x);
        _tail = _head;
    }
    else
    {
        _tail->_next = new LinkNode(x);
        _tail->_next->_prev=_tail;
        _tail = _tail->_next;
    }
}

void List::Clear()         //链表置空*
{
    LinkNode* begin = _head;
    while (begin != _tail)
    {
        _head = _head->_next;
        delete begin;
        begin = _head;
    }
    _head = nullptr;
    _tail = nullptr;
}

void List::PopBack()    //尾删
{
    if (_head == nullptr)
    {
        cout << "This SList is empty !" << endl;
    }
    else if (_head == _tail)
    {
        delete _head;
        _head = nullptr;
        _tail = nullptr;
    }
    else
    {
        LinkNode* cur = _head;
        while (cur->_next != _tail)
        {
            cur = cur->_next;
        }
        delete _tail;
        _tail = cur;
        _tail->_prev = cur->_prev;
        _tail->_next = nullptr;
    }
}

void List::PushFront(DataType x)  //头插*
{
    if (_head == nullptr)
    {
        PushBack(x);
    }
    else
    {
        LinkNode* tmp = _head;
        _head = new LinkNode(x);
        _head->_next = tmp;
        tmp->_prev = _head;
    }
}

void List::PopFront()    //删除首节点
{
    if (_head == nullptr)
    {
        cout << "This SList is empty !" << endl;
        return;
    }
    LinkNode* tmp = _head;
    _head = _head->_next;
    _head->_prev = nullptr;
    delete tmp;
}

//固定位置插入一个节点（这个函数需和Find函数搭配使用）
//先用Find函数找到新节点需要插入的位置
//（将Find函数的返回值传给Insert函数的参数pos），再在pos节点后面插入新节点x
void List::Insert(LinkNode* pos, DataType x)   //*
{
    assert(pos);
    if (pos == _tail)
    {
        PushBack(x);
    }
    else
    {
        LinkNode* tmp = new LinkNode(x);
        tmp->_next = pos->_next;
        pos->_next = tmp;
        tmp->_next->_prev = tmp;
        tmp->_prev = pos;
    }
}

//删除某一节点，同样，要先找到该节点并传参给Erase函数
void List::Erase(LinkNode* pos)
{
    assert(pos);
    if (pos == _tail)
    {
        PopBack();
    }
    else if (pos == _head)
    {
        PopFront();
    }
    else
    {
        pos->_prev->_next = pos->_next;
        pos->_next->_prev = pos->_prev;
        delete pos;
    }
}

//查找节点并返回这个节点的地址
LinkNode* List::Find(DataType x)
{
    if (_head == nullptr)
    {
        cout << "This SList is empty !" << endl;
        return nullptr;
    }
    else
    {
        LinkNode* tmp = _head;
        while (tmp != nullptr)
        {
            if (tmp->_data == x)
            {
                return tmp;
            }
            tmp = tmp->_next;
        }
        return nullptr;
    }
}

int List::Amount()   //计算链表节点的数目
{
    if (_head == nullptr)
    {
        return 0;
    }
    else
    {
        int count = 0;
        LinkNode* cur = _head;
        while (cur != _tail)
        {
            count++;
            cur = cur->_next;
        }
        return ++count;
    }
}

void List::Remove(DataType x)      //查找某节点并删除
{
    if (_head == nullptr)
    {
        cout << "This SList is empty !" << endl;
    }
    else
    {
        LinkNode* tmp = Find(x);
        if (tmp != nullptr)
        {
            Erase(tmp);
        }
    }
}

int List::GetFront() {
    if (_head == nullptr)
    {
        cout << "This SList is empty !" << endl;
        return -1;
    }
    return _head->_data;
}

int List::GetBack() {
    if (_head == nullptr)
    {
        cout << "This SList is empty !" << endl;
        return -1;
    }

    return _tail->_data;
}
