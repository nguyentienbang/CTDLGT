#include <iostream>
#include <string>
#include <unordered_map>
//1.Khai báo cấu trúc của node và danh sách liên kết đơn
struct Node {
    std::string word;
    Node* next;

    Node(std::string w) : word(w), next(nullptr) {}
};

struct LinkedList {
    Node* head;

    LinkedList() : head(nullptr) {}

    void addWord(const std::string& word) {
        Node* newNode = new Node(word);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void removeNode(const std::string& targetWord) {
        if (!head) return;

        Node* temp = head;
        Node* prev = nullptr;

        while (temp) {
            if (temp->word == targetWord) {
                if (prev) {
                    prev->next = temp->next;
                } else {
                    head = temp->next;
                }
                delete temp;
                return;
            }
            prev = temp;
            temp = temp->next;
        }
    }

    void displayList() const {
        Node* temp = head;
        while (temp) {
            std::cout << temp->word << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};

//2.Hàm xác định từ xuất hiện nhiều nhất
std::string findMostFrequentWord(LinkedList& list) {
    std::unordered_map<std::string, int> wordCount;
    Node* current = list.head;

    while (current) {
        wordCount[current->word]++;
        current = current->next;
    }

    std::string mostFrequentWord;
    int maxCount = 0;

    for (const auto& entry : wordCount) {
        if (entry.second > maxCount) {
            maxCount = entry.second;
            mostFrequentWord = entry.first;
        }
    }

    return mostFrequentWord;
}

//3.Hàm loại bỏ từ láy (các từ giống nhau liền kề)
void removeRepetitiveWords(LinkedList& list) {
    Node* current = list.head;
    while (current && current->next) {
        if (current->word == current->next->word) {
            Node* duplicate = current->next;
            current->next = current->next->next;
            delete duplicate;
        } else {
            current = current->next;
        }
    }
}

//4.Hàm đếm số lượng từ vựng xuất hiện trong câu
int countUniqueWords(LinkedList& list) {
    std::unordered_map<std::string, bool> uniqueWords;
    Node* current = list.head;

    while (current) {
        uniqueWords[current->word] = true;
        current = current->next;
    }

    return uniqueWords.size();
}
