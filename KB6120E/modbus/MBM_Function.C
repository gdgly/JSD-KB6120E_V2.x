/**************** (C) COPYRIGHT 2013 �ൺ���˴���ӿƼ����޹�˾ ****************
* �� �� ��: MBM_Function.C
* �� �� ��: ����
* ��  ��  : MODBUS ��������
* ����޸�: 2013��12��13��
*********************************** �޶���¼ ***********************************
* ��  ��: 
* �޶���: 
*******************************************************************************/
#include "MBM_BSP.H"
#include "MBM.H"
#include "MBM_Port.H"

/********************************** ����˵�� ***********************************
*  FC01 Read Coils
*******************************************************************************/
eMBErrorCode	eMBMReadCoils( uint8_t SlaveAddress, uint16_t usRegAddress, uint16_t usCoilCount, uint8_t pCoils[] )
{
	const uint8_t	ucNBytes = HowBytes( usCoilCount );	//	�����ȡ���ݵ��ֽ���
	eMBErrorCode	eStatus = MB_ENOERR;
	uint16_t		usLen = 0u;

    assert(( usCoilCount >= 1u ) && ( usCoilCount <= MB_PDU_FUNC_READ_COILCNT_MAX ));
	//	�ȴ����߿���
	vMBus_apply();
	//	װ������
	ucModbusPDU[usLen++] = MB_FUNC_READ_COILS;		//	FC01
	ucModbusPDU[usLen++] = HIBYTE( usRegAddress );
	ucModbusPDU[usLen++] = LOBYTE( usRegAddress );
	ucModbusPDU[usLen++] = HIBYTE( usCoilCount );
	ucModbusPDU[usLen++] = LOBYTE( usCoilCount );
	//	����ͨѶ
	eStatus = eMBM_IO( SlaveAddress, &usLen );
	//	����Ӧ��
	if ( MB_ENOERR == eStatus )
	{
		if (( MB_PDU_RESPONSE_READ_SIZE + ucNBytes ) != usLen )
		{
			eStatus = MB_EX_Response_IllegalLength;
		}
		else if ( ucNBytes != ucModbusPDU[MB_PDU_RESPONSE_READ_BYTECNT_OFF] )
		{
			eStatus = MB_EX_Response_IllegalByteCnt;
		}
		else
		{	//	�ɹ�
			memcpy( pCoils, &ucModbusPDU[MB_PDU_RESPONSE_READ_VALUES_OFF], ucNBytes );
		} 
	}
	//	�ͷ�����
	vMBus_release();
	//	��¼�����ֵĴ���
	if ( MB_ENOERR != eStatus )
	{
		vMBusLogError( eStatus );
	}
	return	eStatus;
}

/********************************** ����˵�� ***********************************
*  FC02 Read Discretes
*******************************************************************************/
eMBErrorCode	eMBMReadDiscretes( uint8_t SlaveAddress, uint16_t usRegAddress, uint16_t usDiscreteCnt, uint8_t pDiscretes[] )
{
	const uint8_t	ucNBytes = HowBytes( usDiscreteCnt );	//	�����ȡ���ݵ��ֽ���
	eMBErrorCode	eStatus = MB_ENOERR;
	uint16_t		usLen = 0u;

	assert(( usDiscreteCnt >= 1u ) && ( usDiscreteCnt <= MB_PDU_FUNC_READ_DISCCNT_MAX ));
	//	�ȴ����߿���
	vMBus_apply();
	//	װ������
	ucModbusPDU[usLen++] = MB_FUNC_READ_DISCRETE_INPUTS; 	//	FC02
	ucModbusPDU[usLen++] = HIBYTE( usRegAddress );
	ucModbusPDU[usLen++] = LOBYTE( usRegAddress );
	ucModbusPDU[usLen++] = HIBYTE( usDiscreteCnt );
	ucModbusPDU[usLen++] = LOBYTE( usDiscreteCnt );
	//	����ͨѶ
	eStatus = eMBM_IO( SlaveAddress, &usLen );
	//	����Ӧ��
	if ( MB_ENOERR == eStatus )
	{
		if (( MB_PDU_RESPONSE_READ_SIZE + ucNBytes ) != usLen )
		{
			eStatus = MB_EX_Response_IllegalLength;
		}
		else if ( ucNBytes != ucModbusPDU[MB_PDU_RESPONSE_READ_BYTECNT_OFF] )
		{
			eStatus = MB_EX_Response_IllegalByteCnt;
		}
		else
		{	//	�ɹ�
			memcpy( pDiscretes, &ucModbusPDU[MB_PDU_RESPONSE_READ_VALUES_OFF], ucNBytes );
		}
	}
	//	�ͷ�����	
	vMBus_release();
	//	��¼�����ֵĴ���
	if ( MB_ENOERR != eStatus )
	{
		vMBusLogError( eStatus );
	}
	return	eStatus;
}

