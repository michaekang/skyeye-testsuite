#include "c6x.h"
#include "struct.h"
#include "common.h"
#include "can.h"
#include "SJA1000.h"


//�ú�������SJA1000������д��һ������, baseAddr:CA����ַ offset:ƫ�Ƶ�ַ data:��д������
void    Sja1k_Write_Byte(unsigned int baseAddr,unsigned char offset,unsigned char data)
{
    SET_MEMORY(baseAddr,unsigned short,offset); //д��ַ
    SET_MEMORY(baseAddr+4,unsigned short,data); //д����
    return;
}

//�ú�������CAN����������һ������, baseAddr:CAN����ַ offset:ƫ�Ƶ�ַ,����: ����������
unsigned char Sja1k_Read_Byte(unsigned int baseAddr,unsigned char offset)
{
    unsigned char data = 0;
    SET_MEMORY(baseAddr,unsigned short,offset);   // ��ַ��Sja1k��
    data = GET_MEMORY(baseAddr+4,unsigned short); // ��Sja1k�ڵ����ݵ�data
    return data;
}

//��ʼ��SJA1000,baseAddr:����ַ btr0,btr1:���������ò���,����״̬
void    Sja1k_Chip_Init(unsigned int baseAddr,unsigned short btr)
{
    unsigned short i = 0 , exceedT = 0;
    unsigned char ucTmp,btr0,btr1,status;
	
	CSR &= 0xFFFFFFFE;
    do
    {
    	status = SUCCESS;
        do
        {
            Sja1k_Write_Byte(baseAddr,PELI_MOD,PELI_MOD_RM);// ���븴λģʽ
            ucTmp = Sja1k_Read_Byte(baseAddr,PELI_MOD);
        }
        while(((ucTmp&0x01) != 0x01)&&((exceedT++)<4096));

		if (exceedT >= 4096)
		{
			status = FAILED;
		}
		exceedT = 0;

        // ��ʼ��ʱ�ֿ�����: PeilCANģʽ��CLOCKOFF��ֹ
        Sja1k_Write_Byte(baseAddr,PELI_CDR,PELI_CDR_DATA); // ʱ�ֿ��ƼĴ���
    	ucTmp = Sja1k_Read_Byte(baseAddr,PELI_CDR);
        if(ucTmp != PELI_CDR_DATA)
        {
            status = FAILED;
    	}

    	// �жϿ���: �ر������ж�
        Sja1k_Write_Byte(baseAddr,PELI_IER,0x00); // �����ж�ʹ�ܿ���
        ucTmp = Sja1k_Read_Byte(baseAddr,PELI_IER);
        if(ucTmp != 0x00)
        {
            status = FAILED;
    	}
        //
        Sja1k_Write_Byte(baseAddr,PELI_OCR,PELI_OCR_DATA);
        ucTmp = Sja1k_Read_Byte(baseAddr,PELI_OCR);
        if(ucTmp != PELI_OCR_DATA)
    	{
            status = FAILED;
    	}

        // ������
    	btr0 = (btr&0xff);
    	btr1 = ((btr>>8)&0xff);
        Sja1k_Write_Byte(baseAddr,PELI_BTR0,btr0); // ���ʵ�ַָ�����߶�ʱ�Ĵ���0
        ucTmp = Sja1k_Read_Byte(baseAddr,PELI_BTR0);
        if(ucTmp != btr0)
    	{
            status = FAILED;
    	}
        Sja1k_Write_Byte(baseAddr,PELI_BTR1,btr1); // ���ʵ�ַָ�����߶�ʱ�Ĵ���1
        ucTmp = Sja1k_Read_Byte(baseAddr,PELI_BTR1);
        if(ucTmp != btr1)
    	{
            status = FAILED;
    	}

        // �����˲���
        Sja1k_Write_Byte(baseAddr,PELI_ACR0,PELI_ACR0_FID); // ���մ���Ĵ���(ACR1)--IP��ַ���λ
        Sja1k_Write_Byte(baseAddr,PELI_ACR1,PELI_ACR1_FID); // ���մ���Ĵ���(ACR2)
        Sja1k_Write_Byte(baseAddr,PELI_ACR2,PELI_ACR2_FID); // ���մ���Ĵ���(ACR3)
        Sja1k_Write_Byte(baseAddr,PELI_ACR3,PELI_ACR3_FID); // ���մ���Ĵ���(ACR4)--IP��ַ���λ
        Sja1k_Write_Byte(baseAddr,PELI_AMR0,PELI_AMR0_FID); // �������μĴ���(1����0��Ч)
        Sja1k_Write_Byte(baseAddr,PELI_AMR1,PELI_AMR1_FID); // �������μĴ���(1����0��Ч)
        Sja1k_Write_Byte(baseAddr,PELI_AMR2,PELI_AMR2_FID); // �������μĴ���(1����0��Ч)
        Sja1k_Write_Byte(baseAddr,PELI_AMR3,PELI_AMR3_FID); // �������μĴ���(1����0��Ч)--��Ͷ�λ��ƥ��

        // ����ģʽ�Ĵ���������ģʽ�����˲�ģʽ
        Sja1k_Write_Byte(baseAddr,PELI_MOD,PELI_MODE_DATA);
        ucTmp = Sja1k_Read_Byte(baseAddr,PELI_MOD);
        if(ucTmp != PELI_MODE_DATA)
    	{
            status = FAILED;
    	}

    	//����������������ͷŽ��ջ������е���Ϣ
    	do
    	{
    	    ucTmp = Sja1k_Read_Byte(baseAddr,PELI_SR);
    	    Sja1k_Write_Byte(baseAddr,PELI_CMR, RRB_CMD);
    	}while((ucTmp&0x01)&&((exceedT++)<4096));
		
		if (exceedT >= 4096)
		{
			status = FAILED;
		}

		exceedT = 0;

    	// �жϿ���: ֻ�������ж�
        Sja1k_Write_Byte(baseAddr,PELI_IER,PELI_IR_RI); // �����ж�ʹ�ܿ���
        ucTmp = Sja1k_Read_Byte(baseAddr,PELI_IER);
        if(ucTmp != PELI_IR_RI)
    	{
            status = FAILED;
    	}

        while ((exceedT++) < 200); // ��λ��ʱ
    }while((status == FAILED) && ((i++) < 500));

    CSR |= 1;

    return;
}

