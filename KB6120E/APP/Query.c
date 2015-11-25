/**************** (C) COPYRIGHT 2013 �ൺ���˴���ӿƼ����޹�˾ ****************
* �� �� ��: Query.C
* �� �� ��: Dean
* ��  ��  : KB6120C �������� ��¼/��ѯ/��ӡ
* ����޸�: 2013��6��5��
*********************************** �޶���¼ ***********************************
* ��  ��: 
* �޶���: 
*******************************************************************************/
#include "USBCopy.h"
#include <stdio.h>
/**
	�ļ���ӡ
*/
static	BOOL	PromptTest( void ){	return	FALSE; }

static	void	Print_File_TSP( uint16_t FileNum, struct uFile_TSP const * pFile )
{
	CHAR	sbuffer[40];
	struct	tm	t_tm;
	time_t	now;

	while( ! PrinterInit( PromptTest ))
	{
		if( vbCancel == MsgBox( "��ӡ��δ���� !", vbRetryCancel ))
		{
			return;
		}
	}
  sprintf( sbuffer, "\r\n%s��%s\r\n",szTypeIdent[Configure.InstrumentType],szNameIdent[Configure.InstrumentName] );
	PrinterPutString( sbuffer );
	PrinterPutString( "�۳�������¼" );
	sprintf( sbuffer, "�ļ�:%3u [��%2u��/��%2u��]", FileNum, pFile->run_loops, pFile->set_loops );	PrinterPutString( sbuffer );

	(void)_localtime_r ( &pFile->sample_begin, &t_tm );
	sprintf( sbuffer, "��ʼʱ��:%2d��%2d�� %02d:%02d", t_tm.tm_mon + 1, t_tm.tm_mday, t_tm.tm_hour, t_tm.tm_min );
	PrinterPutString( sbuffer );

	sprintf( sbuffer, "���ò���ʱ��: %02u:%02u", pFile->set_time / 60u, pFile->set_time % 60u );	PrinterPutString( sbuffer );
	sprintf( sbuffer, "���ò�������: %5.1f L/m", pFile->set_flow * 0.1f );							PrinterPutString( sbuffer );

	sprintf( sbuffer, "�ۼƲ���ʱ��: %02u:%02u", pFile->sum_min / 60u, pFile->sum_min % 60u ); 		PrinterPutString( sbuffer );
	sprintf( sbuffer, "�������(��): %7.1f L", pFile->vd  );										PrinterPutString( sbuffer );
	sprintf( sbuffer, "�������(��): %7.1f L", pFile->vnd );										PrinterPutString( sbuffer );
	sprintf( sbuffer, "ƽ������(��): %6.2f L/m", (FP32)pFile->vd  / pFile->sum_min );				PrinterPutString( sbuffer );
	sprintf( sbuffer, "ƽ������(��): %6.2f L/m", (FP32)pFile->vnd / pFile->sum_min );				PrinterPutString( sbuffer );

	sprintf( sbuffer, "ƽ����ǰ�¶�: %6.2f �� ", pFile->sum_tr / pFile->sum_min );					PrinterPutString( sbuffer );
	sprintf( sbuffer, "ƽ����ǰѹ��: %6.2f kPa", pFile->sum_pr / pFile->sum_min );					PrinterPutString( sbuffer );
	sprintf( sbuffer, "ƽ������ѹ��: %6.2f kPa", pFile->sum_Ba / pFile->sum_min );					PrinterPutString( sbuffer );

	now = get_Now();
	(void)_localtime_r ( &now, &t_tm );
	sprintf( sbuffer, "  == %4d/%2d/%2d %02d:%02d:%02d ==  ",
	t_tm.tm_year + 1900, t_tm.tm_mon + 1, t_tm.tm_mday, t_tm.tm_hour, t_tm.tm_min, t_tm.tm_sec );
	PrinterPutString( sbuffer );

	PrinterPutString( " " );	PrinterPutString( " " );
}

