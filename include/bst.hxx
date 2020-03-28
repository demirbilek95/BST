/**
 * bst.hxx file
 * @author: Eros Fabrici
 * @author: Dogan Can Demirbilek
 * @author: Alessandro Scardoni
 **/
#include <iostream>
#include <utility>
#include <memory>
#include <vector>


#ifndef BST_HXX__
#define BST_HXX__

//pre-declaration needed for the iterator class
template<class KeyType, class ValueType, class CompareType = std::less<KeyType>>
class bst;

#include "iterator.hxx"

template<class KeyType, class ValueType, class CompareType>
class bst 
{
    
    private:
        class Node;
        std::unique_ptr<Node> root;
        using iterator = __iterator<Node,KeyType,ValueType,CompareType,false>;
        using const_iterator = __iterator<Node,KeyType,ValueType,CompareType,true>;
        /**
         * @brief Given a node in a tree, returns its successor
         * @param node A pointer to a node
         * @return Pointer to node's successor
         */
        //Node *successor(Node * node) const;

        /**
         * @brief Given a pointer to a node, find the leftmost element in the sub-tree
         * with node as root
         * @param node Pointer to a node
         * @return Pointer to a node which is the leftmost element of the sub-tree rooted
         * in node
         */
        Node *leftmost(Node * node) const;


        /**
         * @brief Recursive private method to create deep copy of a binary search tree
         * @param node The root node of the tree that should be copied
         */
        void copy(const std::unique_ptr<Node> &node);

        void swap(Node* node1, Node* node2);

        void erase_aux(const KeyType& key, Node* node);

        /**
         * @brief Find the node of given key
         * @param key The key value to be found in bst
         * @return Iterator to the found node (to nullptr if the node is not found)
         */
        iterator find_aux(const KeyType& key, Node *current);

        /**
         * @brief Find the node of given key
         * @param key The key value to be found in bst
         * @return Const-iterator to the found node (to nullptr if the node is not found)
         */
        const_iterator find_aux(const KeyType& key, Node *current) const;
    public:
        CompareType comparator;
        
        /**
         * @brief Default constructor
         */
        bst() {}
        
        /**
         * @brief Constructor with node
         * @param data The root of the bst to be created
         * @param c The instance of the CompareType
         */
        bst(std::pair<KeyType, ValueType> data, CompareType c = CompareType{}):
            root{std::make_unique<Node>(data)}, comparator{c} {}

        /**
         * @brief copy constructor
         * @param bst A reference to another bst
         */
        bst(const bst& bst)
        {    
            copy(bst.root);
        }
        /**
         * @brief move constructor
         * @param bst Bst to be moved to the new one
         */
        bst(bst&& bst) noexcept : 
            root{std::move(bst.root)} {}
        
        /**
         * @brief Method that generates an iterator
         * @return An iterator to the first element of the bst
         *         according to the in-order visit
         */
        iterator begin() noexcept
        {
            return iterator{leftmost(root.get())};
        }

        /**
         * @brief Method that generates a const-iterator
         * @return A const-iterator to the first element of the bst
         *         according to the in-order visit
         */
        const_iterator begin() const noexcept
        {
            const_iterator it{leftmost(root.get())};
            return it;
        }

        /**
         * @brief Method that generates a const-iterator
         * @return A const-iterator to the first element of the bst
         *         according to the in-order visit
         */
        const_iterator cbegin() const noexcept
        {
            const_iterator it{leftmost(root.get())};
            return it;
        }

        /**
         * @brief Method that returns an iterator to nullptr
         * @return Iterator to nullptr
         */
        iterator end() noexcept { return iterator{nullptr}; }

        /**
         * @brief Method that returns a const-iterator to nullptr
         * @return Const-iterator to nullptr
         */
        const_iterator end() const noexcept
        {
            const_iterator it{nullptr};
            return it;
        }

        /**
         * @brief Method that returns a const-iterator to nullptr
         * @return Const-iterator to nullptr
         */
        const_iterator cend() const noexcept
        {         
            const_iterator it{nullptr};    
            return it; 
        }

        /**
         *  @brief Insert the node of given key
         *  @param data Pair data to be inserted
         *  @return A pair<iterator, bool>
         */
        std::pair<iterator, bool> insert(const std::pair<const KeyType, ValueType>& data);

        /**
         *  @brief Insert the node of given key
         *  @param data r-value of the pair data to be inserted
         *  @return A pair<iterator, bool>
         */
        std::pair<iterator, bool> insert(std::pair<const KeyType, ValueType>&& data);      

        /**
         *  @brief emplace given data to tree specified position
         *  @param args The data to be inserted
         *  @return A pair (iterator, bool)
         */
        template<class... Types>
        std::pair<iterator,bool> emplace(Types&&... args)
        {
            return insert(std::pair<const KeyType, ValueType>{std::forward<Types>(args)...});
        }


