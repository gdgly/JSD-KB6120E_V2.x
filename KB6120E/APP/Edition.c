/**************** (C) COPYRIGHT 2014 �ൺ���˴���ӿƼ����޹�˾ ****************
* �� �� ��: ConfigureEx.C
* �� �� ��: ����(2014��4��8��)
* ��  ��  : KB-6120E ���塢��ʾ�汾��Ϣ
* ����޸�: 2014��4��8��
*********************************** �޶���¼ ***********************************
* ��  ��: 
* �޶���: 
*******************************************************************************/
#include "AppDEF.H"
#include "BMP.H"

/********************************** ����˵�� ***********************************
*  ���������ͺ���ʾ�汾��Ϣ
*  ����������ԱҪ�󣬿��ܻ�ĳ������������ƣ����߸ɴ಻��ʾ��
*******************************************************************************/
CHAR  const * const ExNameIdent1[] =
{
  "/* �� �� �� �� �� */",
  " �� �� �� �� �� ",
//  ...  
};
CHAR  const * const ExNameIdent2[] =
{
  "/* �� �� �� �� �� */",
  "�� �� �� �� �� �� �� ˾",
//  ...  
};
CHAR  const * const EditionNum[] =
{
   "KB6120E V1.20",	//	�ڲ��汾
	__DATE__" V1.00",	//	��ʾ�汾
};
static	void	ShowEdition_NoName( void )
{
	cls();
  Lputs( 0x0809u, szNameIdent[Configure.InstrumentName] );
	Lputs( 0x0F03u, EditionNum[1] );
	Lputs( 0x1509u, "���:" );	ShowFP32( 0x1512u, Configure.ExNum, 0x0700u, NULL );
}
static	void	ShowEdition_HasName( void )
{
  cls();
 	Lputs( 0x0109u, szNameIdent [Configure.InstrumentName] );
	Lputs( 0x0607u, ExNameIdent1[Configure.ExName] );
	Lputs( 0x0C01u, ExNameIdent2[Configure.ExName] );
	Lputs( 0x1203u, EditionNum[1] );
	Lputs( 0x1809u, "���:" );ShowFP32( 0x1812u, Configure.ExNum, 0x0700u, NULL );
}

//  ...
void	ShowEdition( void )
{
  switch( Configure.ExName )
  {
  case  (enum enumExNameIdent) 0: 
    ShowEdition_NoName(); 
    break;
  default: 
    ShowEdition_HasName(); 
    break;
  }
}
void	Animation( void )
{
	switch( Configure.ExName )
  {
	case  (enum enumExNameIdent) 1: 
    WALL( WALL2 );
    break;
  default:
		WALL( WALL2 );	
    break;
	}
}
	
/********************************** ����˵�� ***********************************
*  ��ʾ����汾 ���������ͺ���ʾ�汾��Ϣ
*******************************************************************************/
void	ShowEdition_Inner( void )
{
	cls();
	Lputs( 0x0308u, szNameIdent[Configure.InstrumentName] );
	Lputs( 0x0908u, __DATE__ );
	Lputs( 0x0F0Au, __TIME__ );
	Lputs( 0x1506u, EditionNum[0] );

}

/********************************** ���ݶ��� ***********************************
*  ���õ����������б�
*******************************************************************************/
CHAR  const * const szTypeIdent[] =
{
		"KB-6120C",
		"KB-6120B",
		"KB-2400D",
		"KB-2400 ",   

//   "KB-6120BD",
//    "KB-6120BH",
//    "KB-6120C",
//    "KB-2400",
};

