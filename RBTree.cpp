
#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>
#include<string>

enum class Color { RED, BLACK };

template <typename T>
class RBTree {
private:
    struct Node {
        int key;
        T data;
        Node* left;
        Node* right;
        Node* parent;
        Color color;
        int index;

        Node(int key, T value,int idx)
            : key(key),
            data(value),
            index(idx),
            left(nullptr),
            right(nullptr),
            parent(nullptr),
            color(Color::RED){}
        
    };
    int next_indeks;
    std::size_t size_;
    Node* root_;

    /*
     before left rotation:

              parent
                |
                x(B)
               /   \
            ?      y(R)
                  /   \
                ?      ?

    after left rotation:

              parent
                |
                y(R)
               /   \
            x(B)    ?
           /   \
         ?      ?

    */

    void rotate_left(Node* x, Node* y) {
        assert(x != nullptr);
        assert(y != nullptr);
        assert(x->right == y);

        Node* beta = y->left;

        // y do g�ry
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root_ = y;
        }
        else if (x->parent->left == x) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }

        // przyczepic x na lewo od y's 
        y->left = x;
        x->parent = y;

        // dodaj beta do x->right
        x->right = beta;
        if (beta != nullptr) {
            beta->parent = x;
        }
    }

    /*
     before right rotation:

              parent
                |
                x(B)
               /   \
            y(R)    ?
           /   \
          ?     ?

    after right rotation:

              parent
                |
                y(R)
               /   \
             ?      x(B)
                   /   \
                  ?     ?

    */

    void rotate_right(Node* x, Node* y) {
        assert(x != nullptr);
        assert(y != nullptr);
        assert(x->left == y);
        Node* beta = y->right;
        //up y
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root_ = y;
        }
        else if (x->parent->left == x) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        y->right = x;
        x->parent = y;
        x->left = beta;
        if (beta != nullptr) {
            beta->parent = x;
        }


             
    }

    static Color node_color(Node* n) { return n ? n->color : Color::BLACK; }

    void fix_after_insert(Node* C) {
        // C root
        if (C == root_) {
            C->color = Color::BLACK;
            return;
        }

        Node* P = C->parent;
        if (node_color(P) == Color::BLACK) {
            //rodzic czarny
            return;
        }

        Node* G = P->parent;
        if (G == nullptr) {
            // jesli rodzic jest czerwony i nie ma rodzica(dziadka) to zmie� kolor
            P->color = Color::BLACK;
            return;
        }

        Node* U = (G->left == P ? G->right : G->left);

        // wujek czerwony zmiana koloru i reku
        if (node_color(U) == Color::RED) {
            P->color = Color::BLACK;
            U->color = Color::BLACK;
            G->color = Color::RED;
            fix_after_insert(G);
            return;
        }

        // kiedy wujek jest czarny
        if (P == G->left) {
            /*
                  G (black)
                 /
                P (red)
                 \
                  N (red)
            */

            // wnuczek (left-right) -> na pocz�tku z rodzicem
            if (C == P->right) {
                rotate_left(P, C);
                C = P;
                P = C->parent;
            }

            /*
                    G (black)
                    /
                   P (red)
                  /
                N (red)
            */

            // zewnetrznt wnuczek (left-left): rotacja z dziadkiem
            rotate_right(G, P);
            P->color = Color::BLACK;
            G->color = Color::RED;
        }
        else {
            if (C == P->left) {
                /*
                    G (black)
                     \
                      P (red)
                     /
                    N (red)
                */
                rotate_right(P, C);
                C = P;
                P = C->parent;
            }

            /*
              G (black)
              \
                P (red)
                \
                  N (red)
            */
            rotate_left(G, P);
            P->color = Color::BLACK;
            G->color = Color::RED;
        }

        // zeby root by� czarny
        if (root_ != nullptr) {
            root_->color = Color::BLACK;
        }
    }
    int height(Node* node) {
        if (node == nullptr) {
            return 0;
        }

        int left_h = height(node->left);
        int right_h = height(node->right);

        return std::max(left_h, right_h) + 1;
    }
    void destroy(Node* node) {
        if (node == nullptr) {
            return;
        }
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
    void write_out(Node* node) {
        if (node == nullptr) return;

        std::string col = (node->color == Color::RED) ? "red" : "black";
        std::string parent_index = (node->parent) ? std::to_string(node->parent->index) : "NULL";
        std::string left_index = (node->left) ? std::to_string(node->left->index) : "NULL";
        std::string right_index = (node->right) ? std::to_string(node->right->index) : "NULL";

        std::cout << "(" << node->index << ": [" << col
            << ", p: " << parent_index
            << ", l: " << left_index
            << ", r: " << right_index
            << "] (" << node->key << ", " << node->data << "))" << std::endl;

        write_out(node->left);
        write_out(node->right);
    }
public:
    RBTree() : size_(0), root_(nullptr),next_indeks(0) {}
    ~RBTree() {
        clear();
    }
    std::size_t size() const { return size_; }
    void insert(int key, T data) {
        Node* node = new Node(key, data,next_indeks++);

        Node* x = nullptr;  // parent
        Node* y = root_;    // current

        // wstawianie z bst
        while (y != nullptr) {
            x = y;
            if (node->key < y->key) {
                y = y->left;
            }
            else {
                y = y->right;
            }
        }

        node->parent = x;
        if (x == nullptr) {
            // drzewo bylo puste
            root_ = node;
        }
        else if (node->key < x->key) {
            x->left = node;
        }
        else {
            x->right = node;
        }

        ++size_;
        fix_after_insert(node);
    }
    Node* find(int key) {
        Node* current = root_;
        while (current != nullptr) {
            if (key == current->key) {
                return current;
            }
            else if (key < current->key) {
                current = current->left;
            }
            else {
                current = current->right;
            }

        }
        return nullptr;
    }
    void inorder(Node* node) {
        if (node == nullptr) {
            return;
        }
        inorder(node->left);
        //std::cout << "data: " << node->data << " " << std::endl;
        //std::cout << "index: " << node->index << " " << std::endl;
        std::cout << "key: " << node->key << " " << std::endl;
        inorder(node->right);
    }
    void preorder(Node* node) {

        if (node == nullptr) {
            return;
        }
        //std::cout <<"data: "<< node->data << " " << std::endl;
        //std::cout <<"index: "<< node->index << " " << std::endl;
        std::cout << "key: " << node->key << " " << std::endl;

        preorder(node->left);
        preorder(node->right);

    }
    int height() {
        return height(root_);
    }
    void clear() {
        destroy(root_);
        root_ = nullptr;
        size_ = 0;
       next_indeks = 0;
    }
    void print() {
        std::cout << "red black tree:\n";
        std::cout << "size: " << size_ << "\n{\n";
        write_out(root_);
        std::cout << "}\n";
       
   }
};