        /**
         *  @brief Clears all the elements of the tree
         */
        void clear() noexcept { root.reset(); }

        iterator find(const KeyType& key)
        {
            return find_aux(key, root.get());
        }

        const_iterator find(const KeyType& key) const
        {
            return find_aux(key, root.get());
        }

        /**
         * @brief Given a key, find the node and delete the node
         * @param key The key of the node to be found and deleted
         */
        void erase(const KeyType& key)
        {
            erase_aux(key, root.get());
        }

        /**
         * @brief Method to get the root of tree
         * @return Pointer to Node
         */
        Node* getRoot() 
        {
            return root.get();
        }

        /**
         *  @brief Auxiliary recursive function to build a bst
         *  @param nodes Containers of nodes
         *  @param start Beginning position
         *  @param end Ending position
         */ 
        void buildTree(std::vector<std::pair<KeyType,ValueType>> &nodes, int start, int end);
        
        /**
         * @brief Method to find the height of tree
         * @param node Pointer to tree's root
         * @return The height of the tree
         */
        int height(Node* node); 

        /**
         * @brief Find if tree is balanced
         * @param node Pointer to root node of tree
         * @return 1 if tree is balanced, otherwise 0
         */
        bool isBalanced(Node* node);
        
        /**
         *  @brief function that balance the tree
         */ 
        void balance();

        ValueType& operator[](const KeyType& key) noexcept;
        ValueType& operator[](KeyType&& key) noexcept;
};
/*
template <class KeyType, class ValueType, class CompareType>
typename bst<KeyType,ValueType,CompareType>::Node * bst<KeyType,ValueType,CompareType>::successor(Node * node) const
{
    if (node->right)
    {
        return leftmost(node->right.get());
    }

    Node * p = node->parent;        
    while (p && node == p->right.get())
    {
        node = p;
        p = p->parent;
    }

    return p;
}
*/
template <class KeyType, class ValueType, class CompareType>
typename bst<KeyType,ValueType,CompareType>::Node * bst<KeyType,ValueType,CompareType>::leftmost(Node * node) const
{
    if (node)
    {
        while (node->get_left())
        {
            node = node->get_left().get();
        }
    }

    return node;
}

template <class KeyType, class ValueType, class CompareType>
void bst<KeyType,ValueType,CompareType>::copy(const std::unique_ptr<bst<KeyType,ValueType,CompareType>::Node> &node)
{
    if (node)
    {
        insert(node->data);
        copy(node->left);
        copy(node->right);
    }
}

template <class KeyType, class ValueType, class CompareType>
std::pair<typename bst<KeyType, ValueType, CompareType>::iterator, bool> 
bst<KeyType, ValueType, CompareType>::insert(const std::pair<const KeyType, ValueType> &data)
{
    // If tree isn't empty, cur node will be created
    Node *current = root.get();

    while (current)
    {
        if (comparator(data.first, current->get_data().first))
        {
            if (!current->get_left())
            {
                current->set_left(std::move(data), current);
                iterator it{current->get_left().get()};
                return std::pair<iterator, bool>{it, true};
            }

            current = current->get_left().get();
        }
        else if (comparator(current->get_data().first, data.first))
        {
            if (!current->get_right())
            {
                current->set_right(std::move(data), current);
                iterator it{current->get_right().get()};
                return std::pair<iterator, bool>{it, true};
            }

            current = current->get_right().get();
        }
        else
        {
            //the key already exists in the tree
            iterator it{current};
            return std::pair<iterator, bool>{it, false};
        }
    }

    //current is root and it's nullptr
    root = std::make_unique<Node>(std::move(data));
    iterator it{root.get()};
    return std::pair<iterator, bool>{it, true};
}

template <class KeyType, class ValueType, class CompareType>
std::pair<typename bst<KeyType, ValueType, CompareType>::iterator, bool> 
bst<KeyType, ValueType, CompareType>::insert(std::pair<const KeyType, ValueType> &&data)
{
    // If tree isn't empty, cur node will be created
    Node *current = root.get();
    //using pair_type = std::pair<const KeyType, ValueType>;

    while (current)
    {
        if (comparator(data.first, current->get_data().first))
        {
            if (!current->get_left())
            {
                //current->left = std::make_unique<Node>(
                //    std::forward<pair_type>(data), current);
                current->set_left(std::move(data), current);
                iterator it{current->get_left().get()};
                return std::pair<iterator, bool>{it, true};
            }

            current = current->get_left().get();
        }
        else if (comparator(current->get_data().first, data.first))
        {
            if (!current->get_right())
            {
                //current->right = std::make_unique<Node>(
                //    std::forward<pair_type>(data), current);
                current->set_right(std::move(data), current);
                iterator it{current->get_right().get()};
                return std::pair<iterator, bool>{it, true};
            }

            current = current->get_right().get();
        }
        else
        {
            //the key already exists in the tree
            iterator it{current};
            return std::pair<iterator, bool>{it, false};
        }
    }

    //current is root and it's nullptr
    root = std::make_unique<Node>(std::move(data));
    iterator it{root.get()};
    return std::pair<iterator, bool>{it, true};
}

