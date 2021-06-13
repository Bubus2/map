#pragma once
#include <memory>
#include <sstream>

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

            bool _insert(std::unique_ptr<Node>& current, const Key& key, const Data& data) {
                if (current == nullptr) {
                    current = std::make_unique<Node>(key, data);
                    return true;
                }

                if (!(comp(key, current->key) && !comp(current->key, key))) {
                    return false;
                }

                if (comp(key, current->key)) {
                    return _insert(current->left, key, data);
                }

                return _insert(current->right, key, data);
            }

            std::unique_ptr<Node>& _search(std::unique_ptr<Node>& current, const Key& key) {
                if (current == nullptr || (!comp(key, current->key) && !comp(current->key, key))) {
                    return current;
                }

                if (comp(key, current->key)) {
                    return _search(current->left, key);
                }

                return _search(current->right, key);
            }

            std::stringstream _inorder(const std::unique_ptr<Node>& current) const {
                std::stringstream result;
                if (current != nullptr) {
                    result << _inorder(current->left).str() 
                    << "[" << current->key << "] -> " << current->data << "\n" 
                    << _inorder(current->right).str();
                }

                return result;
                               
            }

        public:
            map() : 
                root(nullptr), comp()
            {}

            map(const Compare& _comp) :
                root(nullptr), comp(_comp)
            {}

            bool insert(const Key& key, const Data& data) {
                return _insert(root, key, data);
            }

            bool insert(std::pair<const Key&, const Data&> value) {
                return _insert(root, value.first, value.second);
            }

            void insert_or_assign(const Key& key, const Data& data) {
                this->operator[](key) = data;
            }

            void insert_or_assign(std::pair<const Key&, const Data&> value) {
                this->operator[](value.first) = value.second;
            }

            Data& operator[](const Key& key) {
                std::unique_ptr<Node>& node = _search(root, key);
                if (node != nullptr) {
                    return node->data;
                }

                _insert(root, key, Data());
                return _search(root, key)->data;                
            }

            std::string to_string() const {
                return _inorder(root).str();
            }
    };
}