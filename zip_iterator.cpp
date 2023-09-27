#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>



class zip_iterator {
private:
    using it_type =  std::vector<double>::iterator;
    it_type it1;
    it_type it2;

public:
    zip_iterator(it_type it_1, it_type it_2) : it1{it_1}, it2{it_2} {}

    zip_iterator &operator++() {
        ++it1;
        ++it2;
        return *this;
    }

    bool operator!=(zip_iterator &other) {
        return it1 != other.it1 && it2 != other.it2;
    }

    bool operator==(zip_iterator &other) {
        return !operator!=(other);
    }
    std::pair<double, double> operator*() const  {
        return {*it1, *it2};
    }



};

namespace std{
    template <>
    struct iterator_traits<zip_iterator> {
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::pair<double, double>;
        using difference_type = long int;
    };
}

class zipper {
    private:
        using vec_type = std::vector<double>;
        vec_type &vec1;
        vec_type &vec2;

    public:
        zipper (vec_type &va1, vec_type &va2) : vec1(va1), vec2(va2) {}

        zip_iterator begin() const {
            return {std::begin(vec1), std::begin(vec2)};
        }

        zip_iterator end() const {
            return {std::end(vec1), std::end(vec2)};
        }


};


int main(){

    std::vector<double> a {1.0, 2.0, 3.0};
    std::vector<double> b {4.0, 5.0, 6.0};

    zipper zip(a, b);

    const auto add_product([](double sum, const auto &p){
        return sum + p.first * p.second;
    });

    const auto dot_product(std::accumulate(std::begin(zip), std::end(zip), 0.0, add_product));

    std::cout << dot_product << std::endl;

return 0;
}
