#include <iostream>
#include <array>
#include <vector>
#include <deque>
#include <string>

// ==========================================
// Клас Товар (Product)
// ==========================================
class Product {
private:
    std::string name;
    int id;

public:
    Product() : name("Unknown"), id(0) {}
    Product(std::string name, int id) : name(name), id(id) {}

    // Оператори для Завдання 1 (Сортування за ID)
    bool operator>(const Product& other) const { return this->id > other.id; }
    bool operator<(const Product& other) const { return this->id < other.id; }

    // Оператор для Завдання 2 (Перевірка ID на парність: product % 2)
    int operator%(int value) const { return this->id % value; }

    // Оператор для Завдання 3 (Порівняння імен для паліндрому)
    bool operator!=(const Product& other) const { return this->name != other.name; }

    friend std::ostream& operator<<(std::ostream& os, const Product& p) {
        os << p.name << "(id:" << p.id << ")";
        return os;
    }
};


//////////////////ЗАВДАННЯ 1/////////////////////////


// Сортування бульбашкою через ітератори
template <typename T, size_t N>
void sort_array(std::array<T, N>& arr) {
    if (N <= 1) return; 
    for (size_t i = 0; i < N - 1; i++) {
        for (auto j = arr.begin(); j != arr.end() - 1 - i; j++) {
            if (*j > *(j + 1)) {
                T temp = *j;
                *j = *(j + 1);
                *(j + 1) = temp;
            }
        }
    }
}

template <typename T, size_t N>
void print_array(const std::string& label, const std::array<T, N>& arr) {
    std::cout << label << ": ";
    for (auto it = arr.begin(); it != arr.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

// Головна функція злиття масивів
template <typename T, size_t N, size_t M>
std::array<T, N + M> merge_arrays(const std::array<T, N>& a, const std::array<T, M>& b) {
    std::array<T, N + M> c;
    auto it_a = a.begin(), it_b = b.begin(), it_c = c.begin();

    while (it_a != a.end() && it_b != b.end()) {
        if (*it_a < *it_b) {
            *it_c = *it_a; it_a++;
        } else {
            *it_c = *it_b; it_b++;
        }
        it_c++;
    }
    while (it_a != a.end()) { *it_c = *it_a; it_a++; it_c++; }
    while (it_b != b.end()) { *it_c = *it_b; it_b++; it_c++; }
    return c;
}


////////////////////ЗАВДАННЯ 2////////////////////////


// Допоміжне виведення для std::vector
template <typename T>
void print_vector(const std::string& label, const std::vector<T>& vec) {
    std::cout << label << ": ";
    for (auto it = vec.begin(); it != vec.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

// Головна функція розбиття на дві групи
template <typename T>
void split(const std::vector<T>& src, std::vector<T>& evens, std::vector<T>& odds) {
    for (auto it = src.begin(); it != src.end(); ++it) {
        if (*it % 2 == 0) {
            evens.push_back(*it);
        } else {
            odds.push_back(*it);
        }
    }
}


////////////////////ЗАВДАННЯ 3////////////////////////


// Головна шаблонна функція перевірки паліндрому
template <typename T>
bool palindrome(const std::deque<T>& deq) {
    if (deq.size() <= 1) {
        return true;
    }
    auto left = deq.cbegin();
    auto right = deq.cend() - 1;
    while (left < right) {
        if (*left != *right) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

// Допоміжне виведення та тест для паліндрому
template <typename T>
void check_palindrome(const std::string& label, const std::deque<T>& deq) {
    std::cout << label << ": [ ";
    for (auto it = deq.begin(); it != deq.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << "] -> " << (palindrome(deq) ? "ПАЛІНДРОМ" : "НЕ паліндром") << std::endl;
}


// ==========================================
// Головна програма
// ==========================================
int main() {
    std::cout << "=================== TASK 1 ===================" << std::endl;
    std::cout << "--- EXAMPLE WITH INT ---" << std::endl;
    std::array<int, 4> arr_int1 = {45, 12, 89, 7};
    std::array<int, 3> arr_int2 = {23, 3, 56};

    sort_array(arr_int1);
    sort_array(arr_int2);
    print_array("Array a (sorted)", arr_int1);
    print_array("Array b (sorted)", arr_int2);

    auto result_int = merge_arrays(arr_int1, arr_int2);
    print_array("Merged result", result_int);
    std::cout << std::endl;

    std::cout << "--- EXAMPLES WITH PRODUCT OBJECTS ---" << std::endl;
    std::array<Product, 3> shop1 = {
        Product("Laptop", 105),
        Product("Mouse", 101),
        Product("Keyboard", 103)
    };
    std::array<Product, 3> shop2 = {
        Product("Monitor", 106),
        Product("Headphones", 102),
        Product("Microphone", 104)
    };

    sort_array(shop1);
    sort_array(shop2);
    print_array("Shop 1 (sorted by ID)", shop1);
    print_array("Shop 2 (sorted by ID)", shop2);

    auto result_products = merge_arrays(shop1, shop2);
    print_array("Merged shop result", result_products);
    std::cout << std::endl;

    std::cout << "=================== TASK 2 ===================" << std::endl;
    std::cout << "--- EXAMPLE WITH INT ---" << std::endl;
    std::vector<int> numbers = {14, 23, 8, 41, 56, 19, 2};
    std::vector<int> evens_int;
    std::vector<int> odds_int;

    split(numbers, evens_int, odds_int);
    print_vector("Original vector", numbers);
    print_vector("Even numbers", evens_int);
    print_vector("Odd numbers", odds_int);
    std::cout << std::endl;

    std::cout << "--- EXAMPLES WITH PRODUCT OBJECTS ---" << std::endl;
    std::vector<Product> product_list = {
        Product("Laptop", 502),
        Product("Mouse", 505),
        Product("Keyboard", 601),
        Product("Monitor", 704),
        Product("Headphones", 807)
    };
    std::vector<Product> evens_products;
    std::vector<Product> odds_products;

    split(product_list, evens_products, odds_products);
    print_vector("Original products", product_list);
    print_vector("Products with Even IDs", evens_products);
    print_vector("Products with Odd IDs", odds_products);
    std::cout << std::endl;

    std::cout << "=================== TASK 3 ===================" << std::endl;
    std::cout << "--- EXAMPLE WITH STRING ---" << std::endl;
    std::deque<std::string> deq_str1 = {"r", "a", "d", "a", "r"};
    std::deque<std::string> deq_str2 = {"h", "e", "l", "l", "o"};
    
    check_palindrome("String Deque 1", deq_str1);
    check_palindrome("String Deque 2", deq_str2);
    std::cout << std::endl;

    std::cout << "--- EXAMPLES WITH PRODUCT OBJECTS ---" << std::endl;
    std::deque<Product> shop_deq1 = {
        Product("Laptop", 1),
        Product("Mouse", 2),
        Product("Laptop", 3)
    };
    std::deque<Product> shop_deq2 = {
        Product("Laptop", 1),
        Product("Mouse", 2),
        Product("Keyboard", 3)
    };

    check_palindrome("Product Deque 1 (by name)", shop_deq1);
    check_palindrome("Product Deque 2 (by name)", shop_deq2);
    std::cout << "=============================================================" << std::endl;

    return 0;
}