template <class KeyType, class ValueType, class CompareType>
typename bst<KeyType, ValueType, CompareType>::iterator 
bst<KeyType, ValueType, CompareType>::find_aux(const KeyType &key, Node *current)
{
    // until current equals to null pointer
    while (current)
    {
        // given key is smaller than current go left
        if (comparator(key, current->get_data().first))
        {
            current = current->get_left().get();
        }
        else if (comparator(current->get_data().first, key))
        {
            current = current->get_right().get();
        }
        else
        {
            // it is equal return current one
            return iterator{current};
        }
    }

    // key does not exist in tree
    return end();
}

template <class KeyType, class ValueType, class CompareType>
typename bst<KeyType, ValueType, CompareType>::const_iterator
bst<KeyType, ValueType, CompareType>::find_aux(const KeyType &key, Node *current) const
{    
    // until current equals to null pointer
    while (current)
    {
        // given key is smaller than current go left
        if (comparator(key, current->get_data().first))
        {
            current = current->get_left().get();
        }
        else if (comparator(current->get_data().first, key))
        {
            current = current->get_right().get();
        }
        else
        {
            // it is equal return current one
            return const_iterator{current};
        }
    }

    // key does not exist in tree
    return cend();
}

template <class KeyType, class ValueType, class CompareType>
void bst<KeyType, ValueType, CompareType>::swap(Node* node1, Node* node2)
{
    Node *n1_left, *n1_right, *n1_parent, *n2_left, *n2_right, *n2_parent;

    //Detach node1's children
    n1_left = node1->detach_left();
    n1_right = node1->detach_right();
    n1_parent = node1->get_parent();

    //detach node1 from its parent. If it has no parent (it is root)
    //we release the ownership of root
    if (node1->is_right())
    {
        n1_parent->detach_right();
    }
    else if (node1->is_left())
    {
        n1_parent->detach_left();
    }
    else
    {
        root.release();
    }
    
    //Detach node2's children
    n2_left = node2->detach_left();
    n2_right = node2->detach_right();
    n2_parent = node2->get_parent();

    //detach node2 from its parent. If it has no parent (it is root)
    //we release the ownership of root
    if (node2->is_right())
    {
        n2_parent->detach_right();
    }
    else if (node2->is_left())
    {
        n2_parent->detach_left();
    }
    else
    {
        root.release();
    }
    
    
    if (n1_parent)
    {   
        //to check whether node1 was left or right child we 
        if (comparator(node2->get_data().first, n1_parent->get_data().first))
        {
            n1_parent->set_left(node2);
        }
        else
        {
            n1_parent->set_right(node2);
        }
    }
    else
    {
        root.reset(node2);
    }
    node2->set_left(n1_left);
    node2->set_right(n1_right);

    if (n2_parent)
    {
        if (comparator(node1->get_data().first, n2_parent->get_data().first))
        {
            n2_parent->set_left(node1);
        }
        else
        {
            n2_parent->set_right(node1);
        }
    }
    else
    {
        root.reset(node1);
    }
    node1->set_left(n2_left);
    node1->set_right(n2_right);
}

template <class KeyType, class ValueType, class CompareType>
void bst<KeyType, ValueType, CompareType>::erase_aux(const KeyType &key, Node* node)
{
    
    Node* current = find_aux(key, node).get_node();
    if (!current)
    {
        return;
    }
    Node* parent = current->get_parent();

    //Case 1: current is a leaf
    if (!current->get_left() && !current->get_right())
    {
        if (current != root.get())
        {
            //if current is left child of its parent
            if (parent->get_left().get() == current)
            {
                parent->destroy_left();
            }
            else
            {
                parent->destroy_right();
            }
            
        }
        //if current is the root
        else
        {
            root.reset();
            return;
        }
    }
    //Case 2: current has both right and left child
    else if (current->get_left() && current->get_right())
    {
        // We get the successor of the current node, which,
        // in the case current has the right child, is the
        // leftmost node in the subtree rooted in the right child
        // of current
        Node* successor = leftmost(current->get_right().get());
        //we swap successor and current
        swap(successor, current);
        //recursively delete current, which now is either a leaf or a node
        //with only one child
        erase_aux(key, current->get_parent());
    }
    //Case 3: current has only one child
    else
    {
        Node* child = (current->get_left()) ? current->detach_left() : current->detach_right();

        if (current != root.get())
        {
            if (current == parent->get_left().get())
            {
                parent->detach_left();
                parent->set_left(child);
            }
            else
            {
                parent->detach_right();
                parent->set_right(child);
            }
        }
        else
        {
            root.release();
            child->set_parent(nullptr);
            root.reset(child);
        }

        delete current;
    }
}

