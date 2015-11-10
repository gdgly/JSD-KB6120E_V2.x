/**************** (C) COPYRIGHT 2015 �ൺ���˴���ӿƼ����޹�˾ ****************
* �� �� ��: Calibrate.C
* �� �� ��: ����
* ��  ��  : KB6120E �궨����
* ����޸�: 2015��6��2��
*********************************** �޶���¼ ***********************************
* ��  ��: 
* �޶���: 
*******************************************************************************/
#include "AppDEF.H"

/********************************** ���ݶ��� ***********************************
//	�궨����
*******************************************************************************/
struct	uCalibrateLocal		CalibrateLocal;
struct	uCalibrateRemote	CalibrateRemote;//[BS_Max][BC_Max];

void	menu_Calibrate_Battery( void );

/********************************** ����˵�� ***********************************
*  �Զ������µı���ֵ
*******************************************************************************/
//	uint16_t Calc_New_Scale( FP32 SetFlow, FP32 run_flow )
//	{
//		uint16_t scale = 1000u;
//		uint16_t ruleflow = (uint16_t)( SetFlow * 1.0e3f + .5f );
//		
//		if ( run_flow < 0.001f )
//		{
//			MsgBox( "�޷�����������!", vbOKOnly );
//			return	0u;
//		}

//		cls();	Lputs( 0x0000u, "�Զ����㱶��" );
//		Lputs( 0x0300u,"У׼�����ƶ���:" );
//		ShowI16U( 0x0504u, ruleflow, 0x0503u, "L/m" );

//		if ( ! EditI16U( 0x0504u, &ruleflow, 0x0503u ))
//		{
//			return 0u;
//		}
//			
//		scale = (uint16_t)(( ruleflow / ( run_flow * 1000.0f ) + 0.5f ));
//		
//		return	scale;
//	}

/********************************** ����˵�� ***********************************
*  �л�������
*******************************************************************************/
void	ShowPumpSelect( uint16_t yx, enum enumPumpSelect PumpSelect )
{
	switch ( PumpSelect )
	{
	case PP_TSP  : 	Lputs( yx, "�� ��" );	break;
	case PP_R24_A:	Lputs( yx, "�վ�A" );	break;
	case PP_R24_B:	Lputs( yx, "�վ�B" );	break;
	case PP_SHI_C:	Lputs( yx, "ʱ��C" );	break;
	case PP_SHI_D:	Lputs( yx, "ʱ��D" );	break;
	case PP_AIR  :	Lputs( yx, "�� ��" );	break;
	default:		Lputs( yx, "δ֪?" );	break;
	}
}

static	void	CalibrateSave_PP( enum enumPumpSelect PumpSelect )
{
	CalibrateSave( );
}

static	void	CalibrateLoad_PP( enum enumPumpSelect PumpSelect )
{
	CalibrateLoad( );
}


