# Red-Black Tree for Hotel Booking Management

## Overview  
This project implements a **Red-Black Tree (RBT)** to manage hotel bookings efficiently.  
It supports **insertion, searching, traversal, and predecessor/successor queries** while maintaining  
**self-balancing properties** through **rotations and color adjustments**.

## Features  
- **Insert** new hotel booking records into the Red-Black Tree.  
- **Search** for a booking by hotel name, arrival date, and confirmation number.  
- **Traverse** the tree in **preorder, inorder, and postorder** sequences.  
- **Find the minimum and maximum** confirmation numbers in the tree.  
- **Retrieve predecessor or successor** bookings based on confirmation numbers.  

## Files  
- `Assignment6.cpp` – Main program that handles user input and executes RBT operations.  
- `RedBlackTree.h` – Defines the **Red-Black Tree structure and operations**.  
- `RedBlackTree.cpp` – Implements **insertion, balancing, searching, and traversal** methods.  

## Compilation & Execution  
### **1. Compile the program:**  
```bash
g++ Assignment6.cpp RedBlackTree.cpp -o Assignment6
