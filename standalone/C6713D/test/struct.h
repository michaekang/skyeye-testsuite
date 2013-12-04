#ifndef _STRUCT_H_
#define _STRUCT_H_

#define		CPLD_SJA1KBASE0			0xB0000040			//实际地址 = 基址+内部寄存器地址
#define		CPLD_SJA1KBASE1			0xB0000048			//实际地址 = 基址+内部寄存器地址
#define  	CANch1                       0
#define  	CANch2                       1


#define    GET_MEMORY(addr,type)          (*(volatile type*)(addr))
#define    SET_MEMORY(addr,type,value)    (*(volatile type*)(addr) = (value))

//----------------------------------------------------------
//--program run status define
//----------------------------------------------------------
#define  Test_Status  0x55
#define  Poli_check   0xaa
#define  Simu_Status  0xFF

//----------------------------------------------------------
//--const define
//----------------------------------------------------------
#define   c_lamta     (1.0/298.257)
#define   c_a_IAG75   6378140.0
#define   c_b_IAG75   6356755.28856
#define   c_GM        3.986005e+14
#define   c_J         (1.5 *1.08263e-3)
#define   c_wie       7.292115e-5
#define   c_e2_IAG75  0.00669438487525

#define   c_PI        3.1415926535897932384626433832795

#define   Missile_M0  1160.5		//导弹初始质量

#define   Sync_1	  1
#define   Sync_2	  2
#define   Sync_3	  3
//----------------------------------------------------------
//--float32 to bytes
//----------------------------------------------------------
union b4f
{
    float         f32;
    unsigned char b[4];
};

//----------------------------------------------------------
//--float64 to bytes
//----------------------------------------------------------
union b8f
{
    double        f64;
    unsigned char b[8];
};

//----------------------------------------------------------
//--CAN frame struct define
//  CAN message queue define,max length 510,usefull length 500
//----------------------------------------------------------
#define  CAN_MAX_CHAR_IN_MESSAGE         8

typedef struct
{
	unsigned char  extended_identifier;// identifier CAN_xxxID
	unsigned int   identifier;         // either extended (the 29 LSB) or standard (the 11 LSB)
	unsigned char  dlc;                // data length:
	unsigned char  data[CAN_MAX_CHAR_IN_MESSAGE];
	unsigned char  rtr;                // remote
	unsigned char  filhit;             // Acceptence Filter that enabled the reception
}CanMessage_struct;

//#define  queue_max_len                   510
#define  queue_max_len                   1
#define  queue_use_len                   500

typedef struct
{
    CanMessage_struct   queue[queue_max_len];
    int                 head,tail;
}CanMessage_queue_struct;

//----------------------------------------------------------
//--system self test result define
//----------------------------------------------------------
#define  SDRAM_TEST_START_ADDRESS        0x80100000
#define  SDRAM_TEST_LENGTH               0x00080000

#define  FLASH_TEST_START_ADDRESS        0x90000000
#define  FLASH_TEST_LENGTH               0x40000

typedef struct
{
    unsigned char     	sdram_status;
    unsigned char		flash_status;
    unsigned char		timer0_status;
    unsigned char		CAN1_status,CAN2_status;
    unsigned char		IMU_Data_Read_status;
	unsigned char		Warhead_Data_Read_status;
    unsigned char     	end;
    unsigned int      	imu_counter_status;
    short             	time_counter;
}self_test_struct;

//----------------------------------------------------------
//--IMU test and calcaulate define
//  attention : imu_ori_para_struct size must be in 16bits
//----------------------------------------------------------
typedef struct
{
    unsigned char  no[16];
    double         K0x,K0y,K0z,K1x,K1y,K1z,K2x,K2y,K2z,Kyx,Kxy,Kxz,Kzx,Kzy,Kyz;
    double         D0x,D0y,D0z,E1x,E1y,E1z,Eyx,Exy,Exz,Ezx,Ezy,Eyz;
    double         Z0,Y0,B0,G0;
    double         D1x,D2x,D3x,D1y,D2y,D3y,D1z,D2z,D3z;

    unsigned char            read_times,write_times;
    unsigned short crc;
}imu_ori_para_struct;

