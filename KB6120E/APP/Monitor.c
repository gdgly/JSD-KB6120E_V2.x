/**************** (C) COPYRIGHT 2014 �ൺ���˴���ӿƼ����޹�˾ ****************
* �� �� ��: Monitor.C
* �� �� ��: KB-6120E
* ��  ��  : �����������ʾ���������еĲ���״̬
* ����޸�: 2013��12��17��
*********************************** �޶���¼ ***********************************
* ��  ��:
* �޶���:
*******************************************************************************/
#include "AppDEF.H"
#include "BMP.H"
/*
������������Ҫ��ʾ��״̬�ֳ����¼�����
0.��Ӧ����������
1.ʱ�����״̬������������������ʱ�䡢ʣ��ʱ�䡢��ǰ����״̬�ǲ���������ͣ���ǹ��ϵȵ�
2.����״̬�������¶ȡ�ѹ��������ѹ���������������꣩����������Ϣ��
3.ͳ����Ϣ�������ۼ�ʱ�䡢�ۻ�����������꣩��
4.������Ϣ���� �������¶ȼ�����״̬�������¶ȡ�����ѹ�� ��

ԭ���ϣ���س���ֻ��ʾ�������ơ�����ʾ�����ݣ���ȫ�ֱ������ݣ�����Ӧ���Ƴ����������¡�
*/





/********************************** ����˵�� ***********************************
*  ��ʾ���״̬
*******************************************************************************/
FP32	get_Bat_Voltage( void );
FP32	get_Bat_Current( void );
bool	get_Bat_Charging( void );


void	show_battery( uint16_t yx )
{
	static const char * BatteryIdentify[]={"���","���","���","���","���","���"};
	
	#define	BatVolStateFULL	5u
	static	uint8_t	BatVolState = BatVolStateFULL;

	uint8_t i;
	bool isCharging;

	FP32 inVoltage = get_Bat_Voltage();
	if( Configure.Battery_SW == TRUE )
	{
    if ( inVoltage < 1.0f )
		{
			return;	//	��ص�ѹ�쳣����Ϊ���ûװ������û�е�ء�
		}
		
		isCharging = get_Bat_Charging();

		if ( ! isCharging )
		{	//	����״̬ �� �ŵ�״̬����ʾ��طֵ�
			FP32	voltage = inVoltage * 0.2f; // 5 �ڵ��
			uint8_t NewState;

			if     ( voltage >= 3.20f )  { NewState = 5; }
			else if( voltage >= 3.10f )  { NewState = 4; }
			else if( voltage >= 3.00f )  { NewState = 3; }
			else if( voltage >= 2.95f )  { NewState = 2; }
			else if( voltage >= 2.85f )  { NewState = 1; }
			else						             { NewState = 0; } // Battery Empty.

			if( NewState < BatVolState )
			{
				BatVolState = NewState;
			}
			i = BatVolState;
		}
		else
		{	//	���״̬������˸����ʾ�����š�

			BatVolState = BatVolStateFULL;
			
			i = get_Now() % BatVolStateFULL + 1;
			}
		
		Lputs( yx, BatteryIdentify[i] );
		}
	
}

/********************************** ����˵�� ***********************************
*  ��ʾ��������������ѹ�������� �� ������ ״̬
*******************************************************************************/
void	show_env_state( void )
{		switch ( Configure.Mothed_Ba )
	{
	case enumUserInput:	Lputs( 0x0910u, "����ѹ=" );	break;
	case enumMeasureBa:	Lputs( 0x0910u, "����ѹ:" );	break;
	}
	ShowFP32( 0x0C14u, get_Ba(), 0x0602u, "kPa" );

	//	������к�����
	switch ( Configure.HeaterType )
	{
	case enumHCBoxOnly :
		{
			FP32	OutValue = get_HCBoxOutput();
			FP32	RunTemp  = get_HCBoxTemp();
			Lputs( 0x0F10u, "������:" );	ShowFP32( 0x1214u, RunTemp, 0x0501u, "��" );
			if      ( OutValue > 0.0f )
			{
				Lputs( 0x1510u, "�� ��: " );	ShowFP32( 0x1814u, OutValue, 0x0601u, "% " );
			}
			else if ( OutValue < 0.0f )
			{
				Lputs( 0x1510u, "�� ��: " );	ShowFP32( 0x1814u, OutValue, 0x0601u, "% " );
			}
			else	//	OutValue == 0.0f
			{			
				Lputs( 0x1510u, "�� ��:" );Lputs( 0x1814u," [�ر�]    " );
			}
		}
		break;
	case enumHeaterOnly:
		{
			FP32	OutValue = get_HeaterOutput();
			FP32	RunTemp  = get_HeaterTemp();
			uint8_t state = Configure.Heater_SW;
			Lputs( 0x0F10u, "������:" );	ShowFP32( 0x1214u, RunTemp, 0x0501u, "��" );
      if( state )
			{
       	if      ( OutValue > 0.0f )
				{
					Lputs( 0x1510u, "�� ��:   " );	ShowFP32( 0x1814u, OutValue, 0x0601u, "% " );
				}
				else
				{			
					Lputs( 0x1510u, "�� ��:");	Lputs( 0x1814u," [�ر�]    " );
				}
			}
			else
			{
				Lputs( 0x1510u, "�� ��:");	Lputs( 0x1814u," [ͣ��]    " );
			}
		
		}
		break;
	}
}
/********************************** ����˵�� ***********************************
*  ��ʾ �ù���״̬
*******************************************************************************/

