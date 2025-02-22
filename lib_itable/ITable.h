template<class TKey, class TVal>
class ITable {
    ITable(Tabel const&);
    ITable(TKey, TVal);
    ITable();
    virtual TKey insert(TVal value) = 0; 
    virtual void insert(TKey key, TVal value) = 0; 
    virtual void erase(TKey key) = 0; 
    virtual TVal& find(TKey key) = 0; 
    virtual ~ITable() = default; 
};
