#ifndef _SJA1000_H_
	#define _SJA1000_H_

	/******************************************************************************/
	///SJA1000

	//消息类型
	#define    EFF_DATA          0x80            //扩展数据帧
	#define    EFF_REMOTE        0xC0            //扩展远程帧

	// 控制寄存器
	#define    PELI_MOD          0x00            //内部控制寄存器
	#define    PELI_CMR          0x01            //命令寄存器
	#define    PELI_SR           0x02            //状态寄存器
	#define    PELI_IR           0x03            //中断寄存器
	#define    PELI_IER          0x04            //中断使能寄存器
	#define    PELI_BTR0         0x06            //总线定时寄存器0
	#define    PELI_BTR1         0x07            //总线定时寄存器1
	#define    PELI_OCR          0x08            //输出控制寄存器
	#define    PELI_TEST         0x09            //测试寄存器
	#define    PELI_ALC          0x0B            //仲裁丢失捕捉
	#define    PELI_ECC          0x0C            //错误代码捕捉
	#define    PELI_EWLR         0x0D            //错误报警限额
	#define    PELI_RXERR        0x0E            //接收错误计数器
	#define    PELI_TXERR        0x0F            //发送错误计数器
	#define    PELI_ACR0         0x10            //验收代码寄存器
	#define    PELI_ACR1         0x11            //验收代码寄存器
	#define    PELI_ACR2         0x12            //验收代码寄存器
	#define    PELI_ACR3         0x13            //验收代码寄存器
	#define    PELI_AMR0         0x14            //验收屏蔽寄存器
	#define    PELI_AMR1         0x15            //验收屏蔽寄存器
	#define    PELI_AMR2         0x16            //验收屏蔽寄存器
	#define    PELI_AMR3         0x17            //验收屏蔽寄存器

	// 发送缓冲区寄存器
	#define    PELI_TXD_FID      0x10            //发送缓冲区1
	#define    PELI_TXD_ID0      0x11            //发送缓冲区2
	#define    PELI_TXD_ID1      0x12            //发送缓冲区3
	#define    PELI_TXD_ID2      0x13            //发送缓冲区4
	#define    PELI_TXD_ID3      0x14            //发送缓冲区5
	#define    PELI_TXB0         0x15            //发送缓冲区6
	#define    PELI_TXB1         0x16            //发送缓冲区7
	#define    PELI_TXB2         0x17            //发送缓冲区8
	#define    PELI_TXB3         0x18            //发送缓冲区9
	#define    PELI_TXB4         0x19            //发送缓冲区10
	#define    PELI_TXB5         0x1A            //发送缓冲区11
	#define    PELI_TXB6         0x1B            //发送缓冲区12
	#define    PELI_TXB7         0x1C            //发送缓冲区13

	// 接收缓冲区寄存器
	#define    PELI_RXD_FID      0x10            //接收缓冲区1
	#define    PELI_RXD_ID0      0x11            //接收缓冲区2
	#define    PELI_RXD_ID1      0x12            //接收缓冲区3
	#define    PELI_RXD_ID2      0x13            //接收缓冲区4
	#define    PELI_RXD_ID3      0x14            //接收缓冲区5
	#define    PELI_RXB0         0x15            //接收缓冲区6
	#define    PELI_RXB1         0x16            //接收缓冲区7
	#define    PELI_RXB2         0x17            //接收缓冲区8
	#define    PELI_RXB3         0x18            //接收缓冲区9
	#define    PELI_RXB4         0x19            //接收缓冲区10
	#define    PELI_RXB5         0x1A            //接收缓冲区11
	#define    PELI_RXB6         0x1B            //接收缓冲区12
	#define    PELI_RXB7         0x1C            //接收缓冲区13
	#define    PELI_RXCOUNT      0x1D            //RX报文计数器
	#define    PELI_RBSA         0x1E            //接收缓冲区起始地址
	#define    PELI_CDR          0x1F            //时钟分频寄存器

	//模式寄存器
	#define    PELI_MOD_RM       0x01            // 复位模式
	#define    PELI_MOD_LOM      0x02            // 只听模式
	#define    PELI_MOD_STM      0x04            // 自检测模式
	#define    PELI_MOD_AFM      0x08            // 验收滤波器
	#define    PELI_MOD_SM       0x10            // 睡眠

	//命令寄存器
	#define    PELI_CMR_TR       0x01            // 发送请求
	#define    PELI_CMR_AT       0x02            // 终止发送
	#define    PELI_CMR_RRB      0x04            // 释放接受缓冲器
	#define    PELI_CMR_CDO      0x08            // 清除数据溢出
	#define    PELI_CMR_SRR      0x10            // 自接收模式

	//状态寄存器
	#define    PELI_SR_RBS       0x01            // 接收缓冲器状态
	#define    PELI_SR_DOS       0x02            // 数据溢出状态
	#define    PELI_SR_TBS       0x04            // 发送缓冲器状态
	#define    PELI_SR_TCS       0x08            // 发送完毕状态
	#define    PELI_SR_RS        0x10            // 接收状态
	#define    PELI_SR_TS        0x20            // 发送状态
	#define    PELI_SR_ES        0x40            // 出错状态
	#define    PELI_SR_BS        0x80            // 总线状态

	//中断寄存器
	#define    PELI_IR_RI        0x01            // 接收中断
	#define    PELI_IR_TI        0x02            // 发送中断
	#define    PELI_IR_EI        0x04            // 错误警报中断
	#define    PELI_IR_DOI       0x08            // 数据溢出中断
	#define    PELI_IR_WUI       0x10            // 唤醒中断
	#define    PELI_IR_EPI       0x20            // 错误消极中断
	#define    PELI_IR_ALI       0x40            // 仲裁丢失中断
	#define    PELI_IR_BEI       0x80            // 总线出错中断

	//中断使能寄存器
	#define    PELI_IER_RIE      0x01            // 接收中断使能
	#define    PELI_IER_TIE      0x02            // 发送中断使能
	#define    PELI_IER_EIE      0x04            // 错误警报中断使能
	#define    PELI_IER_DOIE     0x08            // 数据溢出中断使能
	#define    PELI_IER_WUIE     0x10            // 唤醒中断使能
	#define    PELI_IER_EPIE     0x20            // 错误消极中断使能
	#define    PELI_IER_ALIE     0x40            // 仲裁丢失中断使能
	#define    PELI_IER_BEIE     0x80            // 总线出错中断使能

	//时钟分频寄存器
	#define    PELI_CDR_PELI     0x80            // 设置PeliCAN模式

	// CAN控制器SJA1000通讯波特率. SJA1000的晶振为 晶振为 16MHz 的设定值
	// Samples = 1    SJW =1   BTR0:bit0-7  BTR1:bit8-15
	#define    BTR_RATE_100K     0x2F03          //100KBPS
	#define    BTR_RATE_200K     0x2F01          //200KBPS
	#define    BTR_RATE_400K     0x2F00          //400KBPS
	#define    BTR_RATE_500K     0x1C00          //500KBPS
	#define    BTR_RATE_600K     0x1900          //600KBPS
	#define    BTR_RATE_800K     0x1600          //800KBPS
	#define    BTR_RATE_1000K    0x1400          //1000KBPS

	// 验证位和屏蔽位设置，采用单滤波模式
	// ACR
	#define    PELI_ACR0_FID     0x00
	#define    PELI_ACR1_FID     0x00
	#define    PELI_ACR2_FID     0x60            // 000011 运载计算机
	#define    PELI_ACR3_FID     0x00
	// AMR 0:相关 1:无关
	#define    PELI_AMR0_FID     0xFF
	#define    PELI_AMR1_FID     0xF8
	#define    PELI_AMR2_FID     0x3F            // Bits:18-13 目的ID  允许目的ID为2或3的通过
	#define    PELI_AMR3_FID     0xFF

	/*
	// AMR 0:相关 1:无关
	#define    PELI_AMR0_FID     0xFF
	#define    PELI_AMR1_FID     0xFF
	#define    PELI_AMR2_FID     0xFF            // Bits:18-13 目的ID
	#define    PELI_AMR3_FID     0xFF
	*/

	// 模式参数
	#define    PELI_MODE_DATA    0x08            // 模式控制器: 单滤波器、正常模式
	#define    PELI_TEST_DATA    0xAA            // 测试值
	#define    PELI_CDR_DATA     0xC8            // 时分控制的值: PeilCAN模式、CLOCK无效、关闭输入比较器(Rxd0,Rxd1不比较)
	#define    PELI_INT_ENABLE   0x83            // 中断使能控制的值: 总线错误中断、发送中断、接收中断
	#define    PELI_OCR_DATA     0x1A            // 输出控制的值:

	// 定义命令字
	#define    TXD_ONCE_CMD      0x03            // 产生一次报文发送，当错误时不再重发(单次发送)
	#define    TXD_CMD           0x01            // 发送请求命令,当错误时可重发
	#define    STR_CMD           0x12            // 产生一次自接收性质的报文发送，发送错误时不会重发
	#define    ATX_CMD           0x02            // 中止发送命令
	#define    RRB_CMD           0x04            // 释放接收缓冲区
	#define    COS_CMD           0x08            // 数据溢出清除命令

	/******************************************************************************/

	#define    CTRL_BUS_BASE     CPLD_SJA1KBASE0      //DSP int04
	#define    TEST_BUS_BASE     CPLD_SJA1KBASE1      //DSP int05


	void	Sja1k_Chip_Init(unsigned int baseAddr,unsigned short btr);
	void	Sja1k_Write_Byte(unsigned int baseAddr,unsigned char offset,unsigned char data);
	unsigned char	Sja1k_Read_Byte(unsigned int baseAddr,unsigned char offset);
	unsigned char	Sja1k_CAN_Msg_Send(unsigned int baseAddr,CanMessage_struct frame);
	unsigned char   Sja1k_CAN_Msg_Read(unsigned int baseAddr,CanMessage_struct *pframe);
#endif

