#include <iostream>
#include <string>
#include <fstream>

class Node
{
public:
	std::string key;
	unsigned long long value;
	char color;
	Node * right;
	Node * left;
	Node * dad;

	Node(std::string &_key, unsigned long long &_value)
	{
		left = NULL;
		right = NULL;
		dad = NULL;
		key = _key;
		value = _value;
		color = 'r';
	}
};

class RB_Tree
{
public:
	Node * root = NULL;

	void left_rotate(Node * node)
	{
		Node * child = node->right;
		node->right = child->left;

		if (child->left != NULL)
			child->left->dad = node;

		child->dad = node->dad;

		if (node->dad == NULL)
			root = child;
		else if (node == node->dad->right)
			node->dad->right = child;
		else
			node->dad->left = child;

		child->left = node;
		node->dad = child;
	}

	void right_rotate(Node * node)
	{
		Node * child = node->left;
		node->left = child->right;

		if (child->right != NULL)
			child->right->dad = node;

		child->dad = node->dad;

		if (node->dad == NULL)
			root = child;
		else if (node == node->dad->right)
			node->dad->right = child;
		else
			node->dad->left = child;

		child->right = node;
		node->dad = child;
	}

	void i_balance(Node * node)
	{
		if (node->dad == NULL)
		{
			node->color = 'b';
			return;
		}

		Node * father = node->dad;

		if (father->color == 'b')    // балансировка окончена 
			return;

		Node * grandfather = father->dad;
		Node * uncle;

		if (father == grandfather->left)
			uncle = grandfather->right;
		else
			uncle = grandfather->left;

		// первый случай
		if (uncle != NULL and uncle->color == 'r')
		{
			if (father->color == 'r' and grandfather->color == 'b')
			{
				father->color = 'b';
				grandfather->color = 'r';
				uncle->color = 'b';
				i_balance(grandfather);
			}
		}
		else
		{
			if (father == grandfather->left)
			{
				if (node == father->right)  // второй случай
				{
					node = father;
					left_rotate(node);
					father = node->dad;
				}

				father->color = 'b';   // третий случай
				grandfather->color = 'r';
				right_rotate(grandfather);
			}
			else if (father == grandfather->right)
			{
				if (node == father->left)  // второй случай
				{
					node = father;
					right_rotate(node);
					father = node->dad;
				}

				father->color = 'b';   // третий случай
				grandfather->color = 'r';
				left_rotate(grandfather);
			}
		}
	}

	void d_balance(Node * collapse)
	{
		while (collapse->color == 'b' and collapse != root)
		{
			Node* father = collapse->dad;

			if (father->left == collapse)
			{
				Node* brother = father->right;
				if (brother != NULL and brother->color == 'r') // случай 4
				{
					brother->color = 'b';
					father->color = 'r';
					left_rotate(father);
					brother = father->right;
				}

				if ((brother->left == NULL or brother->left->color == 'b') and (brother->right == NULL or brother->right->color == 'b')) // случай 3
				{
					brother->color = 'r';
					collapse = father;
				}
				else
				{
					if (brother->right == NULL or brother->right->color == 'b') // случай 2
					{
						brother->left->color = 'b';
						brother->color = 'r';
						right_rotate(brother);
						brother = father->right;
					}

					brother->color = father->color; // случай 1
					father->color = 'b';
					brother->right->color = 'b';
					left_rotate(father);
					collapse = root;
				}
			}
			else // зеркально то же самое
			{
				Node* brother = father->left;

				if (brother != NULL and brother->color == 'r')
				{
					brother->color = 'b';
					father->color = 'r';
					right_rotate(father);
					brother = father->left;
				}

				if ((brother->right == NULL or brother->right->color == 'b') and (brother->left == NULL or brother->left->color == 'b'))
				{
					brother->color = 'r';
					collapse = father;
				}
				else
				{
					if (brother->left == NULL or brother->left->color == 'b')
					{
						brother->right->color = 'b';
						brother->color = 'r';
						left_rotate(brother);
						brother = father->left;
					}

					brother->color = father->color;
					father->color = 'b';
					brother->left->color = 'b';
					right_rotate(father);
					collapse = root;
				}
			}
		}

		collapse->color = 'b';
	}

	void delete_node(Node * node)
	{
		if (node->left != NULL and node->right != NULL)
		{
			Node * change = node->right;
			while (change->left != NULL)
			{
				change = change->left;
			}
			node->key = change->key;
			node->value = change->value;
			delete_node(change);
			return;
		}

		Node * father = node->dad;
		d_balance(node);

		if (father != NULL)
		{
			Node *&  collapse = (father->left == node) ? father->left : father->right;

			if (node->right)
			{
				collapse = node->right;
				node->right->dad = father;
			}
			else if (node->left)
			{
				collapse = node->left;
				node->left->dad = father;
			}
			else
			{
				collapse = NULL;
			}
		}
		else
		{
			if (node->right)
			{
				root = node->right;
				node->right->dad = father;
			}
			else if (node->left)
			{
				root = node->left;
				node->left->dad = father;
			}
			else
			{
				root = NULL;
			}

			if (root != NULL) d_balance(root);
		}

		node->left = node->right = NULL;
		delete node;
	}

