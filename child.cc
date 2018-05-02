#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/list.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <string>
#include <iostream>
#include <cstdlib> //std::system

using namespace boost::interprocess;

typedef allocator<char, managed_shared_memory::segment_manager>  CharAllocator;
typedef basic_string<char, std::char_traits<char>, CharAllocator> my_string;

typedef allocator<my_string, managed_shared_memory::segment_manager> ListAllocator;
typedef list<my_string, ListAllocator> MyList;

int main(int argc, char *argv[])
{
    managed_shared_memory segment(open_only, "MySharedMemory1");

    MyList *mylist = segment.find<MyList>("MyList").first;
    for (MyList::iterator it = mylist->begin(); it != mylist->end(); it++)
            std::cout << *it << '\n';

    return 0;
}

