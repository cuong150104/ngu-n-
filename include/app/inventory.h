#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include "list/XArrayList.h"
#include "list/DLinkedList.h"
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

// -------------------- List1D --------------------
template <typename T>
class List1D
{
private:
    IList<T> *pList;

public:
    List1D();
    List1D(int num_elements);
    List1D(const T *array, int num_elements);
    List1D(const List1D<T> &other);
    virtual ~List1D();

    int size() const;
    T get(int index) const;
    void set(int index, T value);
    void add(const T &value);
    string toString() const;
    template <typename U>
    friend ostream &operator<<(ostream &os, const List1D<T> &list);
    void remove(int index);
    void removeAt(int index);

    bool operator==(const List1D<T>& other) const {
        if (this->size() != other.size()) return false;
        for (int i = 0; i < this->size(); i++) {
            if (this->get(i) != other.get(i)) return false;
        }
        return true;
    }
};

// -------------------- List2D --------------------
template <typename T>
class List2D
{
private:
    // IList<IList<T> *> *pMatrix;
      DLinkedList<List1D<T>*>* pMatrix;

public:
    List2D();
    List2D(List1D<T> *array, int num_rows);
    List2D(const List2D<T> &other);
    virtual ~List2D();

    int rows() const;
    void setRow(int rowIndex, const List1D<T> &row);
    T get(int rowIndex, int colIndex) const;
    List1D<T> getRow(int rowIndex) const;
    string toString() const;
    template <typename U>
    friend ostream &operator<<(ostream &os, const List2D<T> &matrix);
    void addRow(const List1D<T> &row);
    void removeRow(int index);
    void add(List1D<T>* row);
};

struct InventoryAttribute
{
    string name;
    double value;
    InventoryAttribute() : name(""), value(0.0) {}
    InventoryAttribute(const string &name, double value) : name(name), value(value) {}
    string toString() const { return name + ": " + to_string(value); }
    friend ostream& operator<<(ostream& os, const InventoryAttribute& attr) {
        os << attr.toString();
        return os;
    }
    bool operator==(const InventoryAttribute& other) const {
        return name == other.name && value == other.value;
    }
    bool operator!=(const InventoryAttribute& other) const {
        return !(*this == other);
    }
    

};

// -------------------- InventoryManager --------------------
class InventoryManager
{
private:
    List2D<InventoryAttribute> attributesMatrix;
    List1D<string> productNames;
    List1D<int> quantities;

public:
    InventoryManager();
    InventoryManager(const List2D<InventoryAttribute> &matrix,
                     const List1D<string> &names,
                     const List1D<int> &quantities);
    InventoryManager(const InventoryManager &other);

    int size() const;
    List1D<InventoryAttribute> getProductAttributes(int index) const;
    string getProductName(int index) const;
    int getProductQuantity(int index) const;
    void updateQuantity(int index, int newQuantity);
    void addProduct(const List1D<InventoryAttribute> &attributes, const string &name, int quantity);
    void removeProduct(int index);

    List1D<string> query(string attributeName, const double &minValue,
                         const double &maxValue, int minQuantity, bool ascending) const;

    void removeDuplicates();

    static InventoryManager merge(const InventoryManager &inv1,
                                  const InventoryManager &inv2);

    void split(InventoryManager &section1,
               InventoryManager &section2,
               double ratio) const;

    List2D<InventoryAttribute> getAttributesMatrix() const;
    List1D<string> getProductNames() const;
    List1D<int> getQuantities() const;
    string toString() const;
    InventoryManager& operator=(const InventoryManager& other){
        if (this != &other) {
            attributesMatrix = other.attributesMatrix;
            productNames = other.productNames;
            quantities = other.quantities;
        }
        return *this;
    }

  /*   bool areAttributesEqual(
        const List1D<InventoryAttribute>& attr1,
        const List1D<InventoryAttribute>& attr2
    ) const {
        if (attr1.size() != attr2.size()) return false;
        for (int i = 0; i < attr1.size(); i++) {
            if (attr1.get(i) != attr2.get(i)) { // Đảm bảo operator!= được định nghĩa
                return false;
            }
        }
        return true;
    } */
};

// -------------------- List1D Method Definitions --------------------
template <typename T>
List1D<T>::List1D()
{
    // TODO
    pList = new XArrayList<T>(); 
}

