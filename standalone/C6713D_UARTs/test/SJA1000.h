#ifndef _SJA1000_H_
	#define _SJA1000_H_

	/******************************************************************************/
	///SJA1000

	//��Ϣ����
	#define    EFF_DATA          0x80            //��չ����֡
	#define    EFF_REMOTE        0xC0            //��չԶ��֡

	// ���ƼĴ���
	#define    PELI_MOD          0x00            //�ڲ����ƼĴ���
	#define    PELI_CMR          0x01            //����Ĵ���
	#define    PELI_SR           0x02            //״̬�Ĵ���
	#define    PELI_IR           0x03            //�жϼĴ���
	#define    PELI_IER          0x04            //�ж�ʹ�ܼĴ���
	#define    PELI_BTR0         0x06            //���߶�ʱ�Ĵ���0
	#define    PELI_BTR1         0x07            //���߶�ʱ�Ĵ���1
	#define    PELI_OCR          0x08            //������ƼĴ���
	#define    PELI_TEST         0x09            //���ԼĴ���
	#define    PELI_ALC          0x0B            //�ٲö�ʧ��׽
	#define    PELI_ECC          0x0C            //������벶׽
	#define    PELI_EWLR         0x0D            //���󱨾��޶�
	#define    PELI_RXERR        0x0E            //���մ��������
	#define    PELI_TXERR        0x0F            //���ʹ��������
	#define    PELI_ACR0         0x10            //���մ���Ĵ���
	#define    PELI_ACR1         0x11            //���մ���Ĵ���
	#define    PELI_ACR2         0x12            //���մ���Ĵ���
	#define    PELI_ACR3         0x13            //���մ���Ĵ���
	#define    PELI_AMR0         0x14            //�������μĴ���
	#define    PELI_AMR1         0x15            //�������μĴ���
	#define    PELI_AMR2         0x16            //�������μĴ���
	#define    PELI_AMR3         0x17            //�������μĴ���

	// ���ͻ������Ĵ���
	#define    PELI_TXD_FID      0x10            //���ͻ�����1
	#define    PELI_TXD_ID0      0x11            //���ͻ�����2
	#define    PELI_TXD_ID1      0x12            //���ͻ�����3
	#define    PELI_TXD_ID2      0x13            //���ͻ�����4
	#define    PELI_TXD_ID3      0x14            //���ͻ�����5
	#define    PELI_TXB0         0x15            //���ͻ�����6
	#define    PELI_TXB1         0x16            //���ͻ�����7
	#define    PELI_TXB2         0x17            //���ͻ�����8
	#define    PELI_TXB3         0x18            //���ͻ�����9
	#define    PELI_TXB4         0x19            //���ͻ�����10
	#define    PELI_TXB5         0x1A            //���ͻ�����11
	#define    PELI_TXB6         0x1B            //���ͻ�����12
	#define    PELI_TXB7         0x1C            //���ͻ�����13

	// ���ջ������Ĵ���
	#define    PELI_RXD_FID      0x10            //���ջ�����1
	#define    PELI_RXD_ID0      0x11            //���ջ�����2
	#define    PELI_RXD_ID1      0x12            //���ջ�����3
	#define    PELI_RXD_ID2      0x13            //���ջ�����4
	#define    PELI_RXD_ID3      0x14            //���ջ�����5
	#define    PELI_RXB0         0x15            //���ջ�����6
	#define    PELI_RXB1         0x16            //���ջ�����7
	#define    PELI_RXB2         0x17            //���ջ�����8
	#define    PELI_RXB3         0x18            //���ջ�����9
	#define    PELI_RXB4         0x19            //���ջ�����10
	#define    PELI_RXB5         0x1A            //���ջ�����11
	#define    PELI_RXB6         0x1B            //���ջ�����12
	#define    PELI_RXB7         0x1C            //���ջ�����13
	#define    PELI_RXCOUNT      0x1D            //RX���ļ�����
	#define    PELI_RBSA         0x1E            //���ջ�������ʼ��ַ
	#define    PELI_CDR          0x1F            //ʱ�ӷ�Ƶ�Ĵ���

	//ģʽ�Ĵ���
	#define    PELI_MOD_RM       0x01            // ��λģʽ
	#define    PELI_MOD_LOM      0x02            // ֻ��ģʽ
	#define    PELI_MOD_STM      0x04            // �Լ��ģʽ
	#define    PELI_MOD_AFM      0x08            // �����˲���
	#define    PELI_MOD_SM       0x10            // ˯��

	//����Ĵ���
	#define    PELI_CMR_TR       0x01            // ��������
	#define    PELI_CMR_AT       0x02            // ��ֹ����
	#define    PELI_CMR_RRB      0x04            // �ͷŽ��ܻ�����
	#define    PELI_CMR_CDO      0x08            // ����������
	#define    PELI_CMR_SRR      0x10            // �Խ���ģʽ

	//״̬�Ĵ���
	#define    PELI_SR_RBS       0x01            // ���ջ�����״̬
	#define    PELI_SR_DOS       0x02            // �������״̬
	#define    PELI_SR_TBS       0x04            // ���ͻ�����״̬
	#define    PELI_SR_TCS       0x08            // �������״̬
	#define    PELI_SR_RS        0x10            // ����״̬
	#define    PELI_SR_TS        0x20            // ����״̬
	#define    PELI_SR_ES        0x40            // ����״̬
	#define    PELI_SR_BS        0x80            // ����״̬

	//�жϼĴ���
	#define    PELI_IR_RI        0x01            // �����ж�
	#define    PELI_IR_TI        0x02            // �����ж�
	#define    PELI_IR_EI        0x04            // ���󾯱��ж�
	#define    PELI_IR_DOI       0x08            // ��������ж�
	#define    PELI_IR_WUI       0x10            // �����ж�
	#define    PELI_IR_EPI       0x20            // ���������ж�
	#define    PELI_IR_ALI       0x40            // �ٲö�ʧ�ж�
	#define    PELI_IR_BEI       0x80            // ���߳����ж�

	//�ж�ʹ�ܼĴ���
	#define    PELI_IER_RIE      0x01            // �����ж�ʹ��
	#define    PELI_IER_TIE      0x02            // �����ж�ʹ��
	#define    PELI_IER_EIE      0x04            // ���󾯱��ж�ʹ��
	#define    PELI_IER_DOIE     0x08            // ��������ж�ʹ��
	#define    PELI_IER_WUIE     0x10            // �����ж�ʹ��
	#define    PELI_IER_EPIE     0x20            // ���������ж�ʹ��
	#define    PELI_IER_ALIE     0x40            // �ٲö�ʧ�ж�ʹ��
	#define    PELI_IER_BEIE     0x80            // ���߳����ж�ʹ��

	//ʱ�ӷ�Ƶ�Ĵ���
	#define    PELI_CDR_PELI     0x80            // ����PeliCANģʽ

	// CAN������SJA1000ͨѶ������. SJA1000�ľ���Ϊ ����Ϊ 16MHz ���趨ֵ
	// Samples = 1    SJW =1   BTR0:bit0-7  BTR1:bit8-15
	#define    BTR_RATE_100K     0x2F03          //100KBPS
	#define    BTR_RATE_200K     0x2F01          //200KBPS
	#define    BTR_RATE_400K     0x2F00          //400KBPS
	#define    BTR_RATE_500K     0x1C00          //500KBPS
	#define    BTR_RATE_600K     0x1900          //600KBPS
	#define    BTR_RATE_800K     0x1600          //800KBPS
	#define    BTR_RATE_1000K    0x1400          //1000KBPS

	// ��֤λ������λ���ã����õ��˲�ģʽ
	// ACR
	#define    PELI_ACR0_FID     0x00
	#define    PELI_ACR1_FID     0x00
	#define    PELI_ACR2_FID     0x60            // 000011 ���ؼ����
	#define    PELI_ACR3_FID     0x00
	// AMR 0:��� 1:�޹�
	#define    PELI_AMR0_FID     0xFF
	#define    PELI_AMR1_FID     0xF8
	#define    PELI_AMR2_FID     0x3F            // Bits:18-13 Ŀ��ID  ����Ŀ��IDΪ2��3��ͨ��
	#define    PELI_AMR3_FID     0xFF

	/*
	// AMR 0:��� 1:�޹�
	#define    PELI_AMR0_FID     0xFF
	#define    PELI_AMR1_FID     0xFF
	#define    PELI_AMR2_FID     0xFF            // Bits:18-13 Ŀ��ID
	#define    PELI_AMR3_FID     0xFF
	*/

	// ģʽ����
	#define    PELI_MODE_DATA    0x08            // ģʽ������: ���˲���������ģʽ
	#define    PELI_TEST_DATA    0xAA            // ����ֵ
	#define    PELI_CDR_DATA     0xC8            // ʱ�ֿ��Ƶ�ֵ: PeilCANģʽ��CLOCK��Ч���ر�����Ƚ���(Rxd0,Rxd1���Ƚ�)
	#define    PELI_INT_ENABLE   0x83            // �ж�ʹ�ܿ��Ƶ�ֵ: ���ߴ����жϡ������жϡ������ж�
	#define    PELI_OCR_DATA     0x1A            // ������Ƶ�ֵ:

	// ����������
	#define    TXD_ONCE_CMD      0x03            // ����һ�α��ķ��ͣ�������ʱ�����ط�(���η���)
	#define    TXD_CMD           0x01            // ������������,������ʱ���ط�
	#define    STR_CMD           0x12            // ����һ���Խ������ʵı��ķ��ͣ����ʹ���ʱ�����ط�
	#define    ATX_CMD           0x02            // ��ֹ��������
	#define    RRB_CMD           0x04            // �ͷŽ��ջ�����
	#define    COS_CMD           0x08            // ��������������

	/******************************************************************************/

	#define    CTRL_BUS_BASE     CPLD_SJA1KBASE0      //DSP int04
	#define    TEST_BUS_BASE     CPLD_SJA1KBASE1      //DSP int05


	void	Sja1k_Chip_Init(unsigned int baseAddr,unsigned short btr);
	void	Sja1k_Write_Byte(unsigned int baseAddr,unsigned char offset,unsigned char data);
	unsigned char	Sja1k_Read_Byte(unsigned int baseAddr,unsigned char offset);
	unsigned char	Sja1k_CAN_Msg_Send(unsigned int baseAddr,CanMessage_struct frame);
	unsigned char   Sja1k_CAN_Msg_Read(unsigned int baseAddr,CanMessage_struct *pframe);
#endif

