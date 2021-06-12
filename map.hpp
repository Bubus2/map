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

                Node() : 
                    key(std::move(Key())), data(std::move(Data()))
                {}

                Node(Key _key, Data _data) :
                    key(_key), data(_data), left(nullptr), right(nullptr)
                {}
            };

            std::unique_ptr<Node> root;
            Compare comp;

            std::pair<std::unique_ptr<Node>, bool> _insert(std::unique_ptr<Node> current, Key key, Data data) {
                if (current == nullptr) {
                    return std::make_unique<Node>(key, data);
                }

                if (current->key == key) {
                    return std::make_pair(current, false);
                }

                if (cur->key < current->key) {
                    return _insert(current->left, key, data);
                }

                return _insert(current->right, key, data);
            }

        public:
            map() : 
                root(nullptr) 
            {}

            map(const Compare& _comp) :
                root(nullptr), comp(_comp)
            {}

            bool insert(const Key& key, const Data& data) {
                std::pair<std::unique_ptr<Node>, bool> p = _insert(root, key, data);
                root = p.first;
                return p.second; 
            }
    };
}