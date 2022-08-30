# Fall-Detection
Ubidots MQTT: stores the code used to send data to the ubidots platform

Secrets.h: File needed by ubidotsMQTT to input wifi username and password as well as ubidots token code

Data_serial: Code for the arduino to send sensor data in a readable format on the serial monitor so that a python script can easily read and store the data in a CSV file. 

Save_to_csv: Python code which reads serial monitor and saves the data onto a csv file

Fall-data stores the falls simulated with the arduino

Train-data stores the data collected when the Arduino was stationary

One Class SVM: This code runs the one class SVM algorithm using both the fall and train data. 

Local outlier factor: This code runs the local outlier factor algorithm using both the fall and train data. 


