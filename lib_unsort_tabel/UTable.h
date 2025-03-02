#include <stdexcept>
#include <utility>
#include "../lib_list/TList.h" 
#include "../lib_pair/TPair.h"

template <class TKey, class TVal>
class TUnsortedTable : public ITable<TKey, TVal> {
private:
    TList<TPair<TKey, TVal>> _data; 

public:
    TUnsortedTable() = default;
    ~TUnsortedTable() override = default;
    TKey insert(TVal value) override {
        TKey new_key = generate_key(); // Генерация ключа
        TPair<TKey, TVal> new_row(new_key, value);
        _data.pushBack(new_row); // Добавление пары в список
        return new_key;
    }

    void insert(TKey key, TVal value) override {
        TPair<TKey, TVal> new_row(key, value);
        _data.pushBack(new_row); // Добавление пары по ключу
    }

    void erase(TKey key) override {
        // Реализация удаления по ключу
        TNode<TPair<TKey, TVal>>* current = _data.getNode(0);
        while (current != nullptr) {
            if (current->getValue().first() == key) {
                _data.removeNode(current);
                return;
            }
            current = current->getNext();
        }
        throw std::runtime_error("Key not found"); 
    }

    TVal& find(TKey key) override {
        // Реализация поиска по ключу
        TNode<TPair<TKey, TVal>>* current = _data.getNode(0);
        while (current != nullptr) {
            if (current->getValue().first() == key) {
                return current->getValue().second(); // Возвращаем значение по ключу
            }
            current = current->getNext();
        }
        throw std::runtime_error("Key not found"); 
    }

    TKey generate_key() {
        static TKey last_key = 0; // Статическая переменная для генерации ключей
        return ++last_key; // Генерация следующего ключа
    }
};
