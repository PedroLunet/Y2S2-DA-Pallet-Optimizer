#!/usr/bin/env python3
"""
Performance Visualization Tool for Pallet Packing Optimization
Generates graphs to compare algorithm performance and accuracy
"""

import matplotlib.pyplot as plt
import numpy as np
import sys
import os
import json
from pathlib import Path

def read_performance_data(filename):
    """Read performance data from JSON file"""
    try:
        with open(filename, 'r') as f:
            return json.load(f)
    except FileNotFoundError:
        print(f"Error: Performance data file '{filename}' not found.")
        return None
    except json.JSONDecodeError:
        print(f"Error: Invalid JSON format in '{filename}'.")
        return None

def create_execution_time_chart(data, dataset_name, output_dir):
    """Create bar chart comparing execution times"""
    algorithms = []
    times = []
    colors = []
    
    # Define colors for different algorithm types
    color_map = {
        'Brute Force': '#ff6b6b',
        'Backtracking': '#4ecdc4', 
        'Dynamic Programming': '#45b7d1',
        'Greedy-A': '#96ceb4',
        'Greedy-B': '#ffeaa7',
        'Approximation': '#dda0dd',
        'ILP (Recursive)': '#fd79a8',
        'ILP (Python)': '#a29bfe'
    }
    
    for algo_data in data['algorithms']:
        algorithm_name = algo_data['name'].split(' - ')[0]  # Remove complexity notation
        algorithms.append(algorithm_name)
        times.append(algo_data['execution_time'])
        
        # Assign color based on algorithm type
        base_color = '#74b9ff'  # default color
        for key, color in color_map.items():
            if key.lower() in algorithm_name.lower():
                base_color = color
                break
        colors.append(base_color)
    
    plt.figure(figsize=(12, 7))
    bars = plt.bar(algorithms, times, color=colors, alpha=0.8, edgecolor='black', linewidth=0.7)
    
    plt.title(f'Algorithm Execution Time Comparison - Dataset {dataset_name}', fontsize=16, fontweight='bold')
    plt.xlabel('Algorithms', fontsize=12, fontweight='bold')
    plt.ylabel('Execution Time (ms)', fontsize=12, fontweight='bold')
    plt.xticks(rotation=45, ha='right')
    
    # Add value labels on bars
    for bar, time in zip(bars, times):
        height = bar.get_height()
        plt.text(bar.get_x() + bar.get_width()/2., height + max(times)*0.01,
                f'{time:.1f}ms', ha='center', va='bottom', fontweight='bold')
    
    plt.grid(axis='y', alpha=0.3, linestyle='--')
    plt.tight_layout()
    
    output_file = os.path.join(output_dir, f'execution_time_dataset_{dataset_name}.png')
    plt.savefig(output_file, dpi=300, bbox_inches='tight')
    plt.close()
    
    return output_file

def create_profit_comparison_chart(data, dataset_name, output_dir):
    """Create bar chart comparing total profits"""
    algorithms = []
    profits = []
    colors = []
    
    color_map = {
        'Brute Force': '#ff6b6b',
        'Backtracking': '#4ecdc4', 
        'Dynamic Programming': '#45b7d1',
        'Greedy-A': '#96ceb4',
        'Greedy-B': '#ffeaa7',
        'Approximation': '#dda0dd',
        'ILP (Recursive)': '#fd79a8',
        'ILP (Python)': '#a29bfe'
    }
    
    for algo_data in data['algorithms']:
        algorithm_name = algo_data['name'].split(' - ')[0]
        algorithms.append(algorithm_name)
        profits.append(algo_data['total_profit'])
        
        base_color = '#74b9ff'
        for key, color in color_map.items():
            if key.lower() in algorithm_name.lower():
                base_color = color
                break
        colors.append(base_color)
    
    plt.figure(figsize=(12, 7))
    bars = plt.bar(algorithms, profits, color=colors, alpha=0.8, edgecolor='black', linewidth=0.7)
    
    plt.title(f'Algorithm Profit Comparison - Dataset {dataset_name}', fontsize=16, fontweight='bold')
    plt.xlabel('Algorithms', fontsize=12, fontweight='bold')
    plt.ylabel('Total Profit', fontsize=12, fontweight='bold')
    plt.xticks(rotation=45, ha='right')
    
    # Add value labels on bars
    for bar, profit in zip(bars, profits):
        height = bar.get_height()
        plt.text(bar.get_x() + bar.get_width()/2., height + max(profits)*0.01,
                f'{profit}', ha='center', va='bottom', fontweight='bold')
    
    plt.grid(axis='y', alpha=0.3, linestyle='--')
    plt.tight_layout()
    
    output_file = os.path.join(output_dir, f'profit_comparison_dataset_{dataset_name}.png')
    plt.savefig(output_file, dpi=300, bbox_inches='tight')
    plt.close()
    
    return output_file

