import serial
import time
import os

# Serial settings
port = 'COM9'  # Change this to match your Arduino's port
baudrate = 9600
test_file = 'test_number.txt'

# Read or initialize the test number
if os.path.exists(test_file):
    with open(test_file, 'r') as f:
        test_number = int(f.read().strip())
else:
    test_number = 1

# Create a new CSV filename with the test number
csv_filename = f'arduino_log_{test_number}.csv'

# Update the test number for next run
with open(test_file, 'w') as f:
    f.write(str(test_number + 1))

# Start logging
with serial.Serial(port, baudrate, timeout=1) as ser, open(csv_filename, 'w') as file:
    time.sleep(2)  # Wait for Arduino to reset
    print(f"Logging to {csv_filename}... Press Ctrl+C to stop.")

    while True:
        try:
            line = ser.readline().decode('utf-8').strip()
            if line:
                print(line)
                file.write(line + '\n')
        except KeyboardInterrupt:
            print("Logging stopped by user.")
            break
        except Exception as e:
            print(f"Error: {e}")