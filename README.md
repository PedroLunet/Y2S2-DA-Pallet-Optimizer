# 📦 Pallet Packing Optimization - Knapsack Problem Solver

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white)
![Algorithm](https://img.shields.io/badge/Algorithm-Dynamic_Programming-red?style=for-the-badge)
![Optimization](https://img.shields.io/badge/Optimization-Knapsack-green?style=for-the-badge)

A sophisticated pallet packing optimization tool developed in C++ for the Design of Algorithms (DA) course at FEUP. This project demonstrates advanced algorithmic implementations for solving the 0-1 Knapsack Problem variant, featuring multiple optimization approaches and comprehensive performance analysis.

## 🌐 About

The Pallet Packing Optimization Tool is a comprehensive solution for optimizing cargo loading in transportation scenarios. Built with performance and algorithm diversity in mind, it offers:

- Multiple algorithmic approaches from exact to approximation solutions
- Real-time performance comparison and analysis
- Comprehensive visualization and reporting capabilities
- Interactive command-line interface for seamless user experience
- Python integration for advanced mathematical programming
- Scalable solutions for datasets of varying complexity

## 🎯 Problem Description

The **Pallet Packing Problem** involves optimizing the loading of pallets into a truck with limited weight capacity. Each pallet has:

- **Weight**: Physical weight constraint
- **Profit**: Value/importance of the pallet

**Objective**: Maximize total profit while respecting the truck's weight capacity constraint.

This is a classic variant of the **0-1 Knapsack Problem** where each pallet can either be selected (1) or not selected (0), but cannot be partially selected.

## 🚀 Features

### 🛠️ Optimization Capabilities

- **Exact Solutions**: Brute force and backtracking for guaranteed optimal results
- **Dynamic Programming**: Efficient optimal solutions with O(n×W) complexity
- **Approximation Algorithms**: Fast greedy approaches with high accuracy ratios
- **Integer Linear Programming**: Advanced mathematical programming with PuLP
- **Hybrid Approaches**: Combined strategies for optimal performance-accuracy balance

### 📊 Advanced Algorithms

- **Brute Force Algorithm**: Complete enumeration with O(2^n) complexity for small datasets
- **Backtracking with Pruning**: Optimized search with early termination strategies
- **Dynamic Programming**: Bottom-up approach with optimal substructure exploitation
- **Greedy Strategies**: Profit-to-weight and pure profit maximization heuristics
- **Mathematical Programming**: Recursive and Python-based ILP implementations

### 💾 Data Management & Analysis

- **CSV Integration**: Efficient parsing of pallet and truck capacity data
- **Performance Metrics**: Comprehensive execution time and accuracy tracking
- **Visualization Tools**: Matplotlib-generated charts and performance graphs
- **JSON Reporting**: Detailed export of algorithm performance and results
- **Dataset Validation**: Robust error handling and data integrity verification

### 🎯 User Interface & Tools

- **Interactive Menu**: Intuitive command-line interface for all operations
- **Real-time Analysis**: Live algorithm execution and performance monitoring
- **Comparative Studies**: Side-by-side algorithm performance evaluation
- **Python Integration**: Seamless integration with visualization and ILP tools

## 🛠 Technical Implementation

### Tech Stack

- **Language**: C++17 with modern STL features
- **Build System**: CMake for cross-platform compilation
- **Mathematical Programming**: Python PuLP for ILP solutions
- **Visualization**: Matplotlib and NumPy for performance analysis
- **Documentation**: Comprehensive inline documentation and analysis

### System Architecture

```
┌─────────────────────┐
│   Menu Interface    │
├─────────────────────┤
│ Algorithm Optimizer │
├─────────────────────┤
│   Data Manager      │
├─────────────────────┤
│ Performance Analyzer│
├─────────────────────┤
│   Dataset Files     │
└─────────────────────┘
```

### Core Components

- **PalletPackingOptimizer**: Main algorithm implementation engine
- **DataManager**: Singleton pattern for efficient dataset management
- **Menu System**: User-friendly interface for algorithm selection and execution
- **Performance Analyzer**: Comprehensive timing and accuracy measurement tools
- **Visualization Engine**: Python-based chart generation and analysis tools

## 🏗 Setup and Installation

### Prerequisites

- **C++17 compatible compiler** (GCC 9+, Clang 10+, MSVC 2019+)
- **CMake 3.15** or higher
- **Python 3.7+** (for visualization and ILP solver)
- **Python Packages**: `matplotlib`, `numpy`, `pulp`

### Quick Start

```bash
# Clone the repository
git clone git@github.com:PedroLunet/Y2S2-DA-Path-Planning-Tool.git
cd Y2S2-DA-Pallet-Optimizer

# Install Python dependencies
pip install matplotlib numpy pulp

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ../src

# Build the project
make

# Run the application
./project2_da_leic
```

### Alternative Build (CLion/IDE)

- Open the project in CLion or your preferred IDE
- CMake should automatically configure the project
- Build and run using the IDE's interface

### Manual Build (without CMake)

```bash
# Navigate to source directory
cd src

# Compile manually
g++ -std=c++17 -O2 -o pallet_optimizer main.cpp menu/Menu.cpp \
    data/DataManager.cpp optimizer/PalletPackingOptimizer.cpp

# Run the executable
./pallet_optimizer
```

## 📁 Project Structure

```
Y2S2-DA-Path-Planning-Tool/
├── src/                          # Source code
│   ├── main.cpp                 # Application entry point
│   ├── CMakeLists.txt           # Build configuration
│   ├── optimizer/               # Algorithm implementations
│   │   ├── PalletPackingOptimizer.h
│   │   └── PalletPackingOptimizer.cpp
│   ├── menu/                    # User interface
│   │   ├── Menu.h
│   │   └── Menu.cpp
│   ├── data/                    # Data management
│   │   ├── DataManager.h
│   │   └── DataManager.cpp
│   ├── knapsack_solver.py       # Python ILP solver
│   └── performance_visualizer.py # Visualization tools
├── datasets/                     # Test datasets
│   ├── TruckAndPallets_XX.csv   # Truck capacity data
│   ├── Pallets_XX.csv           # Pallet specifications
│   └── OptimalSolution_XX.txt   # Known optimal solutions
├── docs/                        # Documentation
│   └── Doxyfile.in             # Doxygen configuration
└── README.md                    # Project documentation
```

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

1. **Load a dataset** (e.g., Dataset 01) to begin analysis
2. **View dataset information** to understand problem complexity
3. **Run performance analysis** to compare all implemented algorithms
4. **Generate visualizations** to analyze results and performance trends

### Command Line Usage

```bash
# Run the main application
./project2_da_leic

# Generate Python visualizations independently
python3 performance_visualizer.py

# Run PuLP ILP solver directly
python3 knapsack_solver.py
```

## ⚡ Performance & Complexity

### Algorithm Complexities

- **Brute Force Algorithm**: O(2^n) - Complete enumeration for small datasets
- **Backtracking with Pruning**: O(2^n) - Optimized with early termination
- **Dynamic Programming**: O(n×W) - Optimal polynomial-time solution
- **Greedy Algorithms**: O(n log n) - Fast approximation with sorting
- **Integer Linear Programming**: Exponential - Exact solutions for medium datasets

### Memory Efficiency

- Efficient data structure design for minimal memory overhead
- Optimized dynamic programming with space complexity optimization
- Smart memory management for large dataset processing
- Template-based implementation for type flexibility

### Visualization Features

- **Execution Time Charts**: Bar graphs comparing algorithm performance
- **Profit Comparison**: Solution quality analysis
- **Accuracy Metrics**: Approximation vs optimal solution ratios
- **Performance vs Dataset Size**: Scalability analysis

### Sample Results

For a typical dataset with 15 pallets:

- **Dynamic Programming**: Optimal solution in ~2ms
- **Greedy Approximation**: 95%+ accuracy in <1ms
- **Backtracking**: Optimal solution in ~15ms
- **Brute Force**: Optimal solution in ~500ms

## 🎯 Key Features Implemented

- ✅ Complete knapsack optimization system with multiple algorithms
- ✅ Dynamic programming optimal solution implementation
- ✅ Greedy approximation algorithms with accuracy analysis
- ✅ Integer Linear Programming with Python PuLP integration
- ✅ Comprehensive performance analysis and comparison tools
- ✅ Advanced visualization with matplotlib charts
- ✅ Interactive command-line interface with menu system
- ✅ Robust error handling and dataset validation
- ✅ JSON export for detailed performance reporting
- ✅ Cross-platform compatibility and build system

## 🏆 Learning Outcomes

Through this project, we gained practical experience with:

- **Advanced Algorithms**: Implementation of dynamic programming and optimization techniques
- **Algorithm Analysis**: Complexity analysis and performance comparison methodologies
- **Software Engineering**: Modern C++ practices and modular design patterns
- **Mathematical Programming**: Integration of ILP solvers and optimization libraries
- **Data Visualization**: Python-based chart generation and performance analysis
- **Project Management**: Team collaboration and version control with Git

## 👥 Development Team

This project was developed by Group 2 - Class 15:

- Pedro Lunet
- [Pedro André Freitas Monteiro](https://github.com/pedroafmonteiro)

## 📜 Course Information

Developed for the Design of Algorithms (DA) course - Project 2, Spring 2025  
Faculty of Engineering, University of Porto (FEUP)

---

_Build and run the application to explore advanced pallet packing optimization with multiple algorithmic approaches. The system demonstrates efficient implementations suitable for real-world cargo loading scenarios._