typedef struct
{
    int           counter_forword[12],imu_counter_sub[12];
	int			  pax_sum,pay_sum,paz_sum,pgx_sum,pgy_sum,pgz_sum;
    int           pax,pay,paz,pgx,pgy,pgz;
	short         pax_simu,pay_simu,paz_simu,pgx_simu,pgy_simu,pgz_simu;
	short         pax_simu_1,pay_simu_1,paz_simu_1,pgx_simu_1,pgy_simu_1,pgz_simu_1;
    double        ax,ay,az,gx,gy,gz,ax_1,ay_1,az_1,gx_1,gy_1,gz_1;

    double        a0x,a0y,a0z,g0x,g0y,g0z;
    double        G11,G12,G13,G21,G22,G23,G31,G32,G33,
                  T11,T12,T13,T21,T22,T23,T31,T32,T33,
                  M11,M12,M13,M21,M22,M23,M31,M32,M33;
    unsigned char calculate;
}imu_struct;


#define		WarHead_300Kg	0
#define		WarHead_200Kg	1

typedef struct
{
	unsigned char	head_type;
	unsigned char	bomb_type;
	unsigned short	reserved;
	unsigned int	missile_No;
}warhead_struct;
//----------------------------------------------------------
//--helm control signal
//----------------------------------------------------------
typedef struct
{
    float      helm1,helm3,helm2,helm4;
}helm_struct;

//----------------------------------------------------------
//--program exccute error code define
//----------------------------------------------------------
#define      Err_GNSS_Frame17_Ack  0x01
#define      Err_GNSS_Sync         0x02
#define      Err_GNSS_Location     0x04
#define      Err_GNSS_Work_Mode    0x08
#define      Err_WM_Frame21_Ack    0x10
#define      Err_WM_Sync           0x20
#define      Err_WM_Work_Mode      0x40
#define      Err_Run_hor_Exceed    0x80
#define      Err_K40_Time_Align    0x100
#define      Err_K39_Time_Align    0x200


//----------------------------------------------------------
//--program exccute control struct
//  time_counter : this machine run time form power on
//  time_run : program run time after selftest
//----------------------------------------------------------
typedef struct
{
    unsigned char   Exec_Status,Terminate_Run;
    unsigned char   sub_exec_status;
    unsigned char   Run_Hor_1st,Run_Hor_1st_end,Run_Hor_2nd,Run_Hor_2nd_end,Igit_Trig;
    unsigned char   K40_Time_Align,K39_Time_Align;
    unsigned int    ErrCode;

    unsigned char   aux_nav_refresh;
    int             aux_nav_counter,aux_cycle;
    int             ctrl_switch;
    int             time_counter,time_run;

    int             two,four;
    unsigned char   exec_control_status;
    unsigned char   mobile_stage;
	int 			mobile_time0;
    int             cn_ax;    
}Program_Exec_struct;

//----------------------------------------------------------
//--GNSS frame 70 struct define
//  same as document define SY400 CAN BUS protocol
//----------------------------------------------------------
typedef struct
{
    unsigned char   buf[48];
    unsigned char   day,month;
    unsigned short  year;
    unsigned int    UTC;
    int             x,y,z,vx,vy,vz;
    unsigned int    t70ms;
    unsigned char   time_mode,location_mode,start_num,reserv1;
    unsigned short  GDOP;
    unsigned int    reserv2;
    unsigned short  CRC;
}
GNSS_70_struct;

