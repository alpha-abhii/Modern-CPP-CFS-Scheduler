import pandas as pd
import matplotlib.pyplot as plt
import sys

def main():
    """
    Reads a CSV file of process schedules and generates a timeline plot.
    """
    csv_file = 'process_schedule.csv'
    try:
        df = pd.read_csv(csv_file)
    except FileNotFoundError:
        print(f"Error: The file '{csv_file}' was not found.")
        print("Please run the C++ simulation first to generate it.")
        sys.exit(1)

    # Convert timestamps from nanoseconds to a more manageable scale for plotting
    min_time = df['start_time'].min()
    df['start_time'] = (df['start_time'] - min_time) / 1e6  # Convert to milliseconds
    df['end_time'] = (df['end_time'] - min_time) / 1e6      # Convert to milliseconds

    # Set a professional plot style
    plt.style.use('seaborn-v0_8-darkgrid')
    fig, ax = plt.subplots(figsize=(14, 7), facecolor='#2c2c2c')
    ax.set_facecolor('#2c2c2c')

    # Assign a unique color to each process ID
    pids = sorted(df['pid'].unique())
    colors = plt.cm.get_cmap('viridis', len(pids))
    pid_colors = {pid: colors(i) for i, pid in enumerate(pids)}

    # Plot each process execution slice as a horizontal bar
    for _, row in df.iterrows():
        ax.hlines(y=f"PID {row['pid']}",
                 xmin=row['start_time'],
                 xmax=row['end_time'],
                 linewidth=20,
                 color=pid_colors[row['pid']],
                 alpha=0.8)

    # Customize the plot for readability and aesthetics
    ax.set_title('Process Schedule Timeline (CFS Simulation)', color='white', fontsize=16, pad=20)
    ax.set_xlabel('Time (milliseconds)', color='white', fontsize=12)
    ax.set_ylabel('Process ID', color='white', fontsize=12)
    
    ax.tick_params(axis='both', colors='white')
    plt.setp(ax.get_xticklabels(), color='white')
    plt.setp(ax.get_yticklabels(), color='white')
    ax.grid(True, axis='x', linestyle='--', alpha=0.4, color='#a0a0a0')
    
    # Invert y-axis to have PID 1 at the top
    ax.invert_yaxis()
    
    plt.tight_layout()
    
    # Save the plot
    output_filename = 'process_schedule.png'
    plt.savefig(output_filename, facecolor=fig.get_facecolor(), dpi=150)
    
    print(f"Plot saved as '{output_filename}'")
    # plt.show() # Uncomment to display the plot directly

if __name__ == '__main__':
    main()
