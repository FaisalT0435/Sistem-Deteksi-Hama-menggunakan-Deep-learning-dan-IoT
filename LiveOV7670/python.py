from cvzone.SerialModule import SerialObject 

Arduino = SerialObject()

while True:
    myData = Arduino.getData()
    print(myData[0])