//----------------------------------------------------------
//--GNSS message struct define
//  GNSS assistant data 6s(aT,dX,dY,dZ)
//  INS data 1s(rec_fs_T,rec_fs_X,rec_fs_Y,rec_fs_Z,rec_fs_Vx,rec_fs_Vy,rec_fs_Vz)
//----------------------------------------------------------
#define      Max_10s_aux_GNSS_Dots        45
#define      Useful_10s_aux_GNSS_Dots     40
#define      Max_Record_1s_Ins_Dots       110
#define      Useful_Record_1s_Ins_Dots    100
typedef struct
{
    unsigned char Run_Status,mode;
    float         Xdx0,Ydx0,Zdx0;
    float         a11,a12,a13,a21,a22,a23,a31,a32,a33;

    unsigned char frame17_ack;
    unsigned char location;
    unsigned char new_frame70;
	unsigned char new_frame70_effect;
    int           T45ms_machine,T45ms_UTC;
    float         t45s_machine,t45s_UTC;

    float         Dt,t70;
    int 		  t70_start;
	int 		  t70_start0,t70_start1,t70_start2,t70_start3,t70_start4;
    float         x,y,z,vx,vy,vz;
    float         tofsX,tofsY,tofsZ,tofsVx,tofsVy,tofsVz;
    unsigned char sample;

    int           dots;
    float         aT[Max_10s_aux_GNSS_Dots],
                  dX[Max_10s_aux_GNSS_Dots],
                  dY[Max_10s_aux_GNSS_Dots],
                  dZ[Max_10s_aux_GNSS_Dots];
    int           rec_fs_index;
    float         rec_fs_T[Max_Record_1s_Ins_Dots],
                  rec_fs_X[Max_Record_1s_Ins_Dots],
                  rec_fs_Y[Max_Record_1s_Ins_Dots],
                  rec_fs_Z[Max_Record_1s_Ins_Dots],
                  rec_fs_Vx[Max_Record_1s_Ins_Dots],
                  rec_fs_Vy[Max_Record_1s_Ins_Dots],
                  rec_fs_Vz[Max_Record_1s_Ins_Dots];
    unsigned char err_refresh;
	unsigned char ctrl;
	float last_effect_dots;
    float         err_t,err_dx,err_dy,err_dz,err_dvx,err_dvy,err_dvz;
}
GNSS_struct;

//----------------------------------------------------------
//--WM frame 70 struct define
//  same as document define SY400 CAN BUS protocol
//----------------------------------------------------------
typedef struct
{
    unsigned char   buf[40];
    unsigned char   valid,station_no;
    unsigned short  T70_count;
    unsigned int    t70ms;
    unsigned int    dr;
    int             x,y,z;
    int             dt1,dt2;
    unsigned int    reserv1;
    unsigned short  reserv2;
    unsigned short  CRC;
}
WM_70_struct;

//----------------------------------------------------------
//--WM message struct define
//  WM data record 1s(rno,rt,rdr,rdt1,rdt2,rxp,ryp,rzp)
//  WM data calculate maxium maybe 1s(cno,ct,cdr,cdt1,cdt2,cxp,cyp,czp)
//  INS record data 1.1s(INS_T,INS_X,......,INS_Wcey,INS_Wcez)
//  WM assistant data 6s(Aux_WM_T,Aux_WM_Dx,Aux_WM_Dy,Aux_WM_Dz)
//----------------------------------------------------------
#define Max_Record_WM_1s_Datas_Len       55
#define Useful_Record_WM_1s_Datas_Len    50

#define Max_Calac_WM_1s_Datas_len        30
#define Useful_Calac_WM_1s_Datas_len     25

#define Max_Record_INS_1z1s_Datas_Len    120
#define Useful_Record_INS_1z1s_Datas_Len 110

#define Max_Err_Calac_10s_Datas_Len      205
#define Useful_Err_Calac_10s_Datas_Len   200

