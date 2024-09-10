# main_window.py
from PyQt5.QtWidgets import QMainWindow, QWidget, QVBoxLayout, QHBoxLayout, QPushButton, QStackedWidget
from gui.plot_widget import IMUPlot
from gui.serial_monitor_widget import SerialMonitor
from serial_communication.serial_reader import SerialReader

class MainWindow(QMainWindow):
    def __init__(self, port='COM6', baudrate=115200):
        super().__init__()

        # Create the serial reader
        self.serial_reader = SerialReader(port=port, baudrate=baudrate)
        self.serial_reader.start()

        # Set up UI
        self.initUI()

    def initUI(self):
        self.setWindowTitle('ESP32 Monitor')

        # Create the stacked widget to switch between pages
        self.stacked_widget = QStackedWidget()
        
        # IMU Plot page
        self.imu_plot = IMUPlot(self.serial_reader)
        self.stacked_widget.addWidget(self.imu_plot)

        # Serial Monitor page
        self.serial_monitor = SerialMonitor(self.serial_reader)
        self.stacked_widget.addWidget(self.serial_monitor)

        # Layout
        main_layout = QVBoxLayout()
        main_layout.addWidget(self.stacked_widget)

        # Create navigation buttons
        nav_layout = QHBoxLayout()
        imu_button = QPushButton("IMU")
        serial_monitor_button = QPushButton("Serial Monitor")
        imu_button.clicked.connect(lambda: self.stacked_widget.setCurrentWidget(self.imu_plot))
        serial_monitor_button.clicked.connect(lambda: self.stacked_widget.setCurrentWidget(self.serial_monitor))
        nav_layout.addWidget(imu_button)
        nav_layout.addWidget(serial_monitor_button)

        # Main layout
        main_layout.addLayout(nav_layout)

        central_widget = QWidget()
        central_widget.setLayout(main_layout)
        self.setCentralWidget(central_widget)

    def closeEvent(self, event):
        # Stop the serial reader when closing
        self.serial_reader.stop()
        event.accept()