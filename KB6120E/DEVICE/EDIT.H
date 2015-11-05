///////////////////////////////////////////////////////////////////
//	Menu.C
///////////////////////////////////////////////////////////////////
struct	uMenu
{
	uint16_t yx;
	const CHAR * sz;
};

enum
{
	enumSelectESC = 0u,
	enumSelectXCH = 0xFFu,
};
extern	void	Show_std_clock( void );
extern	void	Menu_Item_Mask ( const struct uMenu * menu, uint8_t item );
extern	void	Menu_Redraw    ( const struct uMenu * menu );
extern	uint8_t	Menu_Select     ( const struct uMenu * menu, uint8_t item, void ( *pHook ) ( void ) );
// extern	uint8_t	Menu_SelectS ( const struct uMenu * menu, uint8_t item, void ( *pHook ) ( void ) ) ;
extern	uint8_t	Menu_Select2    ( const struct uMenu * menu, uint8_t item, BOOL Direction, void ( *pHook ) ( void ) );
extern  uint8_t	Menu_Select3	  ( const struct uMenu * menu, uint8_t item, uint8_t timeout, void ( *pHook ) ( void ) );
extern	uint8_t	Menu_Select_Ex  ( const struct uMenu * menu, uint8_t item, void ( *pHook )( void ) );
extern	uint8_t	Menu_Select_ExS ( const struct uMenu * menu, uint8_t item, void ( *pHook ) ( void ) );
extern	uint8_t	Menu_Select_Ex2 ( const struct uMenu * menu, uint8_t item, void ( *pHook )( void ), BOOL Direction );
extern	uint8_t	Menu_Select_Ex3 ( const struct uMenu * menu, uint8_t item, void ( *pHook ) ( void ), uint8_t timeout );
///////////////////////////////////////////////////////////////////
//	MsgBox
///////////////////////////////////////////////////////////////////
//	MsgBox�Ĳ�������ֵ
#define	vbOKOnly			0x00u	//	ֻ��ʾ OK ��ť��
#define	vbOKCancel			0x01u	//	��ʾ OK �� Cancel ��ť��
#define	vbAbortRetryIgnore	0x02u	//	��ʾ Abort��Retry �� Ignore ��ť��
#define	vbYesNoCancel		0x03u	//	��ʾ Yes��No �� Cancel ��ť��
#define	vbYesNo				0x04u	//	��ʾ Yes �� No ��ť��
#define	vbRetryCancel		0x05u	//	��ʾ Retry �� Cancel ��ť��
#define	vbDefaultButton1 	0x00u	//	��һ����ť��ȱʡֵ��
#define	vbDefaultButton2 	0x10u	//	�ڶ�����ť��ȱʡֵ��
#define	vbDefaultButton3 	0x20u	//	��������ť��ȱʡֵ��
#define	vbDefaultButton4 	0x30u 	//	���ĸ���ť��ȱʡֵ��
//	MsgBox�ķ���ֵ
#define	vbOK				0x01u
#define	vbCancel			0x02u
#define	vbAbort				0x03u
#define	vbRetry				0x04u
#define	vbIgnore			0x05u
#define	vbYes				0x06u
#define	vbNo				0x07u

extern	uint8_t	MsgBox( const CHAR * sPrompt, uint16_t buttons );

///////////////////////////////////////////////////////////////////
//	Edit.C
///////////////////////////////////////////////////////////////////
extern	void	ShowFP32( uint16_t yx, FP32     NumFP32, uint16_t fmt, const CHAR * szUnit );
extern	void	ShowI16U( uint16_t yx, uint16_t NumI16U, uint16_t fmt, const CHAR * szUnit );
extern	void	ShowTIME( uint16_t yx, uint16_t Time );
extern	void	ShowDATE( uint16_t yx, uint32_t timer ); // const struct uShortDate * pDate );
extern	void	ShowPercent( uint16_t yx, FP32 Percent );
extern	void	ShowHEX16  ( uint16_t yx, uint16_t hex16 );

//	void	Show( uint16_t yx, uint16_t NumI16U, uint16_t fmt, const CHAR * Unit = NULL );
//	void	Show( uint16_t yx, FP32     NumFP32, uint16_t fmt, const CHAR * Unit = NULL );

extern	BOOL	EditI16U( uint16_t yx, uint16_t * pNUM, uint16_t fmt );
extern	BOOL	EditTIME( uint16_t yx, uint16_t * sTime );

//	extern	void	ShowStandard( uint16_t yx );
extern	void	ShowWDay( uint16_t yx, const uClock * Now );
extern	void	ShowClock(     uint16_t yx, const uClock * pClock );
extern	void	ShowClockDate( uint16_t yx, const uClock * pClock );
extern	void	ShowClockTime( uint16_t yx, const uClock * pClock );
extern	BOOL	EditClockDate( uint16_t yx,       uClock * pClock );
extern	BOOL	EditClockTime( uint16_t yx,       uClock * pClock );

extern	uint32_t	InputPassword( void );

///////////////////////////////////////////////// End of File /////