typedef struct
{
    unsigned char mode;
    float         Xdx0,Ydx0,Zdx0;
    float         a11,a12,a13,a21,a22,a23,a31,a32,a33;
    float         R0x,R0y,R0z;

    unsigned char frame21_ack;
    int           T45ms1_machine,T45ms2_machine;
    float         t45s1_machine,t45s2_machine;

    unsigned char no;
    float         t70,t70_machine;
    float         dr,x,y,z,dt1,dt2;//x,y,z地面站坐标,84坐标系
    float         xp,yp,zp;//地面站坐标，转换到地面发射坐标系
    unsigned char new_frame70,new_frame70_effect1,new_frame70_effect2;
    unsigned char sample;

    unsigned char rno[Max_Record_WM_1s_Datas_Len];
    float         rt[Max_Record_WM_1s_Datas_Len],
                  rdr[Max_Record_WM_1s_Datas_Len],
                  rdt1[Max_Record_WM_1s_Datas_Len],
                  rdt2[Max_Record_WM_1s_Datas_Len],
                  rxp[Max_Record_WM_1s_Datas_Len],
                  ryp[Max_Record_WM_1s_Datas_Len],
                  rzp[Max_Record_WM_1s_Datas_Len];

    unsigned char cno[Max_Calac_WM_1s_Datas_len];
    float         ct[Max_Calac_WM_1s_Datas_len],
                  cdr[Max_Calac_WM_1s_Datas_len],
                  cdt1[Max_Calac_WM_1s_Datas_len],
                  cdt2[Max_Calac_WM_1s_Datas_len],
                  cxp[Max_Calac_WM_1s_Datas_len],
                  cyp[Max_Calac_WM_1s_Datas_len],
                  czp[Max_Calac_WM_1s_Datas_len];

    int           rec_fs_1z1s_index;
    float         INS_T[Max_Record_INS_1z1s_Datas_Len],
                  INS_X[Max_Record_INS_1z1s_Datas_Len],
                  INS_Y[Max_Record_INS_1z1s_Datas_Len],
                  INS_Z[Max_Record_INS_1z1s_Datas_Len],
                  INS_Vx[Max_Record_INS_1z1s_Datas_Len],
                  INS_Vy[Max_Record_INS_1z1s_Datas_Len],
                  INS_Vz[Max_Record_INS_1z1s_Datas_Len],
                  INS_Gx[Max_Record_INS_1z1s_Datas_Len],
                  INS_Gy[Max_Record_INS_1z1s_Datas_Len],
                  INS_Gz[Max_Record_INS_1z1s_Datas_Len],
                  INS_Wx[Max_Record_INS_1z1s_Datas_Len],
                  INS_Wy[Max_Record_INS_1z1s_Datas_Len],
                  INS_Wz[Max_Record_INS_1z1s_Datas_Len],
                  INS_Wcex[Max_Record_INS_1z1s_Datas_Len],
                  INS_Wcey[Max_Record_INS_1z1s_Datas_Len],
                  INS_Wcez[Max_Record_INS_1z1s_Datas_Len];

    int           Aux_WM_Effect_Dots;

    float         Aux_WM_T[Max_Err_Calac_10s_Datas_Len],
                  Aux_WM_Dx[Max_Err_Calac_10s_Datas_Len],
                  Aux_WM_Dy[Max_Err_Calac_10s_Datas_Len],
                  Aux_WM_Dz[Max_Err_Calac_10s_Datas_Len];
	unsigned char ctrl;
	float 		  last_effect_dots;
	float		  PDOP,VDOP;
	float		  dx_w,dy_w,dz_w;
    float         err_t,err_dx,err_dy,err_dz,err_dvx,err_dvy,err_dvz;
    unsigned char err_refresh;
}
WM_struct;

//----------------------------------------------------------
//--safe control struct define
//----------------------------------------------------------
typedef struct
{
    unsigned char Bomb_Type;
    unsigned char pre_destroy,destroy;
    int           cnx,cny,cnz;
    int           Run_counter;
}
safe_control_struct;

//----------------------------------------------------------
//--bomb message struct define
//----------------------------------------------------------
#define BOMB_SEED_TYPE              0x00
#define BOMB_WHOLE_YUNBAO_TYPE      0x01
#define BOMB_WHOLE_SHABAO_TYPE      0x02
typedef struct
{
    unsigned short type;
    float          Tjd,Tj2,Tjz,T2g;

    unsigned char  Bomb_detonate_ack;
    float          v,a;
    short          ack_a,ack_v,ack_type,ack_high;

    unsigned char  jd_f,j2_f,jz_f,qb_f;

    double         xf,yf,zf,vxf,vyf,vzf,gx,gy,gz;
    double         Hfj,Hfj_1,Hdxm;

    double         R0X,R0Y,R0Z;
    double         W3W3,OX3,OY3,OZ3,OX,OY,OZ;
  
}
bomb_message_struct;