template <typename T>
List1D<T>::List1D(int num_elements) : List1D()
{
    // TODO
    for (int i = 0; i < num_elements; i++) {
        pList->add(T()); // Thêm các phần tử với giá trị mặc định của kiểu T
    }
}

template <typename T>
List1D<T>::List1D(const T *array, int num_elements): List1D()
{
    // TODO
    for (int i = 0; i < num_elements; i++) {
        pList->add(array[i]);
    }


}

template <typename T>
List1D<T>::List1D(const List1D<T> &other): List1D()
{
    // TODO
    for (int i = 0; i < other.size(); i++) {
        this->add(other.get(i));
    }
}

template <typename T>
List1D<T>::~List1D()
{
    // TODO
    delete pList;
}

template <typename T>
int List1D<T>::size() const
{
    // TODO
    return pList->size();
}

template <typename T>
T List1D<T>::get(int index) const
{
    // TODO
    return pList->get(index);
}

template <typename T>
void List1D<T>::set(int index, T value)
{
    // TODO
   /*  pList->set(index, value); */
   T& element = pList->get(index);  // Giả sử get() trả về tham chiếu
   element = value;          
}


template <typename T>
void List1D<T>::add(const T &value)
{
    // TODO
    pList->add(value);
}

template <typename T>
string List1D<T>::toString() const
{
    // TODO
    stringstream ss;
        ss << "[";
        for (int i = 0; i < size(); i++) {
            ss << get(i);
            if (i < size() - 1) {
                ss << ", ";
            }
        }
        ss << "]";
        return ss.str();
}

template <typename T>
ostream &operator<<(ostream &os, const List1D<T> &list)
{
    // TODO
    os << list.toString();
        return os;
}

template <typename T>
void List1D<T>::remove(int index)
{
    if(index < 0 || index >= size()){
        throw out_of_range("Index is out of range");
    }
    pList->removeAt(index);
}

template <typename T>
void List1D<T>::removeAt(int index)
{
    // TODO
    if(index < 0 || index >= pList->size()){
        throw out_of_range("Index is out of range");
    }
    pList->removeAt(index); // Use the removeAt method of pList to handle the removal
}

// -------------------- List2D Method Definitions --------------------
template <typename T>
List2D<T>::List2D()
{
    // TODO
    // pMatrix = new DLinkedList<IList<InventoryAttribute>*>();

    pMatrix = new DLinkedList<List1D<T>*>();  
    

}

template <typename T>
List2D<T>::List2D(List1D<T> *array, int num_rows): List2D()
{
    // Thêm các dòng vào pMatrix
    for (int i = 0; i < num_rows; i++) {
        List1D<T>* row = new List1D<T>(array[i]);
        pMatrix->add(row);
    }
}

template <typename T>
List2D<T>::List2D(const List2D<T>& other): List2D() {
    // Đảm bảo pMatrix sử dụng đúng kiểu con trỏ với DLinkedList
    pMatrix = new DLinkedList<List1D<T>*>();  // DLinkedList với kiểu con trỏ List1D<T>*

    for (int i = 0; i < other.rows(); i++) {
        // Lấy dòng từ other.getRow(i) và khởi tạo List1D mới
        List1D<T>* newRow = new List1D<T>(other.getRow(i));  // Lấy hàng và sao chép vào List1D
        pMatrix->add(newRow);  // Thêm dòng vào pMatrix
    }
}


template <typename T>
List2D<T>::~List2D()
{
    // TODO
    for (int i = 0; i < pMatrix->size(); i++) {
        delete pMatrix->get(i);
    }
    delete pMatrix;
}

template <typename T>
int List2D<T>::rows() const
{
    // TODO
    return pMatrix->size();
}

template <typename T>
void List2D<T>::setRow(int rowIndex, const List1D<T> &row)
{
    // TODO
    if (rowIndex < 0 || rowIndex >= rows()) {
        throw out_of_range("Row index out of range");
    }
    delete pMatrix->get(rowIndex);
    pMatrix->set(rowIndex, new List1D<T>(row));
}

template <typename T>
T List2D<T>::get(int rowIndex, int colIndex) const
{
    // TODO
    if (rowIndex < 0 || rowIndex >= rows()) {
        throw out_of_range("Row index out of range");
    }
    List1D<T>* row = pMatrix->get(rowIndex);  // Không cần ép kiểu
    return row->get(colIndex);
}