CHAR  const * const szNameIdent[] =
{
	"�����ۺϲ�����  ",
	"�ۺϴ���������  ",
	"����������������",
	"���ܴ�����������",
	"���º���������  ",
	"���ܺ���������  ",
};
#define	T_KB6120C
// #define	T_KB6120B
// #define	T_KB2400D
// #define	T_KB2400
static	void	ConfigureLoad_KB6120C( void )
{
#ifdef	T_KB6120C
	Configure.InstrumentType = type_KB6120C;//6120C
	
	Configure.PumpType[PP_TSP  ] = enumOrifice_1;	Configure.SetFlow[PP_TSP  ]  = 1000u;	//	�۳�  �������� 100.0 L/m
	Configure.PumpType[PP_R24_A] = enumOrifice_1;	Configure.SetFlow[PP_R24_A]  =  200u;	//	�վ�1 �������� 0.200 L/m
	Configure.PumpType[PP_R24_B] = enumOrifice_1;	Configure.SetFlow[PP_R24_B]  =  200u;	//	�վ�2 �������� 0.200 L/m
	Configure.PumpType[PP_SHI_C] = enumOrifice_1; Configure.SetFlow[PP_SHI_C]  =    5u;	//	ʱ��1 �������� 0.5 L/m
	Configure.PumpType[PP_SHI_D] = enumOrifice_1; Configure.SetFlow[PP_SHI_D]  =    5u;	//	ʱ��2 �������� 0.5 L/m
	Configure.PumpType[PP_AIR  ] = enumPumpNone;	Configure.SetFlow[PP_AIR  ]  =  500u;	//	���� ���� 0.5 L/m
	Configure.AIRSetFlow[Q_PP1] = 5;
	Configure.AIRSetFlow[Q_PP2] = 5;
	Configure.HeaterType = enumHCBoxOnly;	//	ֻ�к�����
	Configure.Heater_SetTemp = 300u;		//	�����������¶� 30.0 ��
	Configure.Heater_SW = FALSE;         //����������	
	
	Configure.HCBox_SetMode = MD_Shut;		//	���������ģʽ [�ر�]
	Configure.HCBox_SetTemp = 240u;			//	����������¶� 24.0 ��
	     
	Configure.SetTstd = enum_293K;			//	��������Ķ����¶� 
	
	Configure.Mothed_Delay = enumByDelay;	//	������ʼʱ�䷽ʽ
	Configure.Mothed_Sample = enumBySet;	//	����ʱ����Ʒ�ʽ

	Configure.Mothed_Ba = enumMeasureBa;	//	����ѹ����ȡ��ʽ
	Configure.set_Ba    = 10133u;			//	�����û�������ѹ

	Configure.DisplayGray  = 2000u;	//	��ʾ�Ҷ�����
	Configure.DisplayLight = 50u;	//	��ʾ��������
	Configure.TimeoutLight = 2u;	//	������ʱʱ��
	
	Configure.slope_Bat_Voltage = 1000;
	Configure.slope_Bat_Current = 1000;
	Configure.threshold_Current = 100;
	
	Configure.shouldCalcPbv = 0;		//	����ˮ��ѹ�Ƿ������㡣
	
	Configure.Battery_SW = FALSE;    //����Ƿ����
	Configure.ExName = Name_JSD;
	Configure.Password = 633817;
	
#endif
}
	
static	void	ConfigureLoad_KB6120B( void )
{
#ifdef	T_KB6120B
	Configure.InstrumentType = type_KB6120B; // 6120B

	Configure.PumpType[PP_TSP  ] = enumOrifice_1;	Configure.SetFlow[PP_TSP  ]  = 1000u;	//	�۳�  �������� 100.0 L/m
	Configure.PumpType[PP_R24_A] = enumPumpNone;	Configure.SetFlow[PP_R24_A]  =  200u;	//	�վ�1 �������� 0.200 L/m
	Configure.PumpType[PP_R24_B] = enumPumpNone;	Configure.SetFlow[PP_R24_B]  =  200u;	//	�վ�2 �������� 0.200 L/m
	Configure.PumpType[PP_SHI_C] = enumOrifice_1;	Configure.SetFlow[PP_SHI_C]  =    5u;	//	ʱ��1 �������� 0.5 L/m
	Configure.PumpType[PP_SHI_D] = enumOrifice_1;	Configure.SetFlow[PP_SHI_D]  =    5u;	//	ʱ��2 �������� 0.5 L/m
	Configure.PumpType[PP_AIR  ] = enumPumpNone;	Configure.SetFlow[PP_AIR  ]  =  500u;	//	���� ���� 0.5 L/m
	Configure.AIRSetFlow[Q_PP1] = 5;
	Configure.AIRSetFlow[Q_PP2] = 5;
	Configure.HeaterType = enumHCBoxOnly;	//	ֻ�к�����
	Configure.Heater_SetTemp = 300u;		//	�����������¶� 30.0 ��
	Configure.Heater_SW = FALSE;          // ������������
	
	Configure.HCBox_SetMode = MD_Shut;		//	���������ģʽ [�ر�]
	Configure.HCBox_SetTemp = 240u;			//	����������¶� 24.0 ��

	Configure.SetTstd = enum_293K;			//	��������Ķ����¶� 
	
	Configure.Mothed_Delay = enumByDelay;	//	������ʼʱ�䷽ʽ
	Configure.Mothed_Sample = enumBySet;	//	����ʱ����Ʒ�ʽ

	Configure.Mothed_Ba = enumMeasureBa;	//	����ѹ����ȡ��ʽ
	Configure.set_Ba    = 10133u;			//	�����û�������ѹ

	Configure.DisplayGray  = 2000u;	//	��ʾ�Ҷ�����
	Configure.DisplayLight = 50u;	//	��ʾ��������
	Configure.TimeoutLight = 2u;	//	������ʱʱ��
		
	Configure.shouldCalcPbv = 0;		//	����ˮ��ѹ�Ƿ������㡣

	Configure.Battery_SW = FALSE;    //����Ƿ����
// 	Configure.ExNum = 1501000;			 //�������
  Configure.ExName = Name_JSD;
	Configure.Password = 633817;

#endif
}