//----------------------------------------------------------
//-- ciceroni_calculate struct define
//   thita_len,thita from bind data,calculate standard thita
//   k1k2_len,L,K2_b from bind data,calculate K1 and K2
//   thita_f from bind data
//----------------------------------------------------------
#define Max_bind_thita_h_len   249
#define Max_bind_K1K2_len      249
typedef struct
{
    int           thita_len;
    float         thita_V[Max_bind_thita_h_len],thita[Max_bind_thita_h_len];

    int           k1k2_len;
    float         L[Max_bind_K1K2_len],K2_b[Max_bind_K1K2_len];
    float         thita_f;

    float         K1y,K1z,K0z;

    float         thita_s,Ky,Kz;
    float         Uy,Uz,Uy1,Uz1;
    
    float         Run_time_2nd;
    float         Eita,Eita_1,dEita[2],d_eita_t;
    float         s,s_1,ds[2],d_s_t;
    float         Tg,K1,K2;
    unsigned char d_diff_1st;    

    float         H_blind,Ls,H_blind_Ls,flag;
    unsigned char blind_stop;
	
    float         dthta_s,dxigma_s;
    
    unsigned char data_refresh;
    float         dd_thita,dd_xgma;

}ciceroni_cal_struct;

//----------------------------------------------------------
//-- stance_system struct define
//   fai_len,fai_V,fai from bind data,calculate standard fai
//   G0,G1,H1 from bind data
//   A0,A1,A2,A3,B1,B2,B3 inter from bind data
//   E0,E1,E2,E3,F1,F2,F3 inter from bind data
//   CycleT0 <= 0.01
//   gama0 <= TP.gama0
//----------------------------------------------------------
#define Max_bind_fai_len      249
typedef struct
{
    int           fai_len;
    float         fai_V[Max_bind_fai_len],fai[Max_bind_fai_len];

    float         G0,G1,H1;
    float         A0,A1,A2,A3,B1,B2,B3;
    float         C0,C1,C2,D1,D2;
    float         E0,E1,E2,E3,F1,F2,F3;
    float         f1_A0,f1_A1,f1_B1;
    float         f2_C0,f2_C1,f2_C2,f2_D1,f2_D2;
    float         CycleT0;//0.01
    float         gama0;
	
    float         fai_time0,psa_time0,gma_time0;

    int           run_time;
    float         fai_s,psa_s,gama_s;
    float         Vf0,Vf1;
    float         smooth_fai0,smooth_v0;

    float         q0,q1,q2,q3;
    float         dg,dp,df;

    float         NfI[4],NpI[4],NgI[4],NgsI[4];
    float         NfO[4],NpO[4],NgO[4],NgsO[4];    
    float         f_NfI[4],f_NpI[4],f_NfO[4],f_NpO[4],f_NgI[4],f_NgO[4];
    float         f1_FI[4],f1_FO[4],f1_PI[4],f1_PO[4];
    float         f2_FI[4],f2_FO[4],f2_PI[4],f2_PO[4];
	float		  Ugamazd;
	float		  sc;
	float         Kp;
    float         Ksc,Kt_fp,Kta_fp,Kt_gama;
    float         fai_Kh,fai_Ka,fai_omiga,psa_Kh,psa_Ka,psa_omiga;
    float         Dp_f,Dp_p;
    float         Cmax,Cmin;
    float         thita_g,thita_max,thita_min;
    float         inter_dd_thita,inter_dd_xgma;
    float         U1,U3,U2,U4;
	float		  inter_M;					//200Kg	计算质量时的积分部分
    float		  M;						//200Kg 实时的导弹质量
	float		  Kfs;						//200Kg
	float		  Kfs_gama,Ksc_gama;		//200Kg
	float	 	  Ca;						//200Kg
	float		  wiP,KaP,KhP,KmP;
	float		  wiY,KaY,KhY,KmY;
	float		  M0,M1,N1;					//低通滤波器参数M0,M1,N1
	float		  NgdtI[4],Ugd[4];
	float		  Kc,Ugf;
	float		  gama2_Kh,gama2_Kam;
	float		  Clmax,Clmin;
    int           mobile_time0;
    int           roll_gama_time;    
}stance_system_struct;

