#include "reg51.h"
#include "string.h"
//Dinh nghia mot so chan de dieu khien den LCD
#define LCD_DATA P2
sbit EN=P0^2;
sbit RS=P0^0;
sbit RW=P0^1;	   
//Khai bao prototype cho cac ham
void Init_System();	
void Delay_ms(int interval);  
void LCD_init();
void Wait_For_LCD();
void LCD_Send_Command(unsigned char x);
void LCD_Write_One_Char(unsigned char c);
void LCD_Write_String(unsigned char *s);

sbit SPK  = P3^7;	

//verify this table according to your CPU clock
code unsigned int note_table[]={
    0xf9, 0x1f,        //1 do
    0xf9, 0xdf,        //2 re
    0xfa, 0x8a,        //3 mi
    0xfa, 0xd8,        //4 pha
    0xfb, 0x68,        //5 sol
    0xfb, 0xe9,        //6 la
    0xfc, 0x23,        //7 si
	0xfc, 0x8f,        //8 DO
    0xfc, 0xef,        //9 RE
    0xfd, 0x45,        //10 MI
    0xfd, 0x6c,        //11 PHA
};
unsigned char note_index;	

void init();		
void delay(unsigned int time); 

char uart_data;
void serial_IT(void) interrupt 4
{
  	if (RI == 1)
  	{ 
    	RI = 0; 			/* prepare for next reception */
    	uart_data = SBUF; 	/* Read receive data */
    	SBUF = uart_data; 	/* Send back same data on uart*/
  	}
  	else 
    	TI = 0; 			/* if emission occur */
}

void main(void) 
{
	unsigned char i;		//Bien lap de hien thi not va duy tri speaker
	init();				   	//Khoi tao timer0

	SCON = 0x50; 			/* uart in mode 1 (8 bit), REN=1 */
  	TMOD = TMOD | 0x20 ; 	/* Timer 1 in mode 2 */
 	TH1 = 0xFD; 			/* 9600 Bds at 11.0592MHz */
  	TL1 = 0xFD; 			/* 9600 Bds at 11.0592MHz */
  	ES = 1; 				/* Enable serial interrupt*/
  	EA = 1; 				/* Enable global interrupt */
  	TR1 = 1; 				/* Timer 1 run */
 	
	Init_System();
	for(i = 0; i < 6; i++){		// test man hinh LCD
		LCD_init();
		LCD_Write_String("100a KTMT-k63");
		LCD_Send_Command(0xC0); //Chuyen con tro xuong dong thu 2
		LCD_Write_String("**************");
	}

	while(1){
		note_index=0;
		delay(100);
		switch(uart_data){

			case 'a': 			  	//not C4

				note_index=0;				// vi tri tao do not C4 trong mang
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				for(i = 0; i < 10; i++){   // vua hien thi vua cho phep thay doi som hon khi co ngat 
					LCD_init();
					LCD_Write_String("C4");
					delay(5000);
					if(uart_data != 'a'){
						switch(uart_data);
						break;
					}
				}
				TR0=0;
				SPK=1;
				if(uart_data == 'a') uart_data = 'p';	//xoa phim, khi nguoi dung khong giu phim nua
				break;
			
			case 's':  				// not D4
		
				note_index=2;
				TH0=note_table[note_index];		 // vi tri tao do not D4 trong mang
				TL0=note_table[note_index+1];			
				TR0=1;
				for(i = 0; i < 10; i++){	 // vua hien thi vua cho phep thay doi som hon khi co ngat 
					LCD_init();
					LCD_Write_String("D4");
					delay(5000);
					if(uart_data != 's'){
						switch(uart_data);				
						break;
					}
				}
				TR0=0;
				SPK=1;
				if(uart_data == 's') uart_data = 'p';	//xoa phim, khi nguoi dung khong giu phim nua
				break;

			case 'd':				// not E4
			
				note_index=4;					// vi tri tao do not C4 trong mang
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				for(i = 0; i < 10; i++){	 // vua hien thi vua cho phep thay doi som hon khi co ngat 
					LCD_init();
					LCD_Write_String("E4");
					delay(5000);
					if(uart_data != 'd'){
						switch(uart_data);			
						break;
					}
				}
				TR0=0;
				SPK=1;
				if(uart_data == 'd') uart_data = 'p';	//xoa phim, khi nguoi dung khong giu phim nua
				break;

			case 'f': 			 	// not F4

				note_index=6;				  	// vi tri tao do not F4 trong mang
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				for(i = 0; i < 10; i++){	 // vua hien thi vua cho phep thay doi som hon khi co ngat 
					LCD_init();
					LCD_Write_String("F4");
					delay(5000);
					if(uart_data != 'f'){
						switch(uart_data);
						break;
					}
				}
				TR0=0;
				SPK=1;
				if(uart_data == 'f') uart_data = 'p';	  //xoa phim, khi nguoi dung khong giu phim nua
				break;

			case 'g': 				// not G4

				note_index=8;					// vi tri tao do not C4 trong mang
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				for(i = 0; i < 10; i++){	 // vua hien thi vua cho phep thay doi som hon khi co ngat 
					LCD_init();
					LCD_Write_String("G4");
					delay(5000);
					if(uart_data != 'g'){
						switch(uart_data);
						break;
					}
				}
				TR0=0;
				SPK=1;
				if(uart_data == 'g') uart_data = 'p';	 //xoa phim, khi nguoi dung khong giu phim nua
				break;

			case 'h':			   	// not A4

				note_index=10;			 		// vi tri tao do not A4 trong mang
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				for(i = 0; i < 10; i++){	 // vua hien thi vua cho phep thay doi som hon khi co ngat 
					LCD_init();
					LCD_Write_String("A4");
					delay(5000);
					if(uart_data != 'h'){
						switch(uart_data);
						break;
					}
				}
				TR0=0;
				SPK=1;
				if(uart_data == 'h') uart_data = 'p';	 //xoa phim, khi nguoi dung khong giu phim nua
				break;

			case 'j': 			 	// not B4b

				note_index=12;				   	// vi tri tao do not B4b trong mang
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				for(i = 0; i < 10; i++){	 // vua hien thi vua cho phep thay doi som hon khi co ngat 
					LCD_init();
					LCD_Write_String("B4");
					delay(5000);
					if(uart_data != 'j'){
						switch(uart_data);
						break;
					}
				}
				TR0=0;
				SPK=1;
				if(uart_data == 'j') uart_data = 'p';	 //xoa phim, khi nguoi dung khong giu phim nua
				break;

			case 'k': 			 	// not B4

				note_index=14;					// vi tri tao do not B4 trong mang
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				for(i = 0; i < 10; i++){	 // vua hien thi vua cho phep thay doi som hon khi co ngat 
					LCD_init();
					LCD_Write_String("C5");
					delay(5000);
					if(uart_data != 'k'){
						switch(uart_data);
						break;
					}
				}
				TR0=0;
				SPK=1;
				if(uart_data == 'k') uart_data = 'p';
				break;

			case 'l': 				 // not C5
										   		// vi tri tao do not C5 trong mang
				note_index=16;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				for(i = 0; i < 10; i++){	 // vua hien thi vua cho phep thay doi som hon khi co ngat 
					LCD_init();
					LCD_Write_String("D5");
					delay(5000);
					if(uart_data != 'l'){
						switch(uart_data);
						break;
					}
				}
				TR0=0;
				SPK=1;
				if(uart_data == 'l') uart_data = 'p';	//xoa phim, khi nguoi dung khong giu phim nua
				break;

			case 'z': 				 // not C5
										   		// vi tri tao do not C5 trong mang
				note_index=18;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				for(i = 0; i < 10; i++){	 // vua hien thi vua cho phep thay doi som hon khi co ngat 
					LCD_init();
					LCD_Write_String("E5");
					delay(5000);
					if(uart_data != 'z'){
						switch(uart_data);
						break;
					}
				}
				TR0=0;
				SPK=1;
				if(uart_data == 'z') uart_data = 'p';	//xoa phim, khi nguoi dung khong giu phim nua
				break;

			case 'x': 				 // not C5
										   		// vi tri tao do not C5 trong mang
				note_index=20;
				TH0=note_table[note_index];
				TL0=note_table[note_index+1];			
				TR0=1;
				for(i = 0; i < 10; i++){	 // vua hien thi vua cho phep thay doi som hon khi co ngat 
					LCD_init();
					LCD_Write_String("F5");
					delay(5000);
					if(uart_data != 'x'){
						switch(uart_data);
						break;
					}
				}
				TR0=0;
				SPK=1;
				if(uart_data == 'x') uart_data = 'p';	//xoa phim, khi nguoi dung khong giu phim nua
				break;

			default:				// Nguoi dung nhap cac phim khac not nhac
				LCD_init(); 	   	// Cac truong khac thi xoa man hinh LCD
				break;	
		}
	}			
}

