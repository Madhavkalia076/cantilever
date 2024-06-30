#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Product
{
  string name;
  int quantity;
  double price;
};

class Inventory
{
private:
  vector<Product> products;
  const string filename = "inventory.txt";

public:
  void addProduct()
  {
    Product newProduct;
    cout << "Enter product name: ";
    cin >> newProduct.name;
    cout << "Enter quantity: ";
    cin >> newProduct.quantity;
    cout << "Enter price: ";
    cin >> newProduct.price;
    products.push_back(newProduct);
  }

  void displayProducts()
  {
    if (products.empty())
    {
      cout << "No products in inventory.\n";
      return;
    }
    for (const auto &product : products)
    {
      cout << "Name: " << product.name << ", Quantity: " << product.quantity
           << ", Price: $" << product.price << "\n";
    }
  }

  void updateQuantity()
  {
    string name;
    int newQuantity;
    cout << "Enter product name: ";
    cin >> name;
    auto it = find_if(products.begin(), products.end(),
                      [&name](const Product &p)
                      { return p.name == name; });
    if (it != products.end())
    {
      cout << "Enter new quantity: ";
      cin >> newQuantity;
      it->quantity = newQuantity;
      cout << "Quantity updated.\n";
    }
    else
    {
      cout << "Product not found.\n";
    }
  }

  void generateReport()
  {
    int totalItems = 0;
    double totalValue = 0.0;
    for (const auto &product : products)
    {
      totalItems += product.quantity;
      totalValue += product.quantity * product.price;
    }
    cout << "Total number of items: " << totalItems << "\n";
    cout << "Total inventory value: $" << totalValue << "\n";
  }

  void saveToFile()
  {
    ofstream outFile(filename);
    if (outFile.is_open())
    {
      for (const auto &product : products)
      {
        outFile << product.name << " " << product.quantity << " " << product.price << "\n";
      }
      outFile.close();
      cout << "Inventory saved to file.\n";
    }
    else
    {
      cout << "Unable to open file for saving.\n";
    }
  }

  void loadFromFile()
  {
    products.clear();
    ifstream inFile(filename);
    if (inFile.is_open())
    {
      Product temp;
      while (inFile >> temp.name >> temp.quantity >> temp.price)
      {
        products.push_back(temp);
      }
      inFile.close();
      cout << "Inventory loaded from file.\n";
    }
    else
    {
      cout << "No existing inventory file found.\n";
    }
  }
};

int main()
{
  Inventory inventory;
  inventory.loadFromFile();

  while (true)
  {
    cout << "\n1. Add Product\n2. Display Products\n3. Update Quantity\n"
         << "4. Generate Report\n5. Save and Exit\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
      inventory.addProduct();
      break;
    case 2:
      inventory.displayProducts();
      break;
    case 3:
      inventory.updateQuantity();
      break;
    case 4:
      inventory.generateReport();
      break;
    case 5:
      inventory.saveToFile();
      cout << "Exiting program.\n";
      return 0;
    default:
      cout << "Invalid choice. Please try again.\n";
    }
  }

  return 0;
}