void PumpWorkFlag( void )
{
	static uint8_t i;
	i = get_Now() % 4;
	if( i == 0 )
	WBMP(0x1818,0x010A, PUMP1 );
	if( i == 1 )
	WBMP(0x1818,0x010A, PUMP2 );
	if( i == 2 )
	WBMP(0x1818,0x010A, PUMP3 );
	if( i == 3 )
	WBMP(0x1818,0x010A, PUMP4 );
}
static	FP32	fstdx[4][PP_Max];
static	FP32	fstd ;
void Sampler_TdMonitor( enum enumSamplerSelect SamplerSelect )
{	
  switch(  SamplerSelect )
  {	
    case Q_TSP:
      fstdx[0][PP_TSP] = fstdx[1][PP_TSP];
      fstdx[1][PP_TSP] = fstdx[2][PP_TSP];
      fstdx[2][PP_TSP] = fstdx[3][PP_TSP];
      fstdx[3][PP_TSP] = get_fstd( PP_TSP );    
      break;
    case Q_SHI:
      fstdx[0][PP_SHI_C] = fstdx[1][PP_SHI_C];
      fstdx[1][PP_SHI_C] = fstdx[2][PP_SHI_C];
      fstdx[2][PP_SHI_C] = fstdx[3][PP_SHI_C];
      fstdx[3][PP_SHI_C] = get_fstd( PP_SHI_C );
      fstdx[0][PP_SHI_D] = fstdx[1][PP_SHI_D];
      fstdx[1][PP_SHI_D] = fstdx[2][PP_SHI_D];
      fstdx[2][PP_SHI_D] = fstdx[3][PP_SHI_D];
      fstdx[3][PP_SHI_D] = get_fstd( PP_SHI_D );
      break;
    case Q_R24:
      fstdx[0][PP_R24_A] = fstdx[1][PP_R24_A];
      fstdx[1][PP_R24_A] = fstdx[2][PP_R24_A];
      fstdx[2][PP_R24_A] = fstdx[3][PP_R24_A];
      fstdx[3][PP_R24_A] = get_fstd( PP_R24_A );
      fstdx[0][PP_R24_B] = fstdx[1][PP_R24_B];
      fstdx[1][PP_R24_B] = fstdx[2][PP_R24_B];
      fstdx[2][PP_R24_B] = fstdx[3][PP_R24_B];
      fstdx[3][PP_R24_B] = get_fstd( PP_R24_B );
      break;
    default:  
      break;
  }
    
    
 
}
/********************************** ����˵�� ***********************************
*  ��ʾָ����������ʱ��״̬
*******************************************************************************/
static	void	ShowTimeState ( enum enumSamplerSelect SamplerSelect, enum enumPumpSelect PumpSelect )
{
	struct uSamplerQuery * p = & Q_Sampler[SamplerSelect];
 	struct	uPumpQuery * pT = &Q_Pump[PumpSelect];
  Sampler_TdMonitor( SamplerSelect );
	Lputs ( 0x0102u, "����" );		//	ShowQueryType ( 0x000Au );
	if( PumpSelect != PP_AIR )
	{
		switch ( p->state )
		{
		default:
		case state_ERROR:		Lputs ( 0x0705u, "   !!����!! " ); break;
		case state_FINISH:	Lputs ( 0x0705u, "   ��ɲ��� " );	break;
		case state_SAMPLE:	Lputs ( 0x0705u, "   ���ڲ��� " );	break;
		case state_SUSPEND:	Lputs ( 0x0705u, "   �ȴ����� " );	break;
		case state_PAUSE:		Lputs ( 0x0705u, "   ��ͣ���� " );	break;
		}
		//TODO:	2·ͬ����ͬ�ص�ʱ�䲻һ��������
		Lputs ( 0x0B02u, "��   ��:" );	ShowFP32 ( 0x0B11u, get_Tr( PumpSelect ), 0x0602u, "��" );
		Lputs ( 0x0E02u, "ѹ   ��:" );	ShowFP32 ( 0x0E11u, get_Pr( PumpSelect ), 0x0602u, "kPa" );
		Lputs ( 0x1102u, "����ѹ��:" );	ShowFP32 ( 0x1111u, get_Ba(),             0x0602u, "kPa" );
		Lputs ( 0x1402u, "ʣ��ʱ��:" );	ShowTIME ( 0x1416u, p->timer );	
		Lputs ( 0x1702u, "����ʱ��: " );	ShowTIME ( 0x1716u, pT->sum_time );
		Lputs ( 0x1A02u, "��ǰ����:" );	ShowI16U ( 0x1A11u, p->loops, 0x0500u, NULL );
	}
	else
	{
    
		switch ( p->state )
		{
		default:
		case state_ERROR:		Lputs ( 0x0605u, "    !!����!!    " ); break;
		case state_FINISH:	Lputs ( 0x0605u, "    ��ɲ���    " );	break;
		case state_SAMPLE:	Lputs ( 0x0605u, "    ���ڲ���    " );	break;
		case state_SUSPEND:	Lputs ( 0x0605u, "    �ȴ�����    " );	break;
		case state_PAUSE:		Lputs ( 0x0605u, "    ��ͣ����    " );	break;
		}
		Lputs ( 0x0902u, "��   ��:" );	ShowFP32 ( 0x0911u, get_Tr( PumpSelect ), 0x0602u, "��" );
		Lputs ( 0x0C02u, "ѹ   ��:" );	ShowFP32 ( 0x0C11u, get_Pr( PumpSelect ), 0x0602u, "kPa" );
		Lputs ( 0x0F02u, "����ѹ��:" );	ShowFP32 ( 0x0F11u, get_Ba(),             0x0602u, "kPa" );
		Lputs ( 0x1202u, "ʣ��ʱ��:" );	ShowTIME ( 0x1216u, p->timer );	
		Lputs ( 0x1502u, "��ǰ����:" );	ShowI16U ( 0x1511u, p->loops, 0x0500u, NULL );
		Lputs ( 0x1802u, "�ۻ�ʱ��:" );	ShowTIME ( 0x1816u, pT->sum_time );
	}		
		
}