template <typename T>
List1D<T> List2D<T>::getRow(int rowIndex) const {
    // Kiểm tra chỉ số hàng hợp lệ
    if (rowIndex < 0 || rowIndex >= rows()) {
        throw out_of_range("Row index out of range");
    }
    List1D<T>* row = pMatrix->get(rowIndex);  // Không cần ép kiểu
    // Trả về bản sao của List1D<T> thay vì con trỏ
    return *pMatrix->get(rowIndex);  // Lấy dòng từ pMatrix và trả về một bản sao
}


template <typename T>
string List2D<T>::toString() const
{
    // TODO
    stringstream ss;
    ss << "[";
    for (int i = 0; i < rows(); i++) {
        ss << pMatrix->get(i)->toString();
        if (i < rows() - 1) {
            ss << ", ";
        }
    }
    ss << "]";
    return ss.str();
}
template <typename T>
void List2D<T>::addRow(const List1D<T> &row)
{
    pMatrix->add(new List1D<T>(row));  // Thêm dòng mới vào pMatrix
}
template <typename T>

ostream &operator<<(ostream &os, const List2D<T> &matrix)
{
    // TODO
    os << matrix.toString();
    return os;
}

template <typename T>
void List2D<T>::removeRow(int index)
{
    if(index < 0 || index >= pMatrix->size()){
        throw out_of_range("Index is out of range");
    }
    delete pMatrix->get(index);  // Xóa dòng trước khi loại bỏ
    pMatrix->removeAt(index);  // Loại bỏ dòng khỏi pMatrix 
   
}
template <typename T>
void List2D<T>::add(List1D<T>* row) {
    // Đảm bảo pMatrix là một danh sách chứa con trỏ kiểu List1D<T>*
    pMatrix->add(row);  // Thêm dòng vào pMatrix
}

// -------------------- InventoryManager Method Definitions --------------------
InventoryManager::InventoryManager():attributesMatrix(), productNames(), quantities()
{
    // TODO
}

InventoryManager::InventoryManager(const List2D<InventoryAttribute> &matrix,
                                   const List1D<string> &names,
                                   const List1D<int> &quantities):attributesMatrix(matrix), productNames(names), quantities(quantities)
{
    // TODO
}

InventoryManager::InventoryManager(const InventoryManager &other):attributesMatrix(other.attributesMatrix), productNames(other.productNames), quantities(other.quantities)
{
    // TODO
}

int InventoryManager::size() const
{
    // TODO
    return productNames.size();
}

List1D<InventoryAttribute> InventoryManager::getProductAttributes(int index) const
{
    // TODO
    if (index < 0 || index >= size()) {
        throw out_of_range("Index is invalid!");
    }
    return attributesMatrix.getRow(index);
}

string InventoryManager::getProductName(int index) const
{
    // TODO
    if (index < 0 || index >= size()) {
        throw out_of_range("Index is invalid!");
    }
    return productNames.get(index);
}

int InventoryManager::getProductQuantity(int index) const
{
    // TODO
    if (index < 0 || index >= size()) {
        throw out_of_range("Index is invalid!");
    }
    return quantities.get(index);
}

void InventoryManager::updateQuantity(int index, int newQuantity)
{
    // TODO
     // Add the row using the new addRow method
     if(index < 0 || index >= size()){
        throw out_of_range("Index is out of range");
    }
    quantities.set(index, newQuantity);
}
void InventoryManager::addProduct(const List1D<InventoryAttribute> &attributes, const string &name, int quantity)
{
   /*  List1D<InventoryAttribute> newRow(attributes);
    
    // Thêm vào ma trận (sử dụng phương thức add đúng cách)
    attributesMatrix.add(&newRow);  // Đảm bảo kiểu phù hợp với DLinkedList<List1D<InventoryAttribute>*>
    
    // Thêm tên sản phẩm và số lượng vào các danh sách tương ứng
    productNames.add(name);
    quantities.add(quantity); */
    List1D<InventoryAttribute>* newRow = new List1D<InventoryAttribute>(attributes);
    
    // Thêm con trỏ vào ma trận
    attributesMatrix.add(newRow);
    
    // Thêm tên và số lượng
    productNames.add(name);
    quantities.add(quantity);
    
}
void InventoryManager::removeProduct(int index) {
    if (index < 0 || index >= size()) {
        throw out_of_range("Index is out of range in removeProduct");
    }
    try {
        productNames.remove(index);
        quantities.remove(index);
        attributesMatrix.removeRow(index);
    } catch (const out_of_range& e) {
        cerr << "Error in removeProduct: " << e.what() << endl;
        throw; // Ném lại để báo lỗi
    }
}