//----------------------------------------------------------
//--navigation calculate message struct define
//  g0 from bind data
//  Cycle_T0 <= 0.01
//----------------------------------------------------------
typedef struct
{
    double         g0;
    double         Cycle_T0;
    double         Q0,Q1,Q2,Q3;
    double         a11,a12,a13,a21,a22,a23,a31,a32,a33;
	double		   dwx1j,dwy1j,dwz1j;
    double         Dwxj,Dwyj,Dwzj;
    double         X,Y,Z;
    double         Vx,Vy,Vz;
    double         Gx,Gy,Gz;
    double         Gx_1,Gy_1,Gz_1;
    double         R_1,High,High_1;
    double         V,V_1;
    float          thita;
    int            Nav_Run_Time;
}Nav_Cal_Struct;

//----------------------------------------------------------
//--navigation(fs) calculate message struct define
//  A0,B0,H0,X_target,Y_target,Z_target from bind data
//  Cycle_T0 <= 0.01
//  omg_x,omg_y,omg_z,omg_x2,omg_xy,omg_xz,omg_y2,omg_yz,omg_z2 navigation calculate const
//  R0,R1,R0x,R0y,R0z,H01 navigation calculate const
//----------------------------------------------------------
typedef struct
{
    float         A0,B0,H0;
    float         X_target,Y_target,Z_target;
	float		  Lm;
    float         Cycle_T0;

    float         Xdx0,Ydx0,Zdx0;
    float         Dx2fs11,Dx2fs12,Dx2fs13,Dx2fs21,Dx2fs22,Dx2fs23,Dx2fs31,Dx2fs32,Dx2fs33;

    double        omg_x,omg_y,omg_z;
    double        omg_x2,omg_xy,omg_xz,omg_y2,omg_yz,omg_z2;
    double        R0,R1,R0x,R0y,R0z;
    double        H01;

    double        b11,b12,b13,b21,b22,b23,b31,b32,b33;
    double        dwxj,dwyj,dwzj;
    double        H_asl,H_rel;
    double        X0,Y0,Z0,Vx0,Vy0,Vz0;
	double        X,Y,Z,Vx,Vy,Vz;
    double        Gx,Gy,Gz;
    double        wcxwex,wcywey,wczwez;
	double        delta_X,delta_Y,delta_Z;
	double        delta_Vx,delta_Vy,delta_Vz;
    float         V;
    float         thita,thita_1,d_thita[2],d_thita_t;
    float         xgma,xgma_1,d_xgma[2],d_xgma_t,sta_gma;
    float         mach,q,Cn,Cz1,alfa,beta;
	unsigned char d_diff_1st;
    int           run_time;
	float         aux_nav_ctrl;
    float         gnss_X,gnss_Y,gnss_Z,gnss_Vx,gnss_Vy,gnss_Vz;
}Nav_fs_Cal_Struct;