/********************************** ����˵�� ***********************************
*  FC03 Read holding registers
*******************************************************************************/
eMBErrorCode	eMBMReadHoldingRegisters( uint8_t SlaveAddress, uint16_t usRegAddress, uint16_t usRegCount, uint16_t pHoldingRegisters[] )
{
	const uint8_t	ucNBytes = usRegCount * 2u;		//	�����ȡ���ݵ��ֽ���
	eMBErrorCode	eStatus = MB_ENOERR;
	uint16_t		usLen = 0u;

	assert(( usRegCount >= 1u ) && ( usRegCount <= MB_PDU_FUNC_READ_REGCNT_MAX ));
	//	�ȴ����߿���
	vMBus_apply();
	//	װ������
	ucModbusPDU[usLen++] = MB_FUNC_READ_HOLDING_REGISTER; 	//	FC3
	ucModbusPDU[usLen++] = HIBYTE( usRegAddress );
	ucModbusPDU[usLen++] = LOBYTE( usRegAddress );
	ucModbusPDU[usLen++] = HIBYTE( usRegCount );
	ucModbusPDU[usLen++] = LOBYTE( usRegCount );
	//	����ͨѶ
	eStatus = eMBM_IO( SlaveAddress, &usLen );
	//	����Ӧ��
	if ( MB_ENOERR == eStatus )
	{
		if (( MB_PDU_RESPONSE_READ_SIZE + ucNBytes ) != usLen )
		{
			eStatus = MB_EX_Response_IllegalLength;
		}
		else if ( ucNBytes != ucModbusPDU[MB_PDU_RESPONSE_READ_BYTECNT_OFF] )
		{
			eStatus = MB_EX_Response_IllegalByteCnt;
		}
		else
		{	//	�ɹ�
			vMBus_Memory_Get( pHoldingRegisters, &ucModbusPDU[MB_PDU_RESPONSE_READ_VALUES_OFF], usRegCount );
		}
	}
	//	�ͷ�����	
	vMBus_release();
	//	��¼�����ֵĴ���
	if ( MB_ENOERR != eStatus )
	{
		vMBusLogError( eStatus );
	}
	return	eStatus;
}

/********************************** ����˵�� ***********************************
*  FC04 Read Input Registers
*******************************************************************************/
eMBErrorCode	eMBMReadInputRegisters( uint8_t SlaveAddress, uint16_t usRegAddress, uint16_t usRegCount, uint16_t pInputRegisters[] )
{
	const uint8_t	ucNBytes = usRegCount * 2u;		//	�����ȡ���ݵ��ֽ���
	eMBErrorCode	eStatus = MB_ENOERR;
	uint16_t		usLen = 0u;

	assert(( usRegCount >= 1u ) && ( usRegCount <= MB_PDU_FUNC_READ_REGCNT_MAX ));
	//	�ȴ����߿���
	vMBus_apply();
	//	װ������
	ucModbusPDU[usLen++] = MB_FUNC_READ_INPUT_REGISTER; 		//	FC4
	ucModbusPDU[usLen++] = HIBYTE( usRegAddress );
	ucModbusPDU[usLen++] = LOBYTE( usRegAddress );
	ucModbusPDU[usLen++] = HIBYTE( usRegCount );
	ucModbusPDU[usLen++] = LOBYTE( usRegCount );
	//	����ͨѶ
	eStatus = eMBM_IO( SlaveAddress, &usLen );
	//	����Ӧ��
	if ( MB_ENOERR == eStatus )
	{
		if (( MB_PDU_RESPONSE_READ_SIZE + ucNBytes ) != usLen )
		{
			eStatus = MB_EX_Response_IllegalLength;
		}
		else if ( ucNBytes != ucModbusPDU[MB_PDU_RESPONSE_READ_BYTECNT_OFF] )
		{
			eStatus = MB_EX_Response_IllegalByteCnt;
		}
		else
		{	//	�ɹ�
			vMBus_Memory_Get( pInputRegisters, &ucModbusPDU[MB_PDU_RESPONSE_READ_VALUES_OFF], usRegCount );
		}
	}
	//	�ͷ�����
	vMBus_release();
	//	��¼�����ֵĴ���	
	if ( MB_ENOERR != eStatus )
	{
		vMBusLogError( eStatus );
	}
	return	eStatus;
}