/********************************** ����˵�� ***********************************
*  ��ʾָ�������õļ�ǰ����״̬
*******************************************************************************/
static	void	ShowPumpBefore( enum enumPumpSelect PumpSelect )
{
	struct	uPumpQuery * p = &Q_Pump[PumpSelect];
	Lputs ( 0x0102u, "����" );

	if ( ! Q_Pump[PumpSelect].xp_state )
	{
		switch (PumpSelect )
		{
		case PP_TSP: // TSP_KB120F
			Lputs ( 0x0602u, 		"�������: "				 );	ShowFP32 ( 0x0613u, p->vd,       0x0600u, "L" );
			Lputs ( 0x0902u, 		"������: "				 );	ShowFP32 ( 0x0913u, p->vnd,      0x0600u, "L" );
			Lputs( 0x0C02u, "                   " );
			Lputs( 0x0F02u, "                   " );
			Lputs( 0x1202u, "    ���ѹر�        " );
			Lputs( 0x1502u, "                   " );
			Lputs( 0x1802u, "                   " );
			Lputs( 0x1B02u, "                   " );
			return;
		case PP_R24_A:
		case PP_R24_B:
		case PP_SHI_C:
		case PP_SHI_D:
			Lputs ( 0x0602u, 		"������: " 			);	ShowFP32 ( 0x0611u, p->vnd,  0x0702u, "L" );
			Lputs( 0x0A02u, "                   " );
			Lputs( 0x0E02u, "                   " );
			Lputs( 0x1202u, "    ���ѹر�        " );
			Lputs( 0x1602u, "                   " );
			Lputs( 0x1A02u, "                   " );
			return;
		case PP_AIR:
			break;
		}
	}
	else 
	{
		
		FP32	OutValue = Pump_GetOutput( PumpSelect );
		Sampler_TdMonitor( SamplerSelect );
    fstd = ( fstdx[0][PumpSelect] + fstdx[1][PumpSelect] + fstdx[2][PumpSelect] + fstdx[3][PumpSelect] ) / 4; 
		switch (PumpSelect )
		{
		case PP_TSP: // TSP_KB120F
			{
				FP32	Te   = get_Te();
				FP32	Ba   = get_Ba();
				FP32	flow;
				flow = Calc_flow( fstd, Te, 0.0f, Ba, Q_TSP );
				Lputs ( 0x0602u, "�������: " );		ShowFP32 ( 0x0613u, p->vd,       0x0600u, "L" );
				Lputs ( 0x0902u, "������: " );		ShowFP32 ( 0x0913u, p->vnd,      0x0600u, "L" );
				Lputs ( 0x0C02u, "��   ��: " );		ShowFP32    ( 0x0C11u, flow, 0x0701u, "L/m" );
				Lputs ( 0x0F02u, "��   ��: " );		ShowFP32    ( 0x0F11u, fstd, 0x0701u, "L/m" );	
				Lputs ( 0x1202u, "��   ��:   " );		ShowPercent ( 0x1215u, OutValue );
				switch ( Configure.HeaterType )
				{
				default:
				case enumHeaterNone:	break;	//	MsgBox( "δ��װ������", vbOKOnly );	break;
				case enumHCBoxOnly:
					Lputs ( 0x1502u, "�������¶�:" );		ShowFP32 ( 0x1513u, get_HCBoxTemp(),     0x0602u, "��" );
					Lputs ( 0x1802u, "���������:" );		ShowFP32 ( 0x1815u, get_HCBoxOutput(),   0x0501u, "% " );
					Lputs ( 0x1B02u, "���������:" );		ShowI16U ( 0x1B15u, get_HCBoxFanSpeed(), 0x0500u, "RPM" );
					break;
				case enumHeaterOnly:		
					Lputs ( 0x1502u, "�������¶�:" );		ShowFP32 ( 0x1513u, get_HeaterTemp(),     0x0602u, "��" );
					Lputs ( 0x1802u, "���������:" );		ShowFP32 ( 0x1815u, get_HeaterOutput(),   0x0501u, "%" );
					break;
				case enumHCBoxHeater:
					set_HCBoxTemp( Configure.HCBox_SetTemp * 0.1f, Configure.HCBox_SetMode );
					set_HeaterTemp( Configure.Heater_SetTemp*0.1f);
					break;
				}
			}
			break;
		case PP_R24_A:
		case PP_R24_B:
		case PP_SHI_C:
		case PP_SHI_D:
			Lputs ( 0x0602u, "������: " );		ShowFP32 ( 0x0611u, p->vnd,  0x0702u, "L" );
			Lputs ( 0x0A02u, "��   ��: " );		ShowFP32    ( 0x0A11u, fstd, 0x0703u, "L/m" );
			Lputs ( 0x0E02u, "��   ��: " );		ShowPercent ( 0x0E15u, OutValue );
		switch ( Configure.HeaterType )
		{
		default:
		case enumHeaterNone:	break;	//	MsgBox( "δ��װ������", vbOKOnly );	break;
		case enumHCBoxOnly:
			Lputs ( 0x1202u, "�������¶�:" );		ShowFP32 ( 0x1213u, get_HCBoxTemp(),     0x0602u, "��" );
			Lputs ( 0x1602u, "���������:" );		ShowFP32 ( 0x1615u, get_HCBoxOutput(),   0x0501u, "% " );
			Lputs ( 0x1A02u, "���������:" );		ShowI16U ( 0x1A15u, get_HCBoxFanSpeed(), 0x0500u, "RPM" );
			break;	
		case enumHeaterOnly:
			Lputs ( 0x1202u, "������      " );	
			Lputs ( 0x1602u, "�������¶�:" );		ShowFP32 ( 0x1613u, get_HeaterTemp(),     0x0602u, "��" );
			Lputs ( 0x1A02u, "���������:" );		ShowFP32 ( 0x1A15u, get_HeaterOutput(),   0x0501u, "%" );
			break;
		case enumHCBoxHeater:
			set_HCBoxTemp( Configure.HCBox_SetTemp * 0.1f, Configure.HCBox_SetMode );
			set_HeaterTemp( Configure.Heater_SetTemp*0.1f);
			break;
		}
			break;
		case PP_AIR:
			break;
		}
	}	
	
}

