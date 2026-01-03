# CS214 Data Structures Collection

A set of advanced C++ implementations demonstrating the practical application of core data structures, including AVL Trees, Heaps, and Stacks.

## 🏫 Project Details

* **Course:** CS214 - Data Structures
* **Institution:** Faculty of Computers and Artificial Intelligence, Cairo University (FCAI)

## 📂 Repository Structure

The project is organized into the following directory structure:

```text
CS214-Data-Structures-Collection/
├── Code/                           # Source code for all applications
│   ├── AddressBookAVL.cpp
│   ├── BinaryArrayFlipper.cpp
│   ├── BrowserHistoryManager.cpp
│   ├── PatientPriorityQueue.cpp
│   └── Test-Cases/                 # Input files for testing
│       ├── AddressBookAVL/         # Test cases for the AVL Tree application
│       ├── BinaryArrayFlipper/     # Test cases for the Array Flipper
│       ├── BrowserHistoryManager/  # Test cases for Browser History
│       └── PatientPriorityQueue/   # Test cases for the Priority Queue
├── Material/                       # Course materials and project documentation
├── .gitignore                      # Git configuration to ignore compiled binaries
└── README.md                       # Project documentation
```

## 🛠️ Included Applications

### 1️⃣ Browser History Manager

A navigation simulator that mimics a web browser’s **Back** and **Forward** buttons.

* **Data Structure:**  
  Uses two **Stacks** (`backStack` and `forwardStack`) to manage URL history.

* **Logic:**  
  * **Visit:** Pushes a new URL to `backStack` and clears `forwardStack`.  
  * **Go Back:** Moves the current URL to `forwardStack` and pops the previous URL from `backStack`.  
  * **Go Forward:** Moves the current URL back to `backStack` and pops the next URL from `forwardStack`.

---

### 2️⃣ Address Book (AVL Tree)

A high-performance contact management system ensuring **O(log n)** search times.

* **Data Structure:**  
  **AVL Tree** (Self-Balancing Binary Search Tree) sorted by **Contact ID**.

* **Features:**  
  * **Auto-Balancing:** Implements four rotation cases:
    * Right-Right  
    * Left-Left  
    * Left-Right  
    * Right-Left  
  * **Visualization:** Includes a `displayTreeStructure` function to pretty-print the tree hierarchy and branches in the console.

* **Operations:**  
  * Insert  
  * Search  
  * In-Order Traversal (listing contacts sorted by ID)

---

### 3️⃣ Patient Priority Queue

An Emergency Room (ER) triage system that prioritizes patients based on severity.

* **Data Structure:**  
  **Max Heap** (Priority Queue).

* **Prioritization Logic:**  
  * **Primary Key:** Severity (higher severity → higher priority)  
  * **Secondary Key:** Arrival time (FIFO for patients with equal severity)

* **Additional Feature:**  
  Implements an **in-place Heap Sort** algorithm to organize patient records.

---

### 4️⃣ Binary Array Flipper

An algorithmic solver for array manipulation problems.

* **Data Structure:**  
  Dynamic array with manual memory management and resizing.

* **Algorithm:**  
  Solves the **K-bit flip** problem by calculating the number of subarrays required to flip all zeros to ones.

---

## 🚀 Compilation & Usage

Navigate to the `Code` directory to compile and run the applications.  
Each program expects the path to a test file located in `Code/Test-Cases`.

### 1️⃣ Browser History

```bash
g++ BrowserHistoryManager.cpp -o browser
./browser
```

### 2️⃣ Address Book

```bash
g++ AddressBookAVL.cpp -o address_book
./address_book
```

### 3️⃣ Patient Priority Queue

```bash
g++ PatientPriorityQueue.cpp -o patient_queue
./patient_queue
```

### 4️⃣ Binary Array Flipper

```bash
g++ BinaryArrayFlipper.cpp -o array_flipper
./array_flipper
```

---

### 👥 Contributors

* Abdallah Mohamed

* Hossam Mohamed Ahmed

* Loai Walid Hataba