template <class KeyType, class ValueType, class CompareType>
std::ostream &operator<<(std::ostream &os, const bst<KeyType,ValueType,CompareType> &x)
{
    for (auto &node : x)
    {
        os << "(" << node.first << ", " << node.second << ")";
    }
    return os;
}

template <class KeyType, class ValueType, class CompareType>
void bst<KeyType,ValueType,CompareType>::buildTree(std::vector<std::pair<KeyType, ValueType>> &nodes, int start, int end)
{
    if (start > end)
        return;

    if (start == end)
    {
        insert(nodes[start]);
        return;
    }
    // Get the middle element
    int mid = (start + end) / 2;
    insert(nodes[mid]);

    buildTree(nodes, start, mid - 1);
    buildTree(nodes, mid + 1, end);
}

template <class KeyType, class ValueType, class CompareType>
int bst<KeyType, ValueType, CompareType>::height(typename bst<KeyType, ValueType, CompareType>::Node* node)
{
    if (!node)
    {
        return 0;
    }
    return 1 + std::max(height(node->get_left().get()),
                        height(node->get_right().get()));
}

template <class KeyType, class ValueType, class CompareType>
bool bst<KeyType,ValueType,CompareType>::isBalanced(typename bst<KeyType, ValueType, CompareType>::Node* node)
{
    if (!node)
    {
        return true;
    }

    int lh, rh;

    lh = height(node->get_left().get());
    rh = height(node->get_right().get());

    return abs(lh - rh) <= 1 && isBalanced(node->left.get()) && isBalanced(node->right.get());
}

template <class KeyType, class ValueType, class CompareType>
void bst<KeyType, ValueType, CompareType>::balance()
{
    std::vector<std::pair<KeyType, ValueType>> nodes;
    for(auto& node : *this)
    {
        nodes.push_back(node);
    }
    
    clear();

    buildTree(nodes, 0, nodes.size() - 1);
}

template <class KeyType, class ValueType, class CompareType>
ValueType& bst<KeyType,ValueType,CompareType>::operator[](const KeyType &key) noexcept
{
    Node *current = root.get();

    while (current)
    {
        if (comparator(key, current->get_data().first))
        {
            if (!current->get_left())
            {
                auto pair = std::pair<const KeyType, ValueType>{key, ValueType{}};
                //current->left = std::make_unique<Node>(pair, current);
                current->set_left(pair, current);
                return current->get_left()->get_data().second;
            }
            else
            {
                current = current->get_left().get();
            }
        }
        else if (comparator(current->get_data().first, key))
        {

            if (!current->get_right())
            {
                auto pair = std::pair<const KeyType, ValueType>{key, ValueType{}};
                current->set_right(pair, current);
                return current->get_right()->get_data().second;
            }
            else
            {
                current = current->get_right().get();
            }
        }
        else
        {
            return current->get_data().second;
        }
    }

    //root is null
    auto pair = std::pair<const KeyType, ValueType>{key, ValueType{}};
    root = std::make_unique<Node>(pair, nullptr);
    return root->get_data().second;
}

template <class KeyType, class ValueType, class CompareType>
ValueType& bst<KeyType,ValueType,CompareType>::operator[](KeyType &&key) noexcept
{
    Node *current = root.get();
    while (current)
    {
        if (comparator(std::forward<KeyType>(key), current->get_data().first))
        {
            if (!current->get_left())
            {
                auto pair = std::pair<const KeyType, ValueType>{
                    std::forward<KeyType>(key), ValueType{}};
                //current->left = std::make_unique<Node>(pair, current);
                current->set_left(pair, current);
                return current->get_left()->get_data().second;
            }
            else
            {
                current = current->get_left().get();
            }
        }
        else if (comparator(current->get_data().first, std::forward<KeyType>(key)))
        {

            if (!current->get_right())
            {
                auto pair = std::pair<const KeyType, ValueType>{
                    std::forward<KeyType>(key), ValueType{}
                };
                //current->right = std::make_unique<Node>(pair, current);
                current->set_right(pair, current);
                return current->get_right()->get_data().second;
            }
            else
            {
                current = current->get_right().get();
            }
        }
        else
        {
            //element found
            return current->get_data().second;
        }
    }

    //root is null
    auto pair = std::pair<const KeyType, ValueType>{std::forward<KeyType>(key), ValueType{}};
    root = std::make_unique<Node>(pair, nullptr);
    return root->get_data().second;
}


#include "node.hxx"

#endif