static	void	Print_File_R24( uint16_t FileNum, struct uFile_R24 const * pFile )
{
	CHAR	sbuffer[40];
	struct	tm	t_tm;
	time_t	now;

	while( ! PrinterInit( PromptTest ))
	{
		if( vbCancel == MsgBox( "��ӡ��δ���� !", vbRetryCancel ))
		{
			return;
		}
	}

	sprintf( sbuffer, "\r\n%s��%s\r\n",szTypeIdent[Configure.InstrumentType],szNameIdent[Configure.InstrumentName] );
	PrinterPutString( sbuffer );
	PrinterPutString( "�վ�������¼" );
	sprintf( sbuffer, "�ļ�:%3u [��%2u��/��%2u��]", FileNum, pFile->run_loops, pFile->set_loops );	PrinterPutString( sbuffer );

	(void)_localtime_r ( &pFile->sample_begin, &t_tm );
	sprintf( sbuffer, "��ʼʱ��:%2d��%2d�� %02d:%02d", t_tm.tm_mon + 1, t_tm.tm_mday, t_tm.tm_hour, t_tm.tm_min );
	PrinterPutString( sbuffer );

	sprintf( sbuffer, "���ò���ʱ��: A %02u:%02u",	pFile->set_time[Q_PP1] / 60u, pFile->set_time[Q_PP1] % 60u );	PrinterPutString( sbuffer );
	sprintf( sbuffer, "���ò�������: A %5.3f L/m",	pFile->set_flow[Q_PP1] * 0.001f );								PrinterPutString( sbuffer );
	sprintf( sbuffer, "�ۼƲ���ʱ��: A %02u:%02u",	pFile->sum_min[Q_PP1] / 60u, pFile->sum_min[Q_PP1] % 60u );		PrinterPutString( sbuffer );
	sprintf( sbuffer, "�������(��): A %7.1fL",		pFile->vnd[Q_PP1] );											PrinterPutString( sbuffer );
	sprintf( sbuffer, "ƽ������(��): A %6.3f L/m",	(FP32)pFile->vnd[Q_PP1] / pFile->sum_min[Q_PP1] );				PrinterPutString( sbuffer );
	sprintf( sbuffer, "�������(��): A %7.1fL",		pFile->vd[Q_PP1] );											PrinterPutString( sbuffer );
	sprintf( sbuffer, "ƽ������(��): A %6.3f L/m",	(FP32)pFile->vd[Q_PP1] / pFile->sum_min[Q_PP1] );				PrinterPutString( sbuffer );
	sprintf( sbuffer, "ƽ����ǰ�¶�: A %6.2f ��",	pFile->sum_tr[Q_PP1] / pFile->sum_min[Q_PP1] );					PrinterPutString( sbuffer );
	sprintf( sbuffer, "ƽ����ǰѹ��: A %6.2f kPa",	pFile->sum_pr[Q_PP1] / pFile->sum_min[Q_PP1] );					PrinterPutString( sbuffer );
	sprintf( sbuffer, "ƽ������ѹ��: %6.2f kPa",	pFile->sum_Ba / pFile->sum_min[Q_PP1] );						PrinterPutString( sbuffer );

	sprintf( sbuffer, "���ò���ʱ��: B %02u:%02u",	pFile->set_time[Q_PP2] / 60u, pFile->set_time[Q_PP2] % 60u );	PrinterPutString( sbuffer );
	sprintf( sbuffer, "���ò�������: B %5.3f L/m",	pFile->set_flow[Q_PP2] * 0.001f );								PrinterPutString( sbuffer );
	sprintf( sbuffer, "�ۼƲ���ʱ��: B %02u:%02u",	pFile->sum_min[Q_PP2] / 60u, pFile->sum_min[Q_PP2] % 60u );		PrinterPutString( sbuffer );
	sprintf( sbuffer, "�������(��): B %7.1fL",		pFile->vnd[Q_PP2] );											PrinterPutString( sbuffer );
	sprintf( sbuffer, "ƽ������(��): B %6.3f L/m",	(FP32)pFile->vnd[Q_PP2] / pFile->sum_min[Q_PP2] );				PrinterPutString( sbuffer );
	sprintf( sbuffer, "�������(��): B %7.1fL",		pFile->vd[Q_PP2] );											PrinterPutString( sbuffer );
	sprintf( sbuffer, "ƽ������(��): B %6.3f L/m",	(FP32)pFile->vd[Q_PP2] / pFile->sum_min[Q_PP2] );				PrinterPutString( sbuffer );
	sprintf( sbuffer, "ƽ����ǰ�¶�: B %6.2f �� ",	pFile->sum_tr[Q_PP2] / pFile->sum_min[Q_PP2] );					PrinterPutString( sbuffer );
	sprintf( sbuffer, "ƽ����ǰѹ��: B %6.2f kPa",	pFile->sum_pr[Q_PP2] / pFile->sum_min[Q_PP2] );					PrinterPutString( sbuffer );
	sprintf( sbuffer, "ƽ������ѹ��: %6.2f kPa",	pFile->sum_Ba / pFile->sum_min[Q_PP2] );						PrinterPutString( sbuffer );
	

	now = get_Now();	(void)_localtime_r ( &now, &t_tm );
	sprintf( sbuffer, "  == %4d/%2d/%2d %02d:%02d:%02d ==  ",
		t_tm.tm_year + 1900, t_tm.tm_mon + 1, t_tm.tm_mday, t_tm.tm_hour, t_tm.tm_min, t_tm.tm_sec );
	PrinterPutString( sbuffer );

	PrinterPutString( " " );	PrinterPutString( " " );
}