static	void	ConfigureLoad_KB2400D( void )
{
#ifdef	T_KB2400D
	Configure.InstrumentType = type_KB2400D;//2400D
	
	Configure.PumpType[PP_TSP  ] = enumPumpNone;	Configure.SetFlow[PP_TSP  ]  = 1000u;	//	�۳� �������� 100.0 L/m
	Configure.PumpType[PP_R24_A] = enumOrifice_1;	Configure.SetFlow[PP_R24_A]  =  200u;	//	�վ�1�������� 0.200 L/m
	Configure.PumpType[PP_R24_B] = enumOrifice_1;	Configure.SetFlow[PP_R24_B]  =  200u;	//	�վ�2�������� 0.200 L/m
	Configure.PumpType[PP_SHI_C] = enumOrifice_1;	Configure.SetFlow[PP_SHI_C]  =    5u;	//	ʱ��1�������� 0.5 L/m
	Configure.PumpType[PP_SHI_D] = enumOrifice_1;	Configure.SetFlow[PP_SHI_D]  =    5u;	//	ʱ��2�������� 0.5 L/m
	Configure.PumpType[PP_AIR  ] = enumPumpNone;	Configure.SetFlow[PP_AIR  ]  =  500u;	//	���� ���� 0.5 L/m
	Configure.AIRSetFlow[Q_PP1] = 5;
	Configure.AIRSetFlow[Q_PP2] = 5;
	Configure.HeaterType = enumHCBoxOnly;	//	ֻ�к�����
	Configure.Heater_SetTemp = 300u;		//	�����������¶� 30.0 ��
	Configure.Heater_SW = FALSE;          // ������������
	
	Configure.HCBox_SetMode = MD_Shut;		//	���������ģʽ [�ر�]
	Configure.HCBox_SetTemp = 240u;			//	����������¶� 24.0 ��

	Configure.SetTstd = enum_293K;			//	��������Ķ����¶� 
	
	Configure.Mothed_Delay = enumByDelay;	//	������ʼʱ�䷽ʽ
	Configure.Mothed_Sample = enumBySet;	//	����ʱ����Ʒ�ʽ

	Configure.Mothed_Ba = enumMeasureBa;	//	����ѹ����ȡ��ʽ
	Configure.set_Ba    = 10133u;			//	�����û�������ѹ

	Configure.DisplayGray  = 2000u;	//	��ʾ�Ҷ�����
	Configure.DisplayLight = 50u;	//	��ʾ��������
	Configure.TimeoutLight = 2u;	//	������ʱʱ��
	
	Configure.Battery_SW = FALSE;    //����Ƿ����
// 	Configure.ExNum = 1501000;			 //�������
  Configure.ExName = Name_JSD;
	Configure.Password = 633817;
	
#endif
}

