# plot_widget.py
from PyQt5.QtWidgets import QWidget, QVBoxLayout, QHBoxLayout, QCheckBox, QLabel, QLineEdit, QPushButton
from PyQt5.QtCore import QTimer
import matplotlib.pyplot as plt
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas

class IMUPlot(QWidget):
    def __init__(self, serial_reader):
        super().__init__()
        self.serial_reader = serial_reader
        self.initUI()

    def initUI(self):
        layout = QVBoxLayout(self)

        # Plot canvas
        self.fig, self.ax = plt.subplots()
        self.canvas = FigureCanvas(self.fig)
        layout.addWidget(self.canvas)

        # Checkboxes for turning channels on/off
        self.checkboxes = {}
        channels_layout = QHBoxLayout()
        for i in range(9):  # 9 IMU axes
            checkbox = QCheckBox(f'Channel {i+1}')
            checkbox.setChecked(True)
            checkbox.stateChanged.connect(self.update_plot)
            self.checkboxes[i] = checkbox
            channels_layout.addWidget(checkbox)
        layout.addLayout(channels_layout)

        # Y-range control
        y_range_layout = QHBoxLayout()
        y_range_label = QLabel("Y-Range:")
        self.y_range_min = QLineEdit("-10")
        self.y_range_max = QLineEdit("10")
        y_range_layout.addWidget(y_range_label)
        y_range_layout.addWidget(self.y_range_min)
        y_range_layout.addWidget(self.y_range_max)
        y_range_button = QPushButton("Set Range")
        y_range_button.clicked.connect(self.set_y_range)
        y_range_layout.addWidget(y_range_button)
        layout.addLayout(y_range_layout)

        # Set timer to update plot
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.update_plot)
        self.timer.start(100)

    def set_y_range(self):
        try:
            ymin = float(self.y_range_min.text())
            ymax = float(self.y_range_max.text())
            self.ax.set_ylim([ymin, ymax])
            self.canvas.draw()
        except ValueError:
            pass  # Invalid input, we could show an error message here

    def update_plot(self):
        self.ax.clear()
        
        # If not connected, change background to gray and display error message
        if not self.serial_reader.connected:
            self.ax.set_facecolor("lightgray")  # Set background color to gray
            self.ax.text(0.5, 0.5, self.serial_reader.connection_message, 
                         horizontalalignment='center', verticalalignment='center', 
                         transform=self.ax.transAxes, fontsize=12, color="black")
        else:
            # Plot only enabled channels
            if self.serial_reader.data:
                data = self.serial_reader.data[-1]  # Latest data point
                for i in range(9):  # Assuming 9 IMU axes
                    if self.checkboxes[i].isChecked() and data:
                        self.ax.plot(data[i])

        self.canvas.draw()