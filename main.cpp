#include <iostream>
#include"List.h"

/**
 * 查找递增双向链表中的两个数a,b(可重复),使a+b=x
 * @param x
 */
void findX(int x,List list){

    if(x>2*list.GetBack()||x<2*list.GetFront()){
        std::cout<<"Not Exist!"<<std::endl;
        return;
    }

    while (2*list.GetBack()>=x&&2*list.GetFront()<=x) {
        while (list.GetBack() > x - list.GetFront()) {
            list.PopBack();
        }
        while (list.GetFront() < list.GetBack() - x) {
            list.PopFront();
        }
        if (list.GetFront() + list.GetBack() == x) {
            std::cout << x << "=" << list.GetFront() << "+" << list.GetBack() << std::endl;
            return;
        } else if (2*list.GetFront()==x){
            std::cout << x << "=" << list.GetFront() << "+" << list.GetFront() << std::endl;
            return;
        } else if (2*list.GetBack()==x){
            std::cout << x << "=" << list.GetBack() << "+" << list.GetBack() << std::endl;
            return;
        }
    }
    std::cout<<"Not Exist!"<<std::endl;

}

int main() {

    List list;
    for (int i = 1; i < 101; ++i) {
        list.PushBack(i);
    }

    findX(3,list);
    findX(99,list);
    findX(2,list);
    findX(200,list);
    findX(1,list);
    findX(201,list);
    return 0;
}