/********************************** ����˵�� ***********************************
*  FC05 Write Signle Coil
*******************************************************************************/
eMBErrorCode	eMBMWriteSingleCoil( uint8_t SlaveAddress, uint16_t usRegAddress, BOOL CoilVal )
{
	const	uint16_t	CoilRegVal = ( CoilVal ) ? 0xFF00u : 0x0000u;
	eMBErrorCode	eStatus = MB_ENOERR;
	uint16_t		usLen = 0u;

	//	�ȴ����߿���
	vMBus_apply();
	//	װ������
	ucModbusPDU[usLen++] = MB_FUNC_WRITE_SINGLE_COIL; 		//	FC5
	ucModbusPDU[usLen++] = HIBYTE( usRegAddress );
	ucModbusPDU[usLen++] = LOBYTE( usRegAddress );
	ucModbusPDU[usLen++] = HIBYTE( CoilRegVal );
	ucModbusPDU[usLen++] = LOBYTE( CoilRegVal );
	//	����ͨѶ
	eStatus = eMBM_IO( SlaveAddress, &usLen );
	//	����Ӧ��
	if ( MB_ENOERR == eStatus )
	{
		if ( MB_PDU_RESPONSE_WRITE_SIZE != usLen )
		{
			eStatus = MB_EX_Response_IllegalLength;
		}
		else if ( MAKE16( ucModbusPDU[MB_PDU_DATA_OFF+1], ucModbusPDU[MB_PDU_DATA_OFF+0]) != usRegAddress )
		{
			eStatus = MB_EX_Response_IllegalAddress;
		}
		else if ( MAKE16( ucModbusPDU[MB_PDU_DATA_OFF+3], ucModbusPDU[MB_PDU_DATA_OFF+2]) != CoilRegVal )
		{
			eStatus = MB_EX_Response_IllegalValue;
		}
		else
		{	//	�ɹ�
			;
		}
	}	
	//	�ͷ�����
	vMBus_release();
	//	��¼�����ֵĴ���	
	if ( MB_ENOERR != eStatus )
	{
		vMBusLogError( eStatus );
	}
	return	eStatus;
}

/********************************** ����˵�� ***********************************
*  FC06 Write Signle Register
*******************************************************************************/
eMBErrorCode	eMBMWriteSingleRegister( uint8_t SlaveAddress, uint16_t usRegAddress, uint16_t RegisterVal )
{
	eMBErrorCode	eStatus = MB_ENOERR;
	uint16_t		usLen = 0u;

	//	�ȴ����߿���
	vMBus_apply();
	//	װ������
	ucModbusPDU[usLen++] = MB_FUNC_WRITE_REGISTER; 		//	FC6
	ucModbusPDU[usLen++] = HIBYTE( usRegAddress );
	ucModbusPDU[usLen++] = LOBYTE( usRegAddress );
	ucModbusPDU[usLen++] = HIBYTE( RegisterVal );
	ucModbusPDU[usLen++] = LOBYTE( RegisterVal );
	//	����ͨѶ
	eStatus = eMBM_IO( SlaveAddress, &usLen );
	//	����Ӧ��
	if ( MB_ENOERR == eStatus )
	{
		if ( MB_PDU_RESPONSE_WRITE_SIZE != usLen )
		{
			eStatus = MB_EX_Response_IllegalLength;
		}
		else if ( MAKE16( ucModbusPDU[MB_PDU_DATA_OFF+1], ucModbusPDU[MB_PDU_DATA_OFF+0]) != usRegAddress )
		{
			eStatus = MB_EX_Response_IllegalAddress;
		}
		else if ( MAKE16( ucModbusPDU[MB_PDU_DATA_OFF+3], ucModbusPDU[MB_PDU_DATA_OFF+2]) != RegisterVal )
		{
			eStatus = MB_EX_Response_IllegalValue;
		}
		else 
		{	//	�ɹ�
			;
		}
	}
	//	�ͷ�����
	vMBus_release();
	//	��¼�����ֵĴ���
	if ( MB_ENOERR != eStatus )
	{
		vMBusLogError( eStatus );
	}
	return	eStatus;
}

