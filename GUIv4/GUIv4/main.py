import sys
from PyQt6.QtCore import QThread, pyqtSignal
from PyQt6.QtWidgets import QApplication, QMainWindow
from PyQt6.uic import loadUi
import serial.tools.list_ports
import time
import KinematicRobot  # Kinematics


class DataReceiveThread(QThread):
    data_received = pyqtSignal(str)

    def __init__(self):
        super().__init__()
        self.ser = None

    def set_serial_port(self, serial_port):
        self.ser = serial_port

    def run(self):
        if self.ser is not None:
            self.ser.timeout = 2
            while True:
                data = self.ser.readline().decode()
                self.data_received.emit(data)


class MyMainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        # Load the user interface from the .ui file
        loadUi("GUIv4/Robot3Dof_v4.ui", self)
        self.program_started = False
        self.connected = False
        self.selected_port = None
        self.ser = None
        self.send_data = None
        # self.receive_data = None
        self.receive_thread = DataReceiveThread()
        self.receive_thread.data_received.connect(self.process_receive_data)
        self.receive_thread.start()

        self.pushButton_setTh1.clicked.connect(self.setTheta1)
        self.pushButton_setTh2.clicked.connect(self.setTheta2)
        self.pushButton_setTh3.clicked.connect(self.setTheta3)

        self.pushButton_FK.clicked.connect(self.calculate_FK)

        self.pushButton_IK.clicked.connect(self.calculate_IK)

        self.pushButton_run.clicked.connect(self.run)

        self.pushButton_stop.clicked.connect(self.stop)

        self.pushButton_reset.clicked.connect(self.reset)

        self.pushButton_setHome.clicked.connect(self.setHome)

        self.populate_com_ports()
        self.pushButton_connect.clicked.connect(self.connect_com_port)
        self.pushButton_disconnect.clicked.connect(self.disconnect_com_port)

        self.pushButton_base_setPID.clicked.connect(self.base_setPID)
        self.pushButton_link1_setPID.clicked.connect(self.link1_setPID)
        self.pushButton_link2_setPID.clicked.connect(self.link2_setPID)

    def process_send_data(self, output_string):
        self.send_data = output_string
        self.ser.write(self.send_data.encode())
        self.lineEdit_sent_data.setText(output_string)
        length = len(output_string) * self.dataBits / 8
        self.lineEdit_sent_length.setText(str(length))
        print(output_string)
        # time.sleep(0.01)

    def process_receive_data(self, data):
        self.lineEdit_received_data.setText(data)

    def setTheta1(self):
        if self.program_started:
            self.theta1 = float(self.lineEdit_FK_th1.text())
            self.process_send_data(f"Base: {self.theta1}")

    def setTheta2(self):
        if self.program_started:
            self.theta2 = float(self.lineEdit_FK_th2.text())
            self.process_send_data(f"Link1: {self.theta2}")

    def setTheta3(self):
        if self.program_started:
            self.theta3 = float(self.lineEdit_FK_th3.text())
            self.process_send_data(f"Link2: {self.theta3}")

    def calculate_FK(self):
        if self.program_started:
            self.Px = KinematicRobot.Forward_Kinematic(
                self.theta1, self.theta2, self.theta3
            )[0]
            self.Py = KinematicRobot.Forward_Kinematic(
                self.theta1, self.theta2, self.theta3
            )[1]
            self.Pz = KinematicRobot.Forward_Kinematic(
                self.theta1, self.theta2, self.theta3
            )[2]
            self.lineEdit_FK_Px.setText(str(self.Px))
            self.lineEdit_FK_Py.setText(str(self.Py))
            self.lineEdit_FK_Pz.setText(str(self.Pz))

    def calculate_IK(self):
        if self.program_started:
            self.Px = float(self.lineEdit_IK_Px.text())
            self.Py = float(self.lineEdit_IK_Py.text())
            self.Pz = float(self.lineEdit_IK_Pz.text())
            self.theta = float(self.lineEdit_IK_th.text())
            self.theta1, self.theta2, self.theta3 = KinematicRobot.Inverse_Kinematic(
                self.Px, self.Py, self.Pz, self.theta
            )

            self.lineEdit_IK_th1.setText(str(self.theta1))
            self.lineEdit_IK_th2.setText(str(self.theta2))
            self.lineEdit_IK_th3.setText(str(self.theta3))

            self.process_send_data(f"I{self.theta1}A{self.theta2}B{self.theta3}C")

    def run(self):
        self.program_started = True
        self.process_send_data(f"Run")
        print("Program started")

    def stop(self):
        self.program_started = False
        self.lineEdits = [
            self.lineEdit_FK_th1,
            self.lineEdit_FK_th2,
            self.lineEdit_FK_th3,
            self.lineEdit_FK_Px,
            self.lineEdit_FK_Py,
            self.lineEdit_FK_Pz,
            self.lineEdit_IK_th1,
            self.lineEdit_IK_th2,
            self.lineEdit_IK_th3,
            self.lineEdit_IK_Px,
            self.lineEdit_IK_Py,
            self.lineEdit_IK_Pz,
            self.lineEdit_IK_th,
        ]
        for lineEdit in self.lineEdits:
            lineEdit.clear()
        self.process_send_data(f"Stop")
        print("Program stopped")

    def reset(self):
        if self.program_started:
            self.stop()
            self.run()

    def setHome(self):
        if self.program_started:
            self.theta1 = 0
            self.theta2 = 0
            self.theta3 = 0
            self.lineEdit_FK_th1.setText(str(self.theta1))
            self.lineEdit_FK_th2.setText(str(self.theta2))
            self.lineEdit_FK_th3.setText(str(self.theta3))
            self.calculate_FK()

            self.process_send_data(f"Home: 1")

    def populate_com_ports(self):
        ports = serial.tools.list_ports.comports()
        for port in ports:
            self.comboBox_comPort.addItem(port.device)

    def connect_com_port(self):
        if not self.connected:
            self.selected_port = self.comboBox_comPort.currentText()
            baudrate = int(self.comboBox_baudRate.currentText())
            self.dataBits = int(self.comboBox_dataBits.currentText())
            parity_string = self.comboBox_parity.currentText()
            if parity_string == "None":
                parity = serial.PARITY_NONE
            elif parity_string == "Even":
                parity = serial.PARITY_EVEN
            else:
                parity = serial.PARITY_ODD
            stopBits = int(self.comboBox_stopBits.currentText())
            try:
                # Thực hiện kết nối đến cổng COM
                self.ser = serial.Serial(
                    self.selected_port, baudrate, self.dataBits, parity, stopBits
                )
                self.connected = True
                self.receive_thread.set_serial_port(self.ser)
                self.label_state.setText("ON")
                print(f"Connected to {self.selected_port} at {baudrate} baud")
            except Exception as e:
                print(f"Error connecting to {self.selected_port}: {str(e)}")
        else:
            print("Already connected to a COM port.")

    def disconnect_com_port(self):
        if self.connected:
            self.ser.close()
            self.connected = False
            self.label_state.setText("OFF")
            print(f"Disconnected from {self.selected_port}")
        else:
            print("Not connected to any COM port.")

    def base_setPID(self):
        if self.program_started:
            valueKp = float(self.lineEdit_base_Kp.text())
            valueKi = float(self.lineEdit_base_Ki.text())
            valueKd = float(self.lineEdit_base_Kd.text())
            self.process_send_data(f"Base: Kp-{valueKp} Ki-{valueKi} Kd-{valueKd}")

    def link1_setPID(self):
        if self.program_started:
            valueKp = float(self.lineEdit_link1_Kp.text())
            valueKi = float(self.lineEdit_link1_Ki.text())
            valueKd = float(self.lineEdit_link1_Kd.text())
            self.process_send_data(f"Link1: P{valueKp}I{valueKi}D{valueKd}")

    def link2_setPID(self):
        if self.program_started:
            valueKp = float(self.lineEdit_link2_Kp.text())
            valueKi = float(self.lineEdit_link2_Ki.text())
            valueKd = float(self.lineEdit_link2_Kd.text())
            self.process_send_data(f"Link2: P{valueKp}I{valueKi}D{valueKd}")


if __name__ == "__main__":
    app = QApplication(sys.argv)
    main_window = MyMainWindow()
    main_window.show()
    sys.exit(app.exec())
