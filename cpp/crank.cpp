#include <machine.h>
#include <umachine.h>

#include "misc.h"
#include "hwreg.h"

#include "constbyte.h"
#include "constword.h"
#include "ram.h"
#include "EnVars.h"
#include "FU03.h"
#include "hardware.h"
#include "MISFIRE.h"
#include "crank.h"
#include "com.h"
#include "com_hal.h"


#ifndef DEF_CRANK	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


#define _sub_23180						((void(*)(void))0x23180)
#define _SysInit_sub_230FA				((void(*)(void))0x230FA)
#define _INJECTOR_RESCALED_sub_26174	((u16(*)(u16))0x26174)
#define _StartInjectAsync				((void(*)(u16,u16))0x261CA)
#define _StartInjectSync				((void(*)(u16,u16))0x26218)
#define _F500_InitManifoldVars							((void(*)(void))0x23244)

#pragma regsave(sub_23180)			
#pragma regsave(SysInit_sub_230FA)
#pragma regsave(INJECTOR_RESCALED_sub_26174	)
#pragma regsave(StartInjectAsync			)	
#pragma regsave(StartInjectSync				)			
#pragma regsave(F500_InitManifoldVars							)	

void 	sub_23180					()					{	_sub_23180();							}						
void 	SysInit_sub_230FA			()					{	_SysInit_sub_230FA(); 					}		
u16		INJECTOR_RESCALED_sub_26174	(u32 v)				{	return _INJECTOR_RESCALED_sub_26174(v);	}						
void	StartInjectAsync			(u16 v, u16 mask)	{	_StartInjectAsync(v, mask);				}						
void	StartInjectSync				(u16 v, u16 mask)	{	_StartInjectSync(v, mask);				}						
void	F500_InitManifoldVars()							{	_F500_InitManifoldVars();						}				

#else	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//#define Get_ADC_Knock				((void(*)(void))0xA92C)
//#define atu22_Get_DSTR_0x3C00		((u16(*)(void))0xC850)
//#define Reset_IRQ0F					((u16(*)(void))0xC258)

//extern "C" bool Reset_IRQ0F();

//#define sub_21AAA					((u16(*)(u16))0x21AAA)
//#define sub_21ACC					((u16(*)(u16))0x21ACC)
//#define sub_21B50					((u16(*)(u16))0x21B50)
//
//#define COM_MUT2B_sub_895C			((void(*)(u16))0x895C)
//#define PEDR_LO_Check_sub_A790			((bool(*)(void))0xA790)


//#define CRANK75_Knock_sub_24AC0		((void(*)(void))0x24AC0)

#define ENGINE_MAIN_VARIABLES_DIM_off_9198		((EnVars*)0x9198)

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#define CEL8_7974			((Axis*)0x7974)

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#define unk100_62FC			((Map3D_B *)0x62FC)
#define unk112_5240			((Map3D_B *)0x5240)

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#define	word_98BA				((const u16*)0x98BA)                                                     
#define	word_98C4				((const u16*)0x98C4)                                                     
#define	word_98CC				((const u16*)0x98CC)                                                     
#define	word_98E6				((const u16*)0x98E6)                                                     
#define	word_98D4				((const u16*)0x98D4)                                                     
#define	byte_342F				((const byte*)0x342F)                                                     
#define	byte_35B7				((const byte*)0x35B7)                                                     

#define	word_98C2				(*(const u16*)0x98C2)                                                     
#define	word_98EA				(*(const u16*)0x98EA)                                                     
#define	word_98EC				(*(const u16*)0x98EC)                                                     
#define	word_98EE				(*(const u16*)0x98EE)                                                     

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


static void CRANK5_root_sub_DC18(u16 osbr, u32 icr);
static void CRANK75_root_sub_DB40(u16 osbr, u32 icr);

//void F500_InitManifoldVars();

//static void SetIgnCoilChargeStartTime(u16 mask, u16 v);
//static void SetIgnSparkStartTime(u16 mask, u16 v);

//void StartInjectSync(u16 v, u16 mask);
//void StartInjectAsync(u16 v, u16 mask);

//extern "C" void InjOpenStart(u16 v, u16 mask);

//u16 INJECTOR_RESCALED_sub_26174(u16 v);

//extern "C" u16 atu22_Get_ECNT9A();




static u16 CRANK75_FiltrCrankHT_2494E(u16 v1, u16 v2);
static u16 CRANK75_Get_IgnCoilTime(u16 v);
static void CRANK75_Knock_sub_23F8C();
static void CRANK75_Knock_sub_24AC0();
static void CRANK75_MainUpdateTiming();
void CRANK75_Main_sub_232A0();
static bool CRANK75_sub_24636();
static void CRANK75_sub_2467E(u16 v);
static void CRANK75_sub_260B8();
//static void Misfire_CRANK75_root();
//static void Misfire_CRANK75_sub_2B168();


static void CRANK_MAF_MAP_Calcs_sub_250F8(u16 v1, u16 v2);
static void CRANK_sub_262D0();


static void CRANK5_SetIgnCoilTime_Fin();

void CRANK5_Main_sub_24AF0();

static void CRANK5_sub_2504A();
static void CRANK5_SetIgnSpark5();
//static void CRANK5_sub_21A04();
//static void Misfire_CRANK5_root();
//static void Misfire_CRANK5_sub_29558(u16 v1, u16 v2);
//static void Misfire_CRANK5_sub_29750();
//static void Misfire_CRANK5_sub_2A684();
//static void Misfire_CRANK5_sub_2AAA2();
//static void Misfire_CRANK5_sub_2AC5C();
//static void Misfire_CRANK5_sub_2AEE4();

//extern "C" void CRANK5_sub_C990(u16 v);


//static u16 atu22_Get_ECNT9A();



static u16 sub_2640E(u16 ipw);

//extern "C" void Update_Gen_G_output();
//extern "C" bool CRANK_CheckCamshaft_sub_A7C0();

static void atu22_IMF2G_event();
static void atu22_CMF2G_event();
//static void Disable_Ign_Handler(u16 v);
//extern "C" bool Check_Starter_signal();
//extern "C" bool Check_PEDRL_1();

//extern "C" void Ign_handler(u16 v);
//extern "C" u16 Get_Coil_charge_status();

//extern "C" void Start_Coil_Charge(u16 mask);
//extern "C" void Disable_Coil_Charge(u16 mask);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static void atu02_ici0A();
#pragma address v_atu02_ici0A=0x150
const void *v_atu02_ici0A = atu02_ici0A;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static void atu22_imi2G();
#pragma address v_atu22_imi2G=0x1C8
const void *v_atu22_imi2G = atu22_imi2G;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#pragma address v_crank_end_section = 0x26170
const void *v_crank_end_section = 0;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#pragma section _CRANK

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#pragma interrupt(atu02_ici0A)