static	void	Print_File_SHI( uint16_t FileNum, struct uFile_SHI const * pFile )
{
	CHAR	sbuffer[40];
	struct	tm	t_tm;
	time_t	now;

	while( ! PrinterInit( PromptTest ))
	{
		if( vbCancel == MsgBox( "��ӡ��δ���� !", vbRetryCancel ))
		{
			return;
		}
	}

	sprintf( sbuffer, "\r\n%s��%s\r\n",szTypeIdent[Configure.InstrumentType],szNameIdent[Configure.InstrumentName] );
	PrinterPutString( sbuffer );
	PrinterPutString( "ʱ��������¼" );
	sprintf( sbuffer, "�ļ�:%3u [��%2u��/��%2u��]", FileNum, pFile->run_loops, pFile->set_loops );	PrinterPutString( sbuffer );

	(void)_localtime_r ( &pFile->sample_begin, &t_tm );
	sprintf( sbuffer, "��ʼʱ��:%2d��%2d�� %02d:%02d", t_tm.tm_mon + 1, t_tm.tm_mday, t_tm.tm_hour, t_tm.tm_min );
	PrinterPutString( sbuffer );

	sprintf( sbuffer, "���ò���ʱ��: C %02u:%02u",	pFile->set_time[Q_PP1] / 60u, pFile->set_time[Q_PP1] % 60u );		PrinterPutString( sbuffer );
	sprintf( sbuffer, "���ò�������: C %5.1f L/m",	pFile->set_flow[Q_PP1] * 0.1f );									PrinterPutString( sbuffer );
	sprintf( sbuffer, "�ۼƲ���ʱ��: C %02u:%02u",	pFile->sum_min[Q_PP1] / 60u, pFile->sum_min[Q_PP1] % 60u );			PrinterPutString( sbuffer );
	sprintf( sbuffer, "�������(��): C %7.1fL",		pFile->vnd[Q_PP1] );												PrinterPutString( sbuffer );
	sprintf( sbuffer, "ƽ������(��): C %6.1f L/m",	(FP32)pFile->vnd[Q_PP1] / pFile->sum_min[Q_PP1] );					PrinterPutString( sbuffer );
	sprintf( sbuffer, "�������(��): C %7.1fL",		pFile->vd[Q_PP1] );												PrinterPutString( sbuffer );
	sprintf( sbuffer, "ƽ������(��): C %6.1f L/m",	(FP32)pFile->vd[Q_PP1] / pFile->sum_min[Q_PP1] );					PrinterPutString( sbuffer );
	sprintf( sbuffer, "ƽ����ǰ�¶�: C %6.2f ��",	pFile->sum_tr[Q_PP1] / pFile->sum_min[Q_PP1] );						PrinterPutString( sbuffer );
	sprintf( sbuffer, "ƽ����ǰѹ��: C %6.2f kPa",	pFile->sum_pr[Q_PP1] / pFile->sum_min[Q_PP1] );						PrinterPutString( sbuffer );
	sprintf( sbuffer, "ƽ������ѹ��: %6.2f kPa",	pFile->sum_Ba / pFile->sum_min[Q_PP1] );							PrinterPutString( sbuffer );

	sprintf( sbuffer, "���ò���ʱ��: D %02u:%02u",	pFile->set_time[Q_PP2] / 60u, pFile->set_time[Q_PP2] % 60u );		PrinterPutString( sbuffer );
	sprintf( sbuffer, "���ò�������: D %5.1f L/m",	pFile->set_flow[Q_PP2] * 0.1f );									PrinterPutString( sbuffer );
	sprintf( sbuffer, "�ۼƲ���ʱ��: D %02u:%02u",	pFile->sum_min[Q_PP2] / 60u, pFile->sum_min[Q_PP2] % 60u );			PrinterPutString( sbuffer );
	sprintf( sbuffer, "�������(��): D %7.1fL",		pFile->vnd[Q_PP2] );												PrinterPutString( sbuffer );
	sprintf( sbuffer, "ƽ������(��): D %6.1f L/m",	(FP32)pFile->vnd[Q_PP2] / pFile->sum_min[Q_PP2] );					PrinterPutString( sbuffer );
	sprintf( sbuffer, "�������(��): D %7.1fL",		pFile->vd[Q_PP2] );												PrinterPutString( sbuffer );
	sprintf( sbuffer, "ƽ������(��): D %6.1f L/m",	(FP32)pFile->vd[Q_PP2] / pFile->sum_min[Q_PP2] );					PrinterPutString( sbuffer );
	sprintf( sbuffer, "ƽ����ǰ�¶�: D %6.2f �� ",	pFile->sum_tr[Q_PP2] / pFile->sum_min[Q_PP2] );						PrinterPutString( sbuffer );
	sprintf( sbuffer, "ƽ����ǰѹ��: D %6.2f kPa",	pFile->sum_pr[Q_PP2] / pFile->sum_min[Q_PP2] );						PrinterPutString( sbuffer );
	sprintf( sbuffer, "ƽ������ѹ��: %6.2f kPa",	pFile->sum_Ba / pFile->sum_min[Q_PP2] );							PrinterPutString( sbuffer );
	
	now = get_Now();	(void)_localtime_r ( &now, &t_tm );
	sprintf( sbuffer, "  == %4d/%2d/%2d %02d:%02d:%02d ==  ",
		t_tm.tm_year + 1900, t_tm.tm_mon + 1, t_tm.tm_mday, t_tm.tm_hour, t_tm.tm_min, t_tm.tm_sec );						PrinterPutString( sbuffer );
	PrinterPutString( " " );	PrinterPutString( " " );
}

/***/
static	void	Print_File_AIR( uint16_t FileNum, struct uFile_AIR const * pFile )
{
	CHAR	sbuffer[40];
	struct	tm	t_tm;
	time_t	now;

	while( ! PrinterInit( PromptTest ))
	{
		if( vbCancel == MsgBox( "��ӡ��δ���� !", vbRetryCancel ))
		{
			return;
		}
	}
	sprintf( sbuffer, "\r\n%s��%s\r\n",szTypeIdent[Configure.InstrumentType],szNameIdent[Configure.InstrumentName] );
	PrinterPutString( sbuffer );
	PrinterPutString( "����������¼" );
	sprintf( sbuffer, "�ļ�:%3u [��%2u��/��%2u��]", FileNum, pFile->run_loops, pFile->set_loops );	PrinterPutString( sbuffer );

	(void)_localtime_r ( &pFile->sample_begin, &t_tm );
	sprintf( sbuffer, "��ʼʱ��:%2d��%2d�� %02d:%02d", t_tm.tm_mon + 1, t_tm.tm_mday, t_tm.tm_hour, t_tm.tm_min );
	PrinterPutString( sbuffer );

	sprintf( sbuffer, "���ò���ʱ��: %02u:%02u", pFile->set_time / 60u, pFile->set_time % 60u );	PrinterPutString( sbuffer );
	sprintf( sbuffer, "���ò�������: %5.1f L/m", pFile->set_flow * 0.1f );							PrinterPutString( sbuffer );

	sprintf( sbuffer, "�ۼƲ���ʱ��: %02u:%02u", pFile->sum_min / 60u, pFile->sum_min % 60u ); 		PrinterPutString( sbuffer );
	now = get_Now();
	(void)_localtime_r ( &now, &t_tm );
	sprintf( sbuffer, "  == %4d/%2d/%2d %02d:%02d:%02d ==  ",
	t_tm.tm_year + 1900, t_tm.tm_mon + 1, t_tm.tm_mday, t_tm.tm_hour, t_tm.tm_min, t_tm.tm_sec );
	PrinterPutString( sbuffer );

	PrinterPutString( " " );	PrinterPutString( " " );
}


/************************************************************/
static void FPrintf_TSP(uint16_t FileNum, struct uFile_TSP  const * pFile)
{
	 static	struct uMenu  const  menu[] =
	{
		{ 0x0201u, "�ļ����" },
		{ 0x0C06u, "��ӡ��" },	
		{ 0x1806u, " U�� " },
	};

	uint8_t	item = 1u;
  BOOL state = FALSE;
	do
	{
		cls();
		Menu_Redraw( menu );
		SamplerTypeShow( 0x010Eu );
     
		item = Menu_Select( menu, item, NULL );
		
		switch( item )
		{
		//	�����˵��°�ȡ��������ʾ����ѹ���������¶ȵȻ�������
		case 1:
			Print_File_TSP( FileNum, pFile );
			state = TRUE;	
			break;
		case 2:		
			if( USB_PrintInit() )
			{
        USBPrint_TSP( FileNum, pFile );
				state = TRUE;			
			}
			break;
		case enumSelectESC: 
			state = TRUE;
			break;
		case enumSelectXCH: 
			break;
		}
	}while( state != TRUE );
}

