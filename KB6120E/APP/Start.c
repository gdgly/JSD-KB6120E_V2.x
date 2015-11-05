/**************** (C) COPYRIGHT 2015 �ൺ���˴���ӿƼ����޹�˾ ****************
* �� �� ��: Start.C
* �� �� ��: ����
* ��  ��  : KB-6120E ��������
* ����޸�: 2015��6��2��
*********************************** �޶���¼ **********************************
* ��  ��: 
* �޶���: 
*******************************************************************************/
#include "AppDEF.H"
#include <cmsis_os.h>
#include "U_INC.H"
#include "BMP.H"
extern	void	menu_show_env_state( void );
extern	void	show_battery( uint16_t yx );
/********************************** ����˵�� **********************************
*	ϵͳ��ʱ����
*******************************************************************************/
void	delay( uint16_t	m_sec )
{
	osDelay( m_sec );
}


/********************************** ����˵�� **********************************
*  ��ʾʱ��
*******************************************************************************/
void	Show_std_clock( void )
{
	uint32_t	now = get_Now();

	ShowClock( 0x0318u, &now );
	ShowWDay ( 0x011Au, &now );
	show_battery( 0x0020u );
}
void	Show_std_state( void )
{
	Show_std_clock();
	menu_show_env_state();
}
/********************************** ����˵�� **********************************
*  ���˵�
*******************************************************************************/
void	menu_Main( void )
{
	static	struct uMenu  const  menu[] =
	{
		{ 0x0401u, "���˵�" },
		{ 0x0606u, "����" },	//	����Ĭ�ϲ���������ԭ���ϲ���Ҫÿ�ζ��޸�
		{ 0x0C06u, "����" },	//	����ÿ�β�������Ҫȷ�ϵĲ���������������
		{ 0x1206u, "��ѯ" },	//	�鿴��Ӧ�������Ĳ�����¼�ļ�������ӡ����
		{ 0x1806u, "ά��" }
	};

	static 	uint8_t	item = 1u;
	for(;;)
	{ 
		monitor();

		cls();
		Menu_Redraw( menu );
		SamplerTypeShow( 0x010Eu );		
		WBMP( 0x1818, menu[1].yx-0x04, SAMPLESET );
		WBMP( 0x1818, menu[2].yx-0x04, SAMPLE );
		WBMP( 0x1818, menu[3].yx-0x04, QUERY );
		WBMP( 0x1818, menu[4].yx-0x04, MAINTAIN );
		WBMP( 0xB001, 0x050D, STROCK1 );
		item = Menu_Select2( menu, item, FALSE, Show_std_state );
		
		item = LCD_Gray( item );
		switch( item )
		{
		//	�����˵��°�ȡ��������ʾ����ѹ���������¶ȵȻ�������
		case 1:	menu_SampleSetup();	break;
		case 2:	menu_SampleStart();	break;
		case 3:	menu_SampleQuery();	break;
		case 4:	menu_Maintenance();	break;
		case enumSelectESC:	item = 1u;	break;
		case enumSelectXCH:	SamplerTypeSwitch();	break;
		}
		
	}
}

/********************************** ����˵�� **********************************
*  ��ʼ����Դ��־����
*******************************************************************************/
extern	void	PowerLogSave_PowerBoot( void );
extern	void	PowerLogSave_PowerShut( void );

__task	void	_task_PowerLog( void const * p_arg )
{
	
	PowerLogSave_PowerBoot();

	for(;;)
	{
		PowerLogSave_PowerShut();
		delay( 30000u );			//	��ʱ 30 ����
	}
}

void	PowerLog_Init( void )
{
	static	osThreadDef( _task_PowerLog, osPriorityLow, 1, 200 );

	osThreadCreate( osThread( _task_PowerLog ), NULL );
}


/********************************** ����˵�� **********************************
*	I2C - SPI���ߵĻ�����ʿ���
*******************************************************************************/
static	osMutexId	mutexBus_I2C = NULL;

void	bus_i2c_mutex_apply( void )
{
	osMutexWait( mutexBus_I2C, osWaitForever );
}

void	bus_i2c_mutex_release( void )
{
	osMutexRelease( mutexBus_I2C );
}

static	void	bus_i2c_mutex_init( void )
{
	static	osMutexDef ( mutex_i2cbus );

	mutexBus_I2C = osMutexCreate( osMutex( mutex_i2cbus ));
}
static	osMutexId	mutexBus_SPI = NULL;

void	bus_SPI_mutex_apply( void )
{
	osMutexWait( mutexBus_SPI, osWaitForever );
}

void	bus_SPI_mutex_release( void )
{
	osMutexRelease( mutexBus_SPI );
}

static	void	bus_SPI_mutex_init( void )
{
	static	osMutexDef ( mutex_SPIbus );

	mutexBus_SPI = osMutexCreate( osMutex( mutex_SPIbus ));
}
void	RTOS_Init( void )
{
	bus_i2c_mutex_init();
	bus_SPI_mutex_init();
}

/********************************** ����˵�� **********************************
 *	������ϵͳ�е������򣬳�ʼ��ת�������ϵͳ���д���
*******************************************************************************/
/*
����ϵͳ��˳��
CPU �ڲ����ײ�Ӳ��
�ⲿ�ӿ�
�ⲿӲ������������ʾ��
��ȡ�ⲿ��������
������ϵͳ��RTC ʱ�ӣ�
����ϵͳ
����
פ�������磺��������ȡ���������¿ء�����ʱ���¼��
��������
�������
*/
__task	int32_t	main( void )
{
	
	BIOS_Init();
  beep();
	RTOS_Init();		//	����ִ��
  
	ConfigureLoad();	//	��ȷ�������ͺ�
	CalibrateLoad();	//	��������ǰִ��,	Զ�̴洢���еĲ�����Ӧ��ͨѶ��ʼ�����ٶ���
	SampleSetLoad();	//	�ָ�����ǰִ��
	
	Display_Init();
	DisplaySetGrayVolt( Configure.DisplayGray * 0.01f );
	DisplaySetLight( Configure.DisplayLight );
	DisplaySetTimeout( Configure.TimeoutLight );
	Keyboard_Init();	//	�����걳�ⳬʱʱ����ٳ�ʼ����
		
	RTC_Init();			//	Ϊ��������������ʱ��ʧ����ɵļ������󣬷�����ʾ��ʼ��֮��
	SD_Init();				//	SD����д��ʼ�������ڿ��ػ���ȡ֮ǰ
	PowerLog_Init();	//	���ػ���ȡ��ʱ���ʼ��֮��
	cls();
	delay( 1500u );		//�����λ����ʼ��
	SENSOR_Init();		//	modbusͨ�ų�ʼ��
	
	delay( 1000 );
	HCBox_Init();
	
	Animation();		//	��������
 	delay( 1500 );
	ShowEdition();	//	ȷ���ͺ�֮����ʾ��ʼ��֮��	
	delay( 1000u );
	
	Sampler_BootResume();	//	ʱ���������֮�����ò�������֮��
 	delay( 200u );

	SamplerSelect = Q_ALL;	//	��ʼ����ǰ������Ϊ�������ֵ������һ���л����л�����һ�������ֵ��
	SamplerTypeSwitch();
	
	for(;;)
	{
		menu_Main();	//	ת���˵�
	}
}

/********  (C) COPYRIGHT 2015 �ൺ���˴���ӿƼ����޹�˾  **** End Of File ****/