	void insert_node(std::string &_key, unsigned long long &_value)
	{
		Node * node = new Node(_key, _value);
		Node * _dad = NULL;
		Node * current = root;

		if (root == NULL)
		{
			node->color = 'b';
			root = node;
			return;
		}

		while (current != NULL)
		{
			_dad = current;
			if (_key > current->key)
				current = current->right;
			else
				current = current->left;
		}

		node->dad = _dad;

		if (_dad->key < _key)
		{
			_dad->right = node;
		}
		else
		{
			_dad->left = node;
		}

		i_balance(node);
	}

	Node * search_from_root(std::string &_key, Node * root)
	{
		if (root == NULL)
			return NULL;

		if (_key > root->key)
		{
			if (root->right != NULL)
				return search_from_root(_key, root->right);
			else
				return NULL;
		}
		else if (_key < root->key)
		{
			if (root->left != NULL)
				return search_from_root(_key, root->left);
			else
				return NULL;
		}
		else
			return root;

		return NULL;
	}

	Node * search_node(std::string &_key)
	{
		Node * result = search_from_root(_key, root);

		return result;
	}

	void save(std::ostream & file, Node * node)
	{
		if (node == NULL) return;

		int key_size = (node->key).size();
		file.write((char *)& key_size, sizeof(int));
		file.write((char *)node->key.c_str(), key_size);
		file.write((char *)& node->value, sizeof(unsigned long long));
		file.write((char *)& node->color, sizeof(char));
		bool right = (node->right != NULL);
		bool left = (node->left != NULL);
		file.write((char *)& right, sizeof(bool));
		file.write((char *)& left, sizeof(bool));

		if (right != NULL)	save(file, node->right);

		if (left != NULL)	save(file, node->left);
	}

	void clearing(Node * node)
	{
		if (node != NULL)
		{
			clearing(node->right);
			clearing(node->left);
			delete node;
		}
	}

	Node * load(std::istream & file)
	{
		int key_size;
		file.read((char*)&key_size, sizeof(int));

		if (file.gcount() == 0 or key_size == 0)
		{
			return NULL;
		}

		char* key = new char[key_size + 1];
		file.read(key, key_size);
    	key[key_size] = '\0';
		std::string str_key = key;
		delete[] key;

		unsigned long long value;
		file.read((char *)& value, sizeof(unsigned long long));

		char color;
		file.read((char *)& color, sizeof(char));

		bool right;
		bool left;
		file.read((char *)& right, sizeof(bool));
		file.read((char *)& left, sizeof(bool));

		Node * node = new Node(str_key, value);
		node->color = color;

		if (right)
		{
			node->right = load(file);
			node->right->dad = node;
		}

		if (left)
		{
			node->left = load(file);
			node->left->dad = node;
		}

		return node;
	}
};

int main()
{
	std::cin.tie(0);
	std::cout.tie(0);
	std::ios::sync_with_stdio(false);

	RB_Tree tree;
	std::string command;

	while (std::cin >> command)
	{
		if (command == "+")
		{
			std::string key;
			unsigned long long value;
			std::cin >> key >> value;

			for (char &x : key)
			{
				x = tolower(x);
			}

			if (tree.search_node(key) == NULL)
			{
				tree.insert_node(key, value);
				std::cout << "OK" << std::endl;
			}
			else
				std::cout << "Exist" << std::endl;
		}
		else if (command == "-")
		{
			std::string key;
			std::cin >> key;

			for (char &x : key)
			{
				x = tolower(x);
			}

			Node * search_result = tree.search_node(key);

			if (search_result != NULL)
			{
				tree.delete_node(search_result);
				std::cout << "OK" << std::endl;
			}
			else
			{
				std::cout << "NoSuchWord" << std::endl;
			}
		}
		else if (command == "!")
		{
			std::string new_command, path;
			std::cin >> new_command >> path;

			std::ofstream out;
			std::ifstream in;

			if (new_command == "Save")
			{
				out.open(path, std::ios::binary | std::ios::out);
				tree.save(out, tree.root);
				std::cout << "OK" << std::endl;
			}
			else    // Load
			{
				tree.clearing(tree.root);
				tree.root = NULL;
				in.open(path, std::ios::binary | std::ios::in);
				tree.root = tree.load(in);
				std::cout << "OK" << std::endl;
			}
		}
		else
		{
			for (char &x : command)
			{
				x = tolower(x);
			}

			Node * search_result = tree.search_node(command);

			if (search_result != NULL)
			{
				//std::cout << search_result->color << " ";
				std::cout << "OK: " << search_result->value << std::endl;
			}
			else
			{
				std::cout << "NoSuchWord" << std::endl;
			}
		}
	}

	tree.clearing(tree.root);
	tree.root = NULL;

	return 0;
}
