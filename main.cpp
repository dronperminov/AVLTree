#include <iostream>
#include <cstdlib>
#include "AVLTree.hpp"

using namespace std;

void Print(AVLTree<int> &tree) {
	if (tree.GetSize() == 0) {
		cout << "(empty)" << endl;
	}
	else {
		cout << tree;
	}
}

void Insert(AVLTree<int> &tree) {
	int value;

	cout << "Enter value for insert: ";
	cin >> value;

	tree.Insert(value);
	cout << "Inserted!" << endl;
}

void Find(AVLTree<int> &tree) {
	int value;

	cout << "Enter value for search: ";
	cin >> value;

	if (tree.Find(value)) {
		cout << "Find!" << endl;
	}
	else {
		cout << "No value " << value << " in tree" << endl;
	}
}

void Remove(AVLTree<int> &tree) {
	int value;

	cout << "Enter value for remove: ";
	cin >> value;

	if (tree.Remove(value)) {
		cout << "Removed!" << endl;
	}
	else {
		cout << "No value " << value << " in tree" << endl;
	}
}

void GetHeight(AVLTree<int> &tree) {
	cout << "Height: " << tree.GetHeight() << endl;
}

void GetSize(AVLTree<int> &tree) {
	cout << "Size: " << tree.GetSize() << endl;
}

int main() {
    int item; // выбираемый пункт меню
    AVLTree<int> tree; // создаём дерево

    do {
        // выводим меню
        cout << "What do you want to do?" << endl;
        cout << "1. Print" << endl;
        cout << "2. Insert" << endl;
        cout << "3. Find" << endl;
        cout << "4. Remove" << endl;
        cout << "5. Get height" << endl;
        cout << "6. Get size" << endl;
        cout << "7. Quit" << endl;
        cout << ">";
        cin >> item; // считываем пункт меню

        // обрабатываем некорректный ввод
        while(item < 1 || item > 7) {
            cout << "Incorrect item. Try again: ";
            cin >> item; // считываем пункт меню заново
        }

        // в зависимости от выбранного пункта выполняем действие
        switch (item) {
            case 1:
                Print(tree);
                break;

            case 2:
                Insert(tree);
                break;

            case 3:
                Find(tree);
                break;

            case 4:
                Remove(tree);
                break;

            case 5:
                GetHeight(tree);
                break;

            case 6:
                GetSize(tree);
                break;
        }
    } while (item != 7); // повторяем, пока не решим выйти

    return 0;
}