/************** ����˵�� ****************
        ֹͣ��ͣ״̬ѡ��˵� 
 ****************************************/
void Samplestate_Select( BOOL state )
{
       static	struct  uMenu  const  menu[] =
    {
        { 0x0103u, "����״̬����" },
        { 0x0C02u, "��ͣ" },{ 0x0C0Eu, "ֹͣ" },{ 0x0C19u, "ȡ��" }
		
    };
		   static	struct  uMenu  const  menu2[] =
    {
        { 0x0103u, "����״̬����" },
        { 0x0C02u, "�ָ�" },{ 0x0C0Eu, "ֹͣ" },{ 0x0C1Bu, "ȡ��" }
		
    };
    uint8_t	item = 2u;
    BOOL	need_redraw = TRUE;
    do
    {   
        if ( need_redraw )
        {
          cls();
					if( state ==TRUE)
            Menu_Redraw( menu2 );
					else
						Menu_Redraw( menu );
          need_redraw = FALSE;
        }
				if( state == TRUE )
					item = Menu_Select( menu2, item + 1u, NULL );
				else
					item = Menu_Select( menu, item + 1u, NULL );
        switch( item )
        {
        case 1:
            Sampler_PauseKey( SamplerSelect );
						item = enumSelectESC;
            break;
        case 2:
            Sampler_Terminate( SamplerSelect );
						item = enumSelectESC;
            break;
        case 3:
						item = enumSelectESC;					
            break;
        default:
            break;
        }
	}while( enumSelectESC != item );
}
/********************************** ����˵�� ***********************************
*  ������������ͳһ�����������µİ���
*******************************************************************************/
void	disposeKey( const enum enumSamplerSelect SamplerSelect, uint8_t * pOption, const uint8_t opt_max, enum enumPumpSelect * pPumpSelect )
{
	enum {
		opt_exit,
		opt_min = 1u
	};
	static	uint16_t gray  = 1900u;
	BOOL graychanged = FALSE;	

	uint8_t option  = * pOption;
	enum enumPumpSelect PumpSelect;

	if ( NULL != pPumpSelect )
	{
		PumpSelect = *pPumpSelect;
	}
	else
	{
		PumpSelect = PP_Max;
	}
	
	if ( hitKey ( 100u ) )
	{
		switch ( getKey() )
		{
		case K_UP:
			switch ( SamplerSelect )
			{
			case Q_R24:	PumpSelect = PP_R24_A;	break;
			case Q_SHI:	PumpSelect = PP_SHI_C;	break;
			default:	break;
			}
			break;
		case K_DOWN:
			switch ( SamplerSelect )
			{
			case Q_R24:	PumpSelect = PP_R24_B;	break;
			case Q_SHI:	PumpSelect = PP_SHI_D;	break;
			default:	break;
			}
			break;

		case K_RIGHT:
			++option;
			if ( option >= opt_max )
			{
				option = opt_min;
			}
			break;

		case K_LEFT:
			if ( option <= opt_min )
			{
				option = opt_max;
			}
			--option;
			break;

		case K_SHIFT:
			{
				SamplerTypeSwitch();
				option = opt_exit;
			}
				
			break;

		case K_ESC:
		   Samplestate_Select( StateRead(SamplerSelect) );
			break;

		case K_OK_UP:	
			if ( gray < 2200u )
			{
				++gray;
			}
			if( ! releaseKey( K_OK_UP,100 ))
			{
				while( ! releaseKey( K_OK_UP, 1 ))
				{
					++gray;
					DisplaySetGrayVolt( gray * 0.01f );
				}
			}
			graychanged = true;		
			break;
		case K_OK_DOWN:
			if ( gray >  200u )
			{
				--gray;
			}
			if( ! releaseKey( K_OK_DOWN, 100 ))
			{
				while( ! releaseKey( K_OK_DOWN, 1 ))
				{
					--gray;
					DisplaySetGrayVolt( gray * 0.01f );
				}			
			}
			graychanged = true;
			break;

		case K_OK_RIGHT:
			if ( gray < ( 2000u - 50u ))
			{ 
				gray += 100u;
			}
			graychanged = true;
			break;
		case K_OK_LEFT:	
			if ( gray > ( 200 + 20u ))
			{
				gray -= 20u;
			}
			graychanged = true;
			break;
		default:
			break;
		}
		if( graychanged == true )
		{
			DisplaySetGrayVolt( gray * 0.01f );
			Configure.DisplayGray = gray;
			ConfigureSave();
			graychanged = FALSE;;
		}		

		cls();
		
		*pOption = option;
		if ( NULL != pPumpSelect )
		{
			*pPumpSelect = PumpSelect;
		}
	}
}


