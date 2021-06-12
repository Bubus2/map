#pragma once
#include <memory>

namespace stl {
    template<class Key, class Data, class Compare = std::less<Key>>
    class map {
        private:
            struct Node {
                Key key;
                Data data;

                std::unique_ptr<Node> left;
                std::unique_ptr<Node> right;

                Node(Key _key, Data _data) :
                    key(_key), data(_data), left(nullptr), right(nullptr)
                {}
            };

            std::unique_ptr<Node> root;
            Compare comp;

        public:
            map() : 
                root(nullptr) 
            {}

            map(const Compare& _comp) :
                root(nullptr), comp(_comp)
            {}
    };
}