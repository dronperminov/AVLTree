#pragma once

#include <iostream>

template <typename T>
class AVLTree {
    struct Node {
    	T value; // значение элемента
    	int height; // высота поддерева из данного узла

    	Node *left; // указатель на левое поддерево
    	Node *right; // указатель на правое поддерево
    };

    Node *root; // корень дерева

    Node* RotateLeft(Node *node); // левый поворот
    Node* RotateRight(Node *node); // правый поворот

    int GetBalance(Node *node); // получение сбалансированности дерева

    Node* Insert(Node *node, const T& value); // вставка в дерево
    Node* Remove(Node *node, const T& value); // удаление из дерева

    void Copy(Node *node, Node* &newNode); // копирование дерева
    void Clear(Node* &node); // очистка дерева (освобождение памяти)

    int GetSize(Node *node) const; // количество элементов в дереве
    int GetHeight(Node *node) const; // высота дерева

    void Print(std::ostream &os, Node *node, int level) const; // вывод дерева в виде повёрнутого дерева в поток

public:
    AVLTree(); // конструктор по умолчанию
    AVLTree(const AVLTree& tree); // конструктор копирования

    AVLTree& operator=(const AVLTree& tree); // оператор присваивания

    void Insert(const T& value); // вставка элемента в дерево
    bool Remove(const T& value); // удаление элемента из дерева
    void Clear(); // удаление всех элементов из дерева

    bool Find(const T& value) const; // поиск элемента в дереве

    int GetSize() const; // количество элементов в дереве
    int GetHeight() const; // высота дерева

    ~AVLTree(); // деструктор (освобождение памяти)

    template <typename T1>
    friend std::ostream& operator<<(std::ostream &os, const AVLTree<T1>& tree); // оператор вывода в поток
};

// левый поворот
template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::RotateLeft(Node *node) {
	Node *right = node->right;
	Node *T2 = right->left;

	right->left = node;
	node->right = T2;

	node->height = std::max(GetHeight(node->left), GetHeight(node->right)) + 1;
    right->height = std::max(GetHeight(right->left), GetHeight(right->right)) + 1;

    return right;
}

// правый поворот
template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::RotateRight(Node *node) {
	Node *left = node->left;
	Node *T2 = left->right;

	left->right = node;
	node->left = T2;

	node->height = std::max(GetHeight(node->left), GetHeight(node->right)) + 1;
    left->height = std::max(GetHeight(left->left), GetHeight(left->right)) + 1;

    return left;
}

// получение сбалансированности дерева
template <typename T>
int AVLTree<T>::GetBalance(Node *node) {
	if (node == nullptr)
		return 0;

	return GetHeight(node->left) - GetHeight(node->right);
}

// вставка в дерево
template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::Insert(Node *node, const T& value) {
	if (node == nullptr) {
		node = new Node;

		node->value = value;
		node->height = 1;
		node->left = nullptr;
		node->right = nullptr;

		return node;
	}

	if (value < node->value) {
		node->left = Insert(node->left, value); // вставляем в левое поддерево
	}
	else {
		node->right = Insert(node->right, value);
	}

	node->height = 1 + std::max(GetHeight(node->left), GetHeight(node->right));

	int balance = GetBalance(node);

	if (balance > 1 && value < node->left->value)
        return RotateRight(node);

	if (balance < -1 && value > node->right->value)
		return RotateLeft(node);

	if (balance > 1 && value > node->left->value) {
		node->left = RotateLeft(node->left);
		
		return RotateRight(node);
	}
	
	if (balance < -1 && value < node->right->value) {
		node->right = RotateRight(node->right);
		
		return RotateLeft(node);
	}

	return node;
}

// удаление из дерева
template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::Remove(Node *node, const T& value) {
	if (node == nullptr)
		return nullptr; // если нет узла, возвращаем nullptr

	if (value < node->value) {
		node->left = Remove(node->left, value); // если значение меньше узла, удаляем из левого поддерева
	}
	else if (value > node->value) {
		node->right = Remove(node->right, value); // если значение больше узла, удаляем из правого поддерева
	}
	else {
		if ((node->left == nullptr) || (node->right == nullptr)) {
			Node *tmp = node->left ? node->left : node->right;

			// нет детей
			if (tmp == nullptr) {
				tmp = node;
				node = nullptr;
			}
			else { // один ребёнок
				node->value = tmp->value;
				node->left = tmp->left;
				node->right = tmp->right;
			}
			
			delete tmp;
		}
		else {
			// ищем самую левую вершину
			Node* tmp = node->right;

			while (tmp->left)
				tmp = tmp->left;

			node->value = tmp->value;
			node->right = Remove(node->right, tmp->value);
		}
	}

	// если дерево состоит только из одного элемента
	if (node == nullptr)
		return nullptr;

	node->height = 1 + std::max(GetHeight(node->left), GetHeight(node->right)); // обновляем высоту

	int balance = GetBalance(node); // получаем фактор баланса

	// выполняем повороты в зависимости от значения сбалансированности
	if (balance > 1 && GetBalance(node->left) >= 0)
		return RotateRight(node);

	if (balance > 1 && GetBalance(node->left) < 0) {
		node->left = RotateLeft(node->left);

		return RotateRight(node);
	}

	if (balance < -1 && GetBalance(node->right) <= 0)
		return RotateLeft(node);

	if (balance < -1 && GetBalance(node->right) > 0) {
		node->right = RotateRight(node->right);
		
		return RotateLeft(node);
	}

	return node; // возвращаем узел
}