/********************************** ����˵�� ***********************************
*  FC15 Write Multiple Coils
*******************************************************************************/
eMBErrorCode	eMBMWriteMultipleCoils( uint8_t SlaveAddress, uint16_t usRegAddress, uint16_t usCoilCount, const uint8_t pCoilsVal[] )
{
	eMBErrorCode	eStatus = MB_ENOERR;
	uint16_t		usLen = 0u;

	assert(( usCoilCount >= 1u ) && ( usCoilCount <= MB_PDU_FUNC_WRITE_MUL_COILCNT_MAX ));
	//	�ȴ����߿���
	vMBus_apply();
	//	װ������
	ucModbusPDU[usLen++] = MB_FUNC_WRITE_MULTIPLE_COILS;	//	FC15
	ucModbusPDU[usLen++] = HIBYTE( usRegAddress );
	ucModbusPDU[usLen++] = LOBYTE( usRegAddress );
	ucModbusPDU[usLen++] = HIBYTE( usCoilCount );
	ucModbusPDU[usLen++] = LOBYTE( usCoilCount );
	{	//	����������ݵ�PDU
		const uint8_t	ucNBytes = HowBytes( usCoilCount );	//	���������ݵ��ֽ���
		ucModbusPDU[usLen++] = ucNBytes;
		memcpy( ucModbusPDU + usLen, pCoilsVal, ucNBytes );
		usLen += ucNBytes;
	}
	//	����ͨѶ
	eStatus = eMBM_IO( SlaveAddress, &usLen );
	//	����Ӧ��
	if ( MB_ENOERR == eStatus )
	{
		if ( MB_PDU_RESPONSE_WRITE_SIZE != usLen )
		{
			eStatus = MB_EX_Response_IllegalLength;
		}
		else if ( MAKE16( ucModbusPDU[MB_PDU_DATA_OFF+1], ucModbusPDU[MB_PDU_DATA_OFF+0]) != usRegAddress )
		{
			eStatus = MB_EX_Response_IllegalAddress;
		}
		else if ( MAKE16( ucModbusPDU[MB_PDU_DATA_OFF+3], ucModbusPDU[MB_PDU_DATA_OFF+2]) != usCoilCount )
		{
			eStatus = MB_EX_Response_IllegalCount;
		}
		else
		{	//	�ɹ�
			;
		}
	}
	//	�ͷ�����
	vMBus_release();
	//	��¼�����ֵĴ���
	if ( MB_ENOERR != eStatus )
	{
		vMBusLogError( eStatus );
	}
	return	eStatus;
}

/********************************** ����˵�� ***********************************
*  FC16 Write Multiple Registers
*******************************************************************************/
eMBErrorCode	eMBMWriteMultipleRegisters( uint8_t SlaveAddress, uint16_t usRegAddress, uint16_t usRegCount, const uint16_t pRegistersVal[] )
{
	eMBErrorCode	eStatus = MB_ENOERR;
	uint16_t		usLen = 0u;

	assert(( usRegCount >= 1u ) && ( usRegCount <= MB_PDU_FUNC_WRITE_MUL_REGCNT_MAX ));
	//	�ȴ����߿���
	vMBus_apply();
	//	װ������
	ucModbusPDU[usLen++] = MB_FUNC_WRITE_MULTIPLE_REGISTERS;	//	FC15
	ucModbusPDU[usLen++] = HIBYTE( usRegAddress );
	ucModbusPDU[usLen++] = LOBYTE( usRegAddress );
	ucModbusPDU[usLen++] = HIBYTE( usRegCount );
	ucModbusPDU[usLen++] = LOBYTE( usRegCount );
	{	//	����������ݵ�PDU
		const uint8_t	ucNBytes = usRegCount * 2u;	//	���������ݵ��ֽ���
		ucModbusPDU[usLen++] = ucNBytes;
		vMBus_Memory_Put( ucModbusPDU + usLen, pRegistersVal, usRegCount );
		usLen += ucNBytes;
	}
	//	����ͨѶ
	eStatus = eMBM_IO( SlaveAddress, &usLen );
	//	����Ӧ��
	if ( MB_ENOERR == eStatus )
	{
		if ( MB_PDU_RESPONSE_WRITE_SIZE != usLen )
		{
			eStatus = MB_EX_Response_IllegalLength;
		}
		else if ( MAKE16( ucModbusPDU[MB_PDU_DATA_OFF+1], ucModbusPDU[MB_PDU_DATA_OFF+0]) != usRegAddress )
		{
			eStatus = MB_EX_Response_IllegalAddress;
		}
		else if ( MAKE16( ucModbusPDU[MB_PDU_DATA_OFF+3], ucModbusPDU[MB_PDU_DATA_OFF+2]) != usRegCount )
		{
			eStatus = MB_EX_Response_IllegalCount;
		}
		else
		{	//	�ɹ�
			;
		}
	}
	//	�ͷ�����
	vMBus_release();
	//	��¼�����ֵĴ���
	if ( MB_ENOERR != eStatus )
	{
		vMBusLogError( eStatus );
	}
	return	eStatus;
}