/*********************************************************************/
static void FPrintf_R24(uint16_t FileNum, struct uFile_R24  const * pFile)
{
	  static	struct uMenu  const  menu[] =
	{
		{ 0x0201u, "�ļ����" },
		{ 0x0C06u, "��ӡ��" },	
		{ 0x1806u, " U�� " },
	};

	uint8_t	item = 1u;
  BOOL state = FALSE;
	do
	{
		cls();
		Menu_Redraw( menu );
		SamplerTypeShow( 0x010Eu );
     
		item = Menu_Select( menu, item, NULL );
		
		switch( item )
		{
		//	�����˵��°�ȡ��������ʾ����ѹ���������¶ȵȻ�������
		case 1:
			Print_File_R24( FileNum, pFile );
			state = TRUE;	
			break;
		case 2:		
			if( USB_PrintInit() )
			{
        USBPrint_R24( FileNum, pFile );
				state = TRUE;			
			}
			break;
		case enumSelectESC: 
			state = TRUE;
			break;
		case enumSelectXCH: 
			break;
		}
	}while( state != TRUE );
}

/***********************************************************************/
static void FPrintf_SHI(uint16_t FileNum, struct uFile_SHI  const * pFile)
{
	  static	struct uMenu  const  menu[] =
	{
		{ 0x0201u, "�ļ����" },
		{ 0x0C06u, "��ӡ��" },	
		{ 0x1806u, " U�� " },
	};

	uint8_t	item = 1u;
  BOOL state = FALSE;
	do
	{
		cls();
		Menu_Redraw( menu );
		SamplerTypeShow( 0x010Eu );
     
		item = Menu_Select( menu, item, NULL );
		
		switch( item )
		{
		//	�����˵��°�ȡ��������ʾ����ѹ���������¶ȵȻ�������
		case 1:
			Print_File_SHI( FileNum, pFile );
			state = TRUE;	
			break;
		case 2:		
			if( USB_PrintInit() )
			{
        USBPrint_SHI( FileNum, pFile );
				state = TRUE;			
			}
			break;
		case enumSelectESC: 
			state = TRUE;
			break;
		case enumSelectXCH: 
			break;
		}
	}while( state != TRUE );
}
/************************************************************************/
static void FPrintf_AIR(uint16_t FileNum, struct uFile_AIR  const * pFile)
{
	 static	struct uMenu  const  menu[] =
	{
		{ 0x0201u, "�ļ����" },
		{ 0x0C06u, "��ӡ��" },	
		{ 0x1806u, " U�� " },
	};

	uint8_t	item = 1u;
  BOOL state = FALSE;
	do
	{
		cls();
		Menu_Redraw( menu );
		SamplerTypeShow( 0x010Eu );
     
		item = Menu_Select( menu, item, NULL );
		
		switch( item )
		{
		//	�����˵��°�ȡ��������ʾ����ѹ���������¶ȵȻ�������
		case 1:
			Print_File_AIR( FileNum, pFile );
			state = TRUE;	
			break;
		case 2:		
			if( USB_PrintInit() )
			{
        USBPrint_AIR( FileNum, pFile );
				state = TRUE;			
			}
			break;
		case enumSelectESC: 
			state = TRUE;
			break;
		case enumSelectXCH: 
			break;
		}
	}while( state != TRUE );
}

