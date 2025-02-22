#include <stdexcept>
#include<utility>
#include<type_traits>

template <class TKey, class TVal>
class UnsortedTable : ITable<TPair <TKey, TVal>> {
	TList<TPair<TKey,TVal>>_data;
	size_t _size;
public:
	UnsortedTable(){}
	UnsortedTable(const TList<TPair<TKey, TVal>>_data):
	_data(data){_size = _data.size() }
};