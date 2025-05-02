import sys
import pandas as pd
import matplotlib.pyplot as plt

def main(filename):
    try:
        # Load the CSV file
        data = pd.read_csv(filename)
        
        # Check for required columns
        if 'Times' not in data.columns or 'Measures' not in data.columns:
            print("CSV file must contain 'Times' and 'Measures' columns.")
            return

        # Keep only rows where 10 <= Measures <= 20
        filtered_data = data[(data['Measures'] >= 10) & (data['Measures'] <= 17)]

        # Extract filtered data
        time = filtered_data['Times']
        measures = filtered_data['Measures']

        # Plot
        plt.figure(figsize=(10, 5))
        plt.plot(time, measures, marker='o')
        plt.xlabel('Time')
        plt.ylabel('Measure')
        plt.title('Time vs Measures (10 ≤ Measures ≤ 20)')
        plt.grid(True)
        plt.tight_layout()
        plt.show()
    
    except Exception as e:
        print(f"Error: {e}")

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("Usage: python plot_time_vs_measures.py <filename.csv>")
    else:
        main(sys.argv[1])