void	monitor_TSP( void )
{
	enum
	{
	    opt_exit,
	    opt_qt_1, opt_qt_2,
	    opt_max, opt_min = 1u
	};
	uint8_t option = opt_min;
	uint16_t	iDelay = 1200u;	//	��ʱһ��ʱ�䷵��Ĭ��״̬

	const	enum	enumPumpSelect  PumpSelect = PP_TSP;
	
	while ( ( opt_exit != option ) && Sampler_isRunning( SamplerSelect ))
	{
		if ( 0u != iDelay )
		{
			if ( --iDelay == 0u )
			{
				cls();	option = opt_min;
			}
		}	
		
		SamplerTypeShow( 0x010Eu );
		WBMP( 0x0290,0x0502, STROCK);
		WBMP( 0x0290,0x0514, STROCK);
		Show_std_clock();
		PumpWorkFlag();
		
		switch ( option )
		{
		case opt_qt_1:	ShowTimeState( SamplerSelect, PumpSelect );	break;
		case opt_qt_2:	ShowPumpBefore( PumpSelect );break;
// 		case opt_qt_3:	ShowPumpRunFlow( PumpSelect );	break;
// 		case opt_qt_4:	ShowSumCubage( PumpSelect );	break;
		default:	break;
		}
		
		disposeKey( SamplerSelect, &option, opt_max, NULL );
	}
}