//----------------------------------------------------------
//--run hor struct define
//  g0,A0,B0,A1,kexi,leta from bind data
//----------------------------------------------------------
typedef struct
{
    float      g0,A0,B0,A1,kexi,leta;

    float      wiex0_n,wiey0_n,wiez0_n;
    float      wiex0_p,wiey0_p,wiez0_p;
    float      wiex0,wiey0,wiez0;

    float      fai0_n,fai0_p;

    int        Run_Count;
    int        Run_time;
    float      Cycle_T0;

    float      sum_ax,sum_ay,sum_az;
    float      sum_dtx,sum_dty,sum_dtz;
    float      fai_s,psa_s,gma_s;

    double     X,Y,Z;
    double     Vx,Vy,Vz;

    float      p11,p12,p21,p22;
    float      k[2];
    float      Ax[2],Ay[2],Az[2];

    float      Vx19,Vy19,Vz19;
    float      vx0,vy0,vz0;

    float      psa01p,gma01p;
    float      fai01,psa01,gma01;
    float      gama0;
    float      fai02p,psa02p;
    float      fai02,psa02;
	float	   SL;
	float      Run_hor_nav_X, Run_hor_nav_Y, Run_hor_nav_Z ;
	float	   Run_hor_nav_Vx,Run_hor_nav_Vy,Run_hor_nav_Vz;
    int           Run_Hor_Nav_Time_b12,Run_Hor_Nav_Time_a2,Run_count_a2;
    unsigned int  Err_Code;
    unsigned char Run_Hor_1st_Check,Run_End;
}Run_Hor_Struct;

//----------------------------------------------------------
//--conflict define
//  y = k(x - x0) + b
//----------------------------------------------------------
typedef struct
{
    float   t,a1,b1,a2,b2,a3,b3;
}Min2MulD;

//----------------------------------------------------------
//--bind datas definde
//  32 bits align
//  GNSS,WM : 0x00 must,0x55 abort
//----------------------------------------------------------
#define Max_bind_array_len   249
typedef struct
{
    unsigned int    gnss_work_mode,wm_work_mode,run_status,bomb_type;

    int             thita_len,K1K2_len,fai_len;

    float           A0,A1,B0,L0,H0,g0;
    float           kexi,leta;
    float           K1y,K1z,K0z;
    float           X_t,Y_t,Z_t;
    float           thita_f;

    float           G0,G1,H1;

    float           Tjd,Tj2,Tjz;

    float           fai_V[Max_bind_array_len],thita[Max_bind_array_len];
    float           fai[Max_bind_array_len],L[Max_bind_array_len],K2_b[Max_bind_array_len];
    float           bombH,sc;
    
    float           imu_K0z,imu_D0x,imu_D0y,imu_D0z;

}bind_data_struct;

//----------------------------------------------------------
//--block transmit struct define
//----------------------------------------------------------
#define Block_datas_size     2048
typedef struct
{
    unsigned char buf[Block_datas_size];
    unsigned char RorW;
    unsigned char Op_type;
    short         block_size;
    unsigned int  offset;

    short         index;

}block_data_struct;

//----------------------------------------------------------
//--program status struct define
//----------------------------------------------------------
typedef struct
{
	unsigned char Type_Code;
	unsigned char Serial; 
	unsigned char Main_Ver;
	unsigned char Sub_Ver;
}Program_Status;

typedef struct
{
	float time_run;
	float gx, gy, gz, ax, ay, az;
	float nav_X, nav_Y, nav_Z, nav_Vx, nav_Vy, nav_Vz;
	float fs_X,  fs_Y,  fs_Z,  fs_Vx,  fs_Vy,  fs_Vz;
	float q0, q1, q2, q3;
	float dd_thita, dd_xgma;
	float Uf, Up, Ug;
	float Uz1, Uy1;
	float Run_hor[15];
	float gnss_t70;
	float gnss_X,  gnss_Y,  gnss_Z,  gnss_Vx,  gnss_Vy, gnss_Vz;
	float gnss_Tg;
	float gnss_dx, gnss_dy, gnss_dz, gnss_dvx, gnss_dvy,gnss_dvz;
	float gnss_dots;
	float aux_nav_ctrl;
	float wm_t70, wm_dx_w, wm_dy_w, wm_dz_w, wm_vdop, wm_pdop;
	float wm_Tg, wm_dx, wm_dy, wm_dz, wm_dvx, wm_dvy, wm_dvz;
	float wm_dots;
	float cic_Eita, cic_s, cic_dEita, cic_ds, cic_dthta_s, cic_dxigma_s;
	float M;
	float gnss_t70_start;
	float d_thita_t,d_xgma_t;

}Computer_Word_Struct;


#endif