/********************************** ����˵�� ***********************************
//	01 Read Coils( 0x )
//	02 Read Discretes Inputs( 1x )
//	03 Read Holding Register( 4x )
//	04 Read Input Register ( 3x )
*******************************************************************************/
eMBErrorCode	eMBMRead( uint8_t SlaveAddress, uint16_t Register, uint16_t Count, void * pBuf )
{
	eMBErrorCode	eStatus;
	uint16_t		RegAddress;
	uint8_t			RegArea;

	assert( (( Register >=     1u ) && ( Register <=  9999u )) ||
			(( Register >= 10001u ) && ( Register <= 19999u )) ||
			(( Register >= 40001u ) && ( Register <= 49999u )) ||
			(( Register >= 30001u ) && ( Register <= 39999u )) );

	RegArea    = (uint8_t)( Register / 10000u );
	RegAddress = (( Register % 10000u ) - 1u );
	switch ( RegArea )
	{
	case 0:		eStatus = eMBMReadCoils           ( SlaveAddress, RegAddress, Count, ( uint8_t * )pBuf );	break;	//	FC1
	case 1:		eStatus = eMBMReadDiscretes       ( SlaveAddress, RegAddress, Count, ( uint8_t * )pBuf );	break;	//	FC2
	case 4:		eStatus = eMBMReadHoldingRegisters( SlaveAddress, RegAddress, Count, ( uint16_t *)pBuf );	break;	//	FC3
	case 3:		eStatus = eMBMReadInputRegisters  ( SlaveAddress, RegAddress, Count, ( uint16_t *)pBuf );	break;	//	FC4
	default:	eStatus = MB_EINVAL;	break;
	}

	//	��¼�����ֵĴ���
	if ( MB_ENOERR != eStatus )
	{
		vMBusLogError( eStatus );
	}
	return	eStatus;
}

eMBErrorCode	eMBMWrite( uint8_t SlaveAddress, uint16_t Register, uint16_t Count, const void * pBuf )
{
	eMBErrorCode	eStatus;
	uint16_t		RegAddress;
	uint8_t			RegArea;

	assert((( Register >=     1u ) && ( Register <=  9999u )) ||
		   (( Register >= 40001u ) && ( Register <= 49999u )) );

	RegArea    = (uint8_t)( Register / 10000u );
	RegAddress = (( Register % 10000u ) - 1u );
	switch ( RegArea )
	{
	case 0:		eStatus = eMBMWriteMultipleCoils    ( SlaveAddress, RegAddress, Count, ( uint8_t  *)pBuf );	break;	// FC15	
	case 4:		eStatus = eMBMWriteMultipleRegisters( SlaveAddress, RegAddress, Count, ( uint16_t *)pBuf );	break;	// FC16
	default:	eStatus = MB_EINVAL;	break;
	}

	//	��¼�����ֵĴ���
	if ( MB_ENOERR != eStatus )
	{
		vMBusLogError( eStatus );
	}
	return	eStatus;
} 

/********************************** ����˵�� ***********************************
*  MBM ��ʼ��
*******************************************************************************/
eMBErrorCode	eMBMInit( eMBMode eMode, uint32_t ulBaudrate, eMBParity eParity )
{
	eMBErrorCode	eStatus = MB_ENOERR;
	
	eStatus = eMBM_IO_Init( eMode, ulBaudrate, eParity );
	
	if ( MB_ENOERR == eStatus )
	{
		vMBus_Mutex_Init();
	}

	return	eStatus;
}

/********  (C) COPYRIGHT 2013 �ൺ���˴���ӿƼ����޹�˾  **** End Of File ****/