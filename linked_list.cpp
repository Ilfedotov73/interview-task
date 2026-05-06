#include "linked_list.hpp"

namespace CustomList {
    ListNode *CustomLinkedList::get_rand_ptr(int rand_index)
    {
        ListNode *iter = head_;
        for (int i = 0; iter; ++i) {
            if (i == rand_index) { return iter; }
            iter = iter->next;
        }
        return nullptr;
    }
    /* Т.к. rand_indexes последовательно заполняется вместе со списком, 
     * то каждый элемент вектора соответсвутет каждой ячейке списка и 
     * размеры их равны. В этом случае мы можем просто перебирать элементы
     * вектора и списка, и дозаполнять поле rand для каждой ячейки.
     */
    void CustomLinkedList::rand_ptr_fil(std::vector<int> &rand_indexes)
    {
        int rand_indexes_sz = rand_indexes.size();
        ListNode *iter = head_;
        for (int i = 0; i < rand_indexes_sz && iter; ++i) {
            iter->rand = (rand_indexes[i] > -1) ? get_rand_ptr(rand_indexes[i]) : nullptr;
            iter = iter->next;
        }        
    }
    int CustomLinkedList::search_rand_ptr(ListNode *rand_ptr) const
    {
        if (rand_ptr == nullptr) { return -1; }
        ListNode *iter = head_;
        int i = 0;
        while (iter) {
            if (iter == rand_ptr) { return i; }
            iter = iter->next;
            ++i;
        }
        return -1;
    }

    void CustomLinkedList::push_back(const std::string &data)
    {
        ListNode *new_node = NodeTraits::allocate(node_alloc_,1);
        /* Конструируем объект в байтах по адресу *new_node*/
        new (new_node) ListNode{nullptr, nullptr, nullptr, data};
        if (!head_) { head_ = back_ =  new_node; }
        else {
            new_node->prev = back_;
            back_->next = new_node;
            back_ = new_node;
        }
    }
    void CustomLinkedList::list_deserialize(std::istream &in = std::cin)
    {
        this->~CustomLinkedList(); // Очищаем список.
        std::string line; //Текущая считываемая из поток ввода строка.
        char sep = ';'; // Разделитель.
        std::vector<int> rand_indexes; // Используется для дозаполнения указателей rand.
        std::string data, rand_index;
        while (std::getline(in,line)) {
            std::istringstream token_stream{line};
            std::getline(token_stream, data, sep);
            std::getline(token_stream, rand_index);
            push_back(data);
            rand_indexes.push_back(std::stoi(rand_index));
        }
        rand_ptr_fil(rand_indexes);
    }
    std::string CustomLinkedList::list_serialize() const
    {
        std::string out;
        ListNode *iter = head_;
        while(iter) {
            out.append(iter->data).append(";").append(std::to_string(search_rand_ptr(iter->rand))).append("\n");
            iter = iter->next;
        }
        return out;
    }
}