def create_accuracy_chart(data, dataset_name, output_dir):
    """Create accuracy comparison chart for approximation algorithms"""
    if 'accuracy' not in data or not data['accuracy']:
        return None
        
    algorithms = []
    accuracies = []
    colors = ['#96ceb4', '#ffeaa7', '#dda0dd', '#fd79a8', '#a29bfe']
    
    for algo_name, accuracy in data['accuracy'].items():
        algorithms.append(algo_name)
        accuracies.append(accuracy)
    
    plt.figure(figsize=(10, 6))
    bars = plt.bar(algorithms, accuracies, color=colors[:len(algorithms)], 
                   alpha=0.8, edgecolor='black', linewidth=0.7)
    
    plt.title(f'Algorithm Accuracy Comparison - Dataset {dataset_name}', fontsize=16, fontweight='bold')
    plt.xlabel('Algorithms', fontsize=12, fontweight='bold')
    plt.ylabel('Accuracy (%)', fontsize=12, fontweight='bold')
    plt.xticks(rotation=45, ha='right')
    plt.ylim(0, 105)
    
    # Add value labels on bars
    for bar, accuracy in zip(bars, accuracies):
        height = bar.get_height()
        plt.text(bar.get_x() + bar.get_width()/2., height + 1,
                f'{accuracy:.1f}%', ha='center', va='bottom', fontweight='bold')
    
    # Add horizontal line at 100% for reference
    plt.axhline(y=100, color='red', linestyle='--', alpha=0.7, label='Optimal (100%)')
    plt.legend()
    
    plt.grid(axis='y', alpha=0.3, linestyle='--')
    plt.tight_layout()
    
    output_file = os.path.join(output_dir, f'accuracy_comparison_dataset_{dataset_name}.png')
    plt.savefig(output_file, dpi=300, bbox_inches='tight')
    plt.close()
    
    return output_file

def create_complexity_comparison_chart(data, dataset_name, output_dir):
    """Create a combined chart showing time vs profit trade-off"""
    algorithms = []
    times = []
    profits = []
    
    for algo_data in data['algorithms']:
        algorithm_name = algo_data['name'].split(' - ')[0]
        algorithms.append(algorithm_name)
        times.append(algo_data['execution_time'])
        profits.append(algo_data['total_profit'])
    
    plt.figure(figsize=(12, 8))
    
    # Create scatter plot
    colors = plt.cm.Set3(np.linspace(0, 1, len(algorithms)))
    scatter = plt.scatter(times, profits, c=colors, s=200, alpha=0.7, edgecolors='black', linewidth=1)
    
    # Add algorithm labels
    for i, (time, profit, algo) in enumerate(zip(times, profits, algorithms)):
        plt.annotate(algo, (time, profit), xytext=(5, 5), textcoords='offset points',
                    fontsize=10, fontweight='bold')
    
    plt.title(f'Algorithm Performance Trade-off - Dataset {dataset_name}', fontsize=16, fontweight='bold')
    plt.xlabel('Execution Time (ms)', fontsize=12, fontweight='bold')
    plt.ylabel('Total Profit', fontsize=12, fontweight='bold')
    
    plt.grid(True, alpha=0.3, linestyle='--')
    plt.tight_layout()
    
    output_file = os.path.join(output_dir, f'performance_tradeoff_dataset_{dataset_name}.png')
    plt.savefig(output_file, dpi=300, bbox_inches='tight')
    plt.close()
    
    return output_file