/********************************** ����˵�� ***********************************
* �������궨->����ѹ��
*******************************************************************************/
static	void	menu_Calibrate_Ba( void )
{
	struct	uMenu const menu[] = 
	{
		{ 0x0201u, "�궨����ѹ" },
		{ 0x1000u, "���" },
		{ 0x1800u, "����" }
	};
	enum {
		opt_exit,
		opt_origin, opt_slope, 
		opt_max, opt_min = opt_origin
	};
	uint8_t	option = opt_min;
	uint16_t gray  = Configure.DisplayGray;
	BOOL	graychanged = FALSE;
	BOOL	changed = FALSE;

	cls();
	Menu_Redraw( menu );
	do {
		ShowI16U( 0x100Cu, CalibrateLocal.origin_Ba, 0x0502u, NULL );
		ShowI16U( 0x180Cu, CalibrateLocal. slope_Ba, 0x0503u, NULL );

		Menu_Item_Mask( menu, option );
		do{
			Lputs( 0x0800u, "����ѹ:" );
			ShowFP32( 0x0811u, _sys_get_Ba(), 0x0602u, "kPa" );
		} while( ! hitKey( 25u ));
		Menu_Item_Mask( menu, option );

		switch( getKey())
		{
		case K_DOWN:
			++option;
			if ( option >= opt_max )
			{
				option = opt_min;
			}
			break;
		case K_UP:
			if( option <= opt_min )
			{
				option = opt_max;
			}
			--option;
			break;
		
		case K_OK:
			switch( option )
			{
			case opt_origin:
				if ( EditI16U( 0x100Cu, &CalibrateLocal.origin_Ba, 0x0502u ))
				{
					changed = TRUE;
				}
				break;
			case opt_slope:
				if ( EditI16U( 0x180Cu, &CalibrateLocal. slope_Ba, 0x0503u ))
				{
					changed = TRUE;
				}
				break;
			default:
				break;
			}
			break;

		case K_ESC:
			if( ! changed )
			{
				option = opt_exit;
			}
			else
			{
				switch( MsgBox( "����궨���� ?", vbYesNoCancel + vbDefaultButton3 ))
				{
				case vbYes:
					CalibrateSave();
					option = opt_exit;
					break;
				case vbNo:
					CalibrateLoad();
					option = opt_exit;
					break;
				case vbCancel:
					cls();
					Menu_Redraw( menu );
					break;
				default:
					break;
				}
			}
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

	} while( opt_exit != option );
}

/********************************** ����˵�� ***********************************
* �������궨->�����¶�
*******************************************************************************/
void	menu_Calibrate_Te( void )
{
	struct	uMenu const menu[] = 
	{
		{ 0x0201u, "�궨�����¶�" },
		{ 0x1000u, "���" },
		{ 0x1800u, "����" }
	};
	enum {
		opt_exit,
		opt_origin, opt_slope, 
		opt_max, opt_min = opt_origin
	};
	uint8_t	option = opt_min;
	uint16_t gray  = Configure.DisplayGray;
	BOOL	graychanged = FALSE;
	BOOL	changed = FALSE;

	cls();
	Menu_Redraw( menu );
	do {
		ShowI16U( 0x100Cu, CalibrateRemote.origin_Te, 0x0602u, NULL );
		ShowI16U( 0x180Cu, CalibrateRemote. slope_Te, 0x0503u, NULL );

		Menu_Item_Mask( menu, option );
		do{
			Lputs( 0x0800u, "�¶�:" );
			ShowFP32( 0x080Cu, _sys_get_Te(), 0x0602u, "��" );
		} while( ! hitKey( 25u ));
		Menu_Item_Mask( menu, option );

		switch( getKey())
		{
		case K_DOWN:
			++option;
			if ( option >= opt_max )
			{
				option = opt_min;
			}
			break;
		case K_UP:
			if( option <= opt_min )
			{
				option = opt_max;
			}
			--option;
			break;
		
		case K_OK:
			switch( option )
			{
			case opt_origin:
				if ( EditI16U( 0x100Cu, &CalibrateRemote.origin_Te, 0x0602u ))
				{
					changed = TRUE;
				}
				break;
			case opt_slope:
				if ( EditI16U( 0x180Cu, &CalibrateRemote. slope_Te, 0x0503u ))
				{
					changed = TRUE;
				}
				break;
			default:
				break;
			}
			break;

		case K_ESC:
			if( ! changed )
			{
				option = opt_exit;
			}
			else
			{
				switch( MsgBox( "����궨���� ?", vbYesNoCancel + vbDefaultButton3 ))
				{
				case vbYes:
					CalibrateSave();
					option = opt_exit;
					break;
				case vbNo:
					CalibrateLoad();
					option = opt_exit;
					break;
				case vbCancel:
					cls();
					Menu_Redraw( menu );
					break;
				default:
					break;
				}
			}
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

	} while( opt_exit != option );
}

/********************************** ����˵�� ***********************************
* �������궨->�������¶�
*******************************************************************************/
void	menu_Calibrate_HCBox_Temp( void )
{
	struct	uMenu const menu[] = 
	{
		{ 0x0201u, "�궨�������¶�" },
		{ 0x1000u, "���" },
		{ 0x1800u, "����" }
	};
	enum {
		opt_exit,
		opt_origin, opt_slope, 
		opt_max, opt_min = opt_origin
	};
	uint8_t	option = opt_min;
	uint16_t gray  = Configure.DisplayGray;
	BOOL	graychanged = FALSE;
	BOOL	changed = FALSE;

	cls();
	Menu_Redraw( menu );
	do {
		ShowI16U( 0x100Cu, CalibrateRemote.origin_HCBox_Temp, 0x0602u, NULL );
		ShowI16U( 0x180Cu, CalibrateRemote. slope_HCBox_Temp, 0x0503u, NULL );

		Menu_Item_Mask( menu, option );
		do{
			Lputs( 0x0800u, "�¶�:" );
			ShowFP32( 0x080Cu, get_HCBoxTemp(), 0x0602u, "��" );
		} while( ! hitKey( 25u ));
		Menu_Item_Mask( menu, option );

		switch( getKey())
		{
		case K_DOWN:
			++option;
			if ( option >= opt_max )
			{
				option = opt_min;
			}
			break;
		case K_UP:
			if( option <= opt_min )
			{
				option = opt_max;
			}
			--option;
			break;
		
		case K_OK:
			switch( option )
			{
			case opt_origin:
				if ( EditI16U( 0x100Cu, &CalibrateRemote.origin_HCBox_Temp, 0x0602u ))
				{
					changed = TRUE;
				}
				break;
			case opt_slope:
				if ( EditI16U( 0x180Cu, &CalibrateRemote. slope_HCBox_Temp, 0x0503u ))
				{
					changed = TRUE;
				}
				break;
			default:
				break;
			}
			break;

		case K_ESC:
			if( ! changed )
			{
				option = opt_exit;
			}
			else
			{
				switch( MsgBox( "����궨���� ?", vbYesNoCancel + vbDefaultButton3 ))
				{
				case vbYes:
					CalibrateSave();
					option = opt_exit;
					break;
				case vbNo:
					CalibrateLoad();
					option = opt_exit;
					break;
				case vbCancel:
					cls();
					Menu_Redraw( menu );
					break;
				default:
					break;
				}
			}
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

	} while( opt_exit != option );
}

/********************************** ����˵�� ***********************************
* �������궨->�������¶�
*******************************************************************************/
void	menu_Calibrate_Heater_Temp( void )
{
	struct	uMenu const menu[] = 
	{
		{ 0x0201u, "�궨�������¶�" },
		{ 0x1000u, "���" },
		{ 0x1800u, "����" }
	};
	enum {
		opt_exit,
		opt_origin, opt_slope, 
		opt_max, opt_min = opt_origin
	};
	uint8_t	option = opt_min;
	uint16_t gray  = Configure.DisplayGray;
	BOOL	graychanged = FALSE;
	BOOL	changed = FALSE;

	cls();
	Menu_Redraw( menu );
	do {
		ShowI16U( 0x100Cu, CalibrateRemote.origin_Heater_Temp, 0x0602u, NULL );
		ShowI16U( 0x180Cu, CalibrateRemote. slope_Heater_Temp, 0x0503u, NULL );

		Menu_Item_Mask( menu, option );
		do{
			Lputs( 0x0800u, "�¶�:" );
			ShowFP32( 0x080C, get_HeaterTemp(), 0x0602u, "��" );
		} while( ! hitKey( 25u ));
		Menu_Item_Mask( menu, option );

		switch( getKey())
		{
		case K_DOWN:
			++option;
			if ( option >= opt_max )
			{
				option = opt_min;
			}
			break;
		case K_UP:
			if( option <= opt_min )
			{
				option = opt_max;
			}
			--option;
			break;
		
		case K_OK:
			switch( option )
			{
			case opt_origin:
				if ( EditI16U( 0x100Cu, &CalibrateRemote.origin_Heater_Temp, 0x0602u ))
				{
					changed = TRUE;
				}
				break;
			case opt_slope:
				if ( EditI16U( 0x180Cu, &CalibrateRemote. slope_Heater_Temp, 0x0503u ))
				{
					changed = TRUE;
				}
				break;
			default:
				break;
			}
			break;

		case K_ESC:
			if( ! changed )
			{
				option = opt_exit;
			}
			else
			{
				switch( MsgBox( "����궨���� ?", vbYesNoCancel + vbDefaultButton3 ))
				{
				case vbYes:
					CalibrateSave();
					option = opt_exit;
					break;
				case vbNo:
					CalibrateLoad();
					option = opt_exit;
					break;
				case vbCancel:
					cls();
					Menu_Redraw( menu );
					break;
				default:
					break;
				}
			}
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

	} while( opt_exit != option );
}

/********************************** ����˵�� ***********************************
* �������궨->��ǰ�¶�
*******************************************************************************/
static	void	Calibrate_Tr ( enum enumPumpSelect PumpSelect )
{
	static	struct  uMenu  const  menu[] = 
	{
		{ 0x0201u, "�궨��ǰ�¶�" },
		{ 0x1000u, "���" },
		{ 0x1800u, "����" }
	};
	enum {
		opt_exit,
		opt_origin, opt_slope, 
		opt_max, opt_min = opt_origin
	};
	uint8_t	option = opt_min;

	BOOL	need_redraw = TRUE;
	uint16_t gray  = Configure.DisplayGray;
	BOOL graychanged = FALSE;

	uint16_t	*p_origin = &CalibrateRemote.origin[esid_tr][PumpSelect];
	uint16_t	*p_slope  = &CalibrateRemote.slope [esid_tr][PumpSelect];
	BOOL		changed = FALSE;

	do {
		if ( need_redraw )
		{
			cls();
			Menu_Redraw( menu );
			ShowPumpSelect( 0x0115u, PumpSelect );

			need_redraw = FALSE;
		}

		ShowI16U( 0x100Cu, *p_origin, 0x0602u, NULL );
		ShowI16U( 0x180Cu, *p_slope , 0x0503u, NULL );

		Menu_Item_Mask( menu, option );
		do{
			Lputs( 0x0800u, "�¶�:" );
			ShowFP32( 0x080Cu, get_Tr( PumpSelect ), 0x0602u, "��" );
		} while( ! hitKey( 25u ));
		Menu_Item_Mask( menu, option );

		switch( getKey())
		{
		case K_DOWN:
			++option;
			if ( option >= opt_max )
			{
				option = opt_min;
			}
			break;
		case K_UP:
			if( option <= opt_min )
			{
				option = opt_max;
			}
			--option;
			break;
		
		case K_OK:
			switch( option )
			{
			case opt_origin:
				if ( EditI16U( 0x100Cu, p_origin, 0x0602u ))
				{
					changed = TRUE;
				}
				break;
			case opt_slope:
				if ( EditI16U( 0x180Cu, p_slope , 0x0503u ))
				{
					changed = TRUE;
				}
				break;
			default:
				break;
			}

			break;

		case K_ESC:
			if( ! changed )
			{
				option = opt_exit;
			}
			else
			{
				switch( MsgBox( "����궨���� ?", vbYesNoCancel + vbDefaultButton3 ))
				{
				case vbYes:
					CalibrateSave_PP( PumpSelect );
					option = opt_exit;
					break;
				case vbNo:
					CalibrateLoad_PP( PumpSelect );
					option = opt_exit;
					break;
				default:
					break;
				}
				
				need_redraw = TRUE;
			}
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

	} while( opt_exit != option );
}

/********************************** ����˵�� ***********************************
* �������궨->��ǰѹ��
*******************************************************************************/
static	void	Calibrate_Pr( enum enumPumpSelect PumpSelect )
{
	struct	uMenu const menu[] = 
	{
		{ 0x0201u, "�궨��ǰѹ��" },
		{ 0x1000u, "���" },
		{ 0x1800u, "����" }
	};
	enum {
		opt_exit,
		opt_origin, opt_slope, 
		opt_max, opt_min = 1
	};
	uint8_t	option = opt_min;
	BOOL	need_redraw = TRUE;
	uint16_t gray  = Configure.DisplayGray;
	BOOL graychanged = FALSE;
	
	uint16_t	*p_origin = &CalibrateRemote.origin[esid_pr][PumpSelect];
	uint16_t	*p_slope  = &CalibrateRemote.slope [esid_pr][PumpSelect];
	BOOL		changed   = FALSE;

	do {
		if ( need_redraw )
		{
			cls();
			Menu_Redraw( menu );
			ShowPumpSelect( 0x0115u, PumpSelect );

			need_redraw = FALSE;
		}
		
		ShowI16U( 0x100Cu, *p_origin, 0x0500u, NULL );
		ShowI16U( 0x180Cu, *p_slope,  0x0503u, NULL );

		Menu_Item_Mask( menu, option );
		do{
			Lputs( 0x0800u, "��ѹ:" );
			ShowFP32( 0x080C, get_Pr( PumpSelect ), 0x0602, "kPa" );
		} while( ! hitKey( 25u ));
		Menu_Item_Mask( menu, option );

		switch( getKey())
		{
		case K_DOWN:
			++option;
			if ( option >= opt_max )
			{
				option = opt_min;
			}
			break;
		case K_UP:
			if( option <= opt_min )
			{
				option = opt_max;
			}
			--option;
			break;
		
		case K_OK:
			switch( option )
			{
			case opt_origin:
				if ( EditI16U( 0x100Cu, p_origin, 0x0500u ))
				{
					changed = TRUE;
				}
				break;
			case opt_slope:
				if ( EditI16U( 0x180Cu, p_slope,  0x0503u ))
				{
					changed = TRUE;
				}
				break;
			default:
				break;
			}
			break;

		case K_ESC:
			if( ! changed )
			{
				option = opt_exit;
			}
			else
			{
				switch( MsgBox( "����궨���� ?", vbYesNoCancel + vbDefaultButton3 ))
				{
				case vbYes:
					CalibrateSave_PP( PumpSelect );
					option = opt_exit;
					break;
				case vbNo:
					CalibrateLoad_PP( PumpSelect );
					option = opt_exit;
					break;
				default:
					break;
				}
				need_redraw = TRUE;
			}
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

	} while( opt_exit != option );
}

/********************************** ����˵�� ***********************************
* �������궨->�װ��ѹ
*******************************************************************************/
static	void	Calibrate_pf(  enum enumPumpSelect PumpSelect )
{
	struct	uMenu const	menu[] = {
		{ 0x0201u, "�궨��ѹ" },
		{ 0x1000u, "���" },
		{ 0x1800u, "����" },
	};
	enum {
		opt_exit,
		opt_origin, opt_slope, 
		opt_max, opt_min = 1
	};
	uint8_t option = opt_min;

	BOOL	need_redraw = TRUE;
	uint16_t gray  = Configure.DisplayGray;
	BOOL graychanged = FALSE;

	uint16_t	*p_origin = &CalibrateRemote.origin[esid_pf][PumpSelect];
	uint16_t	*p_slope  = &CalibrateRemote.slope [esid_pf][PumpSelect];
	BOOL		changed   = FALSE;

	do {
		if ( need_redraw )
		{
			cls();
			Menu_Redraw( menu );
			ShowPumpSelect( 0x0115u, PumpSelect );

			need_redraw = FALSE;
		}
		
		ShowI16U( 0x100Cu, *p_origin, 0x0500u, NULL );
		ShowI16U( 0x180Cu, *p_slope,  0x0503u, NULL );

		Menu_Item_Mask( menu, option );
		do{
			Lputs( 0x0800u, "��ѹ:" );
			ShowFP32( 0x080C, get_pf( PumpSelect ), 0x0603, "kPa" );
		} while( ! hitKey( 25u ));
		Menu_Item_Mask( menu, option );

		switch( getKey())
		{
		case K_DOWN:
			++option;
			if ( option >= opt_max )
			{
				option = opt_min;
			}
			break;
		case K_UP:
			if( option <= opt_min )
			{
				option = opt_max;
			}
			--option;
			break;
		
		case K_OK:
			switch( option )
			{
			case opt_origin:
				if ( EditI16U( 0x100Cu, p_origin, 0x0500u ))
				{
					changed = TRUE;
				}
				break;
			case opt_slope:
				if ( EditI16U( 0x180Cu, p_slope,  0x0503u ))
				{
					changed = TRUE;
				}
				break;
			default:
				break;
			}
			break;

		case K_ESC:
			if( ! changed )
			{
				option = opt_exit;
			}
			else
			{
				switch( MsgBox( "����궨���� ?", vbYesNoCancel + vbDefaultButton3 ))
				{
				case vbYes:
					CalibrateSave_PP( PumpSelect );
					option = opt_exit;
					break;
				case vbNo:
					CalibrateLoad_PP( PumpSelect );
					option = opt_exit;
					break;
				default:
					break;
				}
				
				need_redraw = TRUE;
			}
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

	} while( opt_exit != option );
}

extern BOOL	EditI32U( uint16_t yx, uint32_t * pNUM, uint16_t fmt );

/********************************** ����˵�� ***********************************
*  ������У����
*******************************************************************************/
BOOL	CalibrateFLOW_4_Point_Debug( enum enumPumpSelect PumpSelect, uint16_t FlowKSet[], FP32 const PointSet[], uint8_t PointSelect )
{
		enum 
	{
		opt_exit, opt_standard,
	};
	uint8_t	option = opt_standard;
	BOOL	changed = FALSE;
	BOOL	need_redraw = TRUE;
	uint16_t gray  = Configure.DisplayGray;
	BOOL graychanged = FALSE;


	uint16_t FlowKSave[4];
	uint16_t	slope;
	uint32_t Flow32;
	FP32  Flown,Flow = 0.0f;

	//	�ݴ�ԭʼ���ݣ��������е�ı��ʡ��趨������
	slope = FlowKSet[PointSelect];
	FlowKSave[0] = FlowKSet[0];
	FlowKSave[1] = FlowKSet[1];
	FlowKSave[2] = FlowKSet[2];
	FlowKSave[3] = FlowKSet[3];
	// ��������
	Configure.SetFlow[PumpSelect] = ( uint16_t)( PointSet[PointSelect] * 1.0e+1f + 0.5f );
	//	��������������
	Pump_OutCmd( PumpSelect, TRUE ); // Motor_OutCmd( MotorSelect, TRUE );

	do {
		if ( need_redraw )
		{
			cls();	Lputs( 0x0000u, "��������");
		
			need_redraw = FALSE;
		}
			
		//	�����е�ı��ʵ�������ǰ����
		FlowKSet[0] =
		FlowKSet[1] =
		FlowKSet[2] =
		FlowKSet[3] = slope;
		//	��ʾ����
	
		do {	// ʵʱ��ʾ����
			Lputs( 0x0000u, "��������:" );	ShowI16U( 0x0019u, slope, 0x0503u, NULL );
			Lputs( 0x0C00u, "����:" );	ShowFP32( 0x0C0Cu, get_fstd( PumpSelect ), 0x0603u, "L/m" );
			Lputs( 0x1800u, "���:" );	ShowPercent( 0x180Cu, Pump_GetOutput( PumpSelect ));
		} while ( ! hitKey( 100u ));

		switch ( getKey())
		{
		case K_UP:
			if ( slope < 9999u )
			{
				++slope;
			}
			changed = TRUE;
			break;

		case K_DOWN:
			if ( slope > 99u )
			{
				--slope;
			}
			changed = TRUE;
			break;

		case K_OK:
			Flow32 = Configure.SetFlow[PumpSelect] * 100;
			LcmMask( 0x0C00u, 3u, NULL );
			if ( EditI32U( 0x0C0Cu, &Flow32, 0x0603u ))
			{
				changed = TRUE;
				Flown = ( FP32 ) Flow32;
				if( slope != 0 )
					Flow  = Flow / ( slope *0.001);
				else
					Flow = Flown / 1000;
				if( Flow != 0 )				
					slope =(uint16_t) ( Flown / Flow ) ; 
				else
					slope = 1000; 
			}
			break;

		case K_ESC:
			option = opt_exit;
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

	} while ( opt_exit != option );
	
	Pump_OutCmd( PumpSelect, FALSE ); 
	// 	�ָ�����ǰ��֮�������У׼��ı��ʡ�
	FlowKSet[0] = FlowKSave[0];
	FlowKSet[1] = FlowKSave[1];
	FlowKSet[2] = FlowKSave[2];
	FlowKSet[3] = FlowKSave[3];
	FlowKSet[PointSelect] = slope;

	return	changed;
}

BOOL	CalibrateFlow_1_Point_DEBUG( enum enumPumpSelect PumpSelect, uint16_t * const p_FlowK )
{
	BOOL	done = FALSE;
	BOOL	changed = FALSE;
	uint16_t gray  = Configure.DisplayGray;
	BOOL graychanged = FALSE;

	uint32_t Flow32 = 0;
	FP32  Flown,Flow = 0.0f;
	uint16_t	fmt = 0x0000u;
	const CHAR * szUnit = NULL;
	
	switch ( PumpSelect )
	{
	case PP_TSP  :	fmt = 0x0501u;	szUnit = "L/m";	break;
	case PP_R24_A:	fmt = 0x0503u;	szUnit = "L/m";	break;
	case PP_R24_B:	fmt = 0x0503u;	szUnit = "L/m";	break;
	default:	break;
	}

	cls();	
	
	Pump_OutCmd( PumpSelect, TRUE );
	
	while ( ! done )
	{
		
		do {	//	ʵʱ��ʾ����
			FP32	fstd = get_fstd( PumpSelect );
			if( PumpSelect == PP_TSP )
			{	
				FP32	Ba = get_Ba();
				FP32	Te = get_Te();// PumpSelect );
				FP32	flow = Calc_flow( fstd, Te, 0.0f, Ba, Q_TSP );	//	Calc_flow( fstd, Tr, Pr, Ba );
				Flow = flow;
				Lputs ( 0x0000u, "��������:" );	ShowI16U( 0x0019u, * p_FlowK, 0x0503u, NULL );
				Lputs ( 0x0800u, "����:" );	ShowFP32( 0x080Cu, flow, fmt, szUnit );
				Lputs ( 0x1000u, "���:" );	ShowFP32( 0x100Cu, fstd, fmt, szUnit );
				Lputs ( 0x1800u, "���:" );	ShowPercent( 0x180Cu, Pump_GetOutput( PumpSelect ));
			}
			else
			{
				Flow = fstd;
				Lputs( 0x0000u, "��������:" );	ShowI16U( 0x0019u, * p_FlowK, 0x0503u, NULL );
// 				Lputs ( 0x0800u, "����:" );	ShowFP32( 0x080Cu, flow, fmt, szUnit );
				Lputs ( 0x0C00u, "���:" );	ShowFP32( 0x0C0Cu, fstd, fmt, szUnit );
				Lputs ( 0x1800u, "���:" );	ShowPercent( 0x180Cu, Pump_GetOutput( PumpSelect ));
			}
		} while ( ! hitKey( 100u ));

		switch ( getKey())
		{
		case K_UP:
			if ( * p_FlowK < 9999u )
			{
				++ * p_FlowK;
			}
			changed = TRUE;
			break;
		case K_DOWN:
			if ( * p_FlowK > 99u )
			{
				-- * p_FlowK;
			}
			changed = TRUE;
			break;
		case K_OK:
			Flow32 = Configure.SetFlow[PumpSelect];
			
		if( PumpSelect == PP_TSP )
			{
				LcmMask( 0x0800u, 3u,NULL );

				if ( EditI32U( 0x080Cu, &Flow32, fmt ) )
				{
					changed = TRUE;
					Flown = ( FP32 ) Flow32;
					if( * p_FlowK != 0 )
						Flow  = Flow / ( * p_FlowK * 0.001 );
					else
						Flow = Flown;
					if(Flow != 0)
						* p_FlowK =(uint16_t) ( Flown * 100 / Flow ) ;
					else
						* p_FlowK = 1000;
				}
			}
			else
			{
				LcmMask( 0x0C00u, 3u,NULL );

				if ( EditI32U( 0x0C0Cu, &Flow32, fmt ) )
				{
					changed = TRUE;
					Flown = ( FP32 ) Flow32;
					if( * p_FlowK != 0 )
						Flow  = Flow / ( * p_FlowK * 0.001 );
					else
						Flow = Flown;
					if(Flow != 0)
						* p_FlowK =(uint16_t) ( Flown / Flow ) ;
					else
						* p_FlowK = 1000;
				}
			}
			break;
		case K_ESC:
			done = TRUE;
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

	}
	
	Pump_OutCmd( PumpSelect, FALSE );
	
	return	changed;
}

/********************************** ����˵�� ***********************************
* �������궨 -> �۳�����������궨��
*********************************** ����˵�� ***********************************
* �������궨 -> �վ�����������궨��
*******************************************************************************/
static	void	CalibrateFlow_1_Point( enum enumPumpSelect PumpSelect )
{
	struct	uMenu const	menu[] = 
	{
		{ 0x0301u, "�궨����" },
		{ 0x0802u, "����" },
		{ 0x100Eu, "����" },
		{ 0x1802u, "����" },
	};
	BOOL	need_redraw = TRUE;

	uint8_t	option  = 1u;

	uint16_t	*p_FlowK = CalibrateRemote.slope_flow[PumpSelect];
	BOOL		changed  = FALSE;
	uint16_t	fmt;
	
	switch ( PumpSelect )
	{
	default:
	case PP_TSP:	fmt = 0x0501u; 	break;
	case PP_R24_A:
	case PP_R24_B:	fmt = 0x0503u;	break;
	}
	
	do {
		if ( need_redraw )
		{
			cls();
			Menu_Redraw( menu );
			ShowPumpSelect( 0x0115u, PumpSelect );
			need_redraw = FALSE;
		}

		ShowI16U ( 0x080Cu, Configure.SetFlow[PumpSelect], fmt, "L/m" );
		ShowI16U ( 0x180Cu, * p_FlowK, 0x0503u, NULL );

		option = Menu_Select( menu, option, NULL );
		switch( option )
		{
		case 0:
			if ( changed )
			{
				switch( MsgBox( "����궨���� ?", vbYesNoCancel + vbDefaultButton3 ))
				{
				case vbYes:
					CalibrateSave();
					break;
				case vbNo:
					CalibrateLoad();
					break;
				default:
				case vbCancel:
					option = 1u;
					break;
				}

				need_redraw = TRUE;
			}
			break;
		case 1:
			if ( EditI16U( 0x080Cu, &Configure.SetFlow[PumpSelect], fmt ))
			{
				ConfigureSave();			
			}
			break;
		case 2:
			if ( CalibrateFlow_1_Point_DEBUG( PumpSelect, p_FlowK ))
			{
				changed = TRUE;
			}

			need_redraw = TRUE;
			break;
		case 3:
			if ( EditI16U( 0x180Cu, p_FlowK, 0x0503u ))
			{
				changed = TRUE;
			}
			break;

		default:
			break;
		}
	} while( enumSelectESC != option );
}

/********************************** ����˵�� ***********************************
* �������궨->ʱ�����������궨������ı궨������趨�Ŀװ��������Χ����ѡ��
*******************************************************************************/
static	BOOL	CalibrateFLOW_4_Point_1_Point( enum enumPumpSelect PumpSelect, uint16_t FlowKSet[], FP32 const PointSet[], uint8_t PointSelect )
{
	struct	uMenu  const  menu[] = 
	{
		{ 0x0201u, "�궨����" },
		{ 0x0C0Au, "����" },
		{ 0x1802u, "����" },
	};
	BOOL	changed = FALSE;
	uint8_t	option  = 1u;
	
	do {
		cls();	Menu_Redraw( menu );

		ShowFP32( 0x0119u, PointSet[PointSelect], 0x0301u, "L/m" );
		ShowI16U( 0x180Cu, FlowKSet[PointSelect], 0x0503u, NULL );

		option  = Menu_Select( menu, option, NULL );
		
		switch ( option )
		{
		case 1:
			if ( CalibrateFLOW_4_Point_Debug( PumpSelect, FlowKSet, PointSet, PointSelect ))
			{
				changed = TRUE;
			}
			break;

		case 2:
			if ( EditI16U( 0x180Cu, &FlowKSet[PointSelect], 0x0503u ))
			{
				changed = TRUE;
			}
			break;

		default:
			break;
		}

	} while ( 0u != option );
	
	return	changed;
}


extern FP32  const  PumpPoints[4][4];

FP32  const  PumpPoints[4][4] = 
{
	{ 0.0f, 0.0f, 0.0f, 0.0f },	//	enumPumpNone
	{ 0.2f, 0.5f, 0.8f, 1.0f },	//	enumOrifice_1
	{ 0.5f, 1.0f, 1.5f, 2.0f },	//	enumOrifice_2
	{ 0.2f, 0.5f, 0.8f, 1.0f },	//	enumMassflow
};

static	void	CalibrateFlow_4_Point( enum enumPumpSelect PumpSelect )
{
	static	struct	uMenu const	menu_1L[] =
	{
		{ 0x0202u, "�궨����" },
		{ 0x0C02u, "0.2L/m" },
		{ 0x0C16u, "0.5L/m" },
		{ 0x1802u, "0.8L/m" },
		{ 0x1816u, "1.0L/m" }
	};
	static	struct	uMenu const	menu_2L[] =
	{
		{ 0x0202u, "�궨����" },
		{ 0x0C02u, "0.5L/m" },
		{ 0x0C16u, "1.0L/m" },
		{ 0x1802u, "1.5L/m" },
		{ 0x1816u, "2.0L/m" }
	};
	struct uMenu const * menu;
	uint8_t	option  = 1u;

	uint8_t		PumpType = Configure.PumpType[PumpSelect];
	uint16_t *  p_FlowK4 = CalibrateRemote.slope_flow[PumpSelect];
	BOOL		changed = FALSE;
	
	switch ( PumpType )
	{
	default:	return;
	case enumOrifice_1:	menu = menu_1L;	break;
	case enumOrifice_2:	menu = menu_2L;	break;
	}

	do {
		cls();
		Menu_Redraw( menu );
		
		option = Menu_Select( menu, option, NULL );
		switch( option )
		{
		case 0:
			if ( changed )
			{
				switch( MsgBox( "����궨���� ?", vbYesNoCancel + vbDefaultButton3 ))
				{
				case vbYes:
					CalibrateSave();
					break;
				case vbNo:
					CalibrateLoad();
					break;
				default:
					break;
				}
			}
			break;
		case 1:	if ( CalibrateFLOW_4_Point_1_Point( PumpSelect, p_FlowK4, PumpPoints[PumpType], 0 )){ changed = TRUE; }	break;
		case 2:	if ( CalibrateFLOW_4_Point_1_Point( PumpSelect, p_FlowK4, PumpPoints[PumpType], 1 )){ changed = TRUE; }	break;
		case 3:	if ( CalibrateFLOW_4_Point_1_Point( PumpSelect, p_FlowK4, PumpPoints[PumpType], 2 )){ changed = TRUE; }	break;
		case 4:	if ( CalibrateFLOW_4_Point_1_Point( PumpSelect, p_FlowK4, PumpPoints[PumpType], 3 )){ changed = TRUE; }	break;
		default:	break;
		}
	} while( 0u != option );
}

void	menu_Select_Calc_Pbv( void )
{
    static	struct  uMenu  const   menu[] =
    {
        { 0x0201u, "���㱥��ˮ��ѹ" },
        { 0x0C07u, "[�� �� ��]" },
        { 0x1607u, "[�������]" },
    };

    uint8_t	item;

    cls();
    Menu_Redraw( menu );

    if ( Configure .shouldCalcPbv == 0 )
    {
        Lputs( 0x0C00u, " ->" );
        item = 1u;
	}
	else
	{
        Lputs( 0x1600u, " ->" );
        item = 2u;
	}

    item = Menu_Select( menu, item, NULL );

    switch( item )
    {
    case 1:
	case 2:
		Configure .shouldCalcPbv = ! Configure .shouldCalcPbv ;
		ConfigureSave();
        break;
    default:
        break;
    }
}

static	void	menu_Calibrate_Other( void )
{
	static	struct	uMenu const	menu[] = 
	{
		{ 0x0202u, "�������궨" },
		{ 0x0802u, "����ѹ" }, { 0x0814u, "�����¶�" },
		{ 0x1002u, "��ص�ѹ" }, { 0x1019u, "������" },
		
	};
	static	struct	uMenu const	menu1[] = 
	{
		{ 0x0202u, "�������궨" },
		{ 0x0802u, "����ѹ" }, { 0x0814u, "�����¶�" },
		{ 0x1002u, "��ص�ѹ" }, { 0x1019u, "������" },
		
	};
		static	struct	uMenu const	menu2[] = 
	{
		{ 0x0301u, "�������궨" },
		{ 0x0802u, "����ѹ" }, 
		{ 0x1002u, "�����¶�" },
		{ 0x1802u, "������" },
		
	};
	static	struct	uMenu const	menu3[] = 
	{
		{ 0x0301u, "�������궨" },
		{ 0x0802u, "����ѹ" }, 
		{ 0x1002u, "�����¶�" },
		{ 0x1802u, "������" },
		
	};
	uint8_t	item = 1u;
	
	do {
		   cls();
			  if( Configure.HeaterType == enumHeaterOnly && Configure.Battery_SW == TRUE )
				{	
					Menu_Redraw( menu );
					item = Menu_Select( menu, item, NULL );
				}
				else if( Configure.HeaterType != enumHeaterOnly && Configure.Battery_SW == TRUE )
				{
          Menu_Redraw( menu1 );
					item = Menu_Select( menu1, item, NULL );
				}
				else if( Configure.HeaterType == enumHeaterOnly && Configure.Battery_SW == FALSE )
				{
          Menu_Redraw( menu2 );
					item = Menu_Select( menu2, item, NULL );
				}
				else
				{
          Menu_Redraw( menu3 );
					item = Menu_Select( menu3, item, NULL );
				}
		switch( item )
		{
		case 1:	menu_Calibrate_Ba();	break;
		case 2:	menu_Calibrate_Te();	break;
		case 3:	
			menu_Calibrate_Battery( );
			break;	
		case 4:
			if( Configure.HeaterType == enumHeaterOnly )
				menu_Calibrate_Heater_Temp();	
			else
				menu_Calibrate_HCBox_Temp();		
			break; 
		default:	
			break;
		}
	} while( enumSelectESC != item );
}


/********************************** ����˵�� ***********************************
* ���˵� -> ά���˵� -> �궨�˵�
*******************************************************************************/

void	menu_Calibratex( uint8_t configT )
{
	static	struct	uMenu const	menu[] = 
	{
		{ 0x0302u, "�궨" },
		{ 0x0802u, "�¶�" },{ 0x0811u, "�Զ�����" },
		{ 0x1002u, "��ѹ" },{ 0x100Fu, "����ֵ����" }, 
		{ 0x1802u, "��ѹ" },{ 0x1811u, "��������" }, 
	};
	uint8_t	item = 1u;
	uint8_t TO = Configure.TimeoutLight;
	enum	enumPumpSelect	PumpSelect = PP_TSP;
	Configure.TimeoutLight = 4;
	DisplaySetTimeout( Configure.TimeoutLight );
	switch( configT )
	{
	case type_KB2400:		PumpSelect = PP_SHI_C;break;
	case type_KB2400D:	PumpSelect = PP_R24_A;break;
// 	case type_KB6120AD2:PumpSelect = PP_TSP;	break;
	case type_KB6120C:	PumpSelect = PP_TSP; 	break;
	case type_KB6120B:	PumpSelect = PP_TSP; 	break;	
	}
	do {
		cls();
		Menu_Redraw( menu );
		ShowPumpSelect( 0x0115u, PumpSelect );
		item = Menu_Select( menu, item, NULL );
		switch( item )
		{
		case 1:		Calibrate_Tr( PumpSelect );		break;
		case 3:		Calibrate_Pr( PumpSelect );		break;
		case 5:		Calibrate_pf( PumpSelect );		break;
		case 2:
			switch ( PumpSelect )
			{
			default:
			case PP_TSP  : 	CalibrateZeromain_TSP();	break;
			case PP_R24_A:		
			case PP_R24_B:	CalibrateZeromain_R24();  	break;
			case PP_SHI_C:		
			case PP_SHI_D:	CalibrateZeromain_SHI(); 	break;
			}
			break;
		case 4:
			switch ( PumpSelect )
			{
			default:
			case PP_TSP  :
			case PP_R24_A:
			case PP_R24_B:	CalibrateFlow_1_Point( PumpSelect );  	break;
			case PP_SHI_C:
			case PP_SHI_D:	CalibrateFlow_4_Point( PumpSelect ); 	break;
			}
			break;
		case 6:
			menu_Calibrate_Other();
			break;
		case enumSelectXCH:
			switch( configT )
			{
			case type_KB2400:		PumpSelect = (enum	enumPumpSelect) KB2400( PumpSelect ); break;
			case type_KB2400D:	PumpSelect = (enum	enumPumpSelect) KB2400D( PumpSelect ); break;
			case type_KB6120C:	PumpSelect = (enum	enumPumpSelect) KB6120C( PumpSelect ); break;
			case type_KB6120B:	PumpSelect = (enum	enumPumpSelect) KB6120B( PumpSelect ); break;
// 			case type_KB6120AD2:PumpSelect = (enum	enumPumpSelect) KB6120AD2( PumpSelect ); break;
			}
			break;	
		default:
			break;
		}
	} while( enumSelectESC != item );
	Configure.TimeoutLight = TO;
	DisplaySetTimeout( Configure.TimeoutLight );
}

void	menu_Calibrate( void )
{
	menu_Calibratex( Configure.InstrumentType );
}

/********  (C) COPYRIGHT 2015 �ൺ���˴���ӿƼ����޹�˾  **** End Of File ****/

/********************************** ����˵�� ***********************************
* �������궨->��ص�ѹ������
*******************************************************************************/
extern	FP32	get_Bat_Voltage( void );
extern	FP32	get_Bat_Current( void );

void	menu_Calibrate_Battery( void )
{
	struct	uMenu const menu[] = 
	{
		{ 0x0301u, NULL }, // "���" },
		{ 0x0800u, "��ѹ" },
		{ 0x1000u, "����" },
		{ 0x1800u, "����" },
		
	};
	enum {
		opt_exit,
		opt_voltage, opt_current, opt_threshold,
		opt_max, opt_min = opt_voltage
	};
	uint8_t	option = opt_min;
	BOOL	changed = FALSE;
	uint16_t gray  = Configure.DisplayGray;
	BOOL graychanged = FALSE;

	cls();
	Menu_Redraw( menu );
	do {
		ShowI16U( 0x080Cu, Configure.slope_Bat_Voltage, 0x0503u, NULL );
		ShowI16U( 0x100Cu, Configure.slope_Bat_Current, 0x0503u, NULL );
		ShowI16U( 0x180Cu, Configure.threshold_Current, 0x0503u, NULL );

		Menu_Item_Mask( menu, option );
		do{	
			ShowFP32( 0x0000u, get_Bat_Voltage(), 0x0603u, "V," );
			ShowFP32( 0x0014u, get_Bat_Current(), 0x0603u, "A " );
		} while( ! hitKey( 25u ));
		Menu_Item_Mask( menu, option );

		switch( getKey())
		{
		case K_DOWN:
			++option;
			if ( option >= opt_max )
			{
				option = opt_min;
			}
			break;
		case K_UP:
			if( option <= opt_min )
			{
				option = opt_max;
			}
			--option;
			break;
		
		case K_OK:
			switch( option )
			{
			case opt_voltage:
				if ( EditI16U( 0x080Cu, &Configure.slope_Bat_Voltage, 0x0503u ))
				{
					changed = TRUE;
				}
				break;
			case opt_current:
				if ( EditI16U( 0x100Cu, &Configure.slope_Bat_Current, 0x0503u ))
				{
					changed = TRUE;
				}
				break;
				
			case opt_threshold:
				if ( EditI16U( 0x180Cu, &Configure.threshold_Current, 0x0503u ))
				{
					changed = true;
				}
				break;
				
			default:
				break;
			}
			break;

		case K_ESC:
			if( ! changed )
			{
				option = opt_exit;
			}
			else
			{
				switch( MsgBox( "����궨���� ?", vbYesNoCancel + vbDefaultButton3 ))
				{
				case vbYes:
					ConfigureSave();	//	CalibrateSave();
					option = opt_exit;
					break;
				case vbNo:
					ConfigureLoad();	//	CalibrateLoad();
					option = opt_exit;
					break;
				case vbCancel:
					cls();
					Menu_Redraw( menu );
					break;		
				}
			}
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
	} while( opt_exit != option );
}

