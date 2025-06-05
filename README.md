# Pallet Packing Optimization - Knapsack Problem Solver

> **Design of Algorithms Project 2 - Spring 2025**  
> Developed by Group 2 - Class 15

A comprehensive C++ implementation of various algorithms to solve the **Pallet Packing Optimization Problem** (a variant of the 0-1 Knapsack Problem). This project implements and compares multiple algorithmic approaches, from exact solutions to approximation algorithms, with performance analysis and visualization tools.

## Problem Description

The **Pallet Packing Problem** involves optimizing the loading of pallets into a truck with limited weight capacity. Each pallet has:

- **Weight**: Physical weight constraint
- **Profit**: Value/importance of the pallet

**Objective**: Maximize total profit while respecting the truck's weight capacity constraint.

This is a classic variant of the **0-1 Knapsack Problem** where each pallet can either be selected (1) or not selected (0), but cannot be partially selected.

## Features

### Algorithms Implemented

- **Exact Algorithms**:

  - **Brute Force** - Exhaustive search `O(2^n)`
  - **Backtracking** - Optimized search with pruning `O(2^n)` with early termination
  - **Dynamic Programming** - Optimal solution `O(n×W)`
  - **Integer Linear Programming (ILP)** - Both recursive and Python PuLP implementations

- **Approximation Algorithms**:
  - **Greedy-A** - Profit-to-weight ratio based `O(n log n)`
  - **Greedy-B** - Profit value based `O(n log n)`
  - **Combined Approximation** - Best of both greedy approaches

### Analysis & Visualization Tools

- **Performance Comparison** - Execution time, profit, weight analysis
- **Accuracy Metrics** - Compare approximations with optimal solutions
- **Visual Charts** - Matplotlib-generated performance graphs
- **Detailed Reports** - JSON export of performance data

## Project Structure

```
src/
├── main.cpp                     # Main entry point
├── menu/                        # User interface
│   ├── Menu.h                   # Menu class declaration
│   └── Menu.cpp                 # Interactive console menu
├── optimizer/                   # Core algorithms
│   ├── PalletPackingOptimizer.h # Algorithm declarations
│   └── PalletPackingOptimizer.cpp # Algorithm implementations
├── data/                        # Data management
│   ├── DataManager.h            # Singleton data handler
│   └── DataManager.cpp          # Dataset loading & management
├── knapsack_solver.py           # Python ILP solver (PuLP)
├── performance_visualizer.py    # Visualization generator
└── CMakeLists.txt               # Build configuration

datasets/                        # Test datasets
├── TruckAndPallets_XX.csv       # Truck capacity & pallet count
├── Pallets_XX.csv               # Pallet data (ID, weight, profit)
└── OptimalSolution_XX.txt       # Known optimal solutions
```

## Build & Installation

### Prerequisites

- **C++ Compiler**: GCC 9+ or Clang 10+ with C++17 support
- **CMake**: Version 3.15 or higher
- **Python 3.7+** (for visualization and PuLP solver)
- **Python Packages**: `matplotlib`, `numpy`, `pulp`

### Build Instructions

1. **Clone the repository**:

   ```bash
   git clone <repository-url>
   cd proj2
   ```

2. **Install Python dependencies**:

   ```bash
   pip install matplotlib numpy pulp
   ```

3. **Build the project**:

   ```bash
   mkdir build && cd build
   cmake ../src
   make
   ```

4. **Run the application**:
   ```bash
   ./project2_da_leic
   ```

### Alternative Build (CLion/IDE)

- Open the project in CLion or your preferred IDE
- CMake should automatically configure the project
- Build and run using the IDE's interface

## Usage

### Interactive Menu System

The application provides an intuitive menu-driven interface:

```
========== Pallet Packing Optimization Tool ==========
1. Load Dataset
2. Display Dataset Information
3. Run Single Algorithm
4. Run Performance Analysis
5. Generate Visualization
6. Exit
```

### Example Workflow

1. **Load a dataset** (e.g., Dataset 01)
2. **View dataset information** to understand the problem size
3. **Run performance analysis** to compare all algorithms
4. **Generate visualizations** to analyze results

### Command Line Usage

```bash
# Run specific dataset analysis
./project2_da_leic

# Generate Python visualizations
python3 performance_visualizer.py

# Run PuLP solver independently
python3 knapsack_solver.py
```

## Performance Analysis

### Algorithm Complexity Comparison

| Algorithm           | Time Complexity | Space Complexity | Best Use Case                       |
| ------------------- | --------------- | ---------------- | ----------------------------------- |
| Brute Force         | O(2^n)          | O(n)             | Small datasets (n ≤ 20)             |
| Backtracking        | O(2^n)          | O(n)             | Small-medium datasets (n ≤ 30)      |
| Dynamic Programming | O(n×W)          | O(n×W)           | Large datasets, reasonable capacity |
| Greedy-A            | O(n log n)      | O(n)             | Quick approximations                |
| Greedy-B            | O(n log n)      | O(n)             | Quick approximations                |
| ILP                 | Exponential     | Variable         | Exact solutions, medium datasets    |

### Visualization Features

- **Execution Time Charts**: Bar graphs comparing algorithm performance
- **Profit Comparison**: Solution quality analysis
- **Accuracy Metrics**: Approximation vs optimal solution ratios
- **Performance vs Dataset Size**: Scalability analysis

## Sample Results

For a typical dataset with 15 pallets:

- **Dynamic Programming**: Optimal solution in ~2ms
- **Greedy Approximation**: 95%+ accuracy in <1ms
- **Backtracking**: Optimal solution in ~15ms
- **Brute Force**: Optimal solution in ~500ms

## Technical Details

### Core Classes

- **`PalletPackingOptimizer`**: Main algorithm implementation class
- **`DataManager`**: Singleton pattern for dataset management
- **`Menu`**: User interface and interaction handling
- **`Solution`**: Structure containing algorithm results

### Key Features

- **Memory Efficient**: Optimized data structures for large datasets
- **Modular Design**: Easy to add new algorithms
- **Comprehensive Testing**: Multiple datasets with known optimal solutions
- **Cross-Platform**: Compatible with Linux, macOS, and Windows

## Documentation

Comprehensive documentation is available via Doxygen:

- Open `docs/html/index.html` in browser
- Generated from source code comments
- Includes class diagrams and API reference

## Authors

- Pedro Lunet
- [Pedro André Freitas Monteiro](https://github.com/pedroafmonteiro)

## License

This project is developed for academic purposes as part of the Design of Algorithms course.