// копирование дерева
template <typename T>
void AVLTree<T>::Copy(Node *node, Node* &newNode) {
	if (node == nullptr)
		return;

	newNode = new Node;

	newNode->value = node->value;
	newNode->height = node->height;
	newNode->left = nullptr;
	newNode->right = nullptr;

	Copy(node->left, newNode->left); // копируем левое поддерево
	Copy(node->right, newNode->right); // копируем правое поддерево
}

// удаление элементов из дерева и освобождение памяти
template <typename T>
void AVLTree<T>::Clear(Node* &node) {
	if (node == nullptr)
		return;

	Clear(node->left); // удаляем левое поддерево
	Clear(node->right); // удаляем правое поддерево

	delete node; // удаляем элемент
	node = nullptr; // обнуляем значение элемента
}

// количество элементов в дереве
template <typename T>
int AVLTree<T>::GetSize(Node *node) const {
	if (node == nullptr)
		return 0; // лист не считается за элемент

	int leftSize = GetSize(node->left); // находим число элементов в левом поддереве
	int rightSize = GetSize(node->right); // находим число элементов в правом поддереве

	return 1 + leftSize + rightSize; // итоговое число элементов - сумма числа элементов в поддеревьях + 1
}

// высота дерева
template <typename T>
int AVLTree<T>::GetHeight(Node *node) const {
	if (node == nullptr)
		return 0; // высота листа равна 0

	return node->height; // возвращаем высоту узла
}

// вывод дерева в виде повёрнутого дерева в поток
template <typename T>
void AVLTree<T>::Print(std::ostream &os, Node *node, int level) const {
	if (node == nullptr)
		return;

	Print(os, node->right, level + 1);

	for (int i = 0; i < level; i++)
		os << "    ";

	os << node->value << std::endl;

	Print(os, node->left, level + 1);
}

// конструктор по умолчанию
template <typename T>
AVLTree<T>::AVLTree() {
	root = nullptr; // изначально дерева нет
}

// конструктор копирования
template <typename T>
AVLTree<T>::AVLTree(const AVLTree& tree) {
	Copy(tree.root, root);
}

// оператор присваивания
template <typename T>
AVLTree<T>& AVLTree<T>::operator=(const AVLTree& tree) {
    if (this == &tree)
        return *this;

    Clear(root); // очищаем текущее дерево
    Copy(tree.root, root); // копируем второе дерево

    return *this;
}

template <typename T>
void AVLTree<T>::Insert(const T& value) {
	root = Insert(root, value);
}

template <typename T>
bool AVLTree<T>::Remove(const T& value) {
	if (!Find(value))
		return false;

	root = Remove(root, value);

	return true;
}

// удаление всех элементов из дерева
template <typename T>
void AVLTree<T>::Clear() {
	Clear(root); // вызываем рекурсивную функцию очистки от дерева
}

// поиск элемента в дереве
template <typename T>
bool AVLTree<T>::Find(const T& value) const {
	Node *node = root;

	while (node) {
		if (node->value == value)
			return true;

		if (value < node->value) {
			node = node->left;
		}
		else {
			node = node->right;
		}
	}

	return false;
}

// количество элементов в дереве
template <typename T>
int AVLTree<T>::GetSize() const {
	return GetSize(root); // вызываем рекурсивную версию получения размера
}

// высота дерева
template <typename T>
int AVLTree<T>::GetHeight() const {
	return root == nullptr ? 0 : root->height; // если дереева нет, то высота ноль, иначе возвращаем высоту
}

// деструктор (освобождения памяти)
template <typename T>
AVLTree<T>::~AVLTree() {
	Clear(root);
}

// оператор вывода в поток
template <typename T>
std::ostream& operator<<(std::ostream &os, const AVLTree<T>& tree) {
    tree.Print(os, tree.root, 0);

    return os;
}