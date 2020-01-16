#ifndef OLED_H
#define OLED_H
//
// OLED
// 
//
// SeeedOLED Instruction set addresses


#define SeeedOLED_Max_X                 127 //128 Pixels
#define SeeedOLED_Max_Y                 63  //64  Pixels

#define PAGE_MODE                       01
#define HORIZONTAL_MODE                 02


#define SeeedOLED_Address               0x3c
#define SeeedOLED_Command_Mode          0x00
#define SeeedOLED_Data_Mode             0x40
#define SeeedOLED_Display_Off_Cmd       0xAE
#define SeeedOLED_Display_On_Cmd        0xAF
#define SeeedOLED_Normal_Display_Cmd    0xA6
#define SeeedOLED_Inverse_Display_Cmd   0xA7
#define SeeedOLED_Activate_Scroll_Cmd   0x2F
#define SeeedOLED_Dectivate_Scroll_Cmd  0x2E
#define SeeedOLED_Set_Brightness_Cmd    0x81

#define Scroll_Left             0x00
#define Scroll_Right            0x01

#define Scroll_2Frames          0x7
#define Scroll_3Frames          0x4
#define Scroll_4Frames          0x5
#define Scroll_5Frames          0x0
#define Scroll_25Frames         0x6
#define Scroll_64Frames         0x1
#define Scroll_128Frames        0x2
#define Scroll_256Frames        0x3



	void oled_Init(void);

	void oled_SetNormalDisplay();
	void oled_SetInverseDisplay();

	void oled_SendCommand(unsigned char command);
	void oled_SendData(unsigned char Data);

	void oled_SetPageMode();
	void oled_SetHorizontalMode();

	void oled_SetTextXY(unsigned char Row, unsigned char Column);
	void oled_ClearDisplay();
	void oled_SetBrightness(unsigned char Brightness);
	void oled_PutChar(unsigned char c);
	void oled_PutString(const char *String);
	unsigned char oled_PutNumber(long n);
	unsigned char oled_PutFloatn(float floatNumber,unsigned char decimal);
	unsigned char oled_PutFloat(float floatNumber);
	void oled_DrawBitmap(unsigned char *bitmaparray,int bytes);

	void oled_SetHorizontalScrollProperties(unsigned char direction, unsigned char startPage, unsigned char endPage, unsigned char scrollSpeed);
	void oled_ActivateScroll();
	void oled_DeactivateScroll();




#endif // OLED_H
