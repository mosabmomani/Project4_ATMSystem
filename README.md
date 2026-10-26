# 🏧 C++ ATM System

A robust, console-based ATM management system built in **C++** that simulates real-world automated teller machine operations, 
including secure authentication, fast account transactions, and persistent file-based data storage.

---

## 🚀 Features

* **Secure Login System:** Authenticates users using Account Number and PIN code validation.
* **Quick Withdraw:** Fast cash withdrawal options with predefined amounts ($20, $50, $100, $200, $400, $600, $800, $1000).
* **Normal Withdraw:** Custom withdrawal amounts restricted to multiples of 5 with real-time balance checking.
* **Deposit:** Secure deposit mechanism with positive amount validation and instant balance updating.
* **Check Balance:** Instant inquiry of current account balance.
* **File Persistence:** Automatically updates and saves transaction changes to a local flat-file database (`clientdata.txt`).

---

## 🛠️ Technologies & Concepts Used

* **Language:** C++ (Standard Template Library - STL)
* **Data Structures:** Structs (`sClientData`), Vectors (`vector`)
* **File I/O:** Reading and writing data using `<fstream>` with custom delimiter-based parsing (`#//#`)
* **Control Flow & Modular Design:** Enums, Switch-cases, and modular function separation

---

## 📁 File Structure & Data Format

The application relies on a flat-file database named `clientdata.txt` located in the root directory. Each record uses `#//#` as a separator:

```text
AccountNumber#//#PinCode#//#FullName#//#Phone#//#Balance