/**/
/**
	�ļ���ѯ
*/
void	Query_File_TSP( void )
{
	uint16_t	FileNum;
	struct	uFile_TSP File;
	enum 
	{
		opt_exit,
		opt_tsp_1,   opt_tsp_2,  
		opt_max, opt_min = opt_tsp_1
	};
	uint8_t	option = opt_min;
	uint16_t gray  = Configure.DisplayGray;
	BOOL	graychanged = FALSE;
	FileNum = SampleSet[Q_TSP].FileNum;

	if (( FileNum < 1 ) || ( FileNum > FileNum_Max ))
	{	//	�ļ�ȫ�գ���Ҫָ FileNum �� 0 �������
		beep();
		MsgBox( " �۳��ļ�:[��]", vbOKOnly );
		return;	//	��ֹ ��ѯ
	}
  
	File_Load_TSP ( FileNum, &File );
	
	do {
		cls();	
		WBMP( 0x0290,0x0502, STROCK);
		WBMP( 0x0290,0x0514, STROCK);

		if ( 0u == File.sample_begin )
		{
			Lputs( 0x0102u, "�۳��ļ�" );	ShowI16U( 0x0114u, FileNum, 0x0300u, "[��]" );
		}
		else
		{
			Lputs( 0x0102u, "�۳��ļ�" );	ShowI16U( 0x0114u, FileNum, 0x0300u, NULL );
			switch ( option )
			{
			default:
			case opt_tsp_1:
				Lputs( 0x011Bu, "[1/2]" );
				Lputs( 0x0602u, "��ʼʱ��:" );	  ShowDATE( 0x0610u, File.sample_begin );
				Lputs( 0x0A02u, "��������:" );		ShowI16U( 0x0A16u, File.run_loops,  						0x0200u, NULL );
				Lputs( 0x0E02u, "���ô���:" );		ShowI16U( 0x0E16u, File.set_loops,   						0x0200u, NULL );
				Lputs( 0x1202u, "��   ��:" );		ShowFP32( 0x1215u, File.sum_tr / File.sum_min, 	0x0402u, "��" );
				Lputs( 0x1602u, "ѹ   ��:" );		ShowFP32( 0x1615u, File.sum_pr / File.sum_min, 	0x0402u, "kPa" );
				Lputs( 0x1A02u, "����ѹ��:" );	  ShowFP32( 0x1A15u, File.sum_Ba / File.sum_min,	0x0402u, "kPa" );
			//	Lputs( 0x0800u, "�����¶�:" );	ShowFP32( 0x0811u, File.sum_tr / File.sum_min, 0x0602u, "��" );
				break;
			case opt_tsp_2:
				Lputs( 0x011Bu, "[2/2]" );
				Lputs( 0x0602u, "��   ��:" );		ShowFP32( 0x0617u, File.vd     / File.sum_min, 0x0401u, "L/m" );
				Lputs( 0x0A02u, "��   ��:" );		ShowFP32( 0x0A17u, File.vnd    / File.sum_min, 0x0401u, "L/m" );
				Lputs( 0x0E02u, "��   ��:" );		ShowI16U( 0x0E17u, File.set_flow,              0x0401u, "L/m" );
				Lputs( 0x1202u, "�������:" );		ShowFP32( 0x1213u, File.vd,                    0x0600u, "L" );
				Lputs( 0x1602u, "������:" );		ShowFP32( 0x1613u, File.vnd,                   0x0600u, "L" );
				Lputs( 0x1A02u, "����ʱ��:" );		ShowTIME( 0x1A16u, File.sum_min  );
			//	Lputs( 0x1800u, "����ʱ��:" );	ShowTIME( 0x1816u, File.set_time );
				break;
			}
		}		
		switch ( getKey() )
		{
		case K_UP:		//	��ǰ��ʱ�������ļ�������
		{
			uint16_t	fname;
			
			if ( FileNum == 1u )
			{
				fname = 1;
				beep();
				MsgBox( "�޸����ļ�!", vbOKOnly );
			}
			else
			{
				fname = FileNum - 1u;			
			}

			File_Load_TSP ( fname, &File );
			FileNum = fname;
			if ( 0u == File.sample_begin )
			{
				beep();	//	���ļ�������Ч��
			}
		}	break;

		case K_DOWN:	//	���ʱ����µ��ļ�������
		{
			uint16_t	fname;
			
			if ( FileNum == FileNum_Max )
			{
				fname = FileNum_Max;
				beep();
				MsgBox( "�ļ�����", vbOKOnly );	
				return;
			}
			else
			{
				fname = FileNum + 1u;
			}

			File_Load_TSP ( fname, &File );
			if( fname > SampleSet[Q_TSP].FileNum )
			{
				beep();//	�������"��"������Ч����
				File_Load_TSP ( FileNum, &File );
			}
			else	
			{
				if ( 0u == File.sample_begin )
					beep();
				FileNum = fname;
			}
		}	break;
  
		case K_OK:
			if ( 0u != File.sample_begin )
			{
				FPrintf_TSP( FileNum, &File );
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
}
/************************************************************/
void	Query_File_R24( void )
{
	struct	uFile_R24	File;
	uint16_t	FileNum;
	enum 
	{
		opt_exit,
		opt_A2X_1,
		opt_A2X_A1, 
		opt_A2X_B1,  
		opt_max, opt_min = 1u
	};
	uint8_t	option = opt_min;
	uint16_t gray  = Configure.DisplayGray;
	BOOL	graychanged = FALSE;

	FileNum = SampleSet[Q_R24].FileNum;

	if (( FileNum < 1 ) || ( FileNum > FileNum_Max ))
	{
		beep();
		MsgBox( " �վ��ļ�:[��]", vbOKOnly );
		return;	//	��ֹ ��ѯ
	}

	File_Load_R24 ( FileNum, &File );
	
	do {
		cls();
		WBMP( 0x0290,0x0502, STROCK);
		WBMP( 0x0290,0x0514, STROCK);

		if ( 0u == File.sample_begin )
		{
			Lputs( 0x0102u, "�վ��ļ�" );	ShowI16U( 0x0114u, FileNum, 0x0300u, "[��]" );
		} 
		else
		{
			Lputs( 0x0102u, "�վ��ļ�" );	ShowI16U( 0x0114u, FileNum, 0x0300u, NULL );
			switch ( option )
			{
			default:
			case opt_A2X_1:
				Lputs( 0x011Bu, "[1/3]" );
				Lputs( 0x0602u, "��ʼʱ��:" );	ShowDATE( 0x0610u, File.sample_begin );
				Lputs( 0x0C02u, "����ѹ��:" );	ShowFP32( 0x0C11u, File.sum_Ba / File.sum_min[Q_PP1], 0x0602u, "kPa" );
				Lputs( 0x1202u, "��������:" );	ShowI16U( 0x1216u, File.run_loops,   0x0200u, NULL );
				Lputs( 0x1802u, "���ô���:" );	ShowI16U( 0x1816u, File.set_loops,   0x0200u, NULL );
				
				
			
				break;		
			case opt_A2X_A1:
				Lputs( 0x0110u, "A" );Lputs( 0x011Bu, "[2/3]" );
				Lputs( 0x0602u, "�� ��:" );		ShowFP32( 0x0615u, File.sum_tr[Q_PP1] / File.sum_min[Q_PP1], 	0x0402u, "��" );
				Lputs( 0x0A02u, "ѹ ��:" );		ShowFP32( 0x0A15u, File.sum_pr[Q_PP1] / File.sum_min[Q_PP1], 	0x0402u, "kPa" );
				Lputs( 0x0E02u, "�������:" );	ShowFP32( 0x0E17u, File.vnd[Q_PP1] / File.sum_min[Q_PP1], 		0x0403u, "L/m" );	
				Lputs( 0x1202u, "������:" );	ShowFP32( 0x1213u, File.vnd[Q_PP1],  													0x0602u, "L " );
				Lputs( 0x1602u, "����ʱ��:" );	ShowTIME( 0x1615u, File.sum_min[Q_PP1]  );
				Lputs( 0x1A02u, "����ʱ��:" );	ShowTIME( 0x1A15u, File.set_time[Q_PP1] );
				break;
			
			case opt_A2X_B1:
				Lputs( 0x0110u, "B" );Lputs( 0x011Bu, "[3/3]" );
				Lputs( 0x0602u, "�� ��:" );		ShowFP32( 0x0615u, File.sum_tr[Q_PP2] / File.sum_min[Q_PP2], 	0x0402u, "��" );
				Lputs( 0x0A02u, "ѹ ��:" );		ShowFP32( 0x0A15u, File.sum_pr[Q_PP2] / File.sum_min[Q_PP2], 	0x0402u, "kPa" );
				Lputs( 0x0E02u, "�������:" );	ShowFP32( 0x0E17u, File.vnd[Q_PP2] / File.sum_min[Q_PP2], 		0x0403u, "L/m" );
				Lputs( 0x1202u, "������:" );	ShowFP32( 0x1213u, File.vnd[Q_PP2],  													0x0602u, "L " );
				Lputs( 0x1602u, "����ʱ��:" );	ShowTIME( 0x1615u, File.sum_min[Q_PP2]  );
				Lputs( 0x1A02u, "����ʱ��:" );	ShowTIME( 0x1A15u, File.set_time[Q_PP2] );
				break;
			}
		}
		
		switch ( getKey())
		{
		case K_UP:		//	��ǰ��ʱ�������ļ�������
		{
			uint16_t	fname;
			
			if ( FileNum == 1u )
			{
				fname = 1;
				beep();
				MsgBox( "�޸����ļ�!", vbOKOnly );
			}
			else
			{
				fname = FileNum - 1u;			
			}

			File_Load_R24 ( fname, &File );
			FileNum = fname;
			if ( 0u == File.sample_begin )
			{
				beep();	//	���ļ�������Ч��
			}
		}	break;

		case K_DOWN:	//	���ʱ����µ��ļ�������
		{
			uint16_t	fname;
			
			if ( FileNum == FileNum_Max )
			{
				fname = FileNum_Max;
				beep();
				MsgBox( "�ļ�����", vbOKOnly );
				return;				
			}
			else
			{
				fname = FileNum + 1u;
			}

			File_Load_R24 ( fname, &File );
			if( fname > SampleSet[Q_R24].FileNum )
			{
				beep();//	�������"��"������Ч����
				File_Load_R24 ( FileNum, &File );
			}
			else	
			{
				if ( 0u == File.sample_begin )
					beep();
				FileNum = fname;
			}
		}	break;
		case K_OK:
			if ( 0u != File.sample_begin )
			{
				FPrintf_R24( FileNum, &File );
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
}
/*************************************************/
void	Query_File_SHI( void )
{
	struct	uFile_SHI	File;
	uint16_t	FileNum;
	enum 
	{
		opt_exit,
		opt_A2X_1,
		opt_A2X_A1,  
		opt_A2X_B1,
		opt_max, opt_min = 1u
	};
	uint8_t	option = opt_min;
	uint16_t gray  = Configure.DisplayGray;
	BOOL	graychanged = FALSE;

	FileNum = SampleSet[Q_SHI].FileNum;
	
	if (( FileNum < 1 ) || ( FileNum > FileNum_Max ))
	{
		beep();
		MsgBox( " ʱ���ļ�:[��]", vbOKOnly );
		return;	//	��ֹ ��ѯ
	}
	
	File_Load_SHI ( FileNum, &File );

	do {
		cls();
		WBMP( 0x0290,0x0502, STROCK);
		WBMP( 0x0290,0x0514, STROCK);
		if ( 0u == File.sample_begin )
		{
			Lputs( 0x0102u, "ʱ���ļ�" );	ShowI16U( 0x0114u, FileNum, 0x0300u, "[��]" );
		} 
		else
		{
			Lputs( 0x0102u, "ʱ���ļ�" );	ShowI16U( 0x0114u, FileNum, 0x0300u, NULL );
			switch ( option )
			{
			default:
			case opt_A2X_1:
				Lputs( 0x011Bu, "[1/3]" );
				Lputs( 0x0602u, "��ʼʱ��:" );	ShowDATE( 0x0610u, File.sample_begin );
				Lputs( 0x0C02u, "����ѹ��:" );	ShowFP32( 0x0C12u, File.sum_Ba         / File.sum_min[Q_PP1], 0x0602u, "kPa" );
				Lputs( 0x1202u, "��������:" );	ShowI16U( 0x1216u, File.run_loops,   0x0200u, NULL );
				Lputs( 0x1802u, "���ô���:" );	ShowI16U( 0x1816u, File.set_loops,   0x0200u, NULL );
				
			
				break;
			
			case opt_A2X_A1:
				Lputs( 0x0110u, "C" );Lputs( 0x011Bu, "[2/3]" );
				Lputs( 0x0602u, "��   ��:" );	ShowFP32( 0x0615u, File.sum_tr[Q_PP1] / File.sum_min[Q_PP1], 0x0402u, "��" );
				Lputs( 0x0902u, "ѹ   ��:" );	ShowFP32( 0x0915u, File.sum_pr[Q_PP1] / File.sum_min[Q_PP1], 0x0402u, "kPa" );
				Lputs( 0x0C02u, "�������:" );	ShowFP32( 0x0C17u, File.vnd [Q_PP1]   / File.sum_min[Q_PP1], 0x0403u, "L/m" );
				Lputs( 0x0F02u, "��������:" );	ShowI16U( 0x0F17u, File.set_flow[Q_PP1] * 100,               0x0403u, "L/m" );
				Lputs( 0x1202u, "��   ��:" );	ShowFP32( 0x1213u, File.vnd[Q_PP1],                          0x0602u, "L" );
				Lputs( 0x1502u, "����ʱ��:" );	ShowTIME( 0x1515u, File.sum_min[Q_PP1]  );
				Lputs( 0x1802u, "����ʱ��:" );	ShowTIME( 0x1815u, File.set_time[Q_PP1] );
				break;

			case opt_A2X_B1:
				Lputs( 0x0110u, "D" );Lputs( 0x011Bu, "[3/3]" );
				Lputs( 0x0602u, "��   ��:" );	ShowFP32( 0x0615u, File.sum_tr[Q_PP2] / File.sum_min[Q_PP2], 0x0402u, "��" );
				Lputs( 0x0902u, "ѹ   ��:" );	ShowFP32( 0x0915u, File.sum_pr[Q_PP2] / File.sum_min[Q_PP2], 0x0402u, "kPa" );	
				Lputs( 0x0C02u, "�������:" );	ShowFP32( 0x0C17u, File.vnd [Q_PP2]   / File.sum_min[Q_PP2], 0x0403u, "L/m" );
				Lputs( 0x0F02u, "��������:" );	ShowI16U( 0x0F17u, File.set_flow[Q_PP2] * 100,               0x0403u, "L/m" );
				Lputs( 0x1202u, "��   ��:" );	ShowFP32( 0x1213u, File.vnd[Q_PP2],                          0x0602u, "L" );
				Lputs( 0x1502u, "����ʱ��:" );	ShowTIME( 0x1515u, File.sum_min[Q_PP2]  );
				Lputs( 0x1802u, "����ʱ��:" );	ShowTIME( 0x1815u, File.set_time[Q_PP2] );
				break;
			}
		}
		
		switch ( getKey())
		{
		case K_UP:		//	��ǰ��ʱ�������ļ�������
		{
			uint16_t	fname;
			
			if ( FileNum == 1u )
			{
				fname = 1;
				beep();
				MsgBox( "�޸����ļ�!", vbOKOnly );
			}
			else
			{
				fname = FileNum - 1u;			
			}

			File_Load_SHI ( fname, &File );
			FileNum = fname;
			if ( 0u == File.sample_begin )
			{
				beep();	//	���ļ�������Ч��
			}
		}	break;

		case K_DOWN:	//	���ʱ����µ��ļ�������
		{
			uint16_t	fname;
			
			if ( FileNum == FileNum_Max )
			{
				fname = FileNum_Max;
				beep();
				MsgBox( "�ļ�����", vbOKOnly );
				return;
			}
			else
			{
				fname = FileNum + 1u;
			}

			File_Load_SHI ( fname, &File );
			if( fname > SampleSet[Q_SHI].FileNum )
			{
				beep();//	�������"��"������Ч����
				File_Load_SHI ( FileNum, &File );
			}
			else	
			{
				if ( 0u == File.sample_begin )
					beep();
				FileNum = fname;
			}
		}	break;


		case K_OK:
			if ( 0u != File.sample_begin )
			{
          FPrintf_SHI( FileNum, &File );
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
}
/*************************************************/
void	Query_File_AIR( void )
{
	uint16_t	FileNum;
	struct	uFile_AIR	File;
	enum 
	{
		opt_exit,
		opt_air_1, 
		opt_max, opt_min = 1u
	};
	uint8_t	option = opt_min;
	uint16_t gray  = Configure.DisplayGray;
	BOOL	graychanged = FALSE;

	FileNum = SampleSet[Q_AIR].FileNum;
	if (( FileNum < 1 ) || ( FileNum > FileNum_Max ))
	{
		beep();
		MsgBox( " �����ļ�:[��]", vbOKOnly );
		return;	//	��ֹ ��ѯ
	}
	
	File_Load_AIR ( FileNum, &File );

	do {
		cls();
		WBMP( 0x0290,0x0502, STROCK);
		WBMP( 0x0290,0x0514, STROCK);
		
		if ( 0u == File.sample_begin )
		{
			Lputs( 0x0102u, "�����ļ�" );	ShowI16U( 0x0114u, FileNum, 0x0C00u, "[��]" );
		} 
		else
		{
			Lputs( 0x0102u, "�����ļ�" );	ShowI16U( 0x0114u, FileNum, 0x0C00u, NULL );
			switch ( option )
			{
			case opt_air_1:
				Lputs( 0x0800u, "��ʼʱ��:" );	  ShowDATE( 0x080Fu, File.sample_begin );
				Lputs( 0x0C00u, "��������:" );	ShowI16U( 0x0C16u, File.run_loops,   0x0200u, NULL );
				Lputs( 0x1000u, "���ô���:" );	ShowI16U( 0x1016u, File.set_loops,   0x0200u, NULL );
				Lputs( 0x1400u, "����ʱ��:" );	ShowTIME( 0x1416u, File.sum_min  );
				Lputs( 0x1800u, "����ʱ��:" );	ShowTIME( 0x1816u, File.set_time );
				break;   
			default:
				break;
			}	
		}
		
		switch ( getKey())
		{
		case K_UP:		//	��ǰ��ʱ�������ļ�������
		{
			uint16_t	fname;
			
			if ( FileNum == 1u )
			{
				fname = 1;
				beep();
				MsgBox( "�޸����ļ�!", vbOKOnly );
			}
			else
			{
				fname = FileNum - 1u;			
			}

			File_Load_AIR ( fname, &File );
			FileNum = fname;
			if ( 0u == File.sample_begin )
			{
				beep();	//	���ļ�������Ч��
			}
		}	break;

		case K_DOWN:	//	���ʱ����µ��ļ�������
		{
			uint16_t	fname;
			
			if ( FileNum == FileNum_Max )
			{
				fname = FileNum_Max;
				beep();
				MsgBox( "�ļ�����", vbOKOnly );	
				return;
			}
			else
			{
				fname = FileNum + 1u;
			}

			File_Load_AIR ( fname, &File );
			if( fname > SampleSet[Q_AIR].FileNum )
			{
				beep();//	�������"��"������Ч����
				File_Load_AIR ( FileNum, &File );
			}
			else	
			{
				if ( 0u == File.sample_begin )
					beep();
				FileNum = fname;
			}
		}	break;

		case K_OK:
			if ( 0u != File.sample_begin )
			{
				FPrintf_AIR( FileNum, &File);
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
}

/********************************** ����˵�� ***********************************
: ���ѹ��ֵ��¼�Ĳ�ѯ
*******************************************************************************/
//	static	void	QueryLog_TSP( void )
//	{
//		enum {
//			opt_exit, opt_standard
//		};
//		uint8_t	option = opt_standard;
//		struct	uFile_TSP	File;
//		uint16_t	FileNum = SampleSet[Q_TSP].FileNum;

//		cls();
//		do {
//			File.Load( FileNum );	// File_Load( FileNum, &File );
//			Lputs( 0x0000u, "�۳��ļ���¼:" );	ShowI16U( 0x000Cu, FileNum, 0x0300u, NULL );
//			Lputs( 0x0800u, "ʱ��:" );		ShowDATE( 0x080Cu, File.sample_begin );
//			Lputs( 0x1000u, "ѹ��:" );		ShowFP32( 0x1011u, File.max_pr, 0x0602u, "kPa" );

//			switch ( getKey())
//			{
//			case K_UP:
//				++FileNum;
//				if ( FileNum >= ( FileNum_Max + 1u ))
//				{
//					FileNum = 1u;
//				}
//				break;
//			case K_DOWN:
//				if ( FileNum <= 1u )
//				{
//					FileNum = ( FileNum_Max + 1u );
//				}
//				--FileNum;;
//				break;

//			case K_ESC:
//				option = opt_exit;
//				break;

//			default:
//				break;
//			}
//		} while( opt_exit != option );
//	}

//	static	void	QueryLog_R24( void )
//	{
//		enum {
//			opt_exit, opt_standard
//		} option = opt_standard;
//		struct	uFile_R24	File;
//		uint16_t	FileNum = SampleSet[Q_R24].FileNum;

//		cls();
//		do {
//			File_Load( FileNum, &File );
//			Lputs( 0x0000u, "�վ��ļ���¼:" );	ShowI16U( 0x000Cu, FileNum, 0x0300u, NULL );
//			Lputs( 0x0800u, "ʱ��:" );		ShowDATE( 0x080Cu, File.sample_begin );
//			Lputs( 0x1000u, "ѹ��A:" );		ShowFP32( 0x1011u, File.max_pr[Q_PP1], 0x0602u, "kPa" );
//			Lputs( 0x1800u, "ѹ��B:" );		ShowFP32( 0x0607u, File.max_pr[Q_PP2], 0x0602u, "kPa" );

//			switch ( getKey())
//			{
//			case K_UP:
//				++FileNum;
//				if ( FileNum >= ( FileNum_Max + 1u ))
//				{
//					FileNum = 1u;
//				}
//				break;
//			case K_DOWN:
//				if ( FileNum <= 1u )
//				{
//					FileNum = ( FileNum_Max + 1u );
//				}
//				--FileNum;;
//				break;

//			case K_ESC:
//				option = opt_exit;
//				break;

//			default:
//				break;
//			}
//		} while( opt_exit != option );
//	}

//	static	void	QueryLog_SHI( void )
//	{
//		enum {
//			opt_exit, opt_standard
//		} option = opt_standard;
//		struct	uFile_SHI	File;
//		uint16_t	FileNum = SampleSet[Q_SHI].FileNum;

//		cls();
//		do {
//			File_Load( FileNum, &File );
//			Lputs( 0x0000u, "ʱ���ļ���¼:" );	ShowI16U( 0x000Cu, FileNum, 0x0300u, NULL );
//			Lputs( 0x0800u, "ʱ��:" );		ShowDATE( 0x080Cu, File.sample_begin );
//			Lputs( 0x1000u, "ѹ��C:" );		ShowFP32( 0x1011u, File.max_pr[Q_PP1], 0x0602u, "kPa" );
//			Lputs( 0x1800u, "ѹ��D:" );		ShowFP32( 0x0607u, File.max_pr[Q_PP2], 0x0602u, "kPa" );

//			switch ( getKey())
//			{
//			case K_UP:
//				++FileNum;
//				if ( FileNum >= ( FileNum_Max + 1u ))
//				{
//					FileNum = 1u;
//				}
//				break;
//			case K_DOWN:
//				if ( FileNum <= 1u )
//				{
//					FileNum = ( FileNum_Max + 1u );
//				}
//				--FileNum;;
//				break;

//			case K_ESC:
//				option = opt_exit;
//				break;

//			default:
//				break;
//			}
//		} while( opt_exit != option );
//	}

/********************************** ����˵�� ***********************************
: ���ػ���־��¼�Ĳ�ѯ
*******************************************************************************/
extern volatile	uint16_t	PowerLogIndex ;

void	PowerLog_Query( void )
{
	enum
	{
		opt_exit, opt_standard
	};
	uint8_t	option = opt_standard;
	uint16_t	PLindex = 0u;
	uint16_t gray  = Configure.DisplayGray;
	BOOL	graychanged = FALSE;	
	struct	uPowerLog Plog;

	CHAR sbuffer[20] = {0};
	do {
		cls();
		Lputs( 0x0102u, "���ػ���¼" );
		WBMP( 0x0290,0x0502, STROCK);
		WBMP( 0x0290,0x0514, STROCK);		
		sprintf( sbuffer, "���:   [%1u/%1u]",PLindex + 1 ,PowerLogIndex + 1 ); 
		Lputs( 0x0802u, sbuffer );
		PowerLogLoad( PLindex, &Plog );	
		Lputs( 0x1002u, "����:" );	ShowDATE( 0x100Cu, Plog.boot );
		Lputs( 0x1802u, "�ػ�:" );	if ( PLindex ){  ShowDATE( 0x180Cu, Plog.shut ); }
		if( PowerLogIndex < PowerLogIndex_Max )
		{
			switch ( getKey())
			{
			case K_UP:
				if ( PLindex <  PowerLogIndex )
				{
					++PLindex;
				}
				else
				{
					beep();
					MsgBox( "�޸����¼!", vbOKOnly );
				}
				break;

			case K_DOWN:
				if ( PLindex > 0u )
				{
					--PLindex;
				}
				break;

			case K_OK:
				//$TODO:	RecPower_Print( Log, index );
			
				if ( ! releaseKey( K_OK, 200u ))
				{
					beep();
					
					if ( vbYes == MsgBox( "��տ��ػ���¼?", vbYesNo | vbDefaultButton2 ))
					{
						PowerLog_Clean();						
						PLindex = 0u;
					}
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

		}
		else
		{
			beep();
			MsgBox("�ļ�����",vbOKOnly);
			return;
		}
	} while( opt_exit != option );
}

void	menu_SampleQuery( void )	//	enum enumSamplerSelect SamplerSelect )
{
	switch ( SamplerSelect )
	{
	case Q_TSP:	Query_File_TSP();	break;
	case Q_R24:	Query_File_R24();	break;
	case Q_SHI:	Query_File_SHI();	break;
	case Q_AIR:	Query_File_AIR();	break;
	}
}

/********  (C) COPYRIGHT 2013 �ൺ���˴���ӿƼ����޹�˾  **** End Of File ****/
