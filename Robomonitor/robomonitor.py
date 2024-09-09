import pyserial
import time
import threading
import tkinter as tk
from matplotlib import pyplot as plt
from matplotlib.animation import FuncAnimation
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

# Serial port configuration (adjust the port and baudrate to match your ESP32 setup)
SERIAL_PORT = 'COM6'  # Change this to the correct port on your system
BAUDRATE = 115200

# Data storage for plotting
acc_data = {'x': [], 'y': [], 'z': []}
gyro_data = {'x': [], 'y': [], 'z': []}
mag_data = {'x': [], 'y': [], 'z': []}

# Function to read from the serial port
def read_serial(serial_conn):
    while True:
        try:
            line = serial_conn.readline().decode('utf-8').strip()
            values = [float(v) for v in line.split(',')]  # Assuming CSV format

            # Update sensor data
            acc_data['x'].append(values[0])
            acc_data['y'].append(values[1])
            acc_data['z'].append(values[2])

            gyro_data['x'].append(values[3])
            gyro_data['y'].append(values[4])
            gyro_data['z'].append(values[5])

            mag_data['x'].append(values[6])
            mag_data['y'].append(values[7])
            mag_data['z'].append(values[8])

            # Keep only the last 100 points for real-time plotting
            if len(acc_data['x']) > 100:
                for key in acc_data:
                    acc_data[key] = acc_data[key][-100:]
                for key in gyro_data:
                    gyro_data[key] = gyro_data[key][-100:]
                for key in mag_data:
                    mag_data[key] = mag_data[key][-100:]
        except:
            continue

# Function to start reading the serial port in a background thread
def start_serial_read():
    serial_conn = serial.Serial(SERIAL_PORT, BAUDRATE, timeout=1)
    serial_thread = threading.Thread(target=read_serial, args=(serial_conn,))
    serial_thread.daemon = True
    serial_thread.start()

# Initialize real-time plot
fig, (accel_ax, gyro_ax, mag_ax) = plt.subplots(3, 1)

# Function to update the plot dynamically
def update_plot(frame):
    accel_ax.clear()
    gyro_ax.clear()
    mag_ax.clear()

    # Plot accelerometer data
    accel_ax.plot(acc_data['x'], label='accX', color='r')
    accel_ax.plot(acc_data['y'], label='accY', color='g')
    accel_ax.plot(acc_data['z'], label='accZ', color='b')
    accel_ax.set_title('Accelerometer Data')
    accel_ax.legend()

    # Plot gyroscope data
    gyro_ax.plot(gyro_data['x'], label='gyroX', color='r')
    gyro_ax.plot(gyro_data['y'], label='gyroY', color='g')
    gyro_ax.plot(gyro_data['z'], label='gyroZ', color='b')
    gyro_ax.set_title('Gyroscope Data')
    gyro_ax.legend()

    # Plot magnetometer data
    mag_ax.plot(mag_data['x'], label='magX', color='r')
    mag_ax.plot(mag_data['y'], label='magY', color='g')
    mag_ax.plot(mag_data['z'], label='magZ', color='b')
    mag_ax.set_title('Magnetometer Data')
    mag_ax.legend()

# Use FuncAnimation to continuously update the plot
ani = FuncAnimation(fig, update_plot, interval=100)

# Function to create the GUI window using tkinter
def create_gui():
    root = tk.Tk()
    root.title("Sensor Monitor")

    # Embed the Matplotlib figure into tkinter
    canvas = FigureCanvasTkAgg(fig, master=root)
    canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=True)

    # Function to continuously update the tkinter GUI
    def update_gui():
        canvas.draw()
        root.after(100, update_gui)

    # Start updating the GUI
    update_gui()

    # Start tkinter's main loop
    root.mainloop()

# Main entry point
if __name__ == "__main__":
    # Start reading from serial port
    start_serial_read()

    # Start the GUI
    create_gui()