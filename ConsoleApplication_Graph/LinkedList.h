#pragma once

#include <stdexcept> // ��� ����������

// ����� ���� ������
template <typename T>
class Node {
public:
    // ������
    T data;
    // ��������� �� ��������� ����
    Node<T>* next;

    // ����������� � ����������
    Node(const T& data1) {
        this->data = data1;
        next = nullptr;
    }
};


// ����� ������������ ������
template <typename T>
class LinkedList {
private:
    // ��������� �� ������ ������
    Node<T>* head;

public:
    // ����������� ��� ����������
    LinkedList() {
        head = nullptr;
    }

    // ����������
    // ��������� ��� ���� � ������
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

    // ���������� ���� � ����� ������
    void addNode(const T& data);
    // �������� ���� �� ��������
    void removeNode(const T& data);
    // ����� ���� �� ��������
    // true ���� ���� ������, ����� false
    bool searchNode(T& data) const;
    // ����� ������� ����, ���� �� ������, �� -1
    int searchNodeInd(const T& data) const;
    // �������� ���� �� �������
    T& dataByInd(int ind) const;
    // ����� ������ � �������
    void printList() const;
    // ����� ������ � ����
    void printListToFile(const std::string& filename) const;
    // ��������� ����� � ������
    int ListSize() const;

};



// ���������� ���� � ������
template<typename T>
void LinkedList<T>::addNode(const T& data) {
    Node<T>* newNode = new Node<T>(data);

    // ���� ������ ������, �� ������ ������ �������
    if (head == nullptr) {
        head = newNode;
    }
    // ������� ��������� ���� ������ � ��������� ����� ���� ����� ����
    else {
        Node<T>* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}


// �������� ���� �� ��������
template<typename T>
void LinkedList<T>::removeNode(const T& data) {
    // ���� ������ �� ������
    if (head != nullptr) {

        // ���� ����� ������� ���� �� ������
        if (head->data == data) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;

        }
        // ���� ��������� ���� �� � ������
        // ���� ���� �� ��������
        else {
            Node<T>* current = head;
            while (current->next != nullptr) {
                // ���� ������ ���� ������
                // ������� ��� � ������ ���������
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

// ����� ������� ����
// ���������� -1, ���� ������ ���� ���
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

// ���������� ���������� ��������� � ������
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


// �������� ���� �� �������
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