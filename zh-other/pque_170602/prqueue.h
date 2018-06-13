#ifndef PRQUEUE_H_INCLUDED
#define PRQUEUE_H_INCLUDED

#include <map>
#include <vector>
#include <algorithm>
#include <queue>

/* kettesert map segitsegevel
template<class KeyType, class ValueType>
class priority_queue {
    std::map<KeyType, ValueType> values;
public:

    void push(KeyType key, ValueType value) {
        values.insert(std::make_pair(key, value));
    }

    void update_priority(KeyType old_key, ValueType value, KeyType new_key) {
        values.erase(old_key);
        values.insert(std::make_pair(new_key, value));
    }

    const ValueType& top() const {
        return values.rbegin()->second;
    }
};
*/

template<class KeyType, class ValueType, class Compare = std::less<KeyType> >
class priority_queue {
    std::vector<std::pair<KeyType, ValueType> > values;

    struct {
        Compare c;
        bool operator()(const std::pair<KeyType, ValueType>& v1, const std::pair<KeyType, ValueType>& v2) const {
            return c(v1.first, v2.first) || (!c(v2.first, v1.first) && v1.second < v2.second);
        }
    } my_comp;

public:
    void push(KeyType key, ValueType value) {
        values.insert(std::lower_bound(values.begin(), values.end(), std::make_pair(key, value), my_comp), std::make_pair(key, value));
    }

    void update_priority(KeyType old_key, ValueType value, KeyType new_key) {
        std::find(values.begin(), values.end(), std::make_pair(old_key, value))->first = new_key;
        std::sort(values.begin(), values.end(), my_comp);
    }

    const ValueType& top() const {
        return values.back().second;
    }

    ValueType& top() {
        return values.back().second;
    }

    void pop() {
        values.pop_back();
    }

    int size() const {
        return values.size();
    }

    priority_queue() {}

    template <class ContType, class CompType>
    priority_queue(std::priority_queue<KeyType, ContType, CompType> queue) {
        while (queue.size() > 0) {
            push(queue.top(), queue.top());
            queue.pop();
        }
    }
};


#endif //PRQUEUE_H_INCLUDED
