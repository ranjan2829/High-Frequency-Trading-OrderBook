

## **High-Frequency Trading Order Book Project**

This project is a **C++ implementation of a high-frequency trading order book**. It is designed to simulate the behavior of a real-world financial order book, where buy and sell orders are matched based on price and time priority. The project focuses on performance and low-latency processing, which are critical for HFT systems.

---

### **Project Structure**

The project consists of the following key components:

1. **Order Book Implementation**:
   - The order book is implemented as a **limit order book**, which maintains buy (bids) and sell (asks) orders in a sorted manner.
   - Orders are matched based on **price-time priority**: the best price is matched first, and if prices are equal, the earliest order is matched first.

2. **Order Types**:
   - **Limit Orders**: Orders to buy or sell at a specific price or better.
   - **Market Orders**: Orders to buy or sell immediately at the best available price.
   - **Cancel Orders**: Orders to remove a previously placed order from the book.

3. **Data Structures**:
   - The project uses efficient data structures like **red-black trees** (via `std::map`) to store and retrieve orders quickly.
   - Orders are stored in two separate trees: one for bids (buy orders) and one for asks (sell orders).

4. **Matching Engine**:
   - The matching engine processes incoming orders and matches them against the existing orders in the book.
   - When a match occurs, a trade is executed, and the order book is updated.

5. **Input/Output**:
   - The project reads orders from an **input file** and processes them sequentially.
   - The output includes the state of the order book after each order is processed, as well as any trades that occur.

---

### **Files in the Project**

1. **`OrderBook.cpp`**:
   - Contains the core logic for the order book, including order matching and book updates.

2. **`OrderBook.h`**:
   - Header file defining the `OrderBook` class and its methods.

3. **`Order.cpp`**:
   - Implements the `Order` class, which represents individual orders.

4. **`Order.h`**:
   - Header file defining the `Order` class and its attributes.

5. **`main.cpp`**:
   - The main driver program that reads orders from an input file, processes them, and prints the results.

6. **`input.txt`**:
   - A sample input file containing a sequence of orders to be processed by the order book.

7. **`Makefile`**:
   - A Makefile to compile the project.

---

### **How to Run the Project**

#### **Prerequisites**
1. Ensure you have a **C++ compiler** installed (e.g., `g++`).
2. Clone the repository:
   ```bash
   git clone https://github.com/ranjan2829/High-Frequency-Trading-OrderBook.git
   cd High-Frequency-Trading-OrderBook
   ```

#### **Compile the Project**
Use the provided `Makefile` to compile the project:
```bash
make
```
This will generate an executable named `orderbook`.

#### **Run the Project**
Run the executable with the sample input file:
```bash
./orderbook input.txt
```

---

### **Input File Format**

The input file (`input.txt`) contains a sequence of orders, one per line. Each order is represented in the following format:
```
<order_id> <side> <price> <quantity>
```
- **`order_id`**: A unique identifier for the order.
- **`side`**: Either `B` (buy) or `S` (sell).
- **`price`**: The price of the order (a positive integer).
- **`quantity`**: The quantity of the order (a positive integer).

Example:
```
1 B 100 10
2 S 105 5
3 B 99 20
4 S 100 15
```

---

### **Output**

The program will print the state of the order book after processing each order, as well as any trades that occur. The output will look something like this:

```
Order Book State:
Bids:
Price: 100, Quantity: 10
Price: 99, Quantity: 20

Asks:
Price: 105, Quantity: 5

Trades:
Trade: Order 1 (B) matched with Order 4 (S) at Price 100, Quantity 10
```

---

### **Demo**

Here’s a step-by-step demo of how the project works:

1. **Input**:
   ```
   1 B 100 10
   2 S 105 5
   3 B 99 20
   4 S 100 15
   ```

2. **Processing**:
   - The first order (`1 B 100 10`) is added to the bids side of the order book.
   - The second order (`2 S 105 5`) is added to the asks side of the order book.
   - The third order (`3 B 99 20`) is added to the bids side of the order book.
   - The fourth order (`4 S 100 15`) matches with the first order (`1 B 100 10`), resulting in a trade.

3. **Output**:
   ```
   Order Book State:
   Bids:
   Price: 99, Quantity: 20

   Asks:
   Price: 105, Quantity: 5

   Trades:
   Trade: Order 1 (B) matched with Order 4 (S) at Price 100, Quantity 10
   ```

---

### **Customization**

You can customize the project by:
1. Modifying the input file (`input.txt`) to test different order sequences.
2. Extending the `OrderBook` class to support additional order types (e.g., stop orders, iceberg orders).
3. Adding more sophisticated logging or visualization for the order book.

---

### **Conclusion**

This project is a **high-performance C++ implementation of a high-frequency trading order book**. It demonstrates how orders are matched in a financial market and provides a foundation for building more advanced trading systems. By running the project and analyzing the output, you can gain a deeper understanding of how order books work in real-world trading environments.

For further exploration, refer to the source code and experiment with different input scenarios.
