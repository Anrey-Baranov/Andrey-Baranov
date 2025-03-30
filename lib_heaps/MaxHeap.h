template <typename T>
class MaxHeap : public Heap<T> {
protected:
    bool compare(const T& a, const T& b) const override {
        return a > b;
    }

public:
    MaxHeap() = default;
    MaxHeap(const std::vector<T>& array) : Heap<T>(array) {}

    T max() const { return this->top(); }
    T remove_max() { return this->extractTop(); }

    T min() const = delete;
    T remove_min() = delete;
};