import serial
import time
import csv


arduino_port = "COM7"
baud = 9600
fileName = "fall-data.csv"
rows =""
ser = serial.Serial(arduino_port, baud)
ser.flushInput()
file = open(fileName, "a",newline="")
writer = csv.writer(file, delimiter=",")
while True:
    try:
        ser_bytes = ser.readline().decode("utf-8")
          # append the data to the file
        if ser_bytes !="":
            rows = [float(x) for x in ser_bytes.split(',')]
            print(rows)
            rows.insert(0,time.time())
            writer.writerow(rows)
            file.flush()
            # ani = animation.FuncAnimation(fig, animate, fargs=(xs, ys), interval=1000)
            # plt.show()



    except KeyboardInterrupt:
        print("Keyboard Interrupt")

        break
