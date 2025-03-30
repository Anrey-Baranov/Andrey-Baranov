template <typename T>
class MinHeap : public Heap<T> {
protected:
    bool compare(const T& a, const T& b) const override {
        return a < b;
    }

public:
    MinHeap() = default;
    MinHeap(const std::vector<T>& array) : Heap<T>(array) {}

    T min() const { return this->top(); }
    T remove_min() { return this->extractTop(); }
    T max() const = delete;
    T remove_max() = delete;
};