/**************** (C) COPYRIGHT 2014 �ൺ���˴���ӿƼ����޹�˾ ****************
* �� �� ��: ConfigureEx.C
* �� �� ��: ����
* ��  ��  : KB-6120E ���ó��򣨳������ò��֣�
* ����޸�: 2014��3��1��
*********************************** �޶���¼ ***********************************
* ��  ��: 
* �޶���: 
*******************************************************************************/
#include "AppDEF.H"
#include "stdio.h" 
/********************************** ����˵�� ***********************************
*	�������� -> ������
*******************************************************************************/


/********************************** ����˵�� ***********************************
*	��չ���� -> �����õ�ѹ������
*******************************************************************************/
//	static	void	menu_Configure_PrProtect( void )
//	{
//		MsgBox( "TODO: PrProtect", vbOKOnly );
//	}

/********************************** ����˵�� ***********************************
*	��չ���� -> ���ۼ�����ʱ��
*******************************************************************************/
static	void	menu_Clean_SumTime( void )
{
	BOOL	Done = FALSE;
	do{
		cls();	//	Lputs( 0x0000u, "����ʱ��(Сʱ)" );
		Lputs( 0x0102u, "������" );  Lputs( 0x0112u, "ʱ��" );
		
		Lputs( 0x0402u, " A·:" ); 	  ShowFP32( 0x040Cu, PumpSumTimeLoad( PP_R24_A  ) / 60.0f, 0x0601u, "h" );
		Lputs( 0x0802u, " B·:" ); 	  ShowFP32( 0x080Cu, PumpSumTimeLoad( PP_R24_B  ) / 60.0f, 0x0601u, "h" );
		Lputs( 0x0C02u, " C·:" ); 	  ShowFP32( 0x0C0Cu, PumpSumTimeLoad( PP_SHI_C  ) / 60.0f, 0x0601u, "h" );
		Lputs( 0x1002u, " D·:" ); 	  ShowFP32( 0x100Cu, PumpSumTimeLoad( PP_SHI_D  ) / 60.0f, 0x0601u, "h" );
		Lputs( 0x1402u, "����:" ); 	ShowFP32( 0x140Cu, PumpSumTimeLoad( PP_AIR    ) / 60.0f, 0x0601u, "h" );
		Lputs( 0x1802u, "�۳�:" );	ShowFP32( 0x180Cu, PumpSumTimeLoad( PP_TSP    ) / 60.0f, 0x0601u, "h" );
		switch ( getKey() )
		{
		case	K_OK	:						
			if ( ! releaseKey( K_OK, 100u ))
			{
				beep();
				if ( vbYes == MsgBox( "����ۼ�ʱ�� ?", vbYesNo | vbDefaultButton2 ))
				{
					PumpSumTimeSave( PP_TSP,   0u );
					PumpSumTimeSave( PP_R24_A, 0u );
					PumpSumTimeSave( PP_R24_B, 0u );
					PumpSumTimeSave( PP_SHI_C, 0u );
					PumpSumTimeSave( PP_SHI_D, 0u );
					PumpSumTimeSave( PP_AIR,   0u );
				}
			}
			break;
		case	K_ESC	:
			Done = TRUE;
			break;
		default	:
			break;
		}
	}while( !Done );
}

/********************************** ����˵�� ***********************************
*  ϵͳ���� -> �ļ���
*******************************************************************************/
static	void	menu_Clean_FileNum( void )
{
	BOOL	Done = FALSE;
	do{
		cls();	
		Lputs( 0x0102u, "����" );		Lputs( 0x010Cu, "�ļ���" );
		Lputs( 0x0602u, "�۳�:" );	ShowI16U( 0x060Cu, SampleSet[Q_TSP].FileNum, 0x0300u, NULL );
		Lputs( 0x0C02u, "�վ�:" );	ShowI16U( 0x0C0Cu, SampleSet[Q_R24].FileNum, 0x0300u, NULL );
		Lputs( 0x1202u, "ʱ��:" );	ShowI16U( 0x120Cu, SampleSet[Q_SHI].FileNum, 0x0300u, NULL );
		Lputs( 0x1802u, "����:" );	ShowI16U( 0x180Cu, SampleSet[Q_AIR].FileNum, 0x0300u, NULL );
		
		switch ( getKey() )
		{
		case	K_OK	:
			if ( ! releaseKey( K_OK, 100u ))
			{
				beep();
				if ( vbYes == MsgBox( "��������ļ� ?", vbYesNo | vbDefaultButton2 ) )
				{
					File_Clean();
					
					SampleSet[Q_TSP].FileNum =
					SampleSet[Q_R24].FileNum =
					SampleSet[Q_SHI].FileNum =
					SampleSet[Q_AIR].FileNum = 0u;
					SampleSetSave();
				}
			}
			break;
		case	K_ESC	:
			Done = TRUE;
			break;
		default	:
			break;
		}
	}while( !Done );

}
void  menu_Sample_Sum( void )
{
  static	struct  uMenu  const  menu[] =
	{
		{ 0x0201u, "�����ۼ�" },
		{ 0x0C02u, "�ļ����" },
		{ 0x1502u, "���ۼ�" },

	};
	uint8_t item = 1u;
	do {
		cls();
		Menu_Redraw( menu );
    item = Menu_Select( menu, item, NULL );
    switch( item )
    {
		case 1:		menu_Clean_FileNum();	break;
		case 2:		menu_Clean_SumTime();	break;
		default:	break;			
    }
  }while( enumSelectESC != item );
}