def create_summary_report(data, dataset_name, output_dir):
    """Create a comprehensive summary chart with multiple subplots"""
    fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(16, 12))
    fig.suptitle(f'Algorithm Performance Summary - Dataset {dataset_name}', fontsize=18, fontweight='bold')
    
    algorithms = []
    times = []
    profits = []
    weights = []
    
    for algo_data in data['algorithms']:
        algorithm_name = algo_data['name'].split(' - ')[0]
        algorithms.append(algorithm_name)
        times.append(algo_data['execution_time'])
        profits.append(algo_data['total_profit'])
        weights.append(algo_data['total_weight'])
    
    colors = plt.cm.Set3(np.linspace(0, 1, len(algorithms)))
    
    # Execution Time Chart
    bars1 = ax1.bar(algorithms, times, color=colors, alpha=0.8, edgecolor='black')
    ax1.set_title('Execution Time Comparison', fontweight='bold')
    ax1.set_ylabel('Time (ms)')
    ax1.tick_params(axis='x', rotation=45)
    for bar, time in zip(bars1, times):
        height = bar.get_height()
        ax1.text(bar.get_x() + bar.get_width()/2., height + max(times)*0.01,
                f'{time:.1f}', ha='center', va='bottom', fontsize=8)
    
    # Profit Comparison Chart
    bars2 = ax2.bar(algorithms, profits, color=colors, alpha=0.8, edgecolor='black')
    ax2.set_title('Total Profit Comparison', fontweight='bold')
    ax2.set_ylabel('Profit')
    ax2.tick_params(axis='x', rotation=45)
    for bar, profit in zip(bars2, profits):
        height = bar.get_height()
        ax2.text(bar.get_x() + bar.get_width()/2., height + max(profits)*0.01,
                f'{profit}', ha='center', va='bottom', fontsize=8)
    
    # Weight Usage Chart
    bars3 = ax3.bar(algorithms, weights, color=colors, alpha=0.8, edgecolor='black')
    ax3.set_title('Weight Usage Comparison', fontweight='bold')
    ax3.set_ylabel('Total Weight')
    ax3.tick_params(axis='x', rotation=45)
    ax3.axhline(y=data.get('capacity', 100), color='red', linestyle='--', alpha=0.7, label='Capacity Limit')
    ax3.legend()
    for bar, weight in zip(bars3, weights):
        height = bar.get_height()
        ax3.text(bar.get_x() + bar.get_width()/2., height + max(weights)*0.01,
                f'{weight}', ha='center', va='bottom', fontsize=8)
    
    # Performance Trade-off Scatter Plot
    scatter = ax4.scatter(times, profits, c=colors, s=100, alpha=0.7, edgecolors='black')
    ax4.set_title('Performance Trade-off (Time vs Profit)', fontweight='bold')
    ax4.set_xlabel('Execution Time (ms)')
    ax4.set_ylabel('Total Profit')
    for i, (time, profit, algo) in enumerate(zip(times, profits, algorithms)):
        ax4.annotate(algo, (time, profit), xytext=(3, 3), textcoords='offset points', fontsize=8)
    
    plt.tight_layout()
    
    output_file = os.path.join(output_dir, f'performance_summary_dataset_{dataset_name}.png')
    plt.savefig(output_file, dpi=300, bbox_inches='tight')
    plt.close()
    
    return output_file

def main():
    if len(sys.argv) != 3:
        print("Usage: python3 performance_visualizer.py <performance_data_file> <dataset_name>")
        sys.exit(1)
    
    data_file = sys.argv[1]
    dataset_name = sys.argv[2]
    
    # Create output directory
    output_dir = "performance_graphs"
    os.makedirs(output_dir, exist_ok=True)
    
    # Read performance data
    data = read_performance_data(data_file)
    if data is None:
        sys.exit(1)
    
    print(f"Generating performance visualizations for Dataset {dataset_name}...")
    
    # Generate charts
    generated_files = []
    
    try:
        # Execution time comparison
        file1 = create_execution_time_chart(data, dataset_name, output_dir)
        generated_files.append(file1)
        print(f"✓ Execution time chart: {file1}")
        
        # Profit comparison
        file2 = create_profit_comparison_chart(data, dataset_name, output_dir)
        generated_files.append(file2)
        print(f"✓ Profit comparison chart: {file2}")
        
        # Accuracy comparison (if available)
        file3 = create_accuracy_chart(data, dataset_name, output_dir)
        if file3:
            generated_files.append(file3)
            print(f"✓ Accuracy comparison chart: {file3}")
        
        # Performance trade-off
        file4 = create_complexity_comparison_chart(data, dataset_name, output_dir)
        generated_files.append(file4)
        print(f"✓ Performance trade-off chart: {file4}")
        
        # Summary report
        file5 = create_summary_report(data, dataset_name, output_dir)
        generated_files.append(file5)
        print(f"✓ Summary report: {file5}")
        
        print(f"\nAll visualizations generated successfully!")
        print(f"Total files created: {len(generated_files)}")
        
    except Exception as e:
        print(f"Error generating visualizations: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()