// Khai bao timer0
void init()
{
	TMOD=0x01;
	EA=1;
	ET0=1;
	TR0=0;
}

// Khi co ngat timer0 thi thay doi not nhac
void timer0() interrupt 1
{
	TH0=note_table[note_index];
	TL0=note_table[note_index+1];
	SPK=~SPK;			// thay doi trang thai speaker
}

void delay(unsigned int time)
{
	while(time--);
}

void Delay_ms(int interval)	    // Ham delay_ms da giam xuong 10 lan 
								// de vua hien not nhac	vua co nhac, vua cho ngat
{
	unsigned char i,j;
	for(i=0;i<100;i++)
	{
		for(j=0;j<interval;j++);
	}
}

void Init_System()
{
	//Thiet lap LCD o che do doc
	RW=1;	
}

//Ham thuc hien gui mot lenh xuong LCD
void LCD_Send_Command(unsigned char x)
{
	LCD_DATA=x;
	RS=0; //Chon thanh ghi lenh
	RW=0; //De ghi du lieu
	EN=1;
	Delay_ms(1);
	EN=0;		
	Wait_For_LCD(); //Doi cho LCD san sang
	EN=1;		  
}
//Ham kiem tra va cho den khi LCD san sang
void Wait_For_LCD()
{
	Delay_ms(1);
}

void LCD_init()
{
	LCD_Send_Command(0x38); //Chon che do 8 bit, 2 hang cho LCD
	LCD_Send_Command(0x0E); //Bat hien thi, nhap nhay con tro	
	LCD_Send_Command(0x01); //Xoa man hinh	
	LCD_Send_Command(0x80); //Ve dau dong
	
}
//Ham de LCD hien thi mot ky tu
void LCD_Write_One_Char(unsigned char c)
{
	LCD_DATA=c; //Dua du lieu vao thanh ghi 
	RS=1; //Chon thanh ghi du lieu
	RW=0;
	EN=1;
	Delay_ms(1);	
	EN=0;
	Wait_For_LCD();	
	EN=1;
}
//Ham de LCD hien thi mot xau
void LCD_Write_String(unsigned char *s)
{
	unsigned char length;
	length=strlen(s); //Lay do dai xau
	while(length!=0)
	{
		LCD_Write_One_Char(*s); //Ghi ra LCD gia tri duoc tro boi con tro
		s++; //Tang con tro
		length--;	  		 
	}
}
