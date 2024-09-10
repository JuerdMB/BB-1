# serial_reader.py
import serial
import threading
import time

class SerialReader(threading.Thread):
    def __init__(self, port='COM6', baudrate=115200, reconnect_interval=1):
        super().__init__()
        self.port = port
        self.baudrate = baudrate
        self.reconnect_interval = reconnect_interval
        self.ser = None
        self.is_running = True
        self.data = []
        self.connected = False
        self.connection_message = "Not connected"  # Initialize connection message

    def run(self):
        while self.is_running:
            if not self.connected:
                self.try_connect()
            if self.connected:
                try:
                    if self.ser.in_waiting > 0:
                        line = self.ser.readline().decode('utf-8').strip()
                        self.data.append(line)
                except serial.SerialException:
                    # Handle connection loss
                    self.connection_message = f"Lost connection to {self.port}. Attempting to reconnect..."
                    print(self.connection_message)  # Log to terminal
                    self.connected = False
                    if self.ser:
                        self.ser.close()
            time.sleep(0.1)

    def try_connect(self):
        try:
            self.ser = serial.Serial(self.port, self.baudrate)
            self.connected = True
            self.connection_message = f"Connected to {self.port}"
            print(self.connection_message)  # Log to terminal
        except serial.SerialException:
            # Failed to connect, update the message
            self.connection_message = f"Could not open port {self.port}. Retrying in {self.reconnect_interval} seconds..."
            print(self.connection_message)  # Log to terminal
            self.connected = False
            time.sleep(self.reconnect_interval)

    def stop(self):
        self.is_running = False
        if self.connected and self.ser:
            self.ser.close()