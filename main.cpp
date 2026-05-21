#include <iostream>
#include <array>
#include <string>

// ==========================================
// Клас Товар (Product)
// ==========================================
class Product {
private:
    std::string name;
    int price; // ПОВЕРНЕНО: тип int

public:
    Product() : name("Unknown"), price(0) {}
    Product(std::string name, int price) : name(name), price(price) {} // Приймаємо int

    // Сортуємо та порівнюємо товари за ціною
    bool operator>(const Product& other) const { return this->price > other.price; }
    bool operator<(const Product& other) const { return this->price < other.price; }

    friend std::ostream& operator<<(std::ostream& os, const Product& p) {
        os << p.name << "(" << p.price << "uah)";
        return os;
    }
};

// ==========================================
// Шаблонні функції
// ==========================================

// Сортування бульбашкою через ітератори БЕЗ використання bool
template <typename T, size_t N>
void sort_array(std::array<T, N>& arr) {
    if (N <= 1) return; 
    
    // Класичне сортування: фіксована кількість ітерацій (N-1) без перевірки на достроковий вихід
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

// Допоміжна функція для виведення масиву
template <typename T, size_t N>
void print_array(const std::string& label, const std::array<T, N>& arr) {
    std::cout << label << ": ";
    for (auto it = arr.begin(); it != arr.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

// Головна шаблонна функція злиття
template <typename T, size_t N, size_t M>
std::array<T, N + M> merge_arrays(const std::array<T, N>& a, const std::array<T, M>& b) {
    std::array<T, N + M> c;
    
    auto it_a = a.begin();
    auto it_b = b.begin();
    auto it_c = c.begin();

    while (it_a != a.end() && it_b != b.end()) {
        if (*it_a < *it_b) {
            *it_c = *it_a;
            it_a++;
        } else {
            *it_c = *it_b;
            it_b++;
        }
        it_c++;
    }

    while (it_a != a.end()) {
        *it_c = *it_a;
        it_a++;
        it_c++;
    }

    while (it_b != b.end()) {
        *it_c = *it_b;
        it_b++;
        it_c++;
    }

    return c;
}

// ==========================================
// Головна програма
// ==========================================
int main() {
    std::cout << "======= TASK 1 =======" << std::endl;
    std::cout << "------- EXAMPLE WITH INT -------" << std::endl;
    std::array<int, 4> arr_int1 = {45, 12, 89, 7};
    std::array<int, 3> arr_int2 = {23, 3, 56};

    sort_array(arr_int1);
    sort_array(arr_int2);

    print_array("Array a (sorted)", arr_int1);
    print_array("Array b (sorted)", arr_int2);

    auto result_int = merge_arrays(arr_int1, arr_int2);
    print_array("Merged result", result_int);
    std::cout << "\n" << std::endl;


    std::cout << "--- EXAMPLES WITH PRODUCT OBJECTS ---" << std::endl;
    // Значення цін тепер цілі числа (int), ініціалізація працює без попереджень компілятора
    std::array<Product, 3> shop1 = {
        Product("Laptop", 25000),
        Product("Mouse", 450),
        Product("Keyboard", 1200)
    };

    std::array<Product, 3> shop2 = {
        Product("Monitor", 6800),
        Product("Headphones", 1500),
        Product("Microphone", 2200)
    };

    sort_array(shop1);
    sort_array(shop2);

    print_array("Shop 1 (sorted by price)", shop1);
    print_array("Shop 2 (sorted by price)", shop2);

    auto result_products = merge_arrays(shop1, shop2);
    print_array("Merged shop result", result_products);
    std::cout << "\n=========================================================\n" << std::endl;

    return 0;
}