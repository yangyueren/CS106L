/**
 * File: KDTree.h
 * Author: (your name here)
 * ------------------------
 * An interface representing a kd-tree in some number of dimensions. The tree
 * can be constructed from a set of data and then queried for membership and
 * nearest neighbors.
 */

#ifndef KDTREE_INCLUDED
#define KDTREE_INCLUDED

#include "Point.h"
#include "BoundedPQueue.h"
#include <stdexcept>
#include <cmath>
#include <iostream>
// "using namespace" in a header file is conventionally frowned upon, but I'm
// including it here so that you may use things like size_t without having to
// type std::size_t every time.
using namespace std;

template <size_t N, typename ElemType>
struct Node{
    Point<N> pt;
    ElemType val;
    unique_ptr<Node<N, ElemType> > left;
    unique_ptr<Node<N, ElemType> > right;
    int level;
    int dim;

    Node():level(0), dim(N){

    }
    Node(Point<N> pt, ElemType val, int level): pt(pt), val(val), level(level), left(nullptr), right(nullptr), dim(N){

    }
    // add insert method for Node.
    bool insert(const Point<N>& point, const ElemType& value){
//        cout << "insert in the node struct" <<endl;
        if(point == pt){
            val = value;
            return false;
        }
        else if(point[level % dim] <= pt[level % dim]){
            if(this->left){
                return this->left->insert(point, value);
            }else{
                this->left.reset(new Node<N,ElemType>(point, value, level+1));
                return true;
            }

        }else{
            if(this->right){
                return this->right->insert(point, value);
            }else{
                this->right.reset(new Node<N,ElemType>(point, value, level+1));
                return true;
            }

        }

    }
};

template <size_t N, typename ElemType>
class KDTree {
public:
    // Constructor: KDTree();
    // Usage: KDTree<3, int> myTree;
    // ----------------------------------------------------
    // Constructs an empty KDTree.
    KDTree();
    
    // Destructor: ~KDTree()
    // Usage: (implicit)
    // ----------------------------------------------------
    // Cleans up all resources used by the KDTree.
    ~KDTree();
    
    // KDTree(const KDTree& rhs);
    // KDTree& operator=(const KDTree& rhs);
    // Usage: KDTree<3, int> one = two;
    // Usage: one = two;
    // -----------------------------------------------------
    // Deep-copies the contents of another KDTree into this one.
    KDTree(const KDTree& rhs);
    KDTree& operator=(const KDTree& rhs);
    
    // size_t dimension() const;
    // Usage: size_t dim = kd.dimension();
    // ----------------------------------------------------
    // Returns the dimension of the points stored in this KDTree.
    size_t dimension() const;
    
    // size_t size() const;
    // bool empty() const;
    // Usage: if (kd.empty())
    // ----------------------------------------------------
    // Returns the number of elements in the kd-tree and whether the tree is
    // empty.
    size_t size() const;
    bool empty() const;
    
    // bool contains(const Point<N>& pt) const;
    // Usage: if (kd.contains(pt))
    // ----------------------------------------------------
    // Returns whether the specified point is contained in the KDTree.
    bool contains(const Point<N>& pt) const;
    
    // void insert(const Point<N>& pt, const ElemType& value);
    // Usage: kd.insert(v, "This value is associated with v.");
    // ----------------------------------------------------
    // Inserts the point pt into the KDTree, associating it with the specified
    // value. If the element already existed in the tree, the new value will
    // overwrite the existing one.
    void insert(const Point<N>& pt, const ElemType& value);
    
    // ElemType& operator[](const Point<N>& pt);
    // Usage: kd[v] = "Some Value";
    // ----------------------------------------------------
    // Returns a reference to the value associated with point pt in the KDTree.
    // If the point does not exist, then it is added to the KDTree using the
    // default value of ElemType as its key.
    ElemType& operator[](const Point<N>& pt);
    
    // ElemType& at(const Point<N>& pt);
    // const ElemType& at(const Point<N>& pt) const;
    // Usage: cout << kd.at(v) << endl;
    // ----------------------------------------------------
    // Returns a reference to the key associated with the point pt. If the point
    // is not in the tree, this function throws an out_of_range exception.
    ElemType& at(const Point<N>& pt);
    const ElemType& at(const Point<N>& pt) const;
    