static	void	ConfigureLoad_KB2400( void )
{
#ifdef	T_KB2400
	Configure.InstrumentType = type_KB2400;//2400
	
	Configure.PumpType[PP_TSP  ] = enumPumpNone;	Configure.SetFlow[PP_TSP  ]  = 1000u;	//	�۳� �������� 100.0 L/m
	Configure.PumpType[PP_R24_A] = enumPumpNone;	Configure.SetFlow[PP_R24_A]  =  200u;	//	�վ�1�������� 0.200 L/m
	Configure.PumpType[PP_R24_B] = enumPumpNone;	Configure.SetFlow[PP_R24_B]  =  200u;	//	�վ�2�������� 0.200 L/m
	Configure.PumpType[PP_SHI_C] = enumOrifice_1;	Configure.SetFlow[PP_SHI_C]  =    5u;	//	ʱ��1�������� 0.5 L/m
	Configure.PumpType[PP_SHI_D] = enumOrifice_1;	Configure.SetFlow[PP_SHI_D]  =    5u;	//	ʱ��2�������� 0.5 L/m
	Configure.PumpType[PP_AIR  ] = enumPumpNone;	Configure.SetFlow[PP_AIR  ]  =  500u;	//	���� ���� 0.5 L/m
	Configure.AIRSetFlow[Q_PP1] = 5;
	Configure.AIRSetFlow[Q_PP2] = 5;
	Configure.HeaterType = enumHCBoxOnly;	//	ֻ�к�����
	Configure.Heater_SetTemp = 300u;		//	�����������¶� 30.0 ��
	Configure.Heater_SW = FALSE;          // ������������
	
	Configure.HCBox_SetMode = MD_Shut;		//	���������ģʽ [�ر�]
	Configure.HCBox_SetTemp = 240u;			//	����������¶� 24.0 ��

	Configure.SetTstd = enum_293K;			//	��������Ķ����¶� 
	
	Configure.Mothed_Delay = enumByDelay;	//	������ʼʱ�䷽ʽ
	Configure.Mothed_Sample = enumBySet;	//	����ʱ����Ʒ�ʽ

	Configure.Mothed_Ba = enumMeasureBa;	//	����ѹ����ȡ��ʽ
	Configure.set_Ba    = 10133u;			//	�����û�������ѹ

	Configure.DisplayGray  = 2000u;	//	��ʾ�Ҷ�����
	Configure.DisplayLight = 50u;	//	��ʾ��������
	Configure.TimeoutLight = 2u;	//	������ʱʱ��
	
	Configure.Battery_SW = FALSE;    //����Ƿ����
// 	Configure.ExNum = 1501000;			 //�������
  Configure.ExName = Name_JSD;
	Configure.Password = 633817;
	
#endif
}

// static	void	ConfigureLoad_KB6120AD2( void )
// {
// 	Configure.InstrumentType = type_KB6120AD2;

// 	Configure.PumpType[PP_TSP  ] = enumOrifice_1;	Configure.SetFlow[PP_TSP  ]  = 1000u;	//	�۳�  �������� 100.0 L/m
// 	Configure.PumpType[PP_R24_A] = enumPumpNone;	Configure.SetFlow[PP_R24_A]  =  200u;	//	�վ�1 �������� 0.200 L/m
// 	Configure.PumpType[PP_R24_B] = enumPumpNone;	Configure.SetFlow[PP_R24_B]  =  200u;	//	�վ�2 �������� 0.200 L/m
// 	Configure.PumpType[PP_SHI_C] = enumOrifice_1;	Configure.SetFlow[PP_SHI_C]  =    5u;	//	ʱ��1 �������� 0.5 L/m
// 	Configure.PumpType[PP_SHI_D] = enumOrifice_1;	Configure.SetFlow[PP_SHI_D]  =    5u;	//	ʱ��2 �������� 0.5 L/m
// 	Configure.PumpType[PP_AIR  ] = enumPumpNone;	Configure.SetFlow[PP_AIR  ]  =  500u;	//	���� ���� 0.5 L/m

// 	Configure.HeaterType = enumHeaterOnly;	//	ֻ�к�����
// 	Configure.Heater_SetTemp = 300u;		//	�����������¶� 30.0 ��
// 	Configure.Heater_SW = TRUE;          // ������������
// 	
// 	Configure.HCBox_SetMode = MD_Shut;		//	���������ģʽ [�ر�]
// 	Configure.HCBox_SetTemp = 240u;			//	����������¶� 24.0 ��

