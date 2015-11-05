/**************** (C) COPYRIGHT 2014 �ൺ���˴���ӿƼ����޹�˾ ****************
* �� �� ��: Display.C
* �� �� ��: ����
* ��  ��  : ʹ�ò�ͬ�ӿ���ʽ��ģ��ʵ�ֵ�����ʾ����
* ����޸�: 2014��4��18��
*********************************** �޶���¼ ***********************************
* ��  ��: V2.0
* �޶���: ���� 2014��4��18��
* ˵  ��: �Զ����ȷ����ʾ�������͡�
*******************************************************************************/
#include "BSP.H"
#include "BIOS.H"

/********************************** ����˵�� ***********************************
*	Һ��(TM12864)�ı��⡢�Ҷȿ���
*******************************************************************************/
static	void	TM12864_SetLight( uint8_t setLight )
{	//	��������������������
	PWM1_SetOutput( setLight * PWM_Output_Max / 100u );
}

FP32	LCDSetGrayVolt;

/********************************** ����˵�� ***********************************
 *	������ʾ���ȡ��Ҷ�
*******************************************************************************/

static	uint8_t	savLight;

void	Backlight_ON( void )
{
	TM12864_SetLight( savLight );

}

void	Backlight_OFF( void )
{
	TM12864_SetLight( 0u );

}

void	DisplaySetLight( uint8_t ValueOfBrightness )
{	//	��������
	savLight = ValueOfBrightness;

	Backlight_ON();
}

void	DisplaySetGrayVolt( FP32 SetGrayVolt )
{	//	�Ҷ�  �� �Աȶ�

	LCDSetGrayVolt = SetGrayVolt;

}

/********************************** ����˵�� ***********************************
 *	������ʾ����
*******************************************************************************/
void	cls ( void )
{ 
	SED1335_cls();	
}
void Part_cls( void )
{
	SED1335Part_cls( 0xC0D6, 0x060E );
	SED1335_WBMP( 0xB001, 0x050D, STROCK1 );
}
void WBMP( uint16_t bmpyx, uint16_t yx, const CHAR *sz )
{
	SED1335_WBMP( bmpyx, yx, sz );
}
void WALL( const CHAR *sz )
{
	cls();
	SED1335_WALL( sz );
}
void	Lputs( uint16_t yx, const CHAR * sz )
{
	SED1335_puts24( yx, sz );
}
void	SEDLputs( uint16_t yx, const CHAR * sz )
{
	SED1335_puts( yx, sz );
}
void	LcmMask( uint16_t yx, uint8_t xlen, const CHAR * sz )
{
	SED1335_mask24 ( yx, xlen, sz );
}

/********************************** ����˵�� ***********************************
 *	��ʾģ���ʼ��
*******************************************************************************/
void	Display_Init( void )
{
	//	�Զ������ʾ��������
	SED1335_Init();

}

/********  (C) COPYRIGHT 2014 �ൺ���˴���ӿƼ����޹�˾  **** End Of File ****/