    // ElemType kNNValue(const Point<N>& key, size_t k) const
    // Usage: cout << kd.kNNValue(v, 3) << endl;
    // ----------------------------------------------------
    // Given a point v and an integer k, finds the k points in the KDTree
    // nearest to v and returns the most common value associated with those
    // points. In the event of a tie, one of the most frequent value will be
    // chosen.
    ElemType kNNValue(const Point<N>& key, size_t k) const;


private:
    // TODO: Add implementation details here.

    unique_ptr<Node<N, ElemType> > root;
    size_t num_nodes;
    size_t dim;

    const unique_ptr<Node<N, ElemType> >& findNode(const unique_ptr<Node<N, ElemType> >& root ,const Point<N>& pt) const;
    void search(BoundedPQueue<Point<N> > &q, const unique_ptr<Node<N, ElemType> >& root, const Point<N>& key, size_t k);
    unique_ptr<Node<N, ElemType> > copyNodes(const unique_ptr<Node<N, ElemType> >& root);

};

/** KDTree class implementation details */

// my own methods

template <size_t N, typename ElemType>
const unique_ptr<Node<N, ElemType> >& KDTree<N, ElemType>::findNode(const unique_ptr<Node<N, ElemType> >& node, const Point<N>& pt) const{
    if(node == nullptr) return node;
    if(node->pt == pt) return node;
    if(pt[node->level % node->dim] <= node->pt[node->level % node->dim]){
        return findNode(node->left, pt);
    }else{
        return findNode(node->right, pt);
    }

}

template <size_t N, typename ElemType>
unique_ptr<Node<N, ElemType> > KDTree<N, ElemType>::copyNodes(const unique_ptr<Node<N, ElemType> >& root){
    if(root == nullptr) return nullptr;
    unique_ptr<Node<N, ElemType> > new_root(new Node<N, ElemType>(root->pt, root->val, root->level));
    new_root->left = copyNodes(root->left);
    new_root->right = copyNodes(root->right);
    return new_root;
}

template <size_t N, typename ElemType>
KDTree<N, ElemType>::KDTree(const KDTree<N, ElemType> &rhs){
    this->root = copyNodes(rhs.root);
    this->dim = rhs.dim;
    this->num_nodes = rhs.num_nodes;
}
template <size_t N, typename ElemType>
KDTree<N, ElemType>& KDTree<N, ElemType>::operator=(const KDTree<N, ElemType> &rhs){
    if(this != &rhs){
        //when the unique_ptr is assigned with another pointer, its original data will destruct.
        this->root = copyNodes(rhs.root);
        this->dim = rhs.dim;
        this->num_nodes = rhs.num_nodes;
    }
    return *this;
}


template <size_t N, typename ElemType>
KDTree<N, ElemType>::KDTree():root(nullptr), num_nodes(0), dim(N) {
    // TODO: Fill this in.
    //done
}

template <size_t N, typename ElemType>
KDTree<N, ElemType>::~KDTree() {
    // TODO: Fill this in.
    //done
}

template <size_t N, typename ElemType>
size_t KDTree<N, ElemType>::dimension() const {
    // TODO: Fill this in.
    return dim;
}

// TODO: finish the implementation of the rest of the KDTree class

template <size_t N, typename ElemType>
size_t KDTree<N, ElemType>::size() const{
    return num_nodes;
}

// size_t size() const;
// bool empty() const;
// Usage: if (kd.empty())
// ----------------------------------------------------
// Returns the number of elements in the kd-tree and whether the tree is
// empty.
template <size_t N, typename ElemType>
bool KDTree<N, ElemType>::empty() const{
    if(num_nodes==0) return true;
    else return false;
}

// bool contains(const Point<N>& pt) const;
// Usage: if (kd.contains(pt))
// ----------------------------------------------------
// Returns whether the specified point is contained in the KDTree.
template <size_t N, typename ElemType>
bool KDTree<N, ElemType>::contains(const Point<N>& pt) const{
    return findNode(this->root, pt) != nullptr;
}

// void insert(const Point<N>& pt, const ElemType& value);
// Usage: kd.insert(v, "This value is associated with v.");
// ----------------------------------------------------
// Inserts the point pt into the KDTree, associating it with the specified
// value. If the element already existed in the tree, the new value will
// overwrite the existing one.
template <size_t N, typename ElemType>
void KDTree<N, ElemType>::insert(const Point<N>& pt, const ElemType& value){
    if(this->root == nullptr){
//        cout << "kdtree insert null" <<endl;
        this->root.reset(new Node<N, ElemType>(pt, value, 0));
        this->num_nodes++;
    }else{
        auto flag = this->root->insert(pt, value);
        if(flag) this->num_nodes++;
    }


}

