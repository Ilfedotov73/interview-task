#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <utility>
#include "boost/pool/pool_alloc.hpp"

namespace CustomList {
    // Скрытая реализация.
    struct ListNode {
        ListNode *prev = nullptr;
        ListNode *next = nullptr;
        ListNode *rand = nullptr;
    
        std::string data;
    };

    class CustomLinkedList {
        /* Т.к. ListNode не использует обобщение для поля data, то мы можем напрямую
         * использовать аллокатор (сразу выделять для ListNode) без использования rebind.
         */
        using NodeAlloc = boost::fast_pool_allocator<ListNode>;
        using NodeTraits = std::allocator_traits<NodeAlloc>;
    private:
        ListNode *head_;
        ListNode *back_; 
        NodeAlloc node_alloc_;

        ListNode *get_rand_ptr(int rand_index);
        int search_rand_ptr(ListNode *rand_ptr) const;
        void rand_ptr_fil(std::vector<int> &rand_indexes);
    public:
        CustomLinkedList() : head_(nullptr), back_(nullptr), node_alloc_(NodeAlloc{}) {}
        CustomLinkedList(const CustomLinkedList &linked_list) = delete;
        CustomLinkedList &operator=(const CustomLinkedList &linked_list) = delete;
        ~CustomLinkedList()
        {
            ListNode *iter = head_;
            while (iter) {
                ListNode *tmp = iter;
                iter = iter->next;
                NodeTraits::destroy(node_alloc_, tmp);
                NodeTraits::deallocate(node_alloc_, tmp, 1);
            }
        }

        void push_back(const std::string &data);
        void list_deserialize(std::istream &in);
        std::string list_serialize() const;
    };

    inline void print_list(std::ostream &out, const std::string &linked_list_str) {
        out << linked_list_str;
    }
}