// 	Configure.SetTstd = enum_293K;			//	��������Ķ����¶� 
// 	
// 	Configure.Mothed_Delay = enumByDelay;	//	������ʼʱ�䷽ʽ
// 	Configure.Mothed_Sample = enumBySet;	//	����ʱ����Ʒ�ʽ

// 	Configure.Mothed_Ba = enumMeasureBa;	//	����ѹ����ȡ��ʽ
// 	Configure.set_Ba    = 10133u;			//	�����û�������ѹ

// 	Configure.DisplayGray  = 1900u;	//	��ʾ�Ҷ�����
// 	Configure.DisplayLight = 52u;	//	��ʾ��������
// 	Configure.TimeoutLight = 2u;	//	������ʱʱ��
// 		
// 	Configure.shouldCalcPbv = 0;		//	����ˮ��ѹ�Ƿ������㡣
// 	
// 	Configure.Battery_SW = FALSE;    //����Ƿ����
// 	Configure.ExNum = 1501000;			 //�������
// }
uint8_t KB2400D( enum enumPumpSelect PumpSelect )
{
	switch ( PumpSelect )
	{
	default:
	case PP_TSP  :
	case PP_R24_A:	PumpSelect = PP_R24_B;	break;
	case PP_R24_B:	PumpSelect = PP_SHI_C;	break;
	case PP_SHI_C:	PumpSelect = PP_SHI_D;	break;
	case PP_SHI_D:	PumpSelect = PP_R24_A;	break;
	}	
	return  PumpSelect;
}
uint8_t KB2400( enum enumPumpSelect PumpSelect )
{
	switch ( PumpSelect )
	{
	default:
	case PP_TSP  :
	case PP_R24_A:	 
	case PP_R24_B:
	case PP_SHI_C:	PumpSelect = PP_SHI_D;	break;
	case PP_SHI_D:	PumpSelect = PP_SHI_C;	break;
	}	
	return  PumpSelect;
}
// uint8_t KB6120AD2( enum enumPumpSelect PumpSelect )
// {
// 	switch ( PumpSelect )
// 	{
// 	default:
// 	case PP_TSP  :
// 	case PP_R24_A:	 
// 	case PP_R24_B:	PumpSelect = PP_SHI_C;	break;
// 	case PP_SHI_C:	PumpSelect = PP_SHI_D;	break;
// 	case PP_SHI_D:	PumpSelect = PP_TSP;		break;
// 	}	
// 	return  PumpSelect;
// }
uint8_t KB6120C( enum enumPumpSelect PumpSelect )
{
	switch ( PumpSelect )
	{
	default:
	case PP_TSP  :	PumpSelect = PP_R24_A;	break;
	case PP_R24_A:	PumpSelect = PP_R24_B;	break;
	case PP_R24_B:	PumpSelect = PP_SHI_C;	break;
	case PP_SHI_C:	PumpSelect = PP_SHI_D;	break;
	case PP_SHI_D:	PumpSelect = PP_TSP;		break;
	}	
	return PumpSelect;
}
uint8_t KB6120B( enum enumPumpSelect PumpSelect )
{
	switch ( PumpSelect )
	{
	default:
	case PP_R24_A:	 
	case PP_R24_B:
	case PP_TSP  :	PumpSelect = PP_SHI_C;	break;
	case PP_SHI_C:	PumpSelect = PP_SHI_D;	break;
	case PP_SHI_D:	PumpSelect = PP_TSP;		break;
	}	
	return PumpSelect;
}