unsigned char   Sja1k_CAN_Msg_Send(unsigned int baseAddr,CanMessage_struct frame)
{
    unsigned char i,ucTmp,status;
    Union_byte4 ID;
	unsigned int	CSR_backup;

	CSR_backup = CSR;
	CSR &= 0xFFFFFFFE;
	asm(" nop 8");
    ucTmp = Sja1k_Read_Byte(baseAddr,PELI_SR); //���ʵ�ַָ��״̬�Ĵ���

    if((ucTmp&0x04) == 0x04) //�жϷ��ͻ�����״̬  1:����д��0:����
    {
	    // ֡������Ϣ: ��չ֡����֡ + ���ݳ��� (��Զ��֧֡��)
		ucTmp = EFF_DATA | (frame.dlc&0x0f);
	    Sja1k_Write_Byte(baseAddr,PELI_TXD_FID,ucTmp);

	    // ID
	    ID.u32 = 0;
	    ID.u32 = (frame.identifier<<3)&0xfffffff8;

	    Sja1k_Write_Byte(baseAddr,PELI_TXD_ID0,ID.u8[3]);
	    Sja1k_Write_Byte(baseAddr,PELI_TXD_ID1,ID.u8[2]);
	    Sja1k_Write_Byte(baseAddr,PELI_TXD_ID2,ID.u8[1]);
	    Sja1k_Write_Byte(baseAddr,PELI_TXD_ID3,ID.u8[0]);
	    // ����
	    for(i=0;(i<8 && i<frame.dlc);i++)
	    {
	        Sja1k_Write_Byte(baseAddr,PELI_TXB0+i,frame.data[i]);
	    }

	    Sja1k_Write_Byte(baseAddr,PELI_CMR,TXD_CMD); //��������

		status = SUCCESS;

	}
	else
	{
	    status = FAILED;
	}

    CSR = CSR_backup;
    return status;
}

//�ӽ��ջ�������ȡCAN��Ϣ
unsigned char    Sja1k_CAN_Msg_Read(unsigned int baseAddr,CanMessage_struct *pframe)
{

	unsigned char i,format,ucTmp,status;
	Union_byte4 ID;
	CanMessage_struct frame;

	ucTmp = Sja1k_Read_Byte(baseAddr,PELI_SR); //���ʵ�ַָ��״̬�Ĵ���

    if((ucTmp&0x01) == 0x01) //�ж�FIFO���Ƿ�����
    {
		format = Sja1k_Read_Byte(baseAddr,PELI_RXD_FID);
		frame.dlc = format & 0x0F;

		ID.u8[3] = Sja1k_Read_Byte(baseAddr, PELI_RXD_ID0);
		ID.u8[2] = Sja1k_Read_Byte(baseAddr, PELI_RXD_ID1);
	    ID.u8[1] = Sja1k_Read_Byte(baseAddr, PELI_RXD_ID2);
		ID.u8[0] = Sja1k_Read_Byte(baseAddr, PELI_RXD_ID3);

        frame.identifier = (ID.u32>>3)&0x1fffffff;

        for ( i = 0; i< 8; i++)
		{
			frame.data[i] = 0x00;
		}
		for(i = 0; ((i<frame.dlc) && (i<8)); i++)
		{
			frame.data[i] = Sja1k_Read_Byte(baseAddr, PELI_RXB0 + i);
		}

		*pframe = frame;

		//�ͷŽ��ջ������е�ǰ��Ϣ��ʹ��һ��������Ч�����������ѿ����ͷ��ж�
		Sja1k_Write_Byte(baseAddr,PELI_CMR, RRB_CMD);
		status = SUCCESS;
	}
    else
	{
	    status = FAILED;
	}

	return status;
}



