import serial
import msvcrt

# khoi tao serial
s = serial.Serial()
s.port = "COM6" 
s.baudrate = 9600 
s.close() 
s.open()

#cac not nhac tuong ung voi phim bam tren ban phim
#Do-Z
#Re-X
#Mi-C
#Fa-V
#Son-B
#La-N
#Si-M

while True:
	if msvcrt.kbhit(): #kiem tra xem co bam phim khong
		note = msvcrt.getch() # neu co lay gia tri cua phim do
		note = note.decode("ASCII") # chuyen sang ma ASCII
		s.write(bytes(note, "utf-8")) # gui byte ky tu do qua cong COM6
		print(note) # in ra ky tu do tren man hinh
		if(note == "S"): break # neu bam S (STOP) thi thoat chuong trinh

# dong serial
s.close()




