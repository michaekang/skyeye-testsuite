#include "c6x.h"
#include "struct.h"
#include "common.h"
#include "can.h"
#include "SJA1000.h"


//该函数用于SJA1000控制器写入一个数据, baseAddr:CA基地址 offset:偏移地址 data:待写入数据
void    Sja1k_Write_Byte(unsigned int baseAddr,unsigned char offset,unsigned char data)
{
    SET_MEMORY(baseAddr,unsigned short,offset); //写地址
    SET_MEMORY(baseAddr+4,unsigned short,data); //写数据
    return;
}

//该函数用于CAN控制器读出一个数据, baseAddr:CAN基地址 offset:偏移地址,返回: 读出的数据
unsigned char Sja1k_Read_Byte(unsigned int baseAddr,unsigned char offset)
{
    unsigned char data = 0;
    SET_MEMORY(baseAddr,unsigned short,offset);   // 地址到Sja1k口
    data = GET_MEMORY(baseAddr+4,unsigned short); // 读Sja1k口的数据到data
    return data;
}

//初始化SJA1000,baseAddr:基地址 btr0,btr1:波特率设置参数,返回状态
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
            Sja1k_Write_Byte(baseAddr,PELI_MOD,PELI_MOD_RM);// 进入复位模式
            ucTmp = Sja1k_Read_Byte(baseAddr,PELI_MOD);
        }
        while(((ucTmp&0x01) != 0x01)&&((exceedT++)<4096));

		if (exceedT >= 4096)
		{
			status = FAILED;
		}
		exceedT = 0;

        // 初始化时分控制器: PeilCAN模式、CLOCKOFF禁止
        Sja1k_Write_Byte(baseAddr,PELI_CDR,PELI_CDR_DATA); // 时分控制寄存器
    	ucTmp = Sja1k_Read_Byte(baseAddr,PELI_CDR);
        if(ucTmp != PELI_CDR_DATA)
        {
            status = FAILED;
    	}

    	// 中断控制: 关闭所有中断
        Sja1k_Write_Byte(baseAddr,PELI_IER,0x00); // 访问中断使能控制
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

        // 波特率
    	btr0 = (btr&0xff);
    	btr1 = ((btr>>8)&0xff);
        Sja1k_Write_Byte(baseAddr,PELI_BTR0,btr0); // 访问地址指向总线定时寄存器0
        ucTmp = Sja1k_Read_Byte(baseAddr,PELI_BTR0);
        if(ucTmp != btr0)
    	{
            status = FAILED;
    	}
        Sja1k_Write_Byte(baseAddr,PELI_BTR1,btr1); // 访问地址指向总线定时寄存器1
        ucTmp = Sja1k_Read_Byte(baseAddr,PELI_BTR1);
        if(ucTmp != btr1)
    	{
            status = FAILED;
    	}

        // 设置滤波器
        Sja1k_Write_Byte(baseAddr,PELI_ACR0,PELI_ACR0_FID); // 验收代码寄存器(ACR1)--IP地址最低位
        Sja1k_Write_Byte(baseAddr,PELI_ACR1,PELI_ACR1_FID); // 验收代码寄存器(ACR2)
        Sja1k_Write_Byte(baseAddr,PELI_ACR2,PELI_ACR2_FID); // 验收代码寄存器(ACR3)
        Sja1k_Write_Byte(baseAddr,PELI_ACR3,PELI_ACR3_FID); // 验收代码寄存器(ACR4)--IP地址最高位
        Sja1k_Write_Byte(baseAddr,PELI_AMR0,PELI_AMR0_FID); // 验收屏蔽寄存器(1屏，0有效)
        Sja1k_Write_Byte(baseAddr,PELI_AMR1,PELI_AMR1_FID); // 验收屏蔽寄存器(1屏，0有效)
        Sja1k_Write_Byte(baseAddr,PELI_AMR2,PELI_AMR2_FID); // 验收屏蔽寄存器(1屏，0有效)
        Sja1k_Write_Byte(baseAddr,PELI_AMR3,PELI_AMR3_FID); // 验收屏蔽寄存器(1屏，0有效)--最低二位不匹配

        // 设置模式寄存器：正常模式，单滤波模式
        Sja1k_Write_Byte(baseAddr,PELI_MOD,PELI_MODE_DATA);
        ucTmp = Sja1k_Read_Byte(baseAddr,PELI_MOD);
        if(ucTmp != PELI_MODE_DATA)
    	{
            status = FAILED;
    	}

    	//如果缓冲区有数，释放接收缓冲器中的信息
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

    	// 中断控制: 只开接收中断
        Sja1k_Write_Byte(baseAddr,PELI_IER,PELI_IR_RI); // 访问中断使能控制
        ucTmp = Sja1k_Read_Byte(baseAddr,PELI_IER);
        if(ucTmp != PELI_IR_RI)
    	{
            status = FAILED;
    	}

        while ((exceedT++) < 200); // 复位延时
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
    ucTmp = Sja1k_Read_Byte(baseAddr,PELI_SR); //访问地址指向状态寄存器

    if((ucTmp&0x04) == 0x04) //判断发送缓冲区状态  1:可以写，0:锁定
    {
	    // 帧报文信息: 扩展帧数据帧 + 数据长度 (无远程帧支持)
		ucTmp = EFF_DATA | (frame.dlc&0x0f);
	    Sja1k_Write_Byte(baseAddr,PELI_TXD_FID,ucTmp);

	    // ID
	    ID.u32 = 0;
	    ID.u32 = (frame.identifier<<3)&0xfffffff8;

	    Sja1k_Write_Byte(baseAddr,PELI_TXD_ID0,ID.u8[3]);
	    Sja1k_Write_Byte(baseAddr,PELI_TXD_ID1,ID.u8[2]);
	    Sja1k_Write_Byte(baseAddr,PELI_TXD_ID2,ID.u8[1]);
	    Sja1k_Write_Byte(baseAddr,PELI_TXD_ID3,ID.u8[0]);
	    // 数据
	    for(i=0;(i<8 && i<frame.dlc);i++)
	    {
	        Sja1k_Write_Byte(baseAddr,PELI_TXB0+i,frame.data[i]);
	    }

	    Sja1k_Write_Byte(baseAddr,PELI_CMR,TXD_CMD); //发送请求

		status = SUCCESS;

	}
	else
	{
	    status = FAILED;
	}

    CSR = CSR_backup;
    return status;
}

//从接收缓冲区读取CAN消息
unsigned char    Sja1k_CAN_Msg_Read(unsigned int baseAddr,CanMessage_struct *pframe)
{

	unsigned char i,format,ucTmp,status;
	Union_byte4 ID;
	CanMessage_struct frame;

	ucTmp = Sja1k_Read_Byte(baseAddr,PELI_SR); //访问地址指向状态寄存器

    if((ucTmp&0x01) == 0x01) //判断FIFO中是否有数
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

		//释放接收缓冲器中当前信息，使下一条立即生效，若缓冲区已空则释放中断
		Sja1k_Write_Byte(baseAddr,PELI_CMR, RRB_CMD);
		status = SUCCESS;
	}
    else
	{
	    status = FAILED;
	}

	return status;
}



