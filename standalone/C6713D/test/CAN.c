#include"math.h"
#include"c6x.h"

#include "struct.h"
#include "can.h"
#include "common.h"
#include "emif.h"
#include "interrupt.h"
#include "SJA1000.h"
#include "pll.h"
#include "regs.h"
#include "timer.h"


extern  CanMessage_queue_struct    can1_txd;
extern  CanMessage_queue_struct    can2_txd;
extern  CanMessage_queue_struct    can1_rxd;
extern  CanMessage_queue_struct    can2_rxd;


//----------------------------------------------------------
//-- CAN 队列初始化 SJA1000芯片初始化
//----------------------------------------------------------
void CAN_init()
{
 	CAN_init_can_queue((CanMessage_queue_struct *)&can1_rxd);
	//CAN_init_can_queue((CanMessage_queue_struct *)&can2_rxd);
	CAN_init_can_queue((CanMessage_queue_struct *)&can1_txd);
	//CAN_init_can_queue((CanMessage_queue_struct *)&can2_txd);

 	Sja1k_Chip_Init(CPLD_SJA1KBASE0,BTR_RATE_800K);
	//Sja1k_Chip_Init(CPLD_SJA1KBASE1,BTR_RATE_800K);

}


//----------------------------------------------------------
//-- initialize can frame struct
//----------------------------------------------------------
void CAN_init_can_frame(CanMessage_struct *frame)
{
    int    i;

    frame->extended_identifier = 0x00;
    frame->identifier = 0x00;
    frame->dlc = 0x8;
    frame->rtr = 0x0;
    frame->filhit = 0x0;
    for(i=0;i<CAN_MAX_CHAR_IN_MESSAGE;i++)
    {
        frame->data[i] = i;
    }
}

//----------------------------------------------------------
//-- initialize can frame queue struct
//----------------------------------------------------------
void CAN_init_can_queue(CanMessage_queue_struct *queen)
{
    int     i;

    queen->head = 0;
    queen->tail = 0;

    for(i=0;i<queue_max_len;i++)
    {
        CAN_init_can_frame((CanMessage_struct *)&queen->queue[i]);
    }
}

//----------------------------------------------------------
//-- dispatch received can frame
//----------------------------------------------------------
void  CAN_dispatch_receive_CANMessages(unsigned char chan,CanMessage_queue_struct *q)
{
    CanMessage_struct   frame;
#if 0
    if(q->tail != q->head)
    {
        frame = q->queue[q->tail];
        q->tail = q->tail + 1;
        if(q->tail>=queue_use_len)
        {
            q->tail = 0;
        }

        if(q->tail < 0)
        {
            q->tail = 0;
        }
        //CAN_UnpackageReceiveCANFrame(chan,(CanMessage_struct *)&frame);
        Sja1k_CAN_Msg_Read(chan,(CanMessage_struct *)&frame);
    }
#endif
    frame = q->queue[0];
    unsigned int baseAddr = CTRL_BUS_BASE;
    Sja1k_CAN_Msg_Read(baseAddr,(CanMessage_struct *)&frame);
}

//----------------------------------------------------------
//-- dispatch transmit can frame
//----------------------------------------------------------
void  CAN_dispatch_transmit_CANMessages(unsigned char chan,CanMessage_queue_struct *q)
{
    CanMessage_struct   frame;
		unsigned int	baseAddr;
		if (CANch1 == chan)
		{
			baseAddr = CTRL_BUS_BASE;
		}
		else
		{
			baseAddr = TEST_BUS_BASE;
		}
		frame = q->queue[0];
		baseAddr = CTRL_BUS_BASE;
		Sja1k_CAN_Msg_Send(baseAddr,frame);
#if 0
    if(q->tail != q->head)
    {
        frame = q->queue[q->tail];
         if( Sja1k_CAN_Msg_Send(baseAddr,frame) == SUCCESS)
        {
            q->tail = q->tail + 1;
        }
    }

    if(q->tail>=queue_use_len)
    {
        q->tail = 0;
    }

    if(q->tail < 0)
    {
        q->tail = 0;
    }
#endif
}

//----------------------------------------------------------
//-- unpackage can frame
//   unsigned char priority,message_ID,source_ID,target_ID,bus_no,sub_frame_no;
//   unsigned int  Tms_machine,Tms_UTC;
//   priority     = (unsigned char)((frame->identifier>>27)&0x03);
//   message_ID   = (unsigned char)((frame->identifier>>22)&0x1f);
//   source_ID    = (unsigned char)((frame->identifier>>16)&0x3f);
//   target_ID    = (unsigned char)((frame->identifier>>10)&0x3f);
//   bus_no       = (unsigned char)((frame->identifier>>8)&0x03);
//   sub_frame_no = (unsigned char)(frame->identifier&0xff);
//----------------------------------------------------------
void  CAN_UnpackageReceiveCANFrame(unsigned char chan,CanMessage_struct *frame)
{
   
}

//----------------------------------------------------------
//-- package transmit can frame
//----------------------------------------------------------
void  CAN_PackageTransmitCANMessages(CanMessage_queue_struct *q, CanMessage_struct frame)
{

	unsigned int IER_backup;
	IER_backup = IER;
	IER = 0x02;

    if((q->head >=0 ) && (q->head < queue_use_len))
    {
        q->queue[q->head] = frame;
        q->head++;
   }

    if(q->head >= queue_use_len)
    {
        q->head = 0;
    }

    if(q->head < 0)
    {
        q->head = 0;
    }
  	IER = IER_backup;
}

