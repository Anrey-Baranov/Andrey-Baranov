#ifndef ITABLE_H
#define ITABLE_H

template<class TKey, class TVal>
class ITable {
protected:
    ITable(ITable const&) = default;
    ITable(TKey, TVal);
    ITable() = default;
public:
    virtual TKey insert(TVal value) = 0;
    virtual void insert(TKey key, TVal val) = 0;
    virtual void erase(TKey key) = 0;
    virtual TVal find(TKey key) = 0;
    virtual int size() = 0;
    virtual ~ITable() = default;
};

#endif // ITABLE_H