#include <stdexcept>
#include <utility>
#include "../lib_list/TList.h"
#include "../lib_pair/TPair.h"
#include "../lib_itable/ITable.h" 

template <class TKey, class TVal>
class TUnsortedTable : public ITable<TKey, TVal> {
private:
    TList<TPair<TKey, TVal>> _data; 

public:
    TUnsortedTable() : _data() {} 
    ~TUnsortedTable() override = default;

    TKey insert(TVal value) override {
        TKey new_key = generate_key();
        TPair<TKey, TVal> new_row(new_key, value);
        _data.pushBack(new_row);
        return new_key;
    }

    void insert(TKey key, TVal value) override {
        TList<TPair<TKey, TVal>> newData; // —оздаем новый список дл€ хранени€ обновленных данных
        bool found = false;

        for (auto it = _data.begin(); it != _data.end(); ++it) {
            if ((*it).first() == key) {
                std::cout << "Updating key " << key << " from " << (*it).second() << " to " << value << std::endl;
                found = true;
            }
            else {
                newData.pushBack(*it); //  опируем все пары, кроме той, которую обновл€ем
            }
        }

        // ≈сли ключ был найден, добавл€ем новую пару с обновленным значением
        if (found) {
            TPair<TKey, TVal> new_row(key, value);
            newData.pushBack(new_row);
        }
        else {
            TPair<TKey, TVal> new_row(key, value);
            newData.pushBack(new_row);
        }

        _data = newData; 
    }

    void erase(TKey key) override {
        if (_data.isEmpty()) {
            throw std::logic_error("List is empty");
        }

        TList<TPair<TKey, TVal>> newData;
        bool found = false;

        for (auto it = _data.begin(); it != _data.end(); ++it) {
            TPair<TKey, TVal> pair = *it;
            if (pair.first() == key) {
                found = true;
            }
            else {
                newData.pushBack(pair);
            }
        }

        if (!found) {
            throw std::logic_error("Key not found");
        }

        _data = newData;
    }

    TVal find(TKey key) override {
        if (_data.isEmpty()) {
            throw std::logic_error("List is empty");
        }

        for (const auto& pair : _data) {
            //std::cout << "Checking key: " << pair.first() << ", value: " << pair.second() << std::endl;
            if (pair.first() == key) {  
                return pair.second();
            }
        }
        throw std::logic_error("Key not found");
    }

    int size() override {
        return _data.size();
    }
    static_assert(std::is_integral_v<TKey>,"TUnsortedTable: TKey must be an integer type (int, long, etc.)");
    TKey generate_key() {
        static TKey last_key = 0;
        return ++last_key;
    }
};