static	void	monitor_R24 ( void )
{
	enum
	{
	    opt_exit,
	    opt_qt_1, opt_qt_2, 
	    opt_max, opt_min = 1u
	};
	uint8_t option = opt_min;
	uint16_t	iDelay = 1200u;	//	��ʱһ��ʱ�䷵��Ĭ��״̬

	enum	enumPumpSelect  PumpSelect = PP_R24_A;
	
	while ( ( opt_exit != option ) && Sampler_isRunning( SamplerSelect ))
	{
		if ( 0u != iDelay )
		{
			if ( --iDelay == 0u )
			{
				cls();	option = opt_min;
			}
		}
		
		WBMP( 0x0290,0x0502, STROCK);
		WBMP( 0x0290,0x0514, STROCK);
		
		PumpWorkFlag();
		
		switch ( PumpSelect )
		{
		case PP_R24_A:		Lputs ( 0x010Eu, "�վ�A" );		Show_std_clock();	break;
		case PP_R24_B:		Lputs ( 0x010Eu, "�վ�B" );		Show_std_clock();	break;
		}

		switch ( option )
		{
		case opt_qt_1:	ShowTimeState( SamplerSelect, PumpSelect );	
						show_battery( 0x0020u );
						break;
		case opt_qt_2:	ShowPumpBefore( PumpSelect );	break;
		default:	break;
		}

		disposeKey( SamplerSelect, &option, opt_max, &PumpSelect );
	}
}

static	void	monitor_SHI ( void )
{
	enum
	{
	    opt_exit,
	    opt_qt_1, opt_qt_2,  
	    opt_max, opt_min = 1u
	};

	uint8_t	option = opt_min;
	uint16_t	iDelay = 1200u;	//	��ʱһ��ʱ�䷵��Ĭ��״̬

	enum	enumPumpSelect  PumpSelect = PP_SHI_C;

	while (( opt_exit != option ) && Sampler_isRunning( SamplerSelect ))
	{
		if ( 0u != iDelay )
		{
			if ( --iDelay == 0u )
			{
				cls();	option = opt_min;
			}
		}
		

		WBMP( 0x0290,0x0502, STROCK);
		WBMP( 0x0290,0x0514, STROCK);
		

		PumpWorkFlag();
		

		switch ( PumpSelect )
		{
		case PP_SHI_C:		Lputs ( 0x010Eu, "ʱ��C" );		Show_std_clock();break;
		case PP_SHI_D:		Lputs ( 0x010Eu, "ʱ��D" );		Show_std_clock();	break;
		}

		switch ( option )
		{
		case opt_qt_1:	ShowTimeState( SamplerSelect, PumpSelect );	break;
		case opt_qt_2:	ShowPumpBefore( PumpSelect );	break;
		default:	break;
		}

		disposeKey( SamplerSelect, &option, opt_max, &PumpSelect );
	}
}

