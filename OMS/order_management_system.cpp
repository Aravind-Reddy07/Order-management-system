#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Class to represent an order
class Order {
public:
    int orderId;
    string customerName;
    string product;
    string status;
    string paymentStatus;
    bool isCancelled;

    // Constructor to initialize an order
    Order(int id, string name, string prod)
        : orderId(id), customerName(name), product(prod), status("Processing"), paymentStatus("Pending"), isCancelled(false) {}
};

// Order Management System class
class OrderManagementSystem {
private:
    vector<Order> orders; // List of all orders
    int nextOrderId;      // Counter for unique order IDs

public:
    // Constructor
    OrderManagementSystem() : nextOrderId(1) {}

    // Place a new order
    void placeOrder(string customerName, string product) {
        Order newOrder(nextOrderId++, customerName, product);
        orders.push_back(newOrder);
        cout << "Order placed successfully! Order ID: " << newOrder.orderId << endl;
    }

    // View all orders
    void viewOrders() {
        if (orders.empty()) {
            cout << "No orders found!" << endl;
            return;
        }
        cout << "\nList of Orders:\n";
        for (const auto& order : orders) {
            cout << "Order ID: " << order.orderId
                 << ", Customer: " << order.customerName
                 << ", Product: " << order.product
                 << ", Status: " << order.status
                 << ", Payment: " << order.paymentStatus
                 << ", Cancelled: " << (order.isCancelled ? "Yes" : "No") << endl;
        }
    }

    // Update the status of an order
    void updateOrderStatus(int orderId, string newStatus) {
        for (auto& order : orders) {
            if (order.orderId == orderId) {
                if (order.isCancelled) {
                    cout << "Cannot update a cancelled order!" << endl;
                    return;
                }
                order.status = newStatus;
                cout << "Order ID " << orderId << " status updated to '" << newStatus << "'\n";
                return;
            }
        }
        cout << "Order ID not found!" << endl;
    }

    // Update payment status of an order
    void updatePaymentStatus(int orderId, string newPaymentStatus) {
        for (auto& order : orders) {
            if (order.orderId == orderId) {
                order.paymentStatus = newPaymentStatus;
                cout << "Payment status for Order ID " << orderId << " updated to '" << newPaymentStatus << "'\n";
                return;
            }
        }
        cout << "Order ID not found!" << endl;
    }

    // Cancel an order
    void cancelOrder(int orderId) {
        for (auto& order : orders) {
            if (order.orderId == orderId) {
                if (order.isCancelled) {
                    cout << "Order ID " << orderId << " is already cancelled.\n";
                    return;
                }
                order.isCancelled = true;
                order.status = "Cancelled";
                cout << "Order ID " << orderId << " has been cancelled.\n";
                return;
            }
        }
        cout << "Order ID not found!" << endl;
    }
};

// Main function to simulate the system
int main() {
    OrderManagementSystem oms;
    int choice;

    while (true) {
        cout << "\n=== Order Management System ===\n";
        cout << "1. Place Order\n2. View Orders\n3. Update Order Status\n4. Update Payment Status\n5. Cancel Order\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string customerName, product;
            cout << "Enter customer name: ";
            cin.ignore(); // Clear input buffer
            getline(cin, customerName);
            cout << "Enter product name: ";
            getline(cin, product);
            oms.placeOrder(customerName, product);
        } else if (choice == 2) {
            oms.viewOrders();
        } else if (choice == 3) {
            int orderId;
            string newStatus;
            cout << "Enter Order ID: ";
            cin >> orderId;
            cout << "Enter new status (e.g., 'Shipped', 'Delivered'): ";
            cin.ignore(); // Clear input buffer
            getline(cin, newStatus);
            oms.updateOrderStatus(orderId, newStatus);
        } else if (choice == 4) {
            int orderId;
            string newPaymentStatus;
            cout << "Enter Order ID: ";
            cin >> orderId;
            cout << "Enter new payment status (e.g., 'Paid', 'Refunded'): ";
            cin.ignore(); // Clear input buffer
            getline(cin, newPaymentStatus);
            oms.updatePaymentStatus(orderId, newPaymentStatus);
        } else if (choice == 5) {
            int orderId;
            cout << "Enter Order ID to cancel: ";
            cin >> orderId;
            oms.cancelOrder(orderId);
        } else if (choice == 6) {
            cout << "Exiting Order Management System. Goodbye!\n";
            break;
        } else {
            cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}