// ElemType& operator[](const Point<N>& pt);
// Usage: kd[v] = "Some Value";
// ----------------------------------------------------
// Returns a reference to the value associated with point pt in the KDTree.
// If the point does not exist, then it is added to the KDTree using the
// default value of ElemType as its key.
template <size_t N, typename ElemType>
ElemType& KDTree<N, ElemType>::operator[](const Point<N>& pt){
    const unique_ptr<Node<N, ElemType> >& node = findNode(this->root, pt);
    if(node == nullptr){
        this->insert(pt, ElemType());
        const unique_ptr<Node<N, ElemType> >& node = findNode(this->root, pt);
        return node->val;
    }else{
        return node->val;
    }

}

// ElemType& at(const Point<N>& pt);
// const ElemType& at(const Point<N>& pt) const;
// Usage: cout << kd.at(v) << endl;
// ----------------------------------------------------
// Returns a reference to the key associated with the point pt. If the point
// is not in the tree, this function throws an out_of_range exception.
template <size_t N, typename ElemType>
ElemType& KDTree<N, ElemType>::at(const Point<N>& pt){
    const unique_ptr<Node<N, ElemType> >& node = findNode(this->root, pt);
    if(node == nullptr){
        throw out_of_range("out of range: at[]");

    }else{
        return node->val;
    }
}

template <size_t N, typename ElemType>
const ElemType& KDTree<N, ElemType>::at(const Point<N>& pt) const{
    const unique_ptr<Node<N, ElemType> >& node = findNode(this->root, pt);
    if(node == nullptr){
        throw out_of_range("out of range: at[]");

    }else{
        return node->val;
    }
}


template <size_t N, typename ElemType>
void KDTree<N, ElemType>::search(BoundedPQueue<Point<N> > &q, const unique_ptr<Node<N, ElemType> >& root, const Point<N>& key, size_t k){
    if(root == nullptr) return;
    double dis = Distance(root->pt, key);
    q.enqueue(root->pt, dis);
    int dir=0;
    if(key[root->level % root->dim] <= root->pt[root->level % root->dim]){
        search(q, root->left, key, k);
        dir = 0;
    }else{
        search(q, root->right, key, k);
        dir = 1;
    }
    if(q.size() < k || dis < q.worst()){
        if(dir == 0){
            search(q, root->right, key, k);
        }else{
            search(q, root->left, key, k);
        }
    }

}
// ElemType kNNValue(const Point<N>& key, size_t k) const
// Usage: cout << kd.kNNValue(v, 3) << endl;
// ----------------------------------------------------
// Given a point v and an integer k, finds the k points in the KDTree
// nearest to v and returns the most common value associated with those
// points. In the event of a tie, one of the most frequent value will be
// chosen.
template <size_t N, typename ElemType>
ElemType KDTree<N, ElemType>::kNNValue(const Point<N>& key, size_t k) const{
    if(this->root == nullptr) return ElemType();
    BoundedPQueue<Point<N> > q(k);
    //use lambda function to avoid using the search method, which is non const.
    std::function<void(BoundedPQueue<Point<N> > &, const unique_ptr<Node<N, ElemType> >&, const Point<N>&, size_t) > f;
    f = [&](BoundedPQueue<Point<N> > &q, const unique_ptr<Node<N, ElemType> >& root, const Point<N>& key, size_t k){
        if(root == nullptr) return;
        double dis = Distance(root->pt, key);
        q.enqueue(root->pt, dis);
        int dir=0;
        if(key[root->level % root->dim] <= root->pt[root->level % root->dim]){
            f(q, root->left, key, k);
            dir = 0;
        }else{
            f(q, root->right, key, k);
            dir = 1;
        }
        if(q.size() < k || dis < q.worst()){
            if(dir == 0){
                f(q, root->right, key, k);
            }else{
                f(q, root->left, key, k);
            }
        }

    };
    f(q, this->root, key, k);
    std::map<ElemType, int> mp;
    while(!q.empty()){
        auto tmp = q.dequeueMin();
        ElemType t = this->at(tmp);
        if(mp.find(t) != mp.end()){
            mp[t]++;
        }else {
            mp[t] = 1;
        }

    }
    ElemType maxElem;
    int Max = 0;
    for(auto pair: mp){
        if(pair.second > Max){
            Max = pair.second;
            maxElem = pair.first;
        }
    }
    return maxElem;
}

#endif // KDTREE_INCLUDED