void menu_ExName( void )
{
	BOOL changed = FALSE;
	BOOL Done = FALSE;
	
	do{
		cls();
		ShowEdition();
				
		switch( getKey() )
		{
		case	K_OK:	
			++ Configure.ExName;
			if ( Configure.ExName >= Name_Max )
			{
				Configure.ExName = 0u;
			}
			changed = TRUE;	
			break;
		case	K_ESC:
			Done = TRUE;
			if( changed )
			{
				switch( MsgBox("�����޸Ľ��?", vbYesNoCancel|vbDefaultButton3 ) )
				{
				case	vbYes		:	ConfigureSave();	break;
				case	vbNo		:	ConfigureLoad();	break;
				case	vbCancel:	Done = FALSE;			break;
				}				
			}			
			break;
		default:
			break;
		}
		
	}while( !Done );
}

void	menu_ConfigureDisplay( void )
{
	static	struct  uMenu  const  menu[] =
	{
		{ 0x0301u, "���� ��ʾ" },
		{ 0x0802u, "�Ҷ�" },
		{ 0x1002u, "����" },
		{ 0x1802u, "��ʱ" }
	};
	uint8_t item = 1u;
	
	uint16_t gray  = Configure.DisplayGray;
	uint16_t light = Configure.DisplayLight;
	uint8_t  ltime = Configure.TimeoutLight;
	BOOL	changed = FALSE;
	
	cls();
	Menu_Redraw( menu );
	do {
		ShowI16U( 0x080Cu, gray,  0x0502u, " V " );
		ShowI16U( 0x100Cu, light, 0x0300u, " % " );
		switch ( ltime )
		{
		case 0:	Lputs( 0x180Cu, "[�ر�]" );	break;
		case 1:	Lputs( 0x180Cu, "[15��]" );	break;
		case 2:	Lputs( 0x180Cu, "[30��]" );	break;
		case 3:	Lputs( 0x180Cu, "[60��]" );	break;
		default:
		case 4:	Lputs( 0x180Cu, "[����]" );	break;
		}
		item = Menu_Select( menu, item, NULL );

		switch( item )
		{
		case 1:	
			if ( EditI16U( 0x080Cu, &gray, 0x0502u ))
			{
				if ( gray > 2000u ){ gray = 2000u; }
				if ( gray <  200u ){ gray =  200u; }
				DisplaySetGrayVolt( gray * 0.01f );
				changed = TRUE;
			}
			break;
		case 2:
			if ( EditI16U( 0x100Cu, &light, 0x0300u ))
			{
				if ( light > 100u ){ light = 100u; }
				DisplaySetLight( light );
				changed = TRUE;
			}
			break;
		case 3:	
			if ( ++ltime > 4 ){  ltime = 0u; }
			DisplaySetTimeout( ltime );
			changed = TRUE;
			break;
		}
		
	} while ( enumSelectESC != item );
	
	if ( changed )
	{
		Configure.DisplayGray  = gray;
		Configure.DisplayLight = light;
		Configure.TimeoutLight = ltime;
		ConfigureSave();
	}
}
extern	void	Configure_Instrument( void );
static	menu_Instr_Config( void )
{
	Configure_Instrument();
}
/********************************** ����˵�� ***********************************
*	��չ���ã�ֻ�ܳ��Ҳ����Ĳ��֣�

���ҵ���
����汾
���ۼ�����ʱ��
�ã������ƣ��ͺ�ѡ��������ʾ����ѡ��ѡ�񹩵��Դ����
��ǰѹ����������ֵ���ã���ֹ�ö���
��ʾ��Ļ����
�ļ���š��ļ��洢��������
*******************************************************************************/
void	menu_ConfigureEx( void )
{
	static	struct  uMenu  const  menu[] =
	{
		{ 0x0302u, "��������" 	},
		{ 0x0802u, " �� �� "	}, 	{ 0x0814u, "�����ۼ�" 	},
		{ 0x1002u, "��������" 	}, 	{ 0x1014u, " �� ʾ " 	},	//	{ 0x0408u, "ѹ������" },
		{ 0x1802u, "��������"	}, 	{ 0x1814u, "����汾" 	},

	};
	uint8_t	item = 1u;

	do {
		cls();
		Menu_Redraw( menu );
		item = Menu_Select( menu, item, NULL );
		switch( item )
		{
		case 1:	menu_FactoryDebug();		break;	
	 	case 3:	menu_Instr_Config();		break;
		case 5:	menu_ExName();		break;
		case 2:	menu_Sample_Sum();		break;
//		case 4:	menu_Configure_PrProtect();	break;
		case 4:	menu_ConfigureDisplay();	break;
		case 6:	ShowEdition_Inner();  getKey();	break;
		default:	break;
		}
	} while( enumSelectESC != item );
}

/********  (C) COPYRIGHT 2014 �ൺ���˴���ӿƼ����޹�˾  **** End Of File ****/