static	void	monitor_AIR ( void )
{
	enum
	{
	    opt_exit,
	    opt_qt_1,
	    opt_max, opt_min = 1u
	};
	uint8_t	option = opt_min;
	uint16_t	iDelay = 1200u;	//	��ʱһ��ʱ�䷵��Ĭ��״̬

	const enum	enumPumpSelect  PumpSelect = PP_AIR;
	
	while ( ( opt_exit != option ) && Sampler_isRunning( SamplerSelect ))
	{
		if ( 0u != iDelay )
		{
			if ( --iDelay == 0u )
			{
				cls();	option = opt_min;
			}
		}
		
		PumpWorkFlag();
		WBMP( 0x0290,0x0502, STROCK);
		WBMP( 0x0290,0x0514, STROCK);
		ShowTimeState( SamplerSelect, PumpSelect );
		show_battery( 0x0020u );
		SamplerTypeShow( 0x010Eu );
		
		disposeKey( SamplerSelect, &option, opt_max, NULL );
	}
}

/********************************** ����˵�� ***********************************
*  ������������ʾ����״̬
*******************************************************************************/
void	monitor ( void )
{
	while ( Sampler_isRunning( SamplerSelect ))
	{
		cls();

		switch ( SamplerSelect )
		{
		default:	
		case Q_TSP:	monitor_TSP();	break;
		case Q_R24:	monitor_R24();	break;
		case Q_SHI:	monitor_SHI();	break;
		case Q_AIR:	monitor_AIR();	break;
		}
	}
}

/********************************** ����˵�� ***********************************
*  ���������ͺţ���ʾ���л���ǰ�Ĳ�����
*******************************************************************************/
enum  enumSamplerSelect  SamplerSelect; 	//	= Q_TSP;

void	SamplerTypeShow( uint16_t yx )
{
		switch ( SamplerSelect )
		{
		case Q_TSP: Lputs( yx, "<�۳�>" );	break;
		case Q_R24: Lputs( yx, "<�վ�>" );	break;
		case Q_SHI:	Lputs( yx, "<ʱ��>" );	break;
		case Q_AIR:	Lputs( yx, "<����>" );	break;
		default:	Lputs( yx, "<δ֪>" );	break;
		}
}

void	SamplerTypeSwitch( void )
{
	BOOL	hasPumpTSP =  ( enumPumpNone != Configure.PumpType[PP_TSP] );
	BOOL	hasPumpR24 = (( enumPumpNone != Configure.PumpType[PP_R24_A] ) || ( enumPumpNone != Configure.PumpType[PP_R24_B] ));
	BOOL	hasPumpSHI = (( enumPumpNone != Configure.PumpType[PP_SHI_C] ) || ( enumPumpNone != Configure.PumpType[PP_SHI_D] ));
	BOOL	hasPumpAIR =  ( enumPumpNone != Configure.PumpType[PP_AIR] );
	switch ( SamplerSelect )
	{
	case Q_ALL:	if ( hasPumpTSP ) 
								SamplerSelect = Q_TSP; 
							else if ( hasPumpR24 ) 
								SamplerSelect = Q_R24;
							else if( hasPumpSHI) 
								SamplerSelect = Q_SHI;
							else if( hasPumpAIR ) 
								SamplerSelect = Q_AIR;
		break;
		
	case Q_TSP:	if ( hasPumpR24 ) 
								SamplerSelect = Q_R24;
							else if( hasPumpSHI) 
								SamplerSelect = Q_SHI;
							else if( hasPumpAIR ) 
								SamplerSelect = Q_AIR;
		break;	
	case Q_R24:	if( hasPumpSHI) 
								SamplerSelect = Q_SHI;
							else if( hasPumpAIR ) 
								SamplerSelect = Q_AIR;
							else if( hasPumpTSP ) 
								SamplerSelect = Q_TSP;					
		break;
	case Q_SHI:	if( hasPumpAIR ) 
								SamplerSelect = Q_AIR;
							else if( hasPumpTSP ) 
								SamplerSelect = Q_TSP;	
							else if ( hasPumpR24 ) 
								SamplerSelect = Q_R24;			
		break;
	case Q_AIR:	if( hasPumpTSP ) 
								SamplerSelect = Q_TSP;	
							else if ( hasPumpR24 ) 
								SamplerSelect = Q_R24;
							else if( hasPumpSHI) 
								SamplerSelect = Q_SHI;							
		break;
	default:	break;
	}
}

