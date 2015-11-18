/**************** (C) COPYRIGHT 2014 Çàµº½ğÊË´ïµç×Ó¿Æ¼¼ÓĞÏŞ¹«Ë¾ ****************
* ÎÄ ¼ş Ãû: ConfigureEx.C
* ´´ ½¨ Õß: ¶­·å(2014Äê4ÔÂ8ÈÕ)
* Ãè  Êö  : KB-6120E ¶¨Òå¡¢ÏÔÊ¾°æ±¾ĞÅÏ¢
* ×îºóĞŞ¸Ä: 2014Äê4ÔÂ8ÈÕ
*********************************** ĞŞ¶©¼ÇÂ¼ ***********************************
* °æ  ±¾: 
* ĞŞ¶©ÈË: 
*******************************************************************************/
#include "AppDEF.H"
#include "BMP.H"
#define	T_KB6120C
// #define	T_KB6120B
// #define	T_KB2400D
// #define	T_KB2400
<<<<<<< HEAD
=======
extern	uint32_t	eDataValidMask; 
void	EditionSelsct( void )
{
#define	T_KB6120C
// #define	T_KB6120B
// #define	T_KB2400D
// #define	T_KB2400
	#ifdef	T_KB6120C
		eDataValidMask = 0x5A3A;
	#elif	defined	T_KB6120B
		eDataValidMask = 0x5A3B;
	#elif	defined	T_KB2400D
		eDataValidMask = 0x5A3C;
	#elif	defined	T_KB2400
		eDataValidMask = 0x5A3D;
	#endif

}
>>>>>>> 1112æ—¥å‘ç°é—®é¢˜åˆ†æ”¯ä¿®æ”¹
/********************************** ¹¦ÄÜËµÃ÷ ***********************************
*  ¸ù¾İÒÇÆ÷ĞÍºÅÏÔÊ¾°æ±¾ĞÅÏ¢
*  ¸ù¾İÏúÊÛÈËÔ±ÒªÇó£¬¿ÉÄÜ»á¸Ä³ÉÆäËû³§¼ÒÃû³Æ£¬»òÕß¸É´à²»ÏÔÊ¾¡£
*******************************************************************************/
CHAR  const * const ExNameIdent1[] =
{
  "/* ÎŞ ³§ ¼Ò Ãû ³Æ */",
  " Çà µº ½ğ ÊË ´ï ",
//  ...  
};
CHAR  const * const ExNameIdent2[] =
{
  "/* ÎŞ ³§ ¼Ò Ãû ³Æ */",
  "µç ×Ó ¿Æ ¼¼ ÓĞ ÏŞ ¹« Ë¾",
//  ...  
};
CHAR  const * const EditionNum[] =
{
   "KB6120E V2.05",	//	ÄÚ²¿°æ±¾
	__DATE__" V2.00",	//	ÏÔÊ¾°æ±¾
};
static	void	ShowEdition_NoName( void )
{
	cls();
  Lputs( 0x0809u, szNameIdent[Configure.InstrumentName] );
	Lputs( 0x0F03u, EditionNum[1] );
	Lputs( 0x1509u, "±àºÅ:" );	ShowFP32( 0x1512u, Configure.ExNum, 0x0700u, NULL );
}
static	void	ShowEdition_HasName( void )
{
  cls();
 	Lputs( 0x0109u, szNameIdent [Configure.InstrumentName] );
	Lputs( 0x0607u, ExNameIdent1[Configure.ExName] );
	Lputs( 0x0C01u, ExNameIdent2[Configure.ExName] );
	Lputs( 0x1203u, EditionNum[1] );
	Lputs( 0x1809u, "±àºÅ:" );ShowFP32( 0x1812u, Configure.ExNum, 0x0700u, NULL );
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
	
/********************************** ¹¦ÄÜËµÃ÷ ***********************************
*  ÏÔÊ¾³ÌĞò°æ±¾ ¸ù¾İÒÇÆ÷ĞÍºÅÏÔÊ¾°æ±¾ĞÅÏ¢
*******************************************************************************/
void	ShowEdition_Inner( void )
{
	cls();
	Lputs( 0x0308u, szNameIdent[Configure.InstrumentName] );
	Lputs( 0x0908u, __DATE__ );
	Lputs( 0x0F0Au, __TIME__ );
	Lputs( 0x1506u, EditionNum[0] );

}

/********************************** Êı¾İ¶¨Òå ***********************************
*  ¿ÉÓÃµÄÒÇÆ÷Ãû³ÆÁĞ±í
*******************************************************************************/
CHAR  const * const szTypeIdent[] =
{
		"KB-6120C",
		"KB-6120B",
		"KB-2400D",
		"KB-2400 ",   
//		"KB-6120BD",
//		"KB-6120BH",
};

CHAR  const * const szNameIdent[] =
{
	"ÖÇÄÜ×ÛºÏ²ÉÑùÆ÷  ",
	"×ÛºÏ´óÆø²ÉÑùÆ÷  ",
	"ÖÇÄÜÖĞÁ÷Á¿²ÉÑùÆ÷",
	"ÖÇÄÜ´óÁ÷Á¿²ÉÑùÆ÷",
	"ºãÎÂºãÁ÷²ÉÑùÆ÷  ",
	"ÖÇÄÜºãÁ÷²ÉÑùÆ÷  ",
};

static	void	ConfigureLoad_KB6120C( void )
{
	#ifdef	T_KB6120C
		Configure.InstrumentType = type_KB6120C;//6120C
		
		Configure.PumpType[PP_TSP  ] = enumOrifice_1;	Configure.SetFlow[PP_TSP  ]  = 1000u;	//	·Û³¾  ²ÉÑùÁ÷Á¿ 100.0 L/m
		Configure.PumpType[PP_R24_A] = enumOrifice_1;	Configure.SetFlow[PP_R24_A]  =  200u;	//	ÈÕ¾ù1 ²ÉÑùÁ÷Á¿ 0.200 L/m
		Configure.PumpType[PP_R24_B] = enumOrifice_1;	Configure.SetFlow[PP_R24_B]  =  200u;	//	ÈÕ¾ù2 ²ÉÑùÁ÷Á¿ 0.200 L/m
		Configure.PumpType[PP_SHI_C] = enumOrifice_1; Configure.SetFlow[PP_SHI_C]  =    5u;	//	Ê±¾ù1 ²ÉÑùÁ÷Á¿ 0.5 L/m
		Configure.PumpType[PP_SHI_D] = enumOrifice_1; Configure.SetFlow[PP_SHI_D]  =    5u;	//	Ê±¾ù2 ²ÉÑùÁ÷Á¿ 0.5 L/m
		Configure.PumpType[PP_AIR  ] = enumPumpNone;	Configure.SetFlow[PP_AIR  ]  =  500u;	//	´óÆø Á÷Á¿ 0.5 L/m
		Configure.AIRSetFlow[Q_PP1] = 5;
		Configure.AIRSetFlow[Q_PP2] = 5;
		Configure.HeaterType = enumHCBoxOnly;	//	Ö»ÓĞºãÎÂÏä
		Configure.Heater_SetTemp = 300u;		//	¼ÓÈÈÆ÷ºãÎÂÎÂ¶È 30.0 ¡æ
		Configure.Heater_SW = FALSE;         //¼ÓÈÈÆ÷¿ª¹Ø	
		
		Configure.HCBox_SetMode = MD_Shut;		//	ºãÎÂÏä¿ØÖÆÄ£Ê½ [¹Ø±Õ]
		Configure.HCBox_SetTemp = 240u;			//	ºãÎÂÏäºãÎÂÎÂ¶È 24.0 ¡æ
				 
		Configure.SetTstd = enum_293K;			//	±ê¿öÁ÷Á¿µÄ¶¨ÒåÎÂ¶È 
		
		Configure.Mothed_Delay = enumByDelay;	//	²ÉÑù¿ªÊ¼Ê±¼ä·½Ê½
		Configure.Mothed_Sample = enumBySet;	//	²ÉÑùÊ±¼ä¿ØÖÆ·½Ê½

		Configure.Mothed_Ba = enumMeasureBa;	//	´óÆøÑ¹Á¦»ñÈ¡·½Ê½
		Configure.set_Ba    = 10133u;			//	±£´æÓÃ»§ÊäÈëÆøÑ¹

		Configure.DisplayGray  = 2000u;	//	ÏÔÊ¾»Ò¶ÈÉèÖÃ
		Configure.DisplayLight = 50u;	//	ÏÔÊ¾ÁÁ¶ÈÉèÖÃ
		Configure.TimeoutLight = 2u;	//	±³¹âÑÓÊ±Ê±¼ä
		
		Configure.slope_Bat_Voltage = 1000;
		Configure.slope_Bat_Current = 1000;
		Configure.threshold_Current = 100;
		
		Configure.shouldCalcPbv = 0;		//	±¥ºÍË®ÆûÑ¹ÊÇ·ñ²ÎÓë¼ÆËã¡£
		
		Configure.Battery_SW = FALSE;    //µç³ØÊÇ·ñ´æÔÚ
		Configure.ExName = Name_JSD;
		Configure.Password = 633817;
		
	#endif
}
	
static	void	ConfigureLoad_KB6120B( void )
{
	#ifdef	T_KB6120B
		Configure.InstrumentType = type_KB6120B; // 6120B

		Configure.PumpType[PP_TSP  ] = enumOrifice_1;	Configure.SetFlow[PP_TSP  ]  = 1000u;	//	·Û³¾  ²ÉÑùÁ÷Á¿ 100.0 L/m
		Configure.PumpType[PP_R24_A] = enumPumpNone;	Configure.SetFlow[PP_R24_A]  =  200u;	//	ÈÕ¾ù1 ²ÉÑùÁ÷Á¿ 0.200 L/m
		Configure.PumpType[PP_R24_B] = enumPumpNone;	Configure.SetFlow[PP_R24_B]  =  200u;	//	ÈÕ¾ù2 ²ÉÑùÁ÷Á¿ 0.200 L/m
		Configure.PumpType[PP_SHI_C] = enumOrifice_1;	Configure.SetFlow[PP_SHI_C]  =    5u;	//	Ê±¾ù1 ²ÉÑùÁ÷Á¿ 0.5 L/m
		Configure.PumpType[PP_SHI_D] = enumOrifice_1;	Configure.SetFlow[PP_SHI_D]  =    5u;	//	Ê±¾ù2 ²ÉÑùÁ÷Á¿ 0.5 L/m
		Configure.PumpType[PP_AIR  ] = enumPumpNone;	Configure.SetFlow[PP_AIR  ]  =  500u;	//	´óÆø Á÷Á¿ 0.5 L/m
		Configure.AIRSetFlow[Q_PP1] = 5;
		Configure.AIRSetFlow[Q_PP2] = 5;
		Configure.HeaterType = enumHCBoxOnly;	//	Ö»ÓĞºãÎÂÏä
		Configure.Heater_SetTemp = 300u;		//	¼ÓÈÈÆ÷ºãÎÂÎÂ¶È 30.0 ¡æ
		Configure.Heater_SW = FALSE;          // ¼ÓÈÈÆ÷²»¹¤×÷
		
		Configure.HCBox_SetMode = MD_Shut;		//	ºãÎÂÏä¿ØÖÆÄ£Ê½ [¹Ø±Õ]
		Configure.HCBox_SetTemp = 240u;			//	ºãÎÂÏäºãÎÂÎÂ¶È 24.0 ¡æ

		Configure.SetTstd = enum_293K;			//	±ê¿öÁ÷Á¿µÄ¶¨ÒåÎÂ¶È 
		
		Configure.Mothed_Delay = enumByDelay;	//	²ÉÑù¿ªÊ¼Ê±¼ä·½Ê½
		Configure.Mothed_Sample = enumBySet;	//	²ÉÑùÊ±¼ä¿ØÖÆ·½Ê½

		Configure.Mothed_Ba = enumMeasureBa;	//	´óÆøÑ¹Á¦»ñÈ¡·½Ê½
		Configure.set_Ba    = 10133u;			//	±£´æÓÃ»§ÊäÈëÆøÑ¹

		Configure.DisplayGray  = 2000u;	//	ÏÔÊ¾»Ò¶ÈÉèÖÃ
		Configure.DisplayLight = 50u;	//	ÏÔÊ¾ÁÁ¶ÈÉèÖÃ
		Configure.TimeoutLight = 2u;	//	±³¹âÑÓÊ±Ê±¼ä
			
		Configure.shouldCalcPbv = 0;		//	±¥ºÍË®ÆûÑ¹ÊÇ·ñ²ÎÓë¼ÆËã¡£

		Configure.Battery_SW = FALSE;    //µç³ØÊÇ·ñ´æÔÚ
	// 	Configure.ExNum = 1501000;			 //³ö³§±àºÅ
		Configure.ExName = Name_JSD;
		Configure.Password = 633817;

	#endif
}

static	void	ConfigureLoad_KB2400D( void )
{
	#ifdef	T_KB2400D
		Configure.InstrumentType = type_KB2400D;//2400D
		
		Configure.PumpType[PP_TSP  ] = enumPumpNone;	Configure.SetFlow[PP_TSP  ]  = 1000u;	//	·Û³¾ ²ÉÑùÁ÷Á¿ 100.0 L/m
		Configure.PumpType[PP_R24_A] = enumOrifice_1;	Configure.SetFlow[PP_R24_A]  =  200u;	//	ÈÕ¾ù1²ÉÑùÁ÷Á¿ 0.200 L/m
		Configure.PumpType[PP_R24_B] = enumOrifice_1;	Configure.SetFlow[PP_R24_B]  =  200u;	//	ÈÕ¾ù2²ÉÑùÁ÷Á¿ 0.200 L/m
		Configure.PumpType[PP_SHI_C] = enumOrifice_1;	Configure.SetFlow[PP_SHI_C]  =    5u;	//	Ê±¾ù1²ÉÑùÁ÷Á¿ 0.5 L/m
		Configure.PumpType[PP_SHI_D] = enumOrifice_1;	Configure.SetFlow[PP_SHI_D]  =    5u;	//	Ê±¾ù2²ÉÑùÁ÷Á¿ 0.5 L/m
		Configure.PumpType[PP_AIR  ] = enumPumpNone;	Configure.SetFlow[PP_AIR  ]  =  500u;	//	´óÆø Á÷Á¿ 0.5 L/m
		Configure.AIRSetFlow[Q_PP1] = 5;
		Configure.AIRSetFlow[Q_PP2] = 5;
		Configure.HeaterType = enumHCBoxOnly;	//	Ö»ÓĞºãÎÂÏä
		Configure.Heater_SetTemp = 300u;		//	¼ÓÈÈÆ÷ºãÎÂÎÂ¶È 30.0 ¡æ
		Configure.Heater_SW = FALSE;          // ¼ÓÈÈÆ÷²»¹¤×÷
		
		Configure.HCBox_SetMode = MD_Shut;		//	ºãÎÂÏä¿ØÖÆÄ£Ê½ [¹Ø±Õ]
		Configure.HCBox_SetTemp = 240u;			//	ºãÎÂÏäºãÎÂÎÂ¶È 24.0 ¡æ

		Configure.SetTstd = enum_293K;			//	±ê¿öÁ÷Á¿µÄ¶¨ÒåÎÂ¶È 
		
		Configure.Mothed_Delay = enumByDelay;	//	²ÉÑù¿ªÊ¼Ê±¼ä·½Ê½
		Configure.Mothed_Sample = enumBySet;	//	²ÉÑùÊ±¼ä¿ØÖÆ·½Ê½

		Configure.Mothed_Ba = enumMeasureBa;	//	´óÆøÑ¹Á¦»ñÈ¡·½Ê½
		Configure.set_Ba    = 10133u;			//	±£´æÓÃ»§ÊäÈëÆøÑ¹

		Configure.DisplayGray  = 2000u;	//	ÏÔÊ¾»Ò¶ÈÉèÖÃ
		Configure.DisplayLight = 50u;	//	ÏÔÊ¾ÁÁ¶ÈÉèÖÃ
		Configure.TimeoutLight = 2u;	//	±³¹âÑÓÊ±Ê±¼ä
		
		Configure.Battery_SW = FALSE;    //µç³ØÊÇ·ñ´æÔÚ
	// 	Configure.ExNum = 1501000;			 //³ö³§±àºÅ
		Configure.ExName = Name_JSD;
		Configure.Password = 633817;
		
	#endif
}

static	void	ConfigureLoad_KB2400( void )
{
	#ifdef	T_KB2400
		Configure.InstrumentType = type_KB2400;//2400
		
		Configure.PumpType[PP_TSP  ] = enumPumpNone;	Configure.SetFlow[PP_TSP  ]  = 1000u;	//	·Û³¾ ²ÉÑùÁ÷Á¿ 100.0 L/m
		Configure.PumpType[PP_R24_A] = enumPumpNone;	Configure.SetFlow[PP_R24_A]  =  200u;	//	ÈÕ¾ù1²ÉÑùÁ÷Á¿ 0.200 L/m
		Configure.PumpType[PP_R24_B] = enumPumpNone;	Configure.SetFlow[PP_R24_B]  =  200u;	//	ÈÕ¾ù2²ÉÑùÁ÷Á¿ 0.200 L/m
		Configure.PumpType[PP_SHI_C] = enumOrifice_1;	Configure.SetFlow[PP_SHI_C]  =    5u;	//	Ê±¾ù1²ÉÑùÁ÷Á¿ 0.5 L/m
		Configure.PumpType[PP_SHI_D] = enumOrifice_1;	Configure.SetFlow[PP_SHI_D]  =    5u;	//	Ê±¾ù2²ÉÑùÁ÷Á¿ 0.5 L/m
		Configure.PumpType[PP_AIR  ] = enumPumpNone;	Configure.SetFlow[PP_AIR  ]  =  500u;	//	´óÆø Á÷Á¿ 0.5 L/m
		Configure.AIRSetFlow[Q_PP1] = 5;
		Configure.AIRSetFlow[Q_PP2] = 5;
		Configure.HeaterType = enumHCBoxOnly;	//	Ö»ÓĞºãÎÂÏä
		Configure.Heater_SetTemp = 300u;		//	¼ÓÈÈÆ÷ºãÎÂÎÂ¶È 30.0 ¡æ
		Configure.Heater_SW = FALSE;          // ¼ÓÈÈÆ÷²»¹¤×÷
		
		Configure.HCBox_SetMode = MD_Shut;		//	ºãÎÂÏä¿ØÖÆÄ£Ê½ [¹Ø±Õ]
		Configure.HCBox_SetTemp = 240u;			//	ºãÎÂÏäºãÎÂÎÂ¶È 24.0 ¡æ

		Configure.SetTstd = enum_293K;			//	±ê¿öÁ÷Á¿µÄ¶¨ÒåÎÂ¶È 
		
		Configure.Mothed_Delay = enumByDelay;	//	²ÉÑù¿ªÊ¼Ê±¼ä·½Ê½
		Configure.Mothed_Sample = enumBySet;	//	²ÉÑùÊ±¼ä¿ØÖÆ·½Ê½

		Configure.Mothed_Ba = enumMeasureBa;	//	´óÆøÑ¹Á¦»ñÈ¡·½Ê½
		Configure.set_Ba    = 10133u;			//	±£´æÓÃ»§ÊäÈëÆøÑ¹

		Configure.DisplayGray  = 2000u;	//	ÏÔÊ¾»Ò¶ÈÉèÖÃ
		Configure.DisplayLight = 50u;	//	ÏÔÊ¾ÁÁ¶ÈÉèÖÃ
		Configure.TimeoutLight = 2u;	//	±³¹âÑÓÊ±Ê±¼ä
		
		Configure.Battery_SW = FALSE;    //µç³ØÊÇ·ñ´æÔÚ
	// 	Configure.ExNum = 1501000;			 //³ö³§±àºÅ
		Configure.ExName = Name_JSD;
		Configure.Password = 633817;
		
	#endif
}

// static	void	ConfigureLoad_KB6120AD2( void )
// {
// 	Configure.InstrumentType = type_KB6120AD2;

// 	Configure.PumpType[PP_TSP  ] = enumOrifice_1;	Configure.SetFlow[PP_TSP  ]  = 1000u;	//	·Û³¾  ²ÉÑùÁ÷Á¿ 100.0 L/m
// 	Configure.PumpType[PP_R24_A] = enumPumpNone;	Configure.SetFlow[PP_R24_A]  =  200u;	//	ÈÕ¾ù1 ²ÉÑùÁ÷Á¿ 0.200 L/m
// 	Configure.PumpType[PP_R24_B] = enumPumpNone;	Configure.SetFlow[PP_R24_B]  =  200u;	//	ÈÕ¾ù2 ²ÉÑùÁ÷Á¿ 0.200 L/m
// 	Configure.PumpType[PP_SHI_C] = enumOrifice_1;	Configure.SetFlow[PP_SHI_C]  =    5u;	//	Ê±¾ù1 ²ÉÑùÁ÷Á¿ 0.5 L/m
// 	Configure.PumpType[PP_SHI_D] = enumOrifice_1;	Configure.SetFlow[PP_SHI_D]  =    5u;	//	Ê±¾ù2 ²ÉÑùÁ÷Á¿ 0.5 L/m
// 	Configure.PumpType[PP_AIR  ] = enumPumpNone;	Configure.SetFlow[PP_AIR  ]  =  500u;	//	´óÆø Á÷Á¿ 0.5 L/m

// 	Configure.HeaterType = enumHeaterOnly;	//	Ö»ÓĞºãÎÂÏä
// 	Configure.Heater_SetTemp = 300u;		//	¼ÓÈÈÆ÷ºãÎÂÎÂ¶È 30.0 ¡æ
// 	Configure.Heater_SW = TRUE;          // ¼ÓÈÈÆ÷²»¹¤×÷
// 	
// 	Configure.HCBox_SetMode = MD_Shut;		//	ºãÎÂÏä¿ØÖÆÄ£Ê½ [¹Ø±Õ]
// 	Configure.HCBox_SetTemp = 240u;			//	ºãÎÂÏäºãÎÂÎÂ¶È 24.0 ¡æ

// 	Configure.SetTstd = enum_293K;			//	±ê¿öÁ÷Á¿µÄ¶¨ÒåÎÂ¶È 
// 	
// 	Configure.Mothed_Delay = enumByDelay;	//	²ÉÑù¿ªÊ¼Ê±¼ä·½Ê½
// 	Configure.Mothed_Sample = enumBySet;	//	²ÉÑùÊ±¼ä¿ØÖÆ·½Ê½

// 	Configure.Mothed_Ba = enumMeasureBa;	//	´óÆøÑ¹Á¦»ñÈ¡·½Ê½
// 	Configure.set_Ba    = 10133u;			//	±£´æÓÃ»§ÊäÈëÆøÑ¹

// 	Configure.DisplayGray  = 1900u;	//	ÏÔÊ¾»Ò¶ÈÉèÖÃ
// 	Configure.DisplayLight = 52u;	//	ÏÔÊ¾ÁÁ¶ÈÉèÖÃ
// 	Configure.TimeoutLight = 2u;	//	±³¹âÑÓÊ±Ê±¼ä
// 		
// 	Configure.shouldCalcPbv = 0;		//	±¥ºÍË®ÆûÑ¹ÊÇ·ñ²ÎÓë¼ÆËã¡£
// 	
// 	Configure.Battery_SW = FALSE;    //µç³ØÊÇ·ñ´æÔÚ
// 	Configure.ExNum = 1501000;			 //³ö³§±àºÅ
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

/********************************** ¹¦ÄÜËµÃ÷ ***********************************
* 				±Ã°²×°Çé¿ö
*******************************************************************************/
CHAR  const * const Pump[]=
{
	"·Û³¾±Ã ",	//0
	"ÈÕ¾ùA",	//1
	"ÈÕ¾ùB",	//2
	"Ê±¾ùC",	//3
	"Ê±¾ùD",	//4
	"´óÆø±Ã",	//5
	"ºãÎÂÆ÷"		//6
}; 
CHAR  const * const Type[]=
{
	"[K-100L]",	//0
	"[K-1.£Í]",	//1
	"[1L¿×°å]",	//2
	"[2L¿×°å]",	//3
	"[1-µ¥±Ã]",	//4
	"[2-Ë«±Ã]",	//5
	"[¼ÓÈÈÆ÷]",	//6
	"[ºãÎÂÏä]",	//7
	"[È«°²×°]" 	//8
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
		WBMP( 0x0290,0x0502, STROCK); //ÏÔÊ¾ºáÏß
		WBMP( 0x0290,0x0514, STROCK); //ÏÔÊ¾ºáÏß
		switch ( option )
		{
		default:
		case opt_tsp_1:				
			for( i = 0; i < 6; i++)
			{
				if( i < imax)
				{ 
					if( imax <= 6 )
						Lputs(0x0102, "±Ã°²×°Çé¿ö  ");
					else					
						Lputs(0x0102, "±Ã°²×°Çé¿ö 1"); 
					Lputs( dispchar[i%6],   Pump[PumpC[i]] ); 
					Lputs( dispchar2[i%6], Type[TypeC[i]]); 
				}	
			}	
			break;
		case opt_tsp_2:
			for( i = 6; i < 12; i++)
			{
				Lputs(0x0102, "±Ã°²×°Çé¿ö 2");
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
				Lputs(0x0102, "±Ã°²×°Çé¿ö 3");
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
		case K_UP:		//	ÏòÇ°£¨Ê±¼ä½ÏÔçµÄÎÄ¼ş£©²éÕÒ
			--option;
			if ( option < opt_min )
			{
				option = opt_m;
			}
			break;
		case K_DOWN:	//	Ïòºó£¨Ê±¼ä½ÏĞÂµÄÎÄ¼ş£©²éÕÒ
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
/********************************** ¹¦ÄÜËµÃ÷ ***********************************
*	À©Õ¹ÅäÖÃ -> Ñ¡Ôñ±Ã¡¢Á÷Á¿¡¢ÒÇÆ÷Ãû³Æ
*******************************************************************************/
void	Configure_Instrument( void )
{
	static  struct  uMenu  const  menu[] = 
	{
		{ 0x0301u, "ÅäÖÃÒÇÆ÷" },
		{ 0x0802u, "Ãû³Æ" },	
		{ 0x0F02u, "ĞÍºÅ" },
		{ 0x1602u, "±ÃĞÍºÅ"	}, 
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
				switch( MsgBox( "±£´æĞŞ¸Ä½á¹û?", vbYesNoCancel | vbDefaultButton3 ) )
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

/********  (C) COPYRIGHT 2014 Çàµº½ğÊË´ïµç×Ó¿Æ¼¼ÓĞÏŞ¹«Ë¾  **** End Of File ****/

