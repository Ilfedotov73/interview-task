/* Cборка:
 * sudo apt-get install libboost-all-dev -- для pool_alloc.hpp
 * g++ -O2 app.cpp linked_list.cpp -o app
 * ./app < ./tests/inlet.in > ./tests/outlet.out
 */

#include "linked_list.hpp"
#include <chrono>

int main()
{
    CustomList::CustomLinkedList list{};

    std::cerr << "Deserialize start" << '\n';
    auto start = std::chrono::high_resolution_clock::now();
    list.list_deserialize(std::cin);
    auto end = std::chrono::high_resolution_clock::now();
    double ms = std::chrono::duration<double, std::milli>(end - start).count();
    std::cerr << "Stop deserialize, time: " << ms << '\n';

    std::cerr << "Serialize start" << '\n';
    start = std::chrono::high_resolution_clock::now();
    std::string list_str = list.list_serialize();
    end = std::chrono::high_resolution_clock::now();
    ms = std::chrono::duration<double, std::milli>(end - start).count();
    std::cerr << "Stop serialize, time: " << ms << '\n';
    
    CustomList::print_list(std::cout, list_str);
    return 0;
}