void	DisplaySetContrast( uint8_t SetContrast );

/********************************** ����˵�� ***********************************
*  ������ʾ���������п����ڿ�������ʾ������½��룩
*******************************************************************************/
void	ModifyLCD( void )
{
	uint16_t gray  = Configure.DisplayGray;
	BOOL	graychanged = FALSE;

	BOOL	changed = false;
	
	cls();
	Lputs( 0x0000u, "���� Һ�� �Ҷ�" );
	Lputs( 0x1800u, "�÷����������ѹ" );
	for(;;)
	{
		DisplaySetGrayVolt( gray * 0.01f );

		Lputs( 0x0C00u, "�Ҷ�" );	ShowI16U( 0x0C0Cu, gray,  0x0502u, " V " );


		switch( getKey())
		{
		case K_UP:	
			if ( gray < 2000u )
			{
				++gray;
			}
			changed = true;
			break;
		case K_DOWN:
			if ( gray >  200u )
			{
				--gray;
			}
			changed = true;
			break;

		case K_RIGHT:
			if ( gray < ( 2000u - 100u ))
			{ 
				gray += 100u;
			}
			changed = true;
			break;
		case K_LEFT:	
			if ( gray > ( 200 + 20u ))
			{
				gray -= 20u;
			}
			changed = true;
			break;

		case K_ESC:
		case K_OK:
			if ( changed )
			{
				Configure.DisplayGray  = gray;
				ConfigureSave();
			}
			return;
		case K_OK_UP:	
			if ( gray < 2200u )
			{
				++gray;
			}
			if( ! releaseKey( K_OK_UP,100 ))
			{
				while( ! releaseKey( K_OK_UP, 1 ))
				{
					++gray;
					DisplaySetGrayVolt( gray * 0.01f );
				}
			}
			graychanged = true;		
			break;
		case K_OK_DOWN:
			if ( gray >  200u )
			{
				--gray;
			}
			if( ! releaseKey( K_OK_DOWN, 100 ))
			{
				while( ! releaseKey( K_OK_DOWN, 1 ))
				{
					--gray;
					DisplaySetGrayVolt( gray * 0.01f );
				}			
			}
			graychanged = true;
			break;

		case K_OK_RIGHT:
			if ( gray < ( 2000u - 50u ))
			{ 
				gray += 100u;
			}
			graychanged = true;
			break;
		case K_OK_LEFT:	
			if ( gray > ( 200 + 20u ))
			{
				gray -= 20u;
			}
			graychanged = true;
			break;
		default:
			break;
		}
		if( graychanged == true )
		{
			DisplaySetGrayVolt( gray * 0.01f );
			Configure.DisplayGray = gray;
			ConfigureSave();
			graychanged = FALSE;;
		}		

	}
}
uint8_t LCD_Gray( uint8_t item )
{
	if( ( item == 1 ) || ( item == 0xff ) )
  {
    if ( ! releaseKey( K_OK, 300 ))
    {
      item = enumSelectESC;	
      beep();
      delay( 100u );
      beep();
      cls();	
      ModifyLCD();
    }
    else
    if ( ! releaseKey( K_SHIFT, 300 ))
    {
      item = enumSelectESC;
      beep();
      delay( 100u );
      beep();
      cls();
      Lputs( 0x0604u, "������������:" );
      ConfigureLoad();
      if( EditI32U( 0x0A05u, &Configure.ExNum, 0x0700u ))
        if( vbYes == MsgBox("�Ƿ񱣴���?",vbYesNo) )
          ConfigureSave();
        else
          ConfigureLoad();				
    }
  }
  
	return item;
}
void	menu_show_env_state( void )
{

	Lputs( 0x0616u, "״  ̬" );
	show_env_state();

}

/********  (C) COPYRIGHT 2014 �ൺ���˴���ӿƼ����޹�˾  **** End Of File ****/
