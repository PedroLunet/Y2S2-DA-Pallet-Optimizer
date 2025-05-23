from pulp import LpProblem, LpMaximize, LpVariable, lpSum, LpStatus, value, PULP_CBC_CMD
import sys
import csv


def read_truck_data(filename):
    try:
        with open(filename, 'r') as f:
            reader = csv.reader(f)
            header = next(reader)  # Skip header
            data = next(reader)
            capacity = int(data[0])
            return capacity
    except Exception as e:
        print(f"Error reading truck data from {filename}: {e}", file=sys.stderr)
        sys.exit(1)


def read_pallets_data(filename):
    try:
        pallets = []
        with open(filename, 'r') as f:
            reader = csv.reader(f)
            header = next(reader)  # Skip header
            for row in reader:
                pallet_id = int(row[0])
                weight = int(row[1])
                profit = int(row[2])
                pallets.append({
                    'id': pallet_id,
                    'weight': weight,
                    'profit': profit
                })
        return pallets
    except Exception as e:
        print(f"Error reading pallets data from {filename}: {e}", file=sys.stderr)
        sys.exit(1)


def solve_knapsack_ilp(capacity, pallets):
    # Create the problem
    model = LpProblem("Pallet_Packing_Knapsack", LpMaximize)
    
    # Decision variables - binary variables for each pallet
    x = {}
    for pallet in pallets:
        x[pallet['id']] = LpVariable(f"x_{pallet['id']}", cat="Binary")
    
    # Objective function - maximize total profit
    model += lpSum(x[pallet['id']] * pallet['profit'] for pallet in pallets)
    
    # Constraint - total weight cannot exceed capacity
    model += lpSum(x[pallet['id']] * pallet['weight'] for pallet in pallets) <= capacity
    
    # Solve the problem (suppress solver output)
    solver = PULP_CBC_CMD(msg=0)
    model.solve(solver)
    
    # Check if solution is optimal
    if LpStatus[model.status] != "Optimal":
        pass  # Silently handle non-optimal solutions
    
    # Extract results
    selected_pallets = []
    total_profit = 0
    total_weight = 0
    
    for pallet in pallets:
        if value(x[pallet['id']]) > 0.5:  # Binary variable is selected
            selected_pallets.append(pallet['id'])
            total_profit += pallet['profit']
            total_weight += pallet['weight']
    
    return {
        'selected_pallets': selected_pallets,
        'total_profit': total_profit,
        'total_weight': total_weight,
        'status': LpStatus[model.status]
    }


def write_results(filename, solution):
    try:
        with open(filename, 'w') as f:
            f.write(f"{solution['total_profit']}\n")
            f.write(f"{solution['total_weight']}\n")
            if solution['selected_pallets']:
                f.write(" ".join(map(str, solution['selected_pallets'])) + "\n")
            else:
                f.write("\n")
    except Exception as e:
        print(f"Error writing results to {filename}: {e}", file=sys.stderr)
        sys.exit(1)


def main():
    if len(sys.argv) != 4:
        print("Usage: python3 knapsack_solver.py <truck_file> <pallets_file> <output_file>", file=sys.stderr)
        sys.exit(1)
    
    truck_file = sys.argv[1]
    pallets_file = sys.argv[2]
    output_file = sys.argv[3]
    
    # Read input data
    capacity = read_truck_data(truck_file)
    pallets = read_pallets_data(pallets_file)
    
    # Debug output
    print(f"Loaded {len(pallets)} pallets with capacity {capacity}", file=sys.stderr)
    
    # Solve the knapsack problem
    solution = solve_knapsack_ilp(capacity, pallets)
    
    # Debug output
    print(f"Solution status: {solution['status']}", file=sys.stderr)
    print(f"Selected {len(solution['selected_pallets'])} pallets", file=sys.stderr)
    print(f"Total profit: {solution['total_profit']}, Total weight: {solution['total_weight']}", file=sys.stderr)
    
    # Write results
    write_results(output_file, solution)
    
    print("Knapsack solving completed successfully!", file=sys.stderr)


if __name__ == "__main__":
    main()