static void atu02_ici0A()
{
//	u16 r1 = 0;

	__disable_irq();

	ici0A_TCNT2A = reg_TCNT2A;

	CLR(reg_TSR0, 1);

	crank_OSBR2_4us = reg_OSBR2;

	crank_ICR0AH_250ns = reg_ICR0A;

	//if (crank_Flags & 1)
	//{
	//	if ((reg_PADRL & 1) == 0)
	//	{
	//		r1 = 1;
	//	};
	//}
	//else
	//{
	//	if ((reg_PADRL & 1) != 0)
	//	{
	//		r1 = 1;
	//	};
	//};

	if ((crank_Flags ^ reg_PADRL) & 1)
	{
		reg_OCR2G = reg_TCNT2B + 13;

		SET(crank_Flags, 2);
	}
	else
	{
		reg_OCR2G = reg_TCNT2B - 1;

		CLR(crank_Flags, 2);
	};

	CLR(reg_TSR2B, 0x40);

	__enable_irq();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#pragma interrupt(atu22_imi2G)

extern "C" void atu22_imi2G()
{
	if (reg_TSR2A & 0x40)
	{
		__disable_irq();

		CLR(reg_TSR2A, 0x40);

		__enable_irq();

		atu22_IMF2G_event();
	};

	if (reg_TSR2B & 0x40)
	{
		__disable_irq();

		CLR(reg_TSR2B, 0x40);

		__enable_irq();

		atu22_CMF2G_event();
	};
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void atu22_IMF2G_event()
{
	__disable_irq();

	Disable_Ign_Handler(4);

	__enable_irq();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static void atu22_CMF2G_event()
{
	__disable_irq();

	u32 r3 = crank_ICR0AH_250ns;
	u32 r6 = crank_OSBR2_4us;

	if (crank_Flags & 2)
	{
		CLR(crank_Flags, 2);

		if (crank_Flags & 1)
		{
			CRANK75_root_sub_DB40(r6, r3);
		}
		else
		{
			CRANK5_root_sub_DC18(r6, r3);
		};
	}
	else
	{
		__enable_irq();
	};
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//static void CRANK5_sub_C990(u16 v)
//{
//	__disable_irq();
//
//	u32 r13 = v;
//
//	v -= reg_TCNT2A + 2;
//
//	if (v & 0x8000)
//	{
//		r13 = reg_TCNT2A + 2;
//	};
//
//	reg_GR2H = r13;
//
//	CLR(reg_TSR2A, 0x80);
//
//	reg_TIOR2D = reg_TIOR2D & 0x8F | 0x10;
//
//	__enable_irq();
//}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//static u16 Get_Coil_charge_status()
//{
//	__disable_irq();
//
//	u32 r1 = reg_PHDRH;
//
//	__enable_irq();
//
//	return (~(r1 >> 4)) & 7;
//}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//static void Start_Coil_Charge(u16 mask)
//{
//	__disable_irq();
//
//	if (mask & 1)
//	{
//		reg_GR2E = reg_TCNT2A + 2;
//
//		CLR(reg_TSR2A, 0x10);
//
//		reg_TIOR2C = reg_TIOR2C & 0xF8 | 1; // 0 output on GR compare-match
//
//		while(ZRO(reg_TSR2A, 0x10)) ;
//	};
//
//	if (mask & 2)
//	{
//		reg_GR2F = reg_TCNT2A + 2;
//
//		CLR(reg_TSR2A, 0x20);
//
//		reg_TIOR2C = reg_TIOR2C & 0x8F | 0x10; // 0 output on GR compare-match
//
//		while(ZRO(reg_TSR2A, 0x20)) ;
//	};
//
//	if (mask & 4)
//	{
//		reg_GR2G = reg_TCNT2A + 2;
//
//		CLR(reg_TSR2A, 0x40);
//
//		reg_TIOR2D = reg_TIOR2D & 0xF8 | 1; // 0 output on GR compare-match
//
//		while(ZRO(reg_TSR2A, 0x40)) ;
//	};
//
//	__enable_irq();
//}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//static void Disable_Coil_Charge(u16 mask)
//{
//	__disable_irq();
//
//	if (mask & 1)
//	{
//		reg_GR2E = reg_TCNT2A + 2;
//
//		CLR(reg_TSR2A, 0x10);
//
//		reg_TIOR2C = reg_TIOR2C & 0xF8 | 2;
//
//		while(ZRO(reg_TSR2A, 0x10)) ;
//	};
//
//	if (mask & 2)
//	{
//		reg_GR2F = reg_TCNT2A + 2;
//
//		CLR(reg_TSR2A, 0x20);
//
//		reg_TIOR2C = reg_TIOR2C & 0x8F | 0x20;
//
//		while(ZRO(reg_TSR2A, 0x20)) ;
//	};
//
//	if (mask & 4)
//	{
//		reg_GR2G = reg_TCNT2A + 2;
//
//		CLR(reg_TSR2A, 0x40);
//
//		reg_TIOR2D = reg_TIOR2D & 0xF8 | 2;
//
//		while(ZRO(reg_TSR2A, 0x40)) ;
//	};
//
//	__enable_irq();
//}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//static bool Reset_IRQ0F()
//{
//	bool r1 = false;
//
//	__disable_irq();
//
//	if (reg_ISR & 0x80)
//	{
//		CLR(reg_ISR, 0x80);
//
//		r1 = true;
//	};
//
//	__enable_irq();
//
//	return r1;
//}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static void CRANK5_root_sub_DC18(u16 osbr, u32 icr)
{
	if ((u16)(osbr - crank_OSBR2_75) >= 162 || timer_up_FFFF8522 >= 40)
	{
		if (timer_up_FFFF8524 >= 39)
		{
			crank_OSBR2_5 = osbr;

			crankPrev_ICR0AH_5 = icr;

			crank_dt_ICR0AH_5 = ~0;

			crankHT_5 = ~0;
		}
		else
		{
			crankHT_5 = osbr - crank_OSBR2_5;

			crank_OSBR2_5 = osbr;

			crank_dt_ICR0AH_5 = icr - crankPrev_ICR0AH_5;

			crankPrev_ICR0AH_5 = icr;
		};

		timer_up_FFFF8524 = 0;

		__enable_irq();

		CRANK5_Main_sub_24AF0();

		word_FFFF8870 = reg_TCNT2A - ici0A_TCNT2A;

		__disable_irq();

		SET(crank_Flags, 1);
	};

	__enable_irq();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static void CRANK75_root_sub_DB40(u16 osbr, u32 icr)
{
    if ((u16)(osbr - crank_OSBR2_5) >= 254 || timer_up_FFFF8524 >= 40)
	{
		if (timer_up_FFFF8522 >= 39)
		{
			crank_OSBR2_75 = osbr;

			crankPrev_ICR0AH_75 = icr;

			null_crank_dt_ICR0AH_5 = ~0;

			crankHT_75 = ~0;
		}
		else
		{
			crankHT_75 = osbr - crank_OSBR2_75;

			crank_OSBR2_75 = osbr;

			null_crank_dt_ICR0AH_5 = icr - crankPrev_ICR0AH_75;

			crankPrev_ICR0AH_75 = icr;
		};

		timer_up_FFFF8522 = 0;

		__enable_irq();

		CRANK75_Main_sub_232A0();

		word_FFFF886E = reg_TCNT2A - ici0A_TCNT2A;

		__disable_irq();

		CLR(crank_Flags, 1);
	};

	__enable_irq();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//static void Disable_Ign_Handler(u16 v)
//{
//	__disable_irq();
//
//	u32 r13 = reg_TCNT2A;
//
//	r13 -= 1;
//
//	if (v & 1)
//	{
//		reg_GR2E = r13;
//
//		CLR(reg_TSR2A, 0x10);
//	};
//
//	if (v & 2)
//	{
//		reg_GR2F = r13;
//
//		CLR(reg_TSR2A, 0x20);
//	};
//
//	if (v & 4)
//	{
//		reg_GR2G = r13;
//
//		CLR(reg_TSR2A, 0x40);
//	};
//
//	__enable_irq();
//}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//static bool CRANK_CheckCamshaft_sub_A7C0()
//{
//	return (reg_PADRL & 4) == 0;
//}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//static bool Check_Starter_signal()
//{
//	return (reg_PEDRL & 4) == 0;
//}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//static bool Check_PEDRL_1()
//{
//	return (reg_PEDRL & 1) != 0;
//}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void SysInit_sub_230FA()
{
	word_FFFF8F2E = 5;
	
	crankHT_75_4us = ~0;

	state_Ignition = IGNST_NEXT_COIL;

	word_FFFF8C66 = word_FFFF8C68 = word_FFFF8C6A = word_1830/*48*/;

	word_FFFF8C76 = word_FFFF8C78 = word_263A/*200*/;

	injectors_mask_FFFF8C72 = ~0;

	strokeNumber = 3;

	word_FFFF8DE6 = word_1C22/*8*/;

	camshaft_Shift = ~0;

	F500_InitManifoldVars();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void sub_23180()
{
	null_CrankHT_x_4us_1 = ~0;
	null_CrankHT_x_4us_2 = ~0;
	crankHT_75_4us_4 = ~0;
	crankHT_75_4us_3 = ~0;

	word_FFFF8F2E = 5;

	camShaftFlags = 0;
	crankCounter = 0;
	starterCrankCounter = 0;
	strokeNumber = 3;
	word_FFFF8DE6 = word_1C22/*8*/;
	crankHT_75_4us = ~0;
	state_Ignition = IGNST_NEXT_COIL;

	CLR(word_FFFF8BBA, 0x80);

	word_FFFF8AD6 = word_1780/*3*/;

	CLR(word_FFFF8B4E, 0x20);

	CLR(word_FFFF89F2, 0x800);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void F500_InitManifoldVars()
{
	u16 r1 = wMUT1A_Manifold_AbsPressure_ADC8bit;

	__disable_irq();

	Manifold_ADC8bit_1 = r1;
	Manifold_ADC8bit_2 = r1;
	Manifold_ADC8bit_3 = r1;
	Manifold_ADC8bit_4 = r1;
	Manifold_AbsPressure_ADC8bit_avrg = r1;
	Manifold_AbsPressure_ADC8bit_x256_avrg = r1 << 8;

	__enable_irq();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CRANK75_Main_sub_232A0()
{
//	const u32 r9 = 0x8000;

	__disable_irq();

	camshaft_Shift <<= 1;

	if (CRANK_CheckCamshaft_sub_A7C0())
	{
		camshaft_Shift |= 1;
	};

	if (camShaftFlags & CAM_SYNCHRO)
	{
		stroke_75 += 1;

		if (stroke_75 >= 4)
		{
			stroke_75 = 0;
		};
	}
	else
	{
		stroke_75 = 1;
	};

	crankCounter += 1;

	if (crankCounter == 0)
	{
		crankCounter -= 1;
	};

	u16 r1 = word_98BA[stroke_75] ^ camshaft_Shift;//0xB1B1, 0xC6C6, 0x1B1B, 0x6C6C

	if (crankCounter < 4)
	{
		CLR(camShaftFlags, CAM_SYNCHRO);
		camSyncCrankCounter = 2;
	}
	else
	{
		if (word_98C2/*3*/ & r1)
		{
			if (camSyncCrankCounter != 0)
			{
				camSyncCrankCounter -= 1;
			}
			else if ((camshaft_Shift & 0xF) != 0 && (camshaft_Shift & 0xF) != 0xF)
			{
				CLR(camShaftFlags, CAM_SYNCHRO);
			}
		}
		else 
		{
			if ((r1 & 0xF) == 0)
			{
				SET(camShaftFlags, CAM_SYNCHRO);
			};

			camSyncCrankCounter = 2;
		};
	};

	if (Check_Starter_signal())
	{
		if ((starterCrankCounter += 1) == 0)
		{
			starterCrankCounter -= 1;
		};
	}
	else
	{
		starterCrankCounter = 0;
	};

	if ((camShaftFlags & CAM_SYNCHRO) && (starterCrankCounter == 0 || starterCrankCounter >= 5))
	{
		SET(camShaftFlags, CAM_10);
	}
	else
	{
		CLR(camShaftFlags, CAM_10);
	};

	r1 = (camShaftFlags & CAM_10) ? word_98BA[stroke_75] : camshaft_Shift; //0xB1B1, 0xC6C6, 0x1B1B, 0x6C6C

	curTimingMask_75 = word_98C4[r1 & 3]; // 2,1,2,1
	nxtTimingMask_75 = word_98CC[r1 & 3]; // 1,2,1,2

	word_FFFF8C62 <<= 1;

	if (Check_PEDRL_1())
	{
		word_FFFF8C62 |= 1;
	};

	u32 crnkHT75 = crankHT_75_4us = crankHT_75; // r8

	u32 r2 = ((word_FFFF8C5C & (IGN_X_RPM1775|IGN_X_RPM500)) << 1) | IGN_X_RPM4800|IGN_X_RPM1540|IGN_X_RPM1775|IGN_X_RPM500;// 0x35;

	if (IGN_FLAG9_FFFF8BB6 & IGN_F9_FIX5) // Fix timing at 5 degrees;
	{
		SET(r2, IGN_X_FIX5);
	};

	if (crnkHT75 >= t1_crankHT_1798/*1562(4800rpm)*/)
	{
		CLR(r2, IGN_X_RPM4800);

		if (crnkHT75 >= 4225/*1775rpm*/)
		{
			CLR(r2, IGN_X_RPM1775);
		};

		if (crnkHT75 >= 4870/*1540rpm*/)
		{
			CLR(r2, IGN_X_RPM1540);
		};

		r1 = 14848/*500rpm*/;

		if (word_FFFF8C5C & IGN_X_RPM500)
		{
			r1 = 18688/*400rpm*/;
		};

		if (crnkHT75 >= r1)
		{
			CLR(r2, IGN_X_RPM500);
		};
	};

	word_FFFF8C5C = r2;

	CLR(word_FFFF8C5E, 1);
	
//	u32 r4;

	if (timer_FFFF8594 == 0)
	{
		word_FFFF8C5C = 0;

		CRANK75_sub_2467E(0);
	}
	else
	{
		if (Check_Starter_signal() || (word_FFFF8C5C & IGN_X_FIX5) || (camShaftFlags & CAM_SYNCHRO) == 0)
		{
			timingAdvInternal1 = 202;
			timingAdvInternal2 = 202;
			timingAdvScaled = 160;
		}
		else
		{
			CRANK75_MainUpdateTiming();
		};

		if ((Check_Starter_signal() && (wMUT14_Battery_Level_ADC8bit < 0xFF)) || (word_FFFF8C5C & IGN_X_RPM500) == 0)
		{
			word_FFFF8C5C = 0;

			CRANK75_sub_2467E(1);
		}
		else if ((word_FFFF8C5C & IGN_X_PREV_RPM500) == 0)
		{
			if (CRANK75_sub_24636())
			{
				word_FFFF8C5C = 0;
				CRANK75_sub_2467E(1);
			}
			else
			{
				word_FFFF8C5C = IGN_X_RPM500;
				CRANK75_sub_2467E(1);
			};
		}
		else
		{
			// loc_235FA

			u32 fCHT = filtred_crankHT_x_4us = CRANK75_FiltrCrankHT_2494E(crnkHT75, crankHT_75_4us_2);

			if ((crnkHT75 > 6250/*<1200rpm*/ && timingAdvInternal1 <= 202 && CRANK75_sub_24636()) || (fCHT & 0x8000)/*<228rpm*/ || fCHT < 326/*>23000rpm*/)
			{
				word_FFFF8C5C = 0;
				CRANK75_sub_2467E(1);
			}
			else
			{
				// loc_23668

				curTiming_75_4us = Sub_Lim_0(Mul_Div(timingAdvInternal1 , fCHT, 512), word_179E/*15*/);
				nxtTiming_75_4us = Sub_Lim_0(Mul_Div(timingAdvInternal2 , fCHT, 512), word_179E/*15*/);

				if ((Get_Coil_charge_status() & curTimingMask_75) == curTimingMask_75)
				{
					state_Ignition = IGNST_SPARK;

					Disable_Ign_Handler(curTimingMask_75);
				}
				else
				{
					// loc_23704

					state_Ignition = IGNST_CUR_COIL;

					u16 r13 = crank_OSBR2_75 + curTiming_75_4us - CRANK75_Get_IgnCoilTime(fCHT);
					
					u16 r1 = curIgnSparkTime_4us + word_179C/*250*/;

					if ((r13 - r1) & 0x8000)
					{
						r13 = r1;
					};

					if ((r13 - reg_TCNT2A) & 0x8000)
					{
						r13 = reg_TCNT2A;
					};

					curIgnCoilStartTime_4us = r13;

					SetIgnCoilChargeStartTime(curTimingMask_75, r13);
				};

				// loc_2376E

				curIgnSparkTime_4us = crank_OSBR2_75 + curTiming_75_4us;


				if (timingAdvInternal1 >= 202 && ((word_FFFF8C5C & IGN_X_FIX5) || (word_FFFF8C5C & IGN_X_RPM1540) == 0))
				{
					// loc_23796

					SET(word_FFFF8C5E, 1);
				}
				else
				{
					// loc_237A2

					if (state_Ignition != IGNST_CUR_COIL)
					{
						if ((i16)(curIgnSparkTime_4us - reg_TCNT2A) < 0)
						{
							curIgnSparkTime_4us = reg_TCNT2A;
						};

						SetIgnSparkStartTime(curTimingMask_75, curIgnSparkTime_4us);
					};
				};

				// loc_237D6

				if (timingAdvInternal1 <= 199)
				{
					// loc_23834
					curTiming_5_4us = 0;
				}
				else if (word_FFFF8C5C & IGN_X_FIX5)
				{
					// loc_2382A
					curTiming_5_4us = 50;
				}
				else
				{
					u32 r13 = Sub_Lim_0(Mul_Div(fCHT, (timingAdvInternal1 - 199), 512), word_179E/*15*/);

					curTiming_5_4us = (r13 >= 1) ? r13 : 1;
				};

				// loc_2383A
				
				u16 r13 = fCHT + crank_OSBR2_75 + nxtTiming_75_4us - ignCoilTime_Fin_4us;

				u32 r1 = curIgnSparkTime_4us + word_179C/*250*/;

				if ((i16)(r13 - r1) < 0)
				{
					r13 = r1;
				};

				ignCoilNextStartTime_x4us = r13;
			};
		};
	};

	//+++++++++++++++++++++++++++++++++++

	// loc_23872

	crankHT_75_4us_2 = crankHT_75_4us;

	crankHT_75_div_128 = crankHT_75_4us >> 7;

	__enable_irq();

	/*u32*/ r2 = word_1830;

	/*u32*/ r1 = word_FFFF8C62 & 0xF;

	if (ZRO(IGN_FLAG9_FFFF8BB6, IGN_F9_01) || r1 == 0 || r1 == 0xF || ZRO(camShaftFlags, CAM_SYNCHRO))
	{
		// loc_23932

		if (word_FFFF8C66 != 0)
		{
			word_FFFF8C66 = r2;
		};

		if (word_FFFF8C68 != 0)
		{
			word_FFFF8C68 = r2;
		};

		if (word_FFFF8C6A != 0)
		{
			word_FFFF8C6A = r2;
		};
	}
	else
	{
		// loc_2396C

		u16* p = (curTimingMask_75 == 1) ? &word_FFFF8C68 : &word_FFFF8C66;

		r1 &= 3;

		if (r1 == 2 || r1 != 1)
		{
			*p = r2;
		}
		else if (*p != 0)
		{
			*p -= 1;
		};

		u32 r13 = 0xFFFF;

		if (word_FFFF8C66 == 0)
		{
			r13 = ~word_98EA/*9*/ & 0xFFFF;
		};

		if (word_FFFF8C68 == 0)
		{
			r13 &= ~word_98EC/*6*/;
		};

		if (word_FFFF8C6A == 0)
		{
			r13 &= ~word_98EE/*0*/;
		};

		injectors_mask_FFFF8C72 = r13;

		WFLAG(word_FFFF8BBA, 1, (r13 & 0xF) != 0xF)
	};

	// loc_239F4

	if (ZRO(wMUTD1_BitMap_FAA, FAA_3_IMMO) || (word_FFFF80FA & 0x80) || word_FFFF8EBA != 0 || (FLAGS_FFFF8EB0 & 0x80))
	{
		timer_FFFF8594 = 51;
	};

	null_CrankHT_x_4us_1 = null_CrankHT_x_4us_2;
	null_CrankHT_x_4us_2 = crankHT_75_4us_4;
	crankHT_75_4us_4 = crankHT_75_4us_3;
	crankHT_75_4us_3 = crankHT_75_4us;

	r1 = DIV_DW_R(30720000, crankHT_75_4us_3);

	if ((RPM_FLAGS & RPM_0_CRANKING) || cranking_end_timer_up < word_17BA)
	{
		RPM_x_4_096__1 = r1;
		RPM_x_4_096__2 = r1;
		RPM_x_4_096__3 = r1;
	}
	else
	{
		RPM_x_4_096__1 = Interpolate_256(RPM_x_4_096__1, r1, interpolator_RPM_x_4_096);
		RPM_x_4_096__2 = Interpolate_256(RPM_x_4_096__2, r1, word_1842/*230*/);
		RPM_x_4_096__3 = Interpolate_256(RPM_x_4_096__3, r1, word_2340/*205*/);
	};

	// loc_23ABE

	DECLIM(IGN_0xA_FFFF8BE8);

	// loc_23ACE

	if (IGN_0xA_FFFF8BE8 == 0 && ign_lim_dec_fuel_cut < 0x80)
	{
		ign_lim_dec_fuel_cut += 1;

		IGN_0xA_FFFF8BE8 = word_17C2/*3*/;
	};

	DECLIM(timer_Delta_TPS);
		
	if (timer_Delta_TPS == 0)
	{
		abs_Delta_TPS = 0;
	};

	// loc_23B0E

	word_FFFF8BF2 = Sub_Lim_0(word_FFFF8BF2, word_1B1A/*8*/);

	DECLIM(word_FFFF8BEC);
	
	DECLIM(word_FFFF8BEE);

	if (word_FFFF8BEC == 0 && word_FFFF8BEE == 0)
	{
		INCLIM80(word_FFFF8BEA);

		word_FFFF8BEE = word_1898/*1*/;
	};

	// loc_23B70

	RPM8_FFFF8B02 = RPM8_FFFF8B00;
	RPM8_FFFF8B00 = 960;

	if ((word_FFFF8ADA += 1) == 0)
	{
		word_FFFF8ADA -= 1;
	};

	if (RPM_FLAGS & RPM_11_UPDATE_OXIGEN_TRIM)
	{
		u32 r13;

		if (wMUT18_Open_Loop_Bit_Array & MUT18_6_40)
		{
			u32 r1;

			if (word_FFFF81E0 & 0x100)
			{
				r1 = (byte_1053/*0*/ == 1) ? (dec_Oxygen_Trim << 1) : Div_R4_R5__R0(dec_Oxygen_Trim << 7, word_247A/*128*/);
			}
			else
			{
				r1 = dec_Oxygen_Trim << 2;
			};

			r13 = Sub_Lim_0(wMUT0F_Oxygen_Feedback_Trim, r1);
		}
		else
		{
			u32 r1;

			if (word_FFFF81E0 & 0x100)
			{
				r1 = (byte_1053/*0*/ == 1) ? (inc_Oxygen_Trim << 1) : Div_R4_R5__R0(inc_Oxygen_Trim << 7, word_247A/*128*/);
			}
			else
			{
				r1 = inc_Oxygen_Trim << 2;
			};
			
			r13 = Add_Lim_FFFF(wMUT0F_Oxygen_Feedback_Trim, r1);
		};

		wMUT0F_Oxygen_Feedback_Trim = Lim16(r13, limLo_O2_Feedback_Trim, limHi_O2_Feedback_Trim);
	};

	// loc_23D48

	CRANK75_sub_260B8();

	if (	(wMUT1E_MAF_RESET_FLAG & CRANKING) 
		&&	(word_FFFF8A48 & 0x80) 
		&&	ZRO(word_FFFF8B4E, INJ_5_SYNC_INJECT)
		&&	ZRO(word_FFFF89F2, 0x400)
		&&	ZRO(word_FFFF89F2, 0x800))
	{
		CRANK_MAF_MAP_Calcs_sub_250F8(0, 0);
	};

	// loc_23D98

	if ((RPM_FLAGS & RPM_9_wtf_cranking) && ZRO(RPM_FLAGS, RPM_13_CRANKING_SYNC_INJECT))
	{
		CRANK_MAF_MAP_Calcs_sub_250F8(1, 0);
	}
	else if (word_FFFF8B4E & INJ_5_SYNC_INJECT)
	{
		if (injPW_final != 0 && injPW_chnl != 0)
		{
			InjOpenStart(injPW_final, injPW_chnl);
		};

		CLR(word_FFFF8B4E, INJ_5_SYNC_INJECT);

		CRANK_sub_262D0();
	};

	// loc_23E34

	word_FFFF8DD4 += crankHT_75 >> 3;

	DECLIM(word_FFFF8DD8);

	if (word_FFFF8DD8 == 0)
	{
		wMUT90_ECNT9A = atu22_Get_ECNT9A();

		r1 = Mul_Div_R(wMUT90_ECNT9A, 2048, word_FFFF8DD4);

		wMUT91_Timer_Status_Register_9_TSR9_Scaled = r1 = (r1 >= 0xFF) ? 0xFF : r1;

		if (RPM_FLAGS & RPM_0_CRANKING)
		{
			fix8_FFFF8DCE = r1 << 8;

			wMUT92_Timer_Status_Register_9_TSR9_Scaled_Checked = r1;
		}
		else
		{
			wMUT92_Timer_Status_Register_9_TSR9_Scaled_Checked = Div_256_R(fix8_FFFF8DCE = Interpolate_256(fix8_FFFF8DCE, r1 << 8, word_FFFF8DD2));
		};

		word_FFFF8DD4 = 0;
		word_FFFF8DD8 = word_FFFF8DD6;
	};

	// loc_23EE6

	r1 = 0xFFFF;

	if (wMUT8F < 0xFF)
	{
		r1 = DIV_DW_R(Mul16(wMUT8F, crankHT_75), 40000);
	};

	gen_G_timer = (r1 >= 1) ? r1 : 1;

	SET(KNOCK_FLAG2_FFFF887A, KNOCK_F2_01);

	Update_Gen_G_output();

	Misfire_CRANK75_root();

	CRANK75_Knock_sub_23F8C();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CRANK75_Knock_sub_23F8C()
{
	const u32 r8 = 0x8000;

	if ((wMUTD1_BitMap_FAA & FAA_7_HIGH_IGN) == 0) // 0x80 - Enable High Oct Ign Map Lookup and other
	{
		return;
	};

	Get_ADC_Knock();

	u32 r1 = wMUT30_Knock_Voltage;

	if (r1 > 100)
	{
		r1 = Mul_Fix8_R((r1-100),435) + 55;
	}
	else
	{
		if (r1 > 92)
		{
			r1 = Mul_Fix8_R((r1-92), 0xC0) + 49;
		}
		else
		{
			r1 = Mul_Fix8_R(r1, 136);;
		};
	};

	if (r1 >= 255)
	{
		r1 = 255;
	};

	u32 r2 = wMUT6A_Knock_ADC_Processed;

	wMUT6A_Knock_ADC_Processed = r1;

	r1 = r2;

	if ((KNOCK_FLAG_FFFF8C34 & KNOCK_FAULT_CHECK) // 0x400 - (MUT21_RPM_x125div4 >= word_1C28(2000))&&(wMUT1C_ECU_Load >= word_1C26(55kPa))
		&& (KNOCK_FLAG1_FFFF8C36 & KNOCK_RPM_MID) == 0)
	{
		u32 r13, r3;

		r13 = (wMUT6A_Knock_ADC_Processed >= r1) ? (wMUT6A_Knock_ADC_Processed - r1) : (r1 -= wMUT6A_Knock_ADC_Processed);

		r3 = (KNOCK_FLAG2_FFFF887A & KNOCK_GAIN_3) ? t1_knock_signal_change_check_1C2E/*3*/ : t1_knock_signal_change_check_1C2C/*3*/;

		if (r13 >= r3)
		{
			wMUT72_Knock_Present &= ~1;

			wMUT6E_KnockFaultCheckTimer = 0;
		}
		else
		{
			if (wMUT6E_KnockFaultCheckTimer < 0xFFFFFFFF)
			{
				wMUT6E_KnockFaultCheckTimer += 1;
			};

			if (wMUT6E_KnockFaultCheckTimer > word_1C30)
			{
				wMUT72_Knock_Present |= 1;

				wMUT6E_KnockFaultCheckTimer = word_1C30;
			};
		};

		wMUT6D_Knock_Change = r13;

	} // if (KNOCK_FLAG_FFFF8C34 & 0x400)
	else
	{
		wMUT6E_KnockFaultCheckTimer = 0;

		wMUT6D_Knock_Change = 0;
	};

	Timer_Counter_Related_sub_C928();

	KNOCK_BASE_MINUS_ADC_FFFF8C40 = Sub_Lim_0(wMUT6A_Knock_ADC_Processed, knock_base_final);




	if ((KNOCK_FLAG_FFFF8C34 & KNOCK_RETARD_ENABLED) == 0) // 0x40 - enabled knock retard; IG04_Check_17074()
	{
		wMUT26_Knock_Retard = 0;

		CRANK75_Knock_sub_24AC0();

		r1 = 0;
	}
	else if (wMUT72_Knock_Present & 1) // 1 - ? Knock sensor fault; (wMUT6E_Knock_Dynamics >= word_1C30)
	{
		wMUT26_Knock_Retard = (KNOCK_FLAG_FFFF8C34 & KNOCK_F1_80) ? t1_knock_control_ign_retard_faulty_sensor_17E8/*0*/ : t1_knock_control_ign_retard_faulty_sensor_17EA/*0*/;

		CRANK75_Knock_sub_24AC0();

		r1 = 0;
	}
	else
	{
		// loc_2417A:                                                                                     

		if (KNOCK_BASE_MINUS_ADC_FFFF8C40 != 0)
		{
			//r1 = (KNOCK_FLAG_FFFF8C34 & KNOCK_F1_80) ? t1_knock_control__17CC/*32*/ : t1_knock_control__17CE/*16*/;

			r1 = (KNOCK_FLAG_FFFF8C34 & KNOCK_F1_80) ? knock_mul_high : knock_mul_low;

			r1 = 1 + Mul_Div_R(KNOCK_BASE_MINUS_ADC_FFFF8C40, r1, knock_base_final << 3);

			if (r1 >= 0xFF)
			{
				r1 = 0xFF;
			};
		}
		else
		{
			r1 = 0;
		}; //  if (KNOCK_BASE_MINUS_ADC_FFFF8C40 != 0)


		// loc_2421E:                                                                                      ; CODE XREF: CRANK75_Knock_sub_23F8C+230j

		if (KNOCK_FLAG_FFFF8C34 & KNOCK_F1_200) // RPM > 500
		{
			bMUTCD_KNOCK_PRECOUNT_1_FFFF8C4E += 1;

			if (bMUTCD_KNOCK_PRECOUNT_1_FFFF8C4E >= KNOCK_PRECOUNT_MAX_FFFF8C4A/*180*/)
			{
				bMUTCD_KNOCK_PRECOUNT_1_FFFF8C4E = KNOCK_PRECOUNT_MAX_FFFF8C4A;

				bMUTCB_KNOCK_U_FFF8C54 = 0x8000;
			};

			bMUTCE_KNOCK_PRECOUNT_2_FFFF8C50 += 1;

			if (bMUTCE_KNOCK_PRECOUNT_2_FFFF8C50 >= KNOCK_PRECOUNT_MAX_FFFF8C4A/*180*/)
			{
				bMUTCE_KNOCK_PRECOUNT_2_FFFF8C50 = KNOCK_PRECOUNT_MAX_FFFF8C4A;

				bMUTCC_KNOCK_UB_FFFF8C56 = 0x8000;
			};

			KNOCK_REL_compare_to_10_FFFF8C5A <<= 1;


			if (r1 >= t1_unk_180E/*1*/)
			{
				if (r1 <= KNOCK_REL_1_FFFF8C4C/*3*/)
				{
					KNOCK_REL_compare_to_10_FFFF8C5A |= 1;

					if (bMUTCB_KNOCK_U_FFF8C54 == strokeNumber)
					{
						bMUTCD_KNOCK_PRECOUNT_1_FFFF8C4E = 0;

						r1 = 0;
					}
					else if (bMUTCC_KNOCK_UB_FFFF8C56 == strokeNumber)
					{
						bMUTCE_KNOCK_PRECOUNT_2_FFFF8C50 = 0;

						r1 = 0;
					}
					else if (KNOCK_PRECOUNT_1033/*0*/ == 0 || (KNOCK_REL_compare_to_10_FFFF8C5A & 0x10))
					{
						if (r8 == bMUTCB_KNOCK_U_FFF8C54)
						{
							bMUTCB_KNOCK_U_FFF8C54 = strokeNumber;

							bMUTCD_KNOCK_PRECOUNT_1_FFFF8C4E = 0;

							if (KNOCK_PRECOUNT_1033 != 0)
							{
								r1 = 0;
							};
						}
						else if (bMUTCC_KNOCK_UB_FFFF8C56 == r8)
						{
							bMUTCC_KNOCK_UB_FFFF8C56 = strokeNumber;

							bMUTCE_KNOCK_PRECOUNT_2_FFFF8C50 = 0;

							if (KNOCK_PRECOUNT_1033 != 0)
							{
								r1 = 0;
							};
						};
					};
				};
			};
		}
		else  // if (KNOCK_FLAG_FFFF8C34 & 0x200)
		{
			CRANK75_Knock_sub_24AC0();
		}; //     if (KNOCK_FLAG_FFFF8C34 & 0x200)

		// loc_2432C:                                                                                      ; CODE XREF: CRANK75_Knock_sub_23F8C+2F8j

		max_Retard = max_Knock_Retard;

		u32 r13;

		r13 = (KNOCK_FLAG_FFFF8C34 & KNOCK_F1_80) ? t1_knock_control__17D0/*8*/ : t1_knock_control__17D2/*255*/;

		if (r1 > r13)
		{
			r1 = r13;
		};

		r2 = wMUT26_Knock_Retard + r1;

		wMUT26_Knock_Retard = MIN(r2, max_Retard);
	};



	// loc_243A8:                                                                                      ; CODE XREF: CRANK75_Knock_sub_23F8C+1EAj

	wMUT6C_Knock_Sum_Addition = r1;

	knock_filtered_x256_copy = knock_filtered_x256;

	wMUT6B_Knock_Base = knock_base_final;

	if (wMUT6A_Knock_ADC_Processed >= (knock_filtered_x256>>8))
	{
		INCLIM(KNOCK_DYNAMICS2_FFFF8C48);
	}
	else
	{
		KNOCK_DYNAMICS2_FFFF8C48 = 0;
	};

	r2 = 0x20;

	if (wMUT6F_Knock_Accel_timer != 0)
	{
		r2 = 0xF000;
		r1 = wMUT6A_Knock_ADC_Processed << 4;
	}
	else 
	{
		if (KNOCK_BASE_MINUS_ADC_FFFF8C40 != 0)
		{
			r2 = 0x100;
		}
		else if (KNOCK_DYNAMICS2_FFFF8C48 >= t1_knock_dynamics_1820/*6*/)
		{
			r2 = 0x10;
		}
		else if ((knock_filtered_x256 >> 8) != 0 && ((knock_filtered_x256 >> 8) * t1_knock_multiplier_1822/*16*/ <= (wMUT6A_Knock_ADC_Processed << 3)))
		{
			r2 = 0x100;
		};

		if (r2 == 0x10)
		{
			r2 = 0xF000;
			r1 = wMUT6A_Knock_ADC_Processed << 4;
		}
		else if (r2 == 0x20)
		{
			r2 = 0xF800;

			r1 = wMUT6A_Knock_ADC_Processed << 3;
		}
		else
		{
			r2 = 0xFF00;

			r1 = wMUT6A_Knock_ADC_Processed * 1;
		};
	};

	//++++++++++++++++++++++++++++++++++++++++++++++

	// wMUTC9_knock_ADC_proc_filtered = wMUTC9_knock_ADC_proc_filtered * (r2 / 65536) + r1;

	r1 <<= 16;

	wMUTC9_knock_ADC_proc_filtered = Div_65536_R(Add_Lim_FFFFFFFF(wMUTC9_knock_ADC_proc_filtered * r2, r1));

	if ((KNOCK_FLAG2_FFFF887A & KNOCK_GAIN_3) == 0)
	{
		if (knock_base_final >= t1_knock_base_compare_17EE/*143*/)
		{
			KNOCK_FLAG1_FFFF8C36 |= KNOCK_RPM_LOW;

			KNOCK_RPM_FFFF8C74 = MUT21_RPM_x125div4;
		};
	}
	else
	{
		if (MUT21_RPM_x125div4 < Sub_Lim_0(KNOCK_RPM_FFFF8C74, t1_knock_rpm_17F0/*10(312)*/) || knock_base_final < t1_knock_base_compare_17EC/*26*/)
		{
			KNOCK_FLAG1_FFFF8C36 &= ~KNOCK_RPM_LOW;
		};
	};

	//++++++++++++++++++++++++++++++++++++++++++++++

	KNOCK_FLAG1_FFFF8C36 &= ~1;

	if (((KNOCK_FLAG1_FFFF8C36 & KNOCK_RPM_LOW) && (FLAGS_FFFF8EB0 & 0x80) == 0) || ((FLAGS_FFFF8EB0 & 0x80) && (KNOCK_FLAG_FFFF8C34 & KNOCK_RPM_HI)))
	{
		if ((KNOCK_FLAG2_FFFF887A & KNOCK_GAIN_3) == 0)
		{
			wMUTC9_knock_ADC_proc_filtered /= 3;

			knock_filtered_x256 /= 3;

			knock_base_final = Lim16(knock_base_final/3, 1, 0xFF);

			KNOCK_FLAG1_FFFF8C36 |= 1;
		};

		SET(KNOCK_FLAG2_FFFF887A, KNOCK_GAIN_3);
	}
	else
	{
		if ((KNOCK_FLAG2_FFFF887A & KNOCK_GAIN_3) != 0)
		{
			wMUTC9_knock_ADC_proc_filtered *= 3;

			knock_filtered_x256 *= 3;

			knock_base_final = Lim16(knock_base_final*3, 1, 0xFF);

			KNOCK_FLAG1_FFFF8C36 |= 1;
		};

		CLR(KNOCK_FLAG2_FFFF887A, KNOCK_GAIN_3);
	};

}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static bool CRANK75_sub_24636()
{
	u32 r1 = (crankHT_75_4us >= crankHT_75_4us_2) ? (crankHT_75_4us - crankHT_75_4us_2) : (crankHT_75_4us_2 - crankHT_75_4us);

	return r1 >= Mul_Fix8_Lim_FFFF(crankHT_75_4us, word_1792/*0.125*256*/);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static void CRANK75_sub_2467E(u16 v)
{
	if (v == 1)
	{
		filtred_crankHT_x_4us = crankHT_75_4us;
		Start_Coil_Charge(curTimingMask_75);
	};

	state_Ignition = IGNST_NEXT_COIL;
	curTiming_5_4us = 0;
	timingAdvInternal1 = 202;
	timingAdvInternal2 = 202;
	timingAdvScaled = 160;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static void CRANK75_MainUpdateTiming()
{
    if (wMUT26_Knock_Retard > const_24)
    {
		wMUT26_Knock_Retard = 0;
	};

	u32 ign = timingAdv_75;

	if ((IGN_FLAG9_FFFF8BB6 & IGN_F9_04) || word_FFFF8BF4 != 0 || word_FFFF8BFA != 0)
	{
		ign += word_FFFF8BFA;

		if (byte_1077/*0*/ != 0)
		{
			if (ign >= word_FFFF8C8C)
			{
				ign = word_FFFF8C8C;
			};
		}
		else
		{
			if (ign >= word_246E)
			{
				ign = word_246E;
			};
		};
	};

	// loc_247CA

	ign += sub_21AAA(wMUT26_Knock_Retard);


	if ((IGN_FLAG9_FFFF8BB6 & IGN_F9_08) && (camShaftFlags & CAM_SYNCHRO))
	{
		if (IGN_FLAG9_FFFF8BB6 & IGN_F9_20)
		{
			ign += array_OctanNum[stroke_75];
		}
		else
		{
			ign += array_OctanNum[stroke_75];
		};
	};

	// loc_24810

	ign = sub_21ACC(ign);

	if (ign >= const_timing_231)
	{
		ign = const_timing_231;
	};

	ign += 42;

	if (ign <= timingAdvInternal1)
	{
		u32 r1 = timingAdvInternal2;

		u32 r13 = Sub_Lim_0(timingAdvInternal1, const_timing_40_0/*64*/);

		timingAdvInternal1 = (ign >= r13) ? ign : r13;

		if (ign < timingAdvInternal2)
		{
			r13 = Sub_Lim_0(timingAdvInternal2, const_timing_40_0/*64*/);

			timingAdvInternal2 = (ign >= r13) ? ign : r13;
		}
		else
		{
			// loc_2489C

			timingAdvInternal2 = timingAdvInternal1;
		};

		// loc_248A4

		r13 = Sub_Lim_0(r1, sub_21B50(14));

		if (timingAdvInternal1 < r13)
		{
			timingAdvInternal1 = r13;
		};
	}
	else
	{
		// loc_2491C

		u32 t = timingAdvInternal1 + const_timing_40/*64*/;

		if (ign >= t)
		{
			ign = t;
		};

		timingAdvInternal2 = ign;
		timingAdvInternal1 = ign;
	};

	// loc_24938

	timingAdvScaled = timingAdvInternal1 - 42;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static u16 CRANK75_FiltrCrankHT_2494E(u16 r1, u16 r2)
{
	if (ZRO(word_FFFF8C5C, IGN_X_RPM500) || ZRO(word_FFFF8C5C, IGN_X_PREV_RPM500) || (word_FFFF8C5C & IGN_X_RPM4800) || r1 >= 7500)
	{
		return r1;
	};

	u32 r8 = r1 >> 6;

	if (r1 >= r2)
	{
		// loc_249BE

		u32 r13 = r1 - r2;

		if (r13 >= r8)
		{
			r1 = Add_Lim_FFFF(r1, Mul_R4_R5_Div_128_Into_R0(r13 - r8, word_1790/*128*/));
		};
	}
	else
	{
		u32 r13 = r2 - r1;

		if (r13 < r8)
		{
			r1 = Sub_Lim_0(r1, Mul_R4_R5_Div_128_Into_R0(r13 - r8, word_178E/*128*/));;
		};
	};

	return r1;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static u16 CRANK75_Get_IgnCoilTime(u16 r1)
{
	u32 r2;

	if ((word_FFFF8C5C & (IGN_X_PREV_RPM1775|IGN_X_RPM1775)) == (IGN_X_PREV_RPM1775|IGN_X_RPM1775))
	{
		r2 = ignCoilTime_Fin_4us;
	}
	else if (r1 < 4400/*1700rpm*/)
	{
		r2 = ignCoilTime_4us;
	}
	else
	{
		r2 = (r1 - 4400) >> 4;

		if (timingAdvInternal1 > 202)
		{
			u32 r13 = Mul_Div(timingAdvInternal1 - 198, r1, 0x400);

			r2 = MIN(r13, 0x100);
		};

		r2 += ignCoilTime_4us;
	};

	return r2;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static void CRANK75_Knock_sub_24AC0()
{
	word_FFFF8C52 = KNOCK_PRECOUNT_MAX_FFFF8C4A;
	bMUTCE_KNOCK_PRECOUNT_2_FFFF8C50 = KNOCK_PRECOUNT_MAX_FFFF8C4A;
	bMUTCD_KNOCK_PRECOUNT_1_FFFF8C4E = KNOCK_PRECOUNT_MAX_FFFF8C4A;
	knock_null_FFFF8C58 = 0x8000;
	bMUTCC_KNOCK_UB_FFFF8C56 = 0x8000;
	bMUTCB_KNOCK_U_FFF8C54 = 0x8000;
	KNOCK_REL_compare_to_10_FFFF8C5A = 0;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CRANK5_Main_sub_24AF0()
{
//	u32 r8 = 0x8000;

	__disable_irq();

	camshaft_Shift <<= 1;

	if (CRANK_CheckCamshaft_sub_A7C0())
	{
		SET(camshaft_Shift, 1);
	};

	u32 crnkHT5 = crankHT_5_copy = crankHT_5;


	if (timer_FFFF8594 == 0 || (crnkHT5 & 0x8000))
	{
		word_FFFF8C5C = 0;

		// loc_24B50

		CRANK5_sub_2504A();
		CRANK5_SetIgnCoilTime_Fin();
	}
	else if (ZRO(word_FFFF8C5C, IGN_X_PREV_RPM500))
	{
		// loc_24B50

		CRANK5_sub_2504A();
		CRANK5_SetIgnCoilTime_Fin();
	}
	else
	{
		// loc_24B5C

		u32 curTm5 = curTiming_5_4us; // r1

		if (curTm5 != 0)
		{
			if (Get_Coil_charge_status() & curTimingMask_75)
			{
				// loc_24B7E

				u32 r13;

				do
				{
					r13 = Get_Coil_charge_status() & curTimingMask_75;
				}
				while (r13 != curTimingMask_75 && r13 != 0);

				if (state_Ignition != IGNST_NEXT_COIL
					&& ((word_FFFF8C5E & 1) || ABSDIF(curIgnSparkTime_4us - crank_OSBR2_5, curTm5) > crankHT_75_div_128))
				{
					CRANK5_SetIgnSpark5();
				};
			}
			else
			{
				// loc_24C30

				if (state_Ignition == IGNST_CUR_COIL)
				{
					u32 r2 = crank_OSBR2_5 + curTm5 - ignCoilTime_Fin_4us - crankHT_75_div_128;

					if ((r2 - reg_TCNT2A) & 0x8000)
					{
						r2 = reg_TCNT2A;

						Start_Coil_Charge(curTimingMask_75);

						curIgnCoilStartTime_4us = r2;

						CRANK5_SetIgnSpark5();
					}
					else
					{
						// loc_24C80

						SetIgnCoilChargeStartTime(curTimingMask_75, r2);

						curIgnCoilStartTime_4us = r2;
					
						if (((word_FFFF8C5E & 1) || ABSDIF(curIgnSparkTime_4us - crank_OSBR2_5, curTm5) > crankHT_75_div_128))
						{
							curIgnSparkTime_4us = curTm5 + crank_OSBR2_5;
						};
					};
				};
			};
		};

		// loc_24CD0

		if (ZRO(camShaftFlags, CAM_SYNCHRO) || ZRO(camShaftFlags, CAM_10)
			|| (ZRO(word_FFFF8C5C, IGN_X_FIX5) && timingAdvInternal1 < 200 && (Get_Coil_charge_status() & curTimingMask_75) && state_Ignition != IGNST_NEXT_COIL))
		{
			// loc_24D0A

			CRANK5_sub_2504A();
		};


		// loc_24D0E

		CRANK5_SetIgnCoilTime_Fin();

		// ���������� ������ ������� ���������� ������ �������. ����� �������� �� 110 �������� ���� ������� ����� � ���� 5 �������� �� ��� 
		// ���� ����� ������� ��������� ����� ����� �� ����� �������
		
		u32 r2 = Mul_Fix8_Lim_FFFF(156, crankHT_5_copy)/*110 deg*/ + crank_OSBR2_5 + nxtTiming_75_4us - ignCoilTime_Fin_4us;

		u32 r1 = curIgnSparkTime_4us + word_179C/*250*/;

		if ((r2 - r1) & 0x8000)
		{
			r2 = r1;
		};

		// loc_24D54

		if (Get_Coil_charge_status() & curTimingMask_75)
		{
			if (state_Ignition != IGNST_NEXT_COIL)
			{
				ignCoilNextStartTime_x4us = r2;
			};
		}
		else
		{
			if (state_Ignition != IGNST_CUR_COIL)
			{
				state_Ignition = IGNST_NEXT_COIL;

				SetIgnCoilChargeStartTime(nxtTimingMask_75, r2);
			};
			
			ignCoilNextStartTime_x4us = r2;
		};
	};

	// loc_24DBE

	CLR(word_FFFF8C5E, 1);

	SET(word_FFFF8BBA, 0x80);

	if (wMUTD1_BitMap_FAA & FAA_7_HIGH_IGN/*Enable High Oct Ign Map Lookup and other*/)
	{
		CRANK5_sub_C990(25 + (((curIgnSparkTime_4us - crank_OSBR2_5) & 0x8000) ? crank_OSBR2_5 : curIgnSparkTime_4us));
	};
	
	// loc_24DFE

	__enable_irq();

	if (timer_down_TXFLAG3_FFFF8574 == 0 || timer_FFFF8592 == 0)
	{
		camShaftFlags = 0;

		SET(camshaft_Shift, ~1);

		word_FFFF8F28 = (camshaft_Shift & 1) ? 1 : 0;
	};

	// loc_24E3C

	u32 r1 = word_177A/*24*/;

	if (Check_Starter_signal())
	{
		r1 <<= 1;
	};

	if (ZRO(wMUTD1_BitMap_FAA, FAA_3_IMMO) || (word_FFFF80FA & 0x80) || word_FFFF8EBA != 0 || (FLAGS_FFFF8EB0 & 0x80))
	{
		timer_FFFF8592 = r1;
	};
	
	// loc_24EE8


	if (RT_FLAG1_FFFF8888 & RT_7_bit)
	{
		if (crank5_FFFF8A36 != 0)
		{
			crank5_FFFF8A36 -= 1;

			if (crank5_FFFF8A36 == 0)
			{
				SET(RPM_FLAGS, RPM_14_bit);
			};
		};
	}
	else if (ZRO(RT_FLAG1_FFFF8888, DRIVE_ALWAYS_1))
	{
		crank5_FFFF8A36 = word_155E/*16*/;
	}
	else if (SPEED_FLAGS & SPD_2_ALWAYS_0)
	{
		crank5_FFFF8A36 = word_155C/*16*/;
	}
	else
	{
		crank5_FFFF8A36 = word_1560/*16*/;
	};

	// loc_24F58

	if (ZRO(RPM_FLAGS, RPM_2_DECELERATION_FUEL_CUT))
	{
		DECLIM(word_FFFF8AC0);	
	};

	DECLIM(word_FFFF8BF4);	

	DECLIM(word_FFFF8BF6);	

	if (word_FFFF8BF4 == 0 && word_FFFF8BF6 == 0 && word_FFFF8BFA != 0)
	{
		word_FFFF8BFA = Sub_Lim_0(word_FFFF8BFA, word_FFFF8BFE);

		word_FFFF8BF6 = (byte_1077/*0*/ != 0) ? word_FFFF8C8E : word_246C/*1*/;
	};

	// loc_24FDC	

	if ((word_FFFF8A48 & 0x80) && (RPM_FLAGS & RPM_9_wtf_cranking))
	{
		CRANK_MAF_MAP_Calcs_sub_250F8(2, 1);
	}
	else
	{
		CRANK_MAF_MAP_Calcs_sub_250F8(0, 1);
	};

	stroke_FFFF8F26 = strokeNumber;

	Misfire_CRANK5_root();

	if (word_FFFF89F2 & 1)
	{
		SET(word_FFFF89F2, 2);
	}
	else
	{
		SET(word_FFFF89F2, 1);

		curMaxMAP = 0;

		word_FFFF8556 = word_1764/*20*/;
	};

	CRANK5_sub_21A04();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static void CRANK5_sub_2504A()
{
	Disable_Coil_Charge(0xFF);
	state_Ignition = IGNST_NEXT_COIL;
	curIgnSparkTime_4us = reg_TCNT2A;
}	

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static void CRANK5_SetIgnSpark5()
{
	u16 r1 = crank_OSBR2_5 + curTiming_5_4us;

	if ((r1 - reg_TCNT2A) & 0x8000)
	{
		r1 = reg_TCNT2A;
	};

	state_Ignition = IGNST_SPARK;

	SetIgnSparkStartTime(curTimingMask_75, r1);

	curIgnSparkTime_4us = r1;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static void CRANK5_SetIgnCoilTime_Fin()
{
	ignCoilTime_Fin_4us = MIN(Mul_R4_R5_Div_128_Into_R0(crankHT_5, ignCoil_MaxCrankDegrees), ignCoilTime_4us);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// v1 = 0: 

static void CRANK_MAF_MAP_Calcs_sub_250F8(u16 v1, u16 v2)
{
	enum INJMODE {INJ_NONE = 0, INJ_PHASE = 1, INJ_2 = 2, INJ_3 = 3} inj_mode;

//	u32 inj_mode1; // 0 - None; 1 - ; 2 - ; 3 - 
	u32 ipw, r9 = 0;

	if (v1 == 1)
	{
		// async_25DE6

		if (ONE(FUEL_CUT_FLAG_FFFF8A5E, FCF_80) && ONE(RPM_FLAGS, RPM_0_CRANKING) && (word_FFFF8AD6 != 0 || ZRO(camShaftFlags, CAM_02)))
		{
			// loc_25E06

			inj_mode = INJ_NONE; // None
		}
		else
		{
			// loc_25E0C

			inj_mode = INJ_2;
		};

		// loc_25E0E

		ipw = word_FFFF8A4E;
	}
	else
	{
		// loc_25120

		if (crankHT_75_4us_3 < Rev_Limit_Sensor_Error_1576)
		{
			SET(RPM_FLAGS, RPM_5_REVLIM);
		}
		else
		{
			CLR(RPM_FLAGS, RPM_5_REVLIM);
		};
		
		// loc_25142

		u32 r13 = Add_Lim_FFFF(manifold_SumCount, manifold_SumCount_prev);

		if (r13 != 0)
		{
			Manifold_AbsPressure_ADC8bit_x256_avrg = Div_DW(Add_R4w_R5w(manifold_Sum, manifold_Sum_prev) << 8, r13);

			Manifold_AbsPressure_ADC8bit_avrg = Manifold_AbsPressure_ADC8bit_x256_avrg >> 8;
		};

		// loc_25192

		manifold_SumCount_prev = manifold_SumCount;

		manifold_SumCount = 0;

		manifold_Sum_prev = manifold_Sum;

		manifold_Sum = 0;

		if (RPM_FLAGS & RPM_1_MAP_error)
		{
			// loc_251BA
	
			Manifold_ADC8bit_1 = wMUT1A_Manifold_AbsPressure_ADC8bit;
			Manifold_ADC8bit_2 = Manifold_ADC8bit_1;
			Manifold_ADC8bit_3 = Manifold_ADC8bit_1;
			Manifold_ADC8bit_4 = Manifold_ADC8bit_1;

			Manifold_AbsPressure_ADC8bit_x256_avrg = (Manifold_AbsPressure_ADC8bit_avrg = load_vs_tps) << 8;
		};

		// loc_252C0

		if (load_FFFF8976 < baro_FFFF8B10 && word_FFFF86F4 == 0 && ABSDIF(wMUT1A_Manifold_AbsPressure_ADC8bit, Manifold_ADC8bit_1) >= word_2AB2/*2*/)
		{
			u32 r2;

			if (wMUT1A_Manifold_AbsPressure_ADC8bit >= Manifold_ADC8bit_1)
			{
				r2 = Add_Lim_FFFF(Manifold_AbsPressure_ADC8bit_x256_avrg, Mul_Div((wMUT1A_Manifold_AbsPressure_ADC8bit - Manifold_ADC8bit_1) << 8 , word_2542/*122*/, 32));
			}
			else
			{
				// loc_25368

				r2 = Sub_Lim_0(Manifold_AbsPressure_ADC8bit_x256_avrg, Mul_Div((Manifold_ADC8bit_1 - wMUT1A_Manifold_AbsPressure_ADC8bit) << 8 , word_2544/*122*/, 32));
			};

			// loc_2539A

			MAFSxMAF_MULTIPLIER_1_FFFF89A8 = Lim16(r2, word_254A << 8,  wMUT15_Barometric_Pressure << 8);
		}
		else
		{
			// loc_253C0

			MAFSxMAF_MULTIPLIER_1_FFFF89A8/*51200*/ = Manifold_AbsPressure_ADC8bit_x256_avrg;
		};

		// loc_253C8

		if (wMUT1A_Manifold_AbsPressure_ADC8bit >= Manifold_ADC8bit_4)
		{
			r13 = wMUT1A_Manifold_AbsPressure_ADC8bit - Manifold_ADC8bit_4;

			if (MAX_MAP_FALL_CHANGE < r13)
			{
				MAX_MAP_FALL_CHANGE = r13;
			};
		}
		else
		{
			// loc_253F6

			r13 = Manifold_ADC8bit_4 - wMUT1A_Manifold_AbsPressure_ADC8bit;

			if (MAX_MAP_RISE_CHANGE < r13)
			{
				MAX_MAP_RISE_CHANGE = r13;
			};
		};

		// loc_25414

		crank_cur_map = wMUT1A_Manifold_AbsPressure_ADC8bit;
		crank_prev_4_cycle_map = Manifold_ADC8bit_4;

		bool c = true;

		if (wMUTC0_bMUT54_Acceleration_Enrichment != 0)
		{
			if (wMUTC0_bMUT54_Acceleration_Enrichment > word_1672)
			{
				r13 = Mul_Fix8_Lim_FFFF(wMUTC0_bMUT54_Acceleration_Enrichment, enrichCoolTemp);

				wMUTC0_bMUT54_Acceleration_Enrichment = (r13 >= word_1672/*0*/) ? r13 : word_1672/*0*/;
			}
			else if (word_FFFF8B2C == 0)
			{
				wMUTC0_bMUT54_Acceleration_Enrichment = Mul_Fix8_Lim_FFFF(wMUTC0_bMUT54_Acceleration_Enrichment, word_1674/*248*/);
			}
			else
			{
				// loc_25492

				c = false;
			};
		};

		// loc_25494

		if (c && wMUT10_Coolant_Temperature_Scaled < word_167A/*141(101)*/)
		{
			word_FFFF8B2C = word_1678/*8*/;
		};

		// loc_254AE

		DECLIM(word_FFFF8B2C);

		DECLIM(word_FFFF8B30);

		// loc_254CE

		c = true;

		if (wMUTC1_bMUT55_Deceleration_Enleanment != 0)
		{
			if (wMUTC1_bMUT55_Deceleration_Enleanment > word_168C)
			{
				r13 = Mul_Fix8_Lim_FFFF(wMUTC1_bMUT55_Deceleration_Enleanment, word_FFFF8B1C);

				wMUTC1_bMUT55_Deceleration_Enleanment = (r13 >= word_168C) ? r13 : word_168C;
			}
			else if (word_FFFF8B2E == 0)
			{
				wMUTC1_bMUT55_Deceleration_Enleanment = Mul_Fix8_Lim_FFFF(wMUTC1_bMUT55_Deceleration_Enleanment, word_168E);
			}
			else
			{
				// loc_2553C

				c = false;
			};
		};

		// loc_2553E

		if (c && wMUT10_Coolant_Temperature_Scaled < word_1690/*255*/)
		{
			word_FFFF8B2E = word_1692/*4*/;
		};

		// loc_255F4

		DECLIM(word_FFFF8B2E);

		// loc_25604

		if ((RPM_FLAGS & (RPM_4_STALL|RPM_1_MAP_error|RPM_0_CRANKING)) || cranking_end_timer_up < word_1664)
		{
			wMUTC0_bMUT54_Acceleration_Enrichment = 0;
			wMUTC1_bMUT55_Deceleration_Enleanment = 0;
		}
		else if (!PEDR_LO_Check_sub_A790())
		{
			wMUTC1_bMUT55_Deceleration_Enleanment = 0;
		}
		else if ((RPM_FLAGS & (RPM_5_REVLIM|RPM_3_FUEL_CUT)) || (FUEL_CUT_FLAG_FFFF8A5E & FCF_40))
		{
			wMUTC0_bMUT54_Acceleration_Enrichment = 0;
		}
		else if (crank_cur_map < crank_prev_4_cycle_map)
		{
			u32 r2 = Sub_Lim_0(crank_prev_4_cycle_map, crank_cur_map);

			if (r2 >= word_FFFF8B2A)
			{
				word_FFFF8B2A = r2;
			};

			u32 r13 = (wMUT10_Coolant_Temperature_Scaled >= word_167E/*0*/ && wMUT10_Coolant_Temperature_Scaled < word_1680/*151(111)*/ && rise_TPS_timer != 0) ? word_1684/*51*/ : word_FFFF8B20;

			// loc_25798

			if (r2 > r13)
			{
				r2 <<= 1;

				if (r2 >= 0xFF)
				{
					r2 = 0xFF;
				};

				// loc_257B0

				if (r2 >= wMUTC1_bMUT55_Deceleration_Enleanment)
				{
					wMUTC1_bMUT55_Deceleration_Enleanment = r2;
				};

				wMUTC0_bMUT54_Acceleration_Enrichment = 0;
			};
		}
		else // (crank_cur_map < crank_prev_4_cycle_map)
		{
			// loc_25660

			u32 r2 = Sub_Lim_0(crank_cur_map, crank_prev_4_cycle_map);

			if (r2 >= word_FFFF8B28)
			{
				r2 = word_FFFF8B28;
			};

			// loc_25684

			u32 r13 = (wMUT10_Coolant_Temperature_Scaled >= word_167E/*0*/ && wMUT10_Coolant_Temperature_Scaled < word_1680/*151(111)*/ && fall_TPS_timer != 0) ? word_166A/*14*/ : ((word_FFFF855A != 0) ? word_1666/*4*/ : word_1668/*14*/);

			// loc_256C0

			if (r2 > r13)
			{
				if (wMUT10_Coolant_Temperature_Scaled >= word_167C/*0*/)
				{
					if (wMUTC0_bMUT54_Acceleration_Enrichment == 0)
					{
						word_FFFF8B30 = word_1676/*8*/;
					};

					if (word_FFFF8B30 != 0)
					{
						r2 = Mul_Div(r2, word_FFFF8B38, 32);

						if (r2 >= word_FFFF8B28)
						{
							r2 = word_FFFF8B28;
						};
					};
				};

				// loc_25714

				r2 <<= 2;

				if (r2 >= 0xFF)
				{
					r2 = 0xFF;
				};

				// loc_257B0

				if (r2 >= wMUTC0_bMUT54_Acceleration_Enrichment)
				{
					wMUTC0_bMUT54_Acceleration_Enrichment = r2;
				};

				wMUTC1_bMUT55_Deceleration_Enleanment = 0;
			};
		};

		// loc_257CA

		ipw_Enrichment = (wMUTC0_bMUT54_Acceleration_Enrichment != 0) ? Lim_FFFF(Mul_DW_Div(dword_FFFF8B14, wMUTC0_bMUT54_Acceleration_Enrichment, 2048)) : 0;

		ipw_Enleanment = (wMUTC1_bMUT55_Deceleration_Enleanment != 0) ? Mul_Div(wMUTC1_bMUT55_Deceleration_Enleanment, word_FFFF8B18, 2048) : 0;

		// loc_25826

		Manifold_ADC8bit_4 = Manifold_ADC8bit_3;
		Manifold_ADC8bit_3 = Manifold_ADC8bit_2;
		Manifold_ADC8bit_2 = Manifold_ADC8bit_1;
		Manifold_ADC8bit_1 = wMUT1A_Manifold_AbsPressure_ADC8bit;

		if (FLAGS_FFFF8EB0 & 0x80)
		{
			ipw_Enrichment = 0;
			ipw_Enleanment = 0;
		};

		if (!PEDR_LO_Check_sub_A790() || (RPM_FLAGS & RPM_4_STALL))
		{
			// loc_25914

			ipw = 0;

			sub_2640E(0);
		}
		else if (RPM_FLAGS & (RPM_5_REVLIM|RPM_3_FUEL_CUT))
		{
			// loc_25940

			ipw = 0;

			if (byte_1090/*0*/ != 0)
			{
				// loc_259D4

				u32 r13 = word_FFFF8B7C[3];
				u32 r3 = word_FFFF8B8A[3];

				word_FFFF8B98 = 0;
				
				if (word_FFFF8AF2 != 0 || word_FFFF86F2 != 0)
				{
					r3 = 0;
					r13 = 0;
				};

				u32 r2 = word_FFFF8B74;

				word_FFFF8B9A = Interpolate_256(0, Interpolate_256(r13, r3, word_FFFF8B76), r2);

				word_FFFF8B9C = 0;
				word_FFFF8B7C[6] = word_FFFF8B7C[5];
				word_FFFF8B7C[5] = word_FFFF8B7C[4];
				word_FFFF8B7C[4] = word_FFFF8B7C[3];
				word_FFFF8B7C[3] = word_FFFF8B7C[2];
				word_FFFF8B7C[2] = word_FFFF8B7C[1];
				word_FFFF8B7C[1] = word_FFFF8B7C[0];

				word_FFFF8B7C[0] = Interpolate_256(0, r13, word_FFFF8B78);

				word_FFFF8B8A[6] = word_FFFF8B8A[5];
				word_FFFF8B8A[5] = word_FFFF8B8A[4];
				word_FFFF8B8A[4] = word_FFFF8B8A[3];
				word_FFFF8B8A[3] = word_FFFF8B8A[2];
				word_FFFF8B8A[2] = word_FFFF8B8A[1];
				word_FFFF8B8A[1] = word_FFFF8B8A[0];

				word_FFFF8B8A[0] = Interpolate_256(0, r3, word_FFFF8B7A);
			}
			else
			{
				// loc_25954

				if (word_FFFF8B7C[0] > word_2972 && word_FFFF8B8A[0] > word_2974)
				{
					sub_2640E(0);
				}
				else
				{
					word_FFFF8B7C[6] = 0;
					word_FFFF8B7C[5] = 0;
					word_FFFF8B7C[4] = 0;
					word_FFFF8B7C[3] = 0;
					word_FFFF8B7C[2] = 0;
					word_FFFF8B7C[1] = 0;
					word_FFFF8B7C[0] = 0;
					word_FFFF8B8A[6] = 0;
					word_FFFF8B8A[5] = 0;
					word_FFFF8B8A[4] = 0;
					word_FFFF8B8A[3] = 0;
					word_FFFF8B8A[2] = 0;
					word_FFFF8B8A[1] = 0;
					word_FFFF8B8A[0] = 0;

					word_FFFF8B9C = 0;
					word_FFFF8B9A = 0;
					word_FFFF8B98 = 0;
				};
			};
		}
		else if (RPM_FLAGS & RPM_0_CRANKING)
		{
			ipw = ipw_crank_DuringCranking;

			word_FFFF8B7C[6] = ipw;
			word_FFFF8B7C[5] = ipw; 
			word_FFFF8B7C[4] = ipw; 
			word_FFFF8B7C[3] = ipw; 
			word_FFFF8B7C[2] = ipw; 
			word_FFFF8B7C[1] = ipw; 
			word_FFFF8B7C[0] = ipw; 
			word_FFFF8B8A[6] = ipw; 
			word_FFFF8B8A[5] = ipw; 
			word_FFFF8B8A[4] = ipw; 
			word_FFFF8B8A[3] = ipw; 
			word_FFFF8B8A[2] = ipw; 
			word_FFFF8B8A[1] = ipw; 
			word_FFFF8B8A[0] = ipw; 

			word_FFFF8B9C = ipw; 
			word_FFFF8B9A = ipw; 
			word_FFFF8B98 = ipw;

			Table_Lookup_Axis(CEL8_7974);

			word_FFFF86F2 = Table_Lookup_byte_2D_3D(unk100_62FC);

			word_FFFF86F0 = Table_Lookup_byte_2D_3D(unk112_5240);

			word_FFFF8AF2 = 4;
		}
		else
		{
			// loc_25B36

			if (wMUTC0_bMUT54_Acceleration_Enrichment != 0 || wMUTC1_bMUT55_Deceleration_Enleanment != 0);

			u32 r2 = MAFSxMAF_MULTIPLIER_1_FFFF89A8/*51200*/;

			u32 r0 = SHLR8(wMUT0F_Oxygen_Feedback_Trim/*32768*/) << 1; // 256

			r0 += wMUT52_COPY/*128*/ + wMUT50_Long_Fuel_Trim_Bank_1_COPY/*128*/; // 512

			r0 = Mul_Div(MUTC7_copy/*479*/, r0/*512*/, 512); // 479

			r0 = Mul_Div(r0/*479*/, r2/*51200*/, 0x4000); // 1496

			ipw_FFFF9956 = ipw = sub_2640E(r0);

			if (ipw_Enrichment != 0)
			{
				ipw = Add_Lim_FFFF(ipw, ipw_Enrichment);
			};

			if (ipw_Enleanment != 0)
			{
				ipw = Sub_Lim_0(ipw, ipw_Enleanment);

				if (ipw == 0)
				{
					ipw = 1;
				};
			};
		};

		// loc_25BCC

		if (FUEL_CUT_FLAG_FFFF8A5E & FCF_40)
		{
			if (byte_35B7[word_FFFF8AD0] == 0) // 0,  1,  0,  1,  0,  1
			{
				ipw = 0;
			};

			INCLIM(word_FFFF8AD0);

			if (word_FFFF8AD0 >= 4)
			{
				word_FFFF8AD0 = 0;
			};
		}
		else
		{
			word_FFFF8AD0 = 0;
		};

		INCLIM(word_FFFF8F30);

		if (word_FFFF8F30 >= 2)
		{
			word_FFFF8F30 = 0;
		};

		if (camShaftFlags & CAM_02)
		{
			word_FFFF8F30 = 1;
		};

		if (RPM_FLAGS & RPM_13_CRANKING_SYNC_INJECT)
		{
			inj_mode = INJ_3;

			ipw = ipw_crank_DuringCrankingSync;

			DECLIM(timer_CrankingInjectSync);

			if (timer_CrankingInjectSync == 0)
			{
				CLR(RPM_FLAGS, RPM_13_CRANKING_SYNC_INJECT);
			};
		}
		//else if (RPM_FLAGS & RPM_13_CRANKING_SYNC_INJECT)
		//{
		//	r2 = 2;

		//	ipw = ipw_crank_DuringCrankingSync;

		//	DECLIM(timer_CrankingInjectSync)

		//	if (timer_CrankingInjectSync == 0)
		//	{
		//		CLR(RPM_FLAGS, RPM_13_CRANKING_SYNC_INJECT);
		//	};
		//}
		else if ((FUEL_CUT_FLAG_FFFF8A5E & FCF_80) && (RPM_FLAGS & RPM_0_CRANKING) && (word_FFFF8AD6 != 0 || ZRO(camShaftFlags, CAM_02)))
		{
			inj_mode = INJ_NONE;
		}
		else if (RPM_FLAGS & RPM_15_bit)
		{
			inj_mode = INJ_2;
		}
		else if ((camShaftFlags & CAM_02) || (camShaftFlags & (CAM_04|CAM_02)))
		{
			inj_mode = INJ_PHASE;
		}
		else 
		{
			inj_mode = INJ_2;

			ipw = Div_R4_R5__R0(ipw , 4);
		};

		// loc_25DCE

		DECLIM(word_FFFF8AD6);

		word_FFFF8A4E = ipw;
	};

	// loc_25E12

	if (inj_mode != INJ_NONE && ipw != 0)
	{
		// loc_25E26

		r9 = 0;

		if (MUT21_RPM_x125div4 <= rpm_1508/*255(7968)*/)
		{
			r9 = word_1504/*5*/ << 5;
		};

		bMUTC5_InjPulseW_8us = injPulseWidth_null = ipw = Lim16(INJECTOR_RESCALED_sub_26174(ipw), 65000, r9);

		wMUT2A_Injector_Pulse_Width_us = Mul_Lim_FFFF(ipw, 8);

		if ((bMUTD3_BitMap4_FCA_Store_FFFF89D8 & FCA_2_04) && (word_FFFF929A == 6 || word_FFFF929A == 9))
		{
			// loc_25E82

			word_FFFF929A += 1;
		};

		// loc_25E8A

		bMUTC6_FFFF8A52 = ipw;

		MUT_2B_FFFF9996 = Mul_Lim_FFFF(ipw, 8);

		u32 inj_mask;

		if (inj_mode == INJ_PHASE)
		{
			if (ZRO(word_FFFF8B4E, INJ_7_80))
			{
				// loc_25F98

				inj_mask = word_98D4[strokeNumber+1];//2,1,4,8,2

				if (word_FFFF8B4E & INJ_6_40)
				{
					inj_mask |= word_98D4[strokeNumber];//2,1,4,8,2
				};

			}
			else if (ZRO(word_FFFF8B4E, INJ_6_40))
			{
				// loc_25EC0

				u32 r13 = 3;

				if (strokeNumber != 0)
				{
					r13 = Sub_Lim_0(strokeNumber, 1);
				};

				if ((wMUT1E_MAF_RESET_FLAG & CRANKING) && (word_FFFF8A48 & 0x80) && ZRO(word_FFFF8B4E, INJ_5_SYNC_INJECT) && ZRO(word_FFFF89F2, 0x400) && ZRO(word_FFFF89F2, 0x800))
				{
					SET(word_FFFF89F2, 0x800);

					inj_mask = word_98D4[r13];//2,1,4,8,2
				}
				else
				{
					// loc_25F88
					inj_mask = word_98D4[strokeNumber];//2,1,4,8,2
				};
			}
			else
			{
				inj_mask = 0;
			};
		}
		else if (inj_mode == INJ_3)
		{
			if (ZRO(BOOSTCHECK2_FFFF8A0E, 0x40) && ZRO(word_FFFF89F2, 0x400))
			{
				SET(word_FFFF89F2, 0x400);
				word_FFFF8F28 ^= 1;
			};

			// loc_25FEA

			inj_mask = word_98E6[word_FFFF8F28];//0xF,0xF
			word_FFFF8F28 ^= 1;
		}
		else
		{
			// loc_26002
			inj_mask = 0xF;
		};

		// loc_26004

		CLR(word_FFFF8B4E, INJ_6_40);

		if ((word_FFFF8A48 & 0x80) && v1 == 0)
		{
			StartInjectSync(ipw, inj_mask);

			r9 = 0;
		}
		else
		{
			// inj_async_2602C
			StartInjectAsync(ipw, inj_mask);

			r9 = 1;
		};

		// loc_26038

		ipw = 0;

		for (u32 r1 = 1; r1 <= 8; r1 <<= 1)
		{
			if (inj_mask & r1)
			{
				ipw += 1;
			};
		};

		dword_FFFF8B68 = Add_Lim_FFFFFFFF(dword_FFFF8B68, Mul16(ipw, word_FFFF8A4E) << 1);
	}
	else
	{
		// loc_2607E
		injPulseWidth_null = 0;
	};

	// loc_26084

	if (r9 != 0)
	{
		CRANK_sub_262D0();
	};
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static void CRANK75_sub_260B8()
{
	strokeNumber += 1;

	if (strokeNumber >= 4)
	{
		strokeNumber = 0;
	};

	if (camShaftFlags & CAM_SYNCHRO)
	{
		SET(camShaftFlags, (CAM_04|CAM_02));

		word_FFFF8F2E = 5;

		word_FFFF8F2E -= 1;
	}
	else
	{
		if (ZRO(camShaftFlags, CAM_04))
		{
			strokeNumber = ((camshaft_Shift & 3) - 1) & 3;

			SET(camShaftFlags, CAM_02);

			word_FFFF8F2E = 5;
		};

		DECLIM(word_FFFF8F2E);
	};
	
	if (word_FFFF8F2E == 0)
	{
		CLR(camShaftFlags, CAM_02);
		SET(camShaftFlags, CAM_04);
	};

	if (camShaftFlags & CAM_SYNCHRO)
	{
		strokeNumber = stroke_75;
	};

	DECLIM(word_FFFF8DE6);

	if ((camshaft_Shift & 3) == 1)
	{
		word_FFFF8DE6 = word_1C22/*8*/;
	};
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

u16 INJECTOR_RESCALED_sub_26174(u32 v)
{
	if (v <= 260)
	{
		v = Add_Lim_FFFF(v, Div_R4_R5__R0(byte_342F[(u32)v>>2], 2));
	};

	// loc_261AC

	return Add_Lim_FFFF(v, injectorLatencyRescaled);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void StartInjectAsync(u16 v, u16 mask)
{
	u32 r13 = mask & 0xF;

	r13 &= enInjMask;

	r13 &= injectors_mask_FFFF8C72;

	if (bMUTD3_BitMap4_FCA_Store_FFFF89D8 & (FCA_4_10|FCA_5_20)) // Random Misfire Detected
	{
		r13 &= injectors_misfire_mask;
	};

	if (v != 0 && r13 != 0)
	{
		InjOpenStart(v, r13);
	};

	CLR(word_FFFF8B4E, INJ_5_SYNC_INJECT);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void StartInjectSync(u16 v, u16 mask)
{
	u32 r13 = mask & 0xF;

	r13 &= enInjMask;

	r13 &= injectors_mask_FFFF8C72;

	if (bMUTD3_BitMap4_FCA_Store_FFFF89D8 & (FCA_4_10|FCA_5_20)) // Random Misfire Detected
	{
		r13 &= injectors_misfire_mask;
	};

	SET(word_FFFF8B4E, INJ_5_SYNC_INJECT);

	injPW_final = v;
	injPW_chnl = r13;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static void CRANK_sub_262D0()
{
	u32 r1 = atu22_Get_DSTR_0x3C00();

	bool r13 = Reset_IRQ0F();

	if ((word_FFFF8DF2 ^ r1) & word_FFFF8DF2 & word_FFFF8DF4)
	{
		if (r13)
		{
			CLR(wMUT72_Knock_Present, 2);

			word_FFFF8DF4 <<= 1;
		}	
		else
		{
			SET(wMUT72_Knock_Present, 2);

			word_FFFF922E = word_FFFF8DF4;
		};
	};

	if (ZRO(word_FFFF8DF4, 0xF))
	{
		word_FFFF8DF4 = 1;
	};

	word_FFFF8DF2 = r1;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

extern "C" void Ign_handler(u16 mask)
{
	Disable_Ign_Handler(mask);

	SET(local_2636C, curTimingMask_75 & mask);

	mask = curTimingMask_75 & local_2636C;

	if (curTimingMask_75 == mask)
	{
		if (state_Ignition == IGNST_CUR_COIL)
		{
			state_Ignition = IGNST_SPARK;

			if ((word_FFFF8C5E & 1) == 0)
			{
				SetIgnSparkStartTime(mask, curIgnSparkTime_4us);
			};
		}
		else if (state_Ignition == IGNST_SPARK && (word_FFFF8C5E & 1) == 0)
		{
			// loc_263CE

			state_Ignition = IGNST_NEXT_COIL;

			SetIgnCoilChargeStartTime(nxtTimingMask_75, ignCoilNextStartTime_x4us);
		};

		local_2636C &= ~mask;
	};
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static u16 sub_2640E(u16 ipw)
{
	u32 r9 = word_FFFF8B7C[3];
	u32 r8 = word_FFFF8B8A[3];

	word_FFFF8B98 = ipw;

	if (word_FFFF8AF2 != 0 || word_FFFF86F2 != 0)
	{
		r8 = ipw;
		r9 = ipw;
	};

	u32 r13 = Interpolate_256(ipw, Interpolate_256(r9, r8, word_FFFF8B76), word_FFFF8B74);

	u32 r2 = ipw;

	word_FFFF8B9A = r13;

	if (ipw >= r13)
	{
		word_FFFF8BA2 = Sub_Lim_0(r2, r13);

		word_FFFF8BA4 = Mul_Div_R(Mul_R4_R5_Div_128_Into_R0(word_FFFF8BA2, word_FFFF8B9E), 256, word_FFFF8B74);

		r2 = Add_Lim_FFFF(r2, word_FFFF8BA4);
	}
	else
	{
		// loc_264C6

		word_FFFF8BA2 = Sub_Lim_0(r13, r2);

		if (word_FFFF86F0 != 0)
		{
			word_FFFF8BA0 = 0;
		};

		word_FFFF8BA4 = Mul_Div_R(Mul_R4_R5_Div_128_Into_R0(word_FFFF8BA2, word_FFFF8BA0), 256, word_FFFF8B74);

		r2 = Sub_Lim_0(ipw, word_FFFF8BA4);

		if (r2 == 0)
		{
			r2 = 1;
		};
	};

	// loc_26526

	word_FFFF8B9C = r2;

	word_FFFF8B7C[6] = word_FFFF8B7C[5];
	word_FFFF8B7C[5] = word_FFFF8B7C[4];
	word_FFFF8B7C[4] = word_FFFF8B7C[3];
	word_FFFF8B7C[3] = word_FFFF8B7C[2];
	word_FFFF8B7C[2] = word_FFFF8B7C[1];
	word_FFFF8B7C[1] = word_FFFF8B7C[0];

	word_FFFF8B7C[0] = Interpolate_256(r2, r9, word_FFFF8B78);

	word_FFFF8B8A[6] = word_FFFF8B8A[5];
	word_FFFF8B8A[5] = word_FFFF8B8A[4];
	word_FFFF8B8A[4] = word_FFFF8B8A[3];
	word_FFFF8B8A[3] = word_FFFF8B8A[2];
	word_FFFF8B8A[2] = word_FFFF8B8A[1];
	word_FFFF8B8A[1] = word_FFFF8B8A[0];

	word_FFFF8B8A[0] = Interpolate_256(r2, r8, word_FFFF8B7A);

	if (cranking_end_timer_up >= word_22A2 && ONE(BOOSTCHECK2_FFFF8A0E, 0x400) && word_FFFF8BA2 >= word_2970 && ZRO(FLAGS_FFFF8EB0, 0x80))
	{
		ipw = r2;
	};

	DECLIM(word_FFFF8AF2);

	return ipw;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//static void SetIgnCoilChargeStartTime(u16 mask, u16 v)
//{
//	__disable_irq();
//
//	u32 r13 = v;
//
//	v -= reg_TCNT2A + 2;
//
//	if (v & 0x8000)
//	{
//		r13 = reg_TCNT2A + 2;
//	};
//
//	// 0 output on GR compare-match
//
//	if (mask & 1) { reg_GR2E = r13; CLR(reg_TSR2A, 0x10); reg_TIOR2C = reg_TIOR2C & 0xF8 | 1; };	
//	if (mask & 2) { reg_GR2F = r13; CLR(reg_TSR2A, 0x20); reg_TIOR2C = reg_TIOR2C & 0x8F | 0x10; };
//	if (mask & 4) { reg_GR2G = r13; CLR(reg_TSR2A, 0x40); reg_TIOR2D = reg_TIOR2D & 0xF8 | 1; };
//
//	__enable_irq();
//}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//static void SetIgnSparkStartTime(u16 mask, u16 v)
//{
//	__disable_irq();
//
//	u32 r13 = v;
//
//	v -= reg_TCNT2A + 2;
//
//	if (v & 0x8000)
//	{
//		r13 = reg_TCNT2A + 2;
//	};
//
//	// 1 output on GR compare-match
//
//	if (mask & 1) { reg_GR2E = r13; CLR(reg_TSR2A, 0x10); reg_TIOR2C = reg_TIOR2C & 0xF8 | 2; };
//	if (mask & 2) { reg_GR2F = r13; CLR(reg_TSR2A, 0x20); reg_TIOR2C = reg_TIOR2C & 0x8F | 0x20; };
//	if (mask & 4) { reg_GR2G = r13; CLR(reg_TSR2A, 0x40); reg_TIOR2D = reg_TIOR2D & 0xF8 | 2; };
//
//	__enable_irq();
//}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//void InjOpenStart(u16 v, u16 mask)
//{
//	__disable_irq();
//
//	if (v != 0)
//	{
//		u32 r13 = 0xFFFFFFFF + v;
//
//		if (mask & 1) 	{	reg_DCNT8K = r13; 	};
//		if (mask & 2) 	{	reg_DCNT8L = r13; 	};
//		if (mask & 4) 	{	reg_DCNT8M = r13; 	};
//		if (mask & 8) 	{	reg_DCNT8N = r13; 	};
//		if (mask & 16) 	{	reg_DCNT8O = r13; 	};
//		if (mask & 32) 	{	reg_DCNT8P = r13; 	};
//
//		SET(reg_DSTR, (mask & 63) << 10);
//	};
//	
//	__enable_irq();
//}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//static u16 atu22_Get_ECNT9A()
//{
//	__disable_irq();
//
//	u32 r1 = reg_ECNT9A;
//
//	reg_ECNT9A = 0;
//
//	if (reg_TSR9 & 1)
//	{
//		r1 = 0xFF;
//
//		CLR(reg_TSR9, 1);
//	};
//
//	__enable_irq();
//
//	return r1;
//}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//static void CRANK5_sub_21A04()
//{
//	u32 r13 = recieve_buffer_1_2;
//
//	if ((HIGHBAUDFLAG_FFFF93D8 & 1) && (r13 & 1) && (r13 & 0x20))
//	{
//		COM_MUT2B_sub_895C(0);
//	};
//
//	r13 = word_FFFF9A5E;
//
//	if ((HIGHBAUDFLAG_FFFF93D8 & 2) && (r13 & 1) && (r13 & 0x20))
//	{
//		COM_MUT2B_sub_895C(1);
//	};
//}


//static void CRANK5_sub_C990(u16 v)
//{
//	__disable_irq();
//
//	u32 r13 = v;
//
//	v -= reg_TCNT2A + 2;
//
//	if (v & 0x8000)
//	{
//		r13 = reg_TCNT2A + 2;
//	};
//
//	reg_GR2H = r13;
//
//	CLR(reg_TSR2A, 0x80);
//
//	reg_TIOR2D = reg_TIOR2D & 0x8F | 0x10;
//
//	__enable_irq();
//}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#endif // DEF_CRANK	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
