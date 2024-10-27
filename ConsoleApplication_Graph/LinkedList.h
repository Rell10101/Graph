#pragma once

#include <stdexcept> // для исключений

// класс узла списка
template <typename T>
class Node {
public:
    // данные
    T data;
    // указатель на следующий узел
    Node<T>* next;

    // конструктор с параметром
    Node(const T& data1) {
        this->data = data1;
        next = nullptr;
    }
};


// класс односвязного списка
template <typename T>
class LinkedList {
private:
    // указатель на начало списка
    Node<T>* head;

public:
    // конструктор без параметров
    LinkedList() {
        head = nullptr;
    }

    // деструктор
    // удаляются все узлы в списке
    ~LinkedList() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void ClearList() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // добавление узла в конец списка
    void addNode(const T& data);
    // Удаление узла по значению
    void removeNode(const T& data);
    // поиск узла по значению
    // true если узел найден, иначе false
    bool searchNode(T& data) const;
    // поиск индекса узла, если не найден, то -1
    int searchNodeInd(const T& data) const;
    // значение узла по индексу
    T& dataByInd(int ind) const;
    // вывод списка в консоль
    void printList() const;
    // вывод списка в файл
    void printListToFile(const std::string& filename) const;
    // количеств узлов в списке
    int ListSize() const;

};



// добавление узла в список
template<typename T>
void LinkedList<T>::addNode(const T& data) {
    Node<T>* newNode = new Node<T>(data);

    // если список пустой, то создаём первый элемент
    if (head == nullptr) {
        head = newNode;
    }
    // находим последний узел списка и добавляем новый узел после него
    else {
        Node<T>* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}


// Удаление узла по значению
template<typename T>
void LinkedList<T>::removeNode(const T& data) {
    // если список не пустой
    if (head != nullptr) {

        // если нужно удалить узел из начала
        if (head->data == data) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;

        }
        // если удаляемый узел не в начале
        // ищем узел на удаление
        else {
            Node<T>* current = head;
            while (current->next != nullptr) {
                // если нужный узел найден
                // удаляем его и меняем указатели
                if (current->next->data == data) {
                    Node<T>* temp = current->next;
                    current->next = current->next->next;
                    delete temp;
                    return;
                }
                current = current->next;
            }
        }
    }
}

// поиск индекса узла
// возвращает -1, если такого узла нет
template<typename T>
int LinkedList<T>::searchNodeInd(const T& data) const {
    Node<T>* current = head;
    int ind = 0;
    while (current != nullptr) {
        if (current->data == data) {
            return ind;
        }
        current = current->next;
        ind++;
    }
    return -1;
}

// возвращает количество элементов в списке
template<typename T>
int LinkedList<T>::ListSize() const {
    int result = 0;
    Node<T>* current = head;
    while (current != nullptr) {
        result++;
        current = current->next;
    }
    return result;
}


// значение узла по индексу
template<typename T>
T& LinkedList<T>::dataByInd(int ind) const {
    if (ind < 0) {
        throw std::invalid_argument("Wrong index");
    }
    else {
        int i = 0;

        Node<T>* current = head;

        while (i < ind) {
            if (current == nullptr || current->next == nullptr) {
                throw std::invalid_argument("Wrong index");
            }
            else {
                current = current->next;
                i++;
            }
        }

        return current->data;

    }
}