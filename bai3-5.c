/////////////////////////////////////////////////////////////////////////////////////
//                     Embedded Systems - IT4210 (SoICT-HUST)                      //
//						       Sample codes for Lab #2 							   //
/////////////////////////////////////////////////////////////////////////////////////
#include "reg51.h"
#include "string.h"
//Dinh nghia mot so chan de dieu khien den LCD
#define LCD_DATA P2
sbit EN=P0^2;
sbit RS=P0^0;
sbit RW=P0^1;
sbit SPK  = P3^7;	

// cac not nhac
code unsigned int note_table[]={
    0xf8,0x8b,        //1 do
    0xf9,0x5b,        //2 re
    0xfa,0x17,        //3 mi
    0xfa,0x6b,        //4 fa
    0xfb,0x07,        //5 sol
    0xfb,0x92,        //6 la
    0xfc,0x0d,        //7 si
};
code unsigned char musicNote[7][5] = {"do","re","mi","fa","sol","la","si"}; // luu ten cac not in ra trong lcd
code unsigned int song[32]={0,1,2,0,0,1,2,0,2,3,4,2,3,4,4,5,4,3,2,1,4,5,4,3,2,1,0,1,0,0,1,0};
unsigned char note_index;	
char uart_data;
char flag;

void init();		
void delay(unsigned int time); 
void Init_System();	
void Delay_ms(int interval);  
void LCD_init();
void Wait_For_LCD();
void LCD_Send_Command(unsigned char x);
void LCD_Write_One_Char(unsigned char c);
void LCD_Write_String(unsigned char *s);
void music();
void play(char uart_data);
void playMusic(unsigned char i);

void main (void)
{
	init();
	music();
	flag = 0;
	// su dung ban phim choi piano
	while (1) {
		if(flag == 1){ 
			flag = 0;
			play(uart_data);// choi not nhac
			continue;
		}
		// tat loa
		TR0 = 0;
		SPK = 1;
	}
}

// chay tung not nhac
void play(char uart_data) {
	note_index = (uart_data - 65)<<1;
    TH0 = note_table[note_index];
    TL0 = note_table[note_index + 1];
    TR0 = 1;
    LCD_Send_Command(0x01); //Xoa man hinh
    LCD_Write_String(musicNote[note_index>>1]);
}

// chay doan nhac dau
void music() 
{
	unsigned char i;
	note_index=0;
	for(i=0;i<32;i++){		
		note_index = song[i]<<1;
		TH0 = note_table[note_index];
		TL0 = note_table[note_index + 1];
		TR0 = 1;
		delay(30000);
		TR0=0;
		SPK=1;
		delay(10000);
	}			
}

void serial_IT(void) interrupt 4
{
  if (RI == 1)
  { 
    RI = 0; 			/* prepare for next reception */
    uart_data = SBUF; 	/* Read receive data */
	flag = 1;
    SBUF = uart_data; 	/* Send back same data on uart*/
  }
  else 
    TI = 0; 			/* if emission occur */
}

void init()
{
	TMOD=0x01;
	ET0=1;
	TR0=0;
	SCON = 0x50; 			/* uart in mode 1 (8 bit), REN=1 */
	TMOD = TMOD | 0x20 ; 	/* Timer 1 in mode 2 */
	TH1 = 0xFD; 			/* 9600 Bds at 11.0592MHz */
	TL1 = 0xFD; 			/* 9600 Bds at 11.0592MHz */
	ES = 1; 				/* Enable serial interrupt*/
	EA = 1; 				/* Enable global interrupt */
	TR1 = 1; 				/* Timer 1 run */
	Init_System();
	LCD_init();
	LCD_Write_String("Kia con");
	LCD_Send_Command(0xC0); //Chuyen con tro xuong dong thu 2
	LCD_Write_String("Buom vang...");
}

void timer0() interrupt 1
{
	TH0=note_table[note_index];
	TL0=note_table[note_index+1];
	SPK=~SPK;
}

void delay(unsigned int time)
{
	while(time--);
}

void Init_System()
{
	//Thiet lap LCD o che do doc
	RW=1;	
}
void Delay_ms(int interval)
{
	int i,j;
	for(i=0;i<1000;i++)
	{
		for(j=0;j<interval;j++);
	}
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
	Delay_ms(10);
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