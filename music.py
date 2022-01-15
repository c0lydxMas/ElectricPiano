import serial  # thu vien ket noi serial
import msvcrt  # thu vien nhan phim tu ban phim

ser = serial.Serial()  # Khoi tao serial
ser.baudrate = 9600  # Khoi tao bauq
ser.port = 'COM2'  # Dat cong COM2 cho chuong trinh ket noi voi 8051
ser.close()  # Dong serial de ngat ket noi
ser.open()  # Mo cong serial de giao tiếp
print("Welcome to team 6a")
while True:
    print("******Music is life*******")
    print("Enter a charater: ")
    char = msvcrt.getch().decode('ASCII')  # Su kien nhap phim vao
    ser.write(bytes(char, 'utf-8'))  # Gui phim sang 8051
    print("Output: ") 
    print(ser.read())
    if (char == '\x03'): break  # Cho phep Ctr+C de ket thuc chuong trinh

ser.close()  # Dong serial de ngat ket noi