int main() {
    srand(1234);
    const int maxo = 1;
    RBTree<int> tree;
    for (int o = 1; o <= maxo; o++) {
        int n = std::pow(10, o);
        clock_t start = clock();
        for (int i = 0; i < n; i++) {
            int v = ((rand() << 15) + rand()) % 100;//1000000000;;
            tree.insert(v, v);
        }
        clock_t end = clock();
        double czas = double(end - start) / CLOCKS_PER_SEC;
        std::cout << "ilosc dodanych elementow: " << n << " czas: " << czas << "s" << std::endl;
       tree.print();
        int h = tree.height();
        double s = double(h) / n;
        double log = std::log2(n);
        double slog = h / log;
        n = tree.size();
        std::cout << "faktyczne n " << n << " wysokosc: " << h << ", h / n : " << s << ", log2(n)" << log << ", h / log2(n) : " << slog << std::endl;
        const int m = 10000;
        int hits = 0;
        start = clock();
        for (int i = 0; i < m; i++) {
            int sv = ((rand() << 15) + rand()) % 100;// 1000000000;
            if (tree.find(sv) != nullptr) {
                hits++;
            }
        }
        end = clock();
        double czass = double(end - start) / CLOCKS_PER_SEC;
        std::cout << "ilosc wyszukiwanych elementow: " << m << " czas wyszukiwania: " << czass << "s,ilosc trafien " << hits << std::endl;
        tree.clear();
    }
   // RBTree<char> tree;
    //tree.insert(55, 'q');
    //tree.insert(35, 'd');
    //tree.insert(62, 'a');
    //tree.insert(60,'n');
    //tree.insert(130, 'v');
    //tree.insert(14, 'u');
    //tree.insert(23, 'i');
    //tree.insert(87, 'x');

    //tree.print();
    return 0;
}
