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
    struct shm_remove
    {
        shm_remove() { shared_memory_object::remove("MySharedMemory1"); }
        ~shm_remove(){ shared_memory_object::remove("MySharedMemory1"); }
    } remover;

    managed_shared_memory segment(create_only, "MySharedMemory1", 65536);

    MyList *mylist = segment.construct<MyList>("MyList")(segment.get_segment_manager());

    my_string *s = segment.find_or_construct<my_string>("String")("Hello", segment.get_segment_manager());
    s->insert(5, ", world");
    std::cout << *s << '\n';
    for(int i = 0; i < 100; ++i)  //Insert data in the vector
       mylist->push_back(*s);

    sleep(100000);
    return 0;
};

