#include <iostream>
#include <string>
#include <list>

/*
 * Color Definitions (https://stackoverflow.com/a/35125882)
 */
const std::string red("\033[0;31m");
const std::string green("\033[1;32m");
const std::string yellow("\033[1;33m");
const std::string cyan("\033[0;36m");
const std::string magenta("\033[0;35m");
const std::string reset("\033[0m");


class HashTable {
    static const int rows = 10;
    std::list<std::pair<int, std::string>> dataTable[rows];
public:
    int hashingFunction(int key) const;
    bool isEmpty() const;
    /* ------------------------------------------------------------------------
    * insertItem and removeItem can be void, but bool return type lets us know
    * if the operation was performed successfully.
    * -------------------------------------------------------------------------
    */
    void insertItem(int key, std::string value); // <int, std::string>
    void removeItem(int key) ;

    std::string getItem(int key) const;
    void printTable() const;

};

bool HashTable::isEmpty() const {
    /*
     * This function checks if our HashTable is empty or not.
     * This helps avoid operations such as insert or remove on an empty HashTable,
     * which could cause memory errors. (Rust devs won't shut up).
     */
    /*
     * If the sum = 0, then the HashTable is empty;
     * Otherwise it isn't
     */
    int sum{};
    for (int i = 0; i < rows; ++i) {
        sum += dataTable[i].size();
    }

    if (sum == 0) return true;
    return false;
};

int HashTable::hashingFunction(int key) const {
    return key % rows;
}

void HashTable::insertItem(int key, std::string value) {
    int hashValue = hashingFunction(key);
    auto& cell = dataTable[hashValue];
    auto itr = begin(cell);
    bool keyExists = false;
    for (; itr != end(cell); itr++) {
        if (itr->first == key) {
            keyExists = true;
            itr->second = value;
            std::cout << yellow << "[WARN]" << reset << " Key {" << itr->first << "} Exists. Value Replaced!" << "\n";
            break;
        }
    }
    if (!keyExists) {
        cell.emplace_back(key,value);
    }
};

std::string HashTable::getItem(int key) const {
    int hashValue = hashingFunction(key);
    auto& cell = dataTable[hashValue];
    auto itr = begin(cell);
    bool keyExists = false;

    for (; itr != end(cell); itr++) {
        if (itr->first == key) {
            keyExists = true;
            return itr->second;
        }
    }
    return "Value not found!";
}

void HashTable::removeItem(int key) {
    int hashValue = hashingFunction(key);
    auto& cell = dataTable[hashValue];
    auto itr = begin(cell);
    bool keyExists = false;
    for (; itr != end(cell); itr++) {
        if (itr->first == key) {
            keyExists = true;
            itr = cell.erase(itr);
            std::cout << red << "[WARN]" << reset << " Item removed." << "\n";
            break;
        }
    }
    if (!keyExists) {
        std::cout << "Item not found!" << "\n";
    }
}

void HashTable::printTable() const {
    for (int i = 0; i < rows; ++i) {
        if (dataTable[i].empty()) continue;

        auto itr = begin(dataTable[i]);
        for (; itr != end(dataTable[i]); itr++) {
            std::cout << cyan << "[TABLE]" << reset << " Key: " <<  itr->first << " Value: " << itr->second << "\n";
        }

    }
}

int main() {
    std::cout << green << "[INFO]" << reset << " Binary Initialized\n";

    HashTable table;
    std::cout << green << "[INFO]" << reset << " Hash Table Created\n";
    // if (table.isEmpty()) {
    //     std::cout << "Empty Table\n";
    // }
    table.insertItem(800, "Hello");
    table.insertItem(201, "World");
    table.insertItem(506, "Goodbye");
    table.insertItem(107, "Kamakshya");
    table.insertItem(107, "This changed");
    std::cout << cyan << "[INFO]" << reset << " Fetched record: " << table.getItem(800) << "\n";
    table.printTable();
}