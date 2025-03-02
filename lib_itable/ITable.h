template<class TKey, class TVal>
class ITable {
public:
    ITable(ITable const&)= delete;
    ITable(TKey, TVal) = delete;
    ITable& operator=(ITable const&) = delete;
    ITable() = default;
    virtual TKey insert(TVal value) = 0; 
    virtual void insert(TKey key, TVal value) = 0; 
    virtual void erase(TKey key) = 0; 
    virtual TVal& find(TKey key) = 0; 
    virtual ~ITable() = default; 
};
