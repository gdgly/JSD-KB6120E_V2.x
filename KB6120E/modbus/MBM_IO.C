/**************** (C) COPYRIGHT 2013 �ൺ���˴���ӿƼ����޹�˾ ****************
* �� �� ��: MBM_IO.C
* �� �� ��: ����
* ��  ��  : ���ݳ�ʼ�����ã�ת��MODBUS������ѡ����ͨѶ��ʽ��
* ����޸�: 2013��12��28��
*********************************** �޶���¼ ***********************************
* ��  ��: 
* �޶���: 
*******************************************************************************/
#include "MBM_BSP.H"
#include "MBM.H"
#include "MBM_Port.H"

static	eMBMode eCurrentMode;

/********************************** ����˵�� ***********************************
*  �����յ��Ĵӻ��쳣��Ӧ����ת���ɴ�����Ϣ����
*******************************************************************************/
static	eMBErrorCode	Exception2MBError( uint8_t ExceptionCode )
{
	static	eMBErrorCode const ExceptionList[] = 
	{
		MB_EX_Unknow,
		MB_EX_ILLEGAL_FUNCTION,         //  Illegal function exception.              01���쳣���Ƿ�����
		MB_EX_ILLEGAL_DATA_ADDRESS,     //  Illegal data address.                    02���쳣���Ƿ����ݵ�ַ
		MB_EX_ILLEGAL_DATA_VALUE,       //  Illegal data value.                      03���쳣���Ƿ�����ֵ
		MB_EX_SLAVE_DEVICE_FAILURE,     //  Slave device failure.                    04���쳣����վ�豸����
		MB_EX_ACKNOWLEDGE,              //  Slave acknowledge.                       05���쳣��ȷ��
		MB_EX_SLAVE_BUSY,               //  Slave device busy.                       06���쳣�������豸æ
		MB_EX_Unknow,
		MB_EX_MEMORY_PARITY_ERROR,      //  Memory parity error.                     08���쳣���洢��ż�Բ��
		MB_EX_Unknow,		
		MB_EX_GATEWAY_PATH_UNAVAILABLE, //  Gateway path unavailable.                0A���쳣������������·��
		MB_EX_GATEWAY_TARGET_FAILED,   	//  Gateway target device failed to respond. 0B���쳣������Ŀ���豸��Ӧʧ��
	};

	eMBErrorCode eStatus = MB_EX_Unknow;
	
	if ( ExceptionCode < sizeof( ExceptionList ) / sizeof(ExceptionList[0]))
	{
		eStatus = ExceptionList[ExceptionCode];
	}
	return	eStatus;
}

/********************************** ����˵�� ***********************************
	MBM ͨѶ
	������ӻ�ͨѶ������ͨѶ״̬
	������ָ���ӻ���������Ӧ��
	�쳣��ָ���ӻ����쳣��Ӧ�����а����������ܲ�һ�µ�������Ӧ
	��ʱ��ָ���ӻ��ڹ涨��ʱ��������Ӧ�������ӻ�����Ӧȫ������
*******************************************************************************/
eMBErrorCode	eMBM_IO( uint8_t ucSlaveAddress, uint16_t * pusLen )
{
	const	uint8_t	FunctionCode = ucModbusPDU[MB_PDU_FUNC_OFF];	//	��������Ĺ�����
	uint8_t ucRcvSlaveAddress = 0u;
	eMBErrorCode	eStatus;
	uint16_t	usLen = * pusLen;

	switch ( eCurrentMode )
	{
	case MB_RTU:
		eStatus = eMBM_RTU_Assemble( ucSlaveAddress, usLen );		//	װ��SerialPDU
		break;
	default:
		eStatus = MB_EINVAL;
	}
	
	if ( MB_ENOERR != eStatus )
	{
		return	eStatus;		//	װ�����������װ��ʱ����Ĵ���
	}
	
	//	�ȴ���������
	vMBM_RTU_Send_Init();										//	����Serial����
	if ( ! xMBM_EventPut_Poll())								//	�ȴ�Serila����
	{
		return	MB_EILLSTATE;	//	�ȴ�����ʱ������󣬷��� ��ֲ����
	}
	
	if ( MB_ADDRESS_BROADCAST == ucSlaveAddress )
	{
		return	MB_ENOERR;
	}
	
	//	�ȴ�Ӧ��������
	vMBM_RTU_Receive_Init( );									//	����Serial����
	if ( ! xMBM_EventGet_Poll())								//	�ȴ�Serial����
	{
		return	MB_ETIMEDOUT;	//	�ȴ�����ʱ������󣬷��� ��ʱ
	}

	switch ( eCurrentMode )
	{
	case MB_RTU:
		eStatus = eMBM_RTU_Analyze( &ucRcvSlaveAddress, &usLen );	//	����SerialPDU
		break;
	default:
		eStatus = MB_EINVAL;
	}

	if ( MB_ENOERR != eStatus )
	{
		return	eStatus;		//	���ճ��������ؽ���ʱ����Ĵ����� У���
	}
	
	//	�����ǶԽ��յ���ModbusPDU����һЩ���������ڼ��һЩ�����Ĵ���

	//	�������ӻ���Ӧ
	if ( ucRcvSlaveAddress != ucSlaveAddress )
	{
		return	MB_EX_Response_IllegalSlave;
	}

	//	������������Ӧ
	if ( FunctionCode != ( ucModbusPDU[MB_PDU_FUNC_OFF] & 0x7Fu ))
	{
		return	MB_EX_Response_IllegalFunction;
	}

	//	�쳣��Ӧ
	if ( MB_FUNC_ERROR & ucModbusPDU[MB_PDU_FUNC_OFF] )
	{	//	�����쳣��Ӧ����
		eStatus = Exception2MBError( ucModbusPDU[MB_PDU_DATA_OFF] );
		return	eStatus;
	}

	* pusLen = usLen;

	return	MB_ENOERR;
}


/********************************** ����˵�� ***********************************
*  MBM ��ʼ��
*******************************************************************************/
eMBErrorCode	eMBM_IO_Init( eMBMode eMode, uint32_t ulBaudRate, eMBParity eParity )
{
	eMBErrorCode    eStatus = MB_ENOERR;
    uint32_t		usTimerT35;

	eCurrentMode = eMode;
	
	switch ( eMode )
	{
	case MB_RTU:
		/* Modbus RTU uses 8 Databits. */
		vMBM_Serial_Init( ulBaudRate, 8u, eParity );
		/* If baudrate > 19200 then we should use the fixed timer values
		 * t35 = 1750us. Otherwise t35 must be 3.5 times the character time.
		 */
		if ( ulBaudRate > 19200u )
		{
			usTimerT35 = 1750u;
		}
		else
		{
			usTimerT35 = (uint32_t)( 1000000 * 11 * 3.5f ) / ulBaudRate ;
		}
        vMBM_Timers_Init( ( uint16_t ) usTimerT35 );
		break;

	default:
	case MB_ASCII:
	case MB_TCP:
		eStatus = MB_EINVAL;
		break;
	}

	if ( MB_ENOERR == eStatus )
	{
		vMBM_Event_Init();
	}

	return eStatus;
}

/********  (C) COPYRIGHT 2013 �ൺ���˴���ӿƼ����޹�˾  **** End Of File ****/