List1D<string> InventoryManager::query(string attributeName, const double &minValue,
                                       const double &maxValue, int minQuantity, bool ascending) const
{
    // TODO
    List1D<string> result;
        List1D<int> indices;
        
        // Find matching products
        for (int i = 0; i < size(); i++) {
            if (quantities.get(i) < minQuantity) continue;
            
            bool found = false;
            List1D<InventoryAttribute> attrs = attributesMatrix.getRow(i);
            for (int j = 0; j < attrs.size(); j++) {
                InventoryAttribute attr = attrs.get(j);
                if (attr.name == attributeName && 
                    attr.value >= minValue && 
                    attr.value <= maxValue) {
                    found = true;
                    break;
                }
            }
            if (found) indices.add(i);
        }
        
        // Sort indices
        for (int i = 0; i < indices.size(); i++) {
            for (int j = i + 1; j < indices.size(); j++) {
                int idx1 = indices.get(i);
                int idx2 = indices.get(j);
                
                double val1 = 0, val2 = 0;
                List1D<InventoryAttribute> attrs1 = attributesMatrix.getRow(idx1);
                List1D<InventoryAttribute> attrs2 = attributesMatrix.getRow(idx2);
                
                for (int k = 0; k < attrs1.size(); k++) {
                    if (attrs1.get(k).name == attributeName) {
                        val1 = attrs1.get(k).value;
                        break;
                    }
                }
                
                for (int k = 0; k < attrs2.size(); k++) {
                    if (attrs2.get(k).name == attributeName) {
                        val2 = attrs2.get(k).value;
                        break;
                    }
                }
                
                if ((ascending && val1 > val2) || (!ascending && val1 < val2)) {
                    indices.set(i, idx2);
                    indices.set(j, idx1);
                }
            }
        }
        
        // Get results
        for (int i = 0; i < indices.size(); i++) {
            result.add(productNames.get(indices.get(i)));
        }
        
        return result;
   

}


void InventoryManager::removeDuplicates() {
    for (int i = 0; i < size(); i++) {
        int currentSize = size(); // Lưu kích thước tại thời điểm này
        for (int j = i + 1; j < currentSize; ) {
            try {
                if (getProductAttributes(i) == getProductAttributes(j)) {
                    int newQuantity = getProductQuantity(i) + getProductQuantity(j);
                    updateQuantity(i, newQuantity);
                    removeProduct(j);
                    currentSize--; // Giảm kích thước sau khi xóa
                } else {
                    j++;
                }
            } catch (const out_of_range& e) {
                cerr << "Error in removeDuplicates: " << e.what() << endl;
                break;
            }
        }
    }
}

InventoryManager InventoryManager::merge(const InventoryManager &inv1,
                                         const InventoryManager &inv2)
{
    InventoryManager result = inv1;
    for (int i = 0; i < inv2.size(); i++) {
        result.addProduct(inv2.getProductAttributes(i),
                        inv2.getProductName(i),
                        inv2.getProductQuantity(i));
    }
    return result;
}

void InventoryManager::split(InventoryManager &section1,
                             InventoryManager &section2,
                             double ratio) const
{
    // TODO
    int splitPoint = static_cast<int>(ceil(size() * ratio));
        
        for (int i = 0; i < size(); i++) {
            if (i < splitPoint) {
                section1.addProduct(getProductAttributes(i),
                                  getProductName(i),
                                  getProductQuantity(i));
            } else {
                section2.addProduct(getProductAttributes(i),
                                  getProductName(i),
                                  getProductQuantity(i));
            }
        }
}

List2D<InventoryAttribute> InventoryManager::getAttributesMatrix() const
{
    // TODO
    return attributesMatrix;
}

List1D<string> InventoryManager::getProductNames() const
{
    // TODO
    return productNames;
}

List1D<int> InventoryManager::getQuantities() const
{
    // TODO
    return quantities;
}

string InventoryManager::toString() const
{
    // TODO
    stringstream ss;
    ss << "InventoryManager[\n";
    ss << "  AttributesMatrix: " << attributesMatrix << ",\n";
    ss << "  ProductNames: " << productNames << ",\n";
    ss << "  Quantities: " << quantities << "\n";
    ss << "]";
    return ss.str();
}





#endif /* INVENTORY_MANAGER_H */