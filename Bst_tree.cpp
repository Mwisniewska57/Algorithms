



#include<time.h>
#include <iostream>
#include<string>
#include<cmath>
template <typename T>
struct Node {
	int key;
	int index;
	T data;
	Node<T>* left;
	Node<T>* right;
	Node<T>* parent;
	/// konstruktor
	Node(int k, const T& d) {
		key = k;
		data = d;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}
};
template <typename T>
struct bst {
	Node<T>* root;
	std::size_t size;
	int nextindex;
	bst() {
		root = nullptr;
		size = 0;
		nextindex = 0;
	}
	~bst() {
		clear();
	}
	Node<T>* the_smallest_element(Node<T>* node) {
		if (node == nullptr) {
			return nullptr;
		}
		while (node->left != nullptr) {
			node = node->left;
		}
		return node;
	}
	void adding(int key, T data) {   //dodawanie nowego node
		Node<T>* newnode = new Node<T>(key, data);
		newnode->index = nextindex;
		nextindex++;
		Node<T>* current = root;
		Node<T>* parent = nullptr;
		if (root == nullptr) {
			root = newnode;
			size++;
			return;
		}
		else {
			//szukanie miejsca
			while (current != nullptr) {
				parent = current;
				if (key < current->key) {
					current = current->left;
				}
				//jesli juz istnieje
				else if (key == current->key) {
					delete newnode;
					return;
				}
				else {
					current = current->right;
				}
			}
			//dod elementu
			if (key < parent->key) {
				parent->left = newnode;
			}
			else {
				parent->right = newnode;
			}

			//info o rodzicu
			newnode->parent = parent;
			size++;
		}
	}
	Node<T>* find(int key) {
		Node<T>* current = root;
		while (current != nullptr) {
			if (key == current->key) {
				return current;
			}
			else if (key < current->key) {
				current = current->left;
			}
			else  {
				current = current->right;
			}
		
		}
		return nullptr;
	}
	void switching(Node<T>* u, Node<T>* v) { ///przepinanie poddrzewa v na u
		if (u == nullptr) {
			return;
		}
		if (u->parent == nullptr) {//jesli u byl korzenieem to v jest nowym korzeniem
			root = v;
		}
		else if (u == u->parent->left) { //jesli u jest lewym dzieckiem
			u->parent->left = v;
		}
		else {
			u->parent->right = v;
		}
		//aktualizacja rodzica
		if(v!=nullptr){
			v->parent = u->parent;
        }
	}
	void erase(Node<T>* x) {
		if (x == nullptr) {
			return;
		}
		//jesli nie ma lewego dziecka
		if (x->left == nullptr) {
			switching(x, x->right);
		}
		//jesli nie ma prawego
		else if (x->right == nullptr) {
			switching(x, x->left);
		}
		//jesli ma lewe i prawe dziecko
		else {
			Node<T>* y = the_smallest_element(x->right);
			//jesli y nie jest dzieckiem x
			if (y->parent != x) {
				switching(y, y->right); //prawe dziecko y z y
				y->right = x->right; //kradne dziecko x do y
				if (y->right != nullptr) {
					y->right->parent = y;
				}
			}
		    switching(x, y);
			y->left = x->left;
			if (y->left != nullptr) {
				y->left->parent = y;
			}
		}
		delete x;
		--size;
	}
	void preorder(Node<T>* node) {
		
		if (node == nullptr) {
			return;
		}
		//std::cout <<"data: "<< node->data << " " << std::endl;
		//std::cout <<"index: "<< node->index << " " << std::endl;
		std::cout << "key: " << node->key<< " " << std::endl;

		preorder(node->left);
	    preorder(node->right);
    	
	}
	void inorder(Node<T>* node) {
		if (node == nullptr) {
			return;
		}
		inorder(node->left);
		//std::cout << "data: " << node->data << " " << std::endl;
		//std::cout << "index: " << node->index << " " << std::endl;
		std::cout << "key: " << node->key << " " << std::endl;
		inorder(node->right);
	}
	void destroy(Node<T>* node) {
		if (node == nullptr) {
			return;
		}
		destroy(node->left);
		destroy(node->right);
		delete node;
	}
	void clear() {
		destroy(root);
		root = nullptr;
		size = 0;
		nextindex = 0;
	}
	int height(Node<T>* node) {
		if (node == nullptr) {
			return 0;
		}
		
		int left_h = height(node->left);
		int right_h = height(node->right);
		
		return std::max(left_h, right_h) + 1;
	}
	//ctrl shift /
	void write_out(Node<T>* node) {
		if (node == nullptr) {
			return;
		}
		std::string parent_index = (node->parent) ? std::to_string(node->parent->index) : "null";
		std::string left_index = (node->left) ? std::to_string(node->left->index) : "null";
		std::string right_index = (node->right) ? std::to_string(node->right->index) : "null";
		std::cout << "(" << node->index << " :[p: " << parent_index << " ,l: " << left_index << " ,r: " 
			<< right_index << " ],data: " << node->data << ")"<<" pomocnik->key:"<<node->key<< std::endl;
		write_out(node->left);
		write_out(node->right);

	}
	void naglowekheader() {
		if (root == nullptr) {
			std::cout << "drzewo puste" << std::endl;
			return;
		}
		std::cout << "Binary search tree:" << std::endl;
		std::cout << "size: " << size << std::endl;
		std::cout << "height: " << height(root) << std::endl;
		std::cout << "{" << std::endl;
		write_out(root);
		std::cout << "}" << std::endl;
	}
		
	
};
int main()
{
	srand(time(0));
	const int maxo = 6;
	bst<int> tree;
	for (int o = 1; o <= maxo; o++) {
		int n =std::pow(10, o); 
		clock_t start = clock();
		for (int i = 0; i < n; i++) {
			int v = ((rand() << 15) + rand()) % 1000000000;;
			tree.adding(v, v);
		}
		clock_t end = clock();
		double czas = double(end - start) / CLOCKS_PER_SEC;
		std::cout << "ilosc dodanych elementow: " << n << " czas: " << czas <<"s"<< std::endl;
		///tree.naglowekheader();

		int h = tree.height(tree.root);
		double s = double(h) / n;
		double log = std::log2(n);
		double slog = h / log;
		n = tree.size;
		std::cout << "faktyczne n "<<n<<" wysokosc: " << h << ", h / n : " << s << ", log2(n)" << log << ", h / log2(n) : " << slog << std::endl;
		const int m = 10000;
		int hits = 0;
		start = clock();
		for (int i = 0; i < m; i++) {
			int sv = ((rand()<<15)+rand())%1000000000;
			if (tree.find(sv) != nullptr) {
				hits++;
			}
		}
		end = clock();
		double czass = double(end - start) / CLOCKS_PER_SEC;
		///tree.inorder(tree.root);
		std::cout << "ilosc wyszukiwanych elementow: " << m << " czas wyszukiwania: " << czass << "s,ilosc trafien " << hits << std::endl;
		tree.clear();
		
	}
	//bst<int> tree;
	////key,data
	//tree.adding(10, 4);
	//tree.adding(5, 6);
	//tree.adding(20, 24);
	//tree.adding(30, 8);
	//Node<int>* n1 = tree.find(5);
	//Node<int>* n2 = tree.find(3);
	//if (n1) {
	//	std::cout << "znaleziono n1" << std::endl;;
	//}
	//if (!n2) {
	//	std::cout << "nie znaleziono n2" << std::endl;
	//}
	////Node<int>* nodedousuniecia = tree.find(5);
	////tree.erase(nodedousuniecia);
	//std::cout << "preorder"<<std::endl;
	//tree.preorder(tree.root);
	//std::cout << "inorder"<<std::endl;
	//tree.inorder(tree.root);
	//tree.clear();
	//std::cout << "po clear";
	//tree.adding(10, 23);
	//tree.adding(6, 2);
	//tree.adding(12, 223);
	//tree.adding(3, 423);
	//tree.adding(11, 023);
	//tree.naglowekheader();
	return 0;
}