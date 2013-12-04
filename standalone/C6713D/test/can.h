#ifndef _CAN_H_
#define _CAN_H_


void CAN_init_can_frame(CanMessage_struct *frame);
void CAN_init_can_queue(CanMessage_queue_struct *queen);
void CAN_dispatch_receive_CANMessages(unsigned char chan,CanMessage_queue_struct *q);
void CAN_dispatch_transmit_CANMessages(unsigned char chan,CanMessage_queue_struct *q);
void CAN_UnpackageReceiveCANFrame(unsigned char chan,CanMessage_struct *frame);
void CAN_PackageTransmitCANMessages(CanMessage_queue_struct *q, CanMessage_struct frame);

#endif