/********************************** ����˵�� ***********************************
* 				�ð�װ���
*******************************************************************************/
CHAR  const * const Pump[]=
{
	"�۳��� ",	//0
	"�վ�A",	//1
	"�վ�B",	//2
	"ʱ��C",	//3
	"ʱ��D",	//4
	"������",	//5
	"������"		//6
}; 
CHAR  const * const Type[]=
{
	"[K-100L]",	//0
	"[K-1.��]",	//1
	"[1L�װ�]",	//2
	"[2L�װ�]",	//3
	"[1-����]",	//4
	"[2-˫��]",	//5
	"[������]",	//6
	"[������]",	//7
	"[ȫ��װ]" 	//8
};
CHAR  PumpC[PP_Max+1];
CHAR  TypeC[PP_Max+1];
static	void	PumpConfigure( void )
{
	enum 
	{
		opt_exit,
		opt_tsp_1,   opt_tsp_2,   opt_tsp_3,
		opt_max, opt_min = opt_tsp_1
	};
	uint16_t gray  = Configure.DisplayGray;
	BOOL	graychanged = FALSE;
	uint8_t opt_m;
	uint8_t	option = opt_min;
	uint16_t dispchar [6] ={ 0x0602u, 0x0A02u, 0x0E02u, 0x1202u, 0x1602u, 0x1A02u };
	uint16_t dispchar2[6] ={ 0x060Bu, 0x0A0Bu, 0x0E0Bu, 0x120Bu, 0x160Bu, 0x1A0Bu };
	uint8_t i,imax;
		
	do {
		imax = 
		i    = 0;
		ConfigureLoad();
		if( Configure.PumpType[PP_TSP] != enumPumpNone )
		{	
			switch ( Configure.PumpType[PP_TSP] )
			{
			case enumOrifice_1: TypeC[i] = 0;break; 
			case enumOrifice_2: TypeC[i] = 1;break; 
			}
			PumpC[i++] = 0; 		
		}		
		if( Configure.PumpType[PP_R24_A] != enumPumpNone )
		{		
			switch (Configure.PumpType[PP_R24_A] )
			{
			case enumOrifice_1:TypeC[i] = 2;break; 
			case enumOrifice_2:TypeC[i] = 3;break; 
			}
			PumpC[i++] = 1; 	
		}
		if( Configure.PumpType[PP_R24_B] != enumPumpNone )
		{
			switch ( Configure.PumpType[PP_R24_B] )
			{
			case enumOrifice_1:TypeC[i] = 2;break; 
			case enumOrifice_2:TypeC[i] = 3;break; 
			}
			PumpC[i++] = 2; 
		}
		if( Configure.PumpType[PP_SHI_C] != enumPumpNone )
		{
			switch ( Configure.PumpType[PP_SHI_C] )
			{
			case enumOrifice_1:TypeC[i] = 2;break; 
			case enumOrifice_2:TypeC[i] = 3;break; 
			}
			PumpC[i++] = 3; 
		}	 
		if( Configure.PumpType[PP_SHI_D] != enumPumpNone )
		{
			switch ( Configure.PumpType[PP_SHI_D] )
			{
			case enumOrifice_1:TypeC[i] = 2;break; 
			case enumOrifice_2:TypeC[i] = 3;break; 
			}
			PumpC[i++] = 4; 
		}	 
		if( Configure.PumpType[PP_AIR] != enumPumpNone )
		{
			switch ( Configure.PumpType[PP_AIR] )
			{
			case enumOrifice_1:TypeC[i] = 4;break; 
			case enumOrifice_2:TypeC[i] = 5;break; 
			}
			PumpC[i++] = 5; 
		}	 
		if( Configure.HeaterType != enumPumpNone )
		{
			switch ( Configure.HeaterType )
			{ 
			case enumHeaterOnly:	 TypeC[i] = 6;break; 
			case enumHCBoxOnly :	 TypeC[i] = 7;break; 
			case enumHCBoxHeater:  TypeC[i] = 8;break; 

			}
			PumpC[i++] = 6; 
		}
		imax = i;
		
		cls();
		WBMP( 0x0290,0x0502, STROCK); //��ʾ����
		WBMP( 0x0290,0x0514, STROCK); //��ʾ����
		switch ( option )
		{
		default:
		case opt_tsp_1:				
			for( i = 0; i < 6; i++)
			{
				if( i < imax)
				{ 
					if( imax <= 6 )
						Lputs(0x0102, "�ð�װ���  ");
					else					
						Lputs(0x0102, "�ð�װ��� 1"); 
					Lputs( dispchar[i%6],   Pump[PumpC[i]] ); 
					Lputs( dispchar2[i%6], Type[TypeC[i]]); 
				}	
			}	
			break;
		case opt_tsp_2:
			for( i = 6; i < 12; i++)
			{
				Lputs(0x0102, "�ð�װ��� 2");
				if( i < imax )
				{
					Lputs( dispchar[i%6],   Pump[PumpC[i]] ); 
					Lputs( dispchar2[i%6], Type[TypeC[i]]); 
				}		
			}	
			break;
		case opt_tsp_3:
			for( i = 12; i < 18; i++)
			{
				Lputs(0x0102, "�ð�װ��� 3");
				if( i < imax)
				{
					Lputs( dispchar[i%6],   Pump[PumpC[i]] ); 
					Lputs( dispchar2[i%6], Type[TypeC[i]]); 
				}					
			}	
			break;
		}
		
		opt_m = ( imax + 5 ) / 6 ;
		
		switch ( getKey() )
		{
		case K_UP:		//	��ǰ��ʱ�������ļ�������
			--option;
			if ( option < opt_min )
			{
				option = opt_m;
			}
			break;
		case K_DOWN:	//	���ʱ����µ��ļ�������
			++option;
			if ( option > opt_m )
			{
				option = opt_min;
			}
			break;
		case K_RIGHT:
			++option;
			if ( option > opt_m )
			{
				option = opt_min;
			}
			break;
		case K_LEFT:
			--option;
			if ( option < opt_min )
			{
				option = opt_m;
			}
			break;
		case K_OK:
			option = opt_exit;
			break;
		case K_SHIFT:		
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

extern BOOL	EditI32U( uint16_t yx, uint32_t * pNUM, uint16_t fmt );
/********************************** ����˵�� ***********************************
*	��չ���� -> ѡ��á���������������
*******************************************************************************/
void	Configure_Instrument( void )
{
	static  struct  uMenu  const  menu[] = 
	{
		{ 0x0301u, "��������" },
		{ 0x0802u, "����" },	
		{ 0x0F02u, "�ͺ�" },
		{ 0x1602u, "���ͺ�"	}, 
	};
	uint8_t item = 0u;
	BOOL	changed = FALSE;

	do {
		cls();
		Menu_Redraw( menu );		
		Lputs( 0x080Bu, szNameIdent[Configure.InstrumentName] );
		Lputs( 0x0F0Bu, szTypeIdent[Configure.InstrumentType] );
		item = Menu_Select( menu, item, NULL );
		switch ( item )
		{
		case 1:
			cls();
			++Configure.InstrumentName;
			if ( Configure.InstrumentName >= (sizeof(szNameIdent) / sizeof(szNameIdent[0] )))
			{
				Configure.InstrumentName = 0u;
			}
			changed = TRUE;
			break;
		case 2:	
			cls();			
			++Configure.InstrumentType;
			if ( Configure.InstrumentType >= (sizeof(szTypeIdent) / sizeof(szTypeIdent[0] )))
			{
				Configure.InstrumentType = 0u;
			}
			changed = TRUE;
			break;
		case 3:			
			PumpConfigure();			
		break;
		case enumSelectESC:
			if( changed == TRUE )
				switch( MsgBox( "�����޸Ľ��?", vbYesNoCancel | vbDefaultButton3 ) )
				{
				case vbYes :
					break;
				case vbNo :
					changed = FALSE;
					break;
				default :
				case vbCancel :
					item = 1;
					break;
				}
			break;
		default:
			break;
		}
	} while ( enumSelectESC != item );
	
	if ( changed )
	{
		ConfigureLoadDefault( );
		ConfigureSave();
	}
	else
		ConfigureLoad();
}


// void	ConfigureLoadDefault( void )
// {
// 	switch ( Configure.InstrumentType )
// 	{
// 	case type_KB6120C:		ConfigureLoad_KB6120C();	break;
// 	case type_KB6120B:		ConfigureLoad_KB6120B();	break;
// 	case type_KB2400D:		ConfigureLoad_KB2400D();	break;
// // 	case type_KB6120AD2:	ConfigureLoad_KB6120AD2();break;
// 	case type_KB2400:			ConfigureLoad_KB2400();		break;
// 	}
// }
void	ConfigureLoadDefault( void )
{

	ConfigureLoad_KB6120C();
	
	ConfigureLoad_KB6120B();
	
	ConfigureLoad_KB2400D();
	
	ConfigureLoad_KB2400();	
	
}

/********  (C) COPYRIGHT 2014 �ൺ���˴���ӿƼ����޹�˾  **** End Of File ****/

