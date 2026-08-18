# CS214 Data Structures Collection

A set of advanced C++ implementations demonstrating the practical application of core data structures, including AVL Trees, Heaps, and Stacks. 

**Recent Update:** The project has been completely refactored from legacy monolithic scripts into a strict **Clean Architecture**. It now features generic, template-based data structures, decoupled domain models, and a unified interactive CLI.

## 🏫 Project Details

* **Course:** CS214 - Data Structures
* **Institution:** Faculty of Computers and Artificial Intelligence, Cairo University (FCAI)

## 📂 Repository Structure

The project is organized into the following clean, modular structure:

```text
CS214-Data-Structures-Collection/
├── Code/                           
│   ├── apps/                       # Application logic and orchestrators
│   │   ├── AddressBookApp.h
│   │   ├── ArrayFlipperApp.h
│   │   ├── BrowserHistoryApp.h
│   │   └── PatientTriageApp.h
│   ├── core/                       # Reusable, templated data structures
│   │   ├── AVLTree.h
│   │   ├── MaxHeap.h
│   │   └── Stack.h
│   ├── models/                     # Decoupled domain entities
│   │   ├── Contact.h
│   │   └── Patient.h
│   ├── Test-Cases/                 # Input files for testing
│   └── main.cpp                    # Unified CLI entry point
├── Material/                       # Course materials and project documentation
├── .gitignore                      # Git configuration to ignore compiled binaries
└── README.md                       # Project documentation
```

## 🛠️ Included Applications

### 1️⃣ Browser History Manager
A navigation simulator that mimics a web browser’s **Back** and **Forward** buttons.
* **Data Structure:** Uses two generic **Stacks** (`Stack<std::string>`) to manage URL history safely.
* **Logic:** 
  * **Visit:** Pushes a new URL to backStack and clears forwardStack.
  * **Go Back:** Moves the current URL to forwardStack and pops the previous URL from backStack.
  * **Go Forward:** Moves the current URL back to backStack and pops the next URL from forwardStack.

---

### 2️⃣ Address Book (AVL Tree)
A high-performance contact management system ensuring **O(log n)** search times.
* **Data Structure:** **AVL Tree** (`AVLTree<int, Contact>`).
* **Features:** 
  * **Auto-Balancing:** Implements all four self-balancing rotation cases (LL, RR, LR, RL).
  * **Visualization:** Includes a tree structure visualizer that pretty-prints the tree hierarchy.
* **Operations:** Insert, Search, and In-Order Traversal using decoupled `std::function` callbacks.

---

### 3️⃣ Patient Priority Queue
An Emergency Room (ER) triage system that prioritizes patients based on severity.
* **Data Structure:** **Max Heap** (`MaxHeap<Patient>`).
* **Prioritization Logic:** Encapsulated within the `Patient` struct's overloaded `operator<`:
  * **Primary Key:** Severity (higher severity → higher priority).
  * **Secondary Key:** Arrival time (FIFO for patients with equal severity).

---

### 4️⃣ Binary Array Flipper
An algorithmic solver for array manipulation problems.
* **Data Structure:** `std::vector` for memory-safe dynamic array management.
* **Algorithm:** Solves the **K-bit flip** problem by calculating the number of subarrays required to flip all zeros to ones.

---

## 🚀 Compilation & Usage

With the new Clean Architecture, all applications are unified under a single entry point. You no longer need to compile multiple files.

1. Navigate to the `Code` directory:
   ```bash
   cd Code
   ```

2. Compile the unified suite:
   ```bash
   g++ main.cpp -o app_suite
   ```

3. Run the interactive CLI:
   ```bash
   ./app_suite
   ```

The application will present a menu allowing you to choose which system to run. It will prompt for the test file name (e.g., `AddressBookAVL/test1`—which resolves automatically from the `Test-Cases` folder).

---

### 👥 Contributors

* Abdallah Mohamed
* Hossam Mohamed Ahmed
* Loai Walid Hataba
