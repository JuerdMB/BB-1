# serial_monitor_widget.py
from PyQt5.QtWidgets import QWidget, QVBoxLayout, QTextEdit
from PyQt5.QtCore import QTimer
from PyQt5.QtGui import QColor

class SerialMonitor(QWidget):
    def __init__(self, serial_reader):
        super().__init__()
        self.serial_reader = serial_reader

        self.initUI()

        # Set up a timer to periodically update the serial monitor display
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.update_serial_monitor)
        self.timer.start(100)  # Refresh every 100ms

    def initUI(self):
        layout = QVBoxLayout(self)

        # QTextEdit for displaying serial data
        self.text_edit = QTextEdit()
        self.text_edit.setReadOnly(True)
        layout.addWidget(self.text_edit)

    def update_serial_monitor(self):
        # If not connected, set background to gray and display error message
        if not self.serial_reader.connected:
            self.text_edit.setStyleSheet("background-color: lightgray;")
            self.text_edit.setPlainText(self.serial_reader.connection_message)
            return

        # If connected, restore default background and append new data
        self.text_edit.setStyleSheet("background-color: white;")
        while self.serial_reader.data:
            data_line = self.serial_reader.data.pop(0)  # Pop the oldest data
            self.text_edit.append(data_line)

        # Scroll to the bottom
        self.text_edit.verticalScrollBar().setValue(self.text_edit.verticalScrollBar().maximum())