#ifndef __OPCODES_H__
#define __OPCODES_H__

#define ADC_RR8		(0)
#define ADC_RR16	(ADC_RR8 + 1)
#define ADC_RM8		(ADC_RR16 + 1)
#define ADC_RM16	(ADC_RM8 + 1)
#define ADC_RA8		(ADC_RM16 + 1)
#define ADC_RA16	(ADC_RA8 + 1)
#define ADC_RI8		(ADC_RA16 + 1)
#define ADC_RI16	(ADC_RI8 + 1)
#define ADC_MR8		(ADC_RI16 + 1)
#define ADC_MR16	(ADC_MR8 + 1)
#define ADC_M8I8	(ADC_MR16 + 1)
#define ADC_M16I8	(ADC_M8I8 + 1)
#define ADC_MI16	(ADC_M16I8 + 1)
#define ADC_AR8		(ADC_MI16 + 1)
#define ADC_AR16	(ADC_AR8 + 1)
#define ADC_A8I8	(ADC_AR16 + 1)
#define ADC_A16I8	(ADC_A8I8 + 1)
#define ADC_AI16	(ADC_A16I8 + 1)

#define AND_RR8		(ADC_AI16 + 1)
#define AND_RR16	(AND_RR8 + 1)
#define AND_RM8		(AND_RR16 + 1)
#define AND_RM16	(AND_RM8 + 1)
#define AND_RA8		(AND_RM16 + 1)
#define AND_RA16	(AND_RA8 + 1)
#define AND_RI8		(AND_RA16 + 1)
#define AND_RI16	(AND_RI8 + 1)
#define AND_MR8		(AND_RI16 + 1)
#define AND_MR16	(AND_MR8 + 1)
#define AND_M8I8	(AND_MR16 + 1)
#define AND_M16I8	(AND_M8I8 + 1)
#define AND_MI16	(AND_M16I8 + 1)
#define AND_AR8		(AND_MI16 + 1)
#define AND_AR16	(AND_AR8 + 1)
#define AND_A8I8	(AND_AR16 + 1)
#define AND_A16I8	(AND_A8I8 + 1)
#define AND_AI16	(AND_A16I8 + 1)

#define BIT_RR8		(AND_AI16 + 1)
#define BIT_RR16	(BIT_RR8 + 1)
#define BIT_RM8		(BIT_RR16 + 1)
#define BIT_RM16	(BIT_RM8 + 1)
#define BIT_RA8		(BIT_RM16 + 1)
#define BIT_RA16	(BIT_RA8 + 1)
#define BIT_RI8		(BIT_RA16 + 1)
#define BIT_RI16	(BIT_RI8 + 1)
#define BIT_MR8		(BIT_RI16 + 1)
#define BIT_MR16	(BIT_MR8 + 1)
#define BIT_M8I8	(BIT_MR16 + 1)
#define BIT_M16I8	(BIT_M8I8 + 1)
#define BIT_MI16	(BIT_M16I8 + 1)
#define BIT_AR8		(BIT_MI16 + 1)
#define BIT_AR16	(BIT_AR8 + 1)
#define BIT_A8I8	(BIT_AR16 + 1)
#define BIT_A16I8	(BIT_A8I8 + 1)
#define BIT_AI16	(BIT_A16I8 + 1)

#define BRK		(BIT_AI16 + 1)

#define CALL_R16	(BRK + 1)
#define CALL_M16	(CALL_R16 + 1)
#define CALL_A16	(CALL_M16 + 1)
#define CALL_I16	(CALL_A16 + 1)

#define CLC		(CALL_I16 + 1)

#define CLI		(CLC + 1)

#define CMP_RR8		(CLI + 1)
#define CMP_RR16	(CMP_RR8 + 1)
#define CMP_RM8		(CMP_RR16 + 1)
#define CMP_RM16	(CMP_RM8 + 1)
#define CMP_RA8		(CMP_RM16 + 1)
#define CMP_RA16	(CMP_RA8 + 1)
#define CMP_RI8		(CMP_RA16 + 1)
#define CMP_RI16	(CMP_RI8 + 1)
#define CMP_MR8		(CMP_RI16 + 1)
#define CMP_MR16	(CMP_MR8 + 1)
#define CMP_M8I8	(CMP_MR16 + 1)
#define CMP_M16I8	(CMP_M8I8 + 1)
#define CMP_MI16	(CMP_M16I8 + 1)
#define CMP_AR8		(CMP_MI16 + 1)
#define CMP_AR16	(CMP_AR8 + 1)
#define CMP_A8I8	(CMP_AR16 + 1)
#define CMP_A16I8	(CMP_A8I8 + 1)
#define CMP_AI16	(CMP_A16I8 + 1)

#define DEC_R8		(CMP_AI16 + 1)
#define DEC_R16		(DEC_R8 + 1)
#define DEC_M8		(DEC_R16 + 1)
#define DEC_M16		(DEC_M8 + 1)
#define DEC_A8		(DEC_M16 + 1)
#define DEC_A16		(DEC_A8 + 1)

#define DEX		(DEC_A16 + 1)

#define INC_R8		(DEX + 1)
#define INC_R16		(INC_R8 + 1)
#define INC_M8		(INC_R16 + 1)
#define INC_M16		(INC_M8 + 1)
#define INC_A8		(INC_M16 + 1)
#define INC_A16		(INC_A8 + 1)

#define INX		(INC_A16 + 1)

#define IRET		(INX + 1)

#define JCC		(IRET + 1)

#define JCS		(JCC + 1)

#define JMI		(JCS + 1)

#define JMP_R16		(JMI + 1)
#define JMP_M16		(JMP_R16 + 1)
#define JMP_A16		(JMP_M16 + 1)
#define JMP_I16		(JMP_A16 + 1)

#define JNZ		(JMP_I16 + 1)

#define JPL		(JNZ + 1)

#define JVC		(JPL + 1)

#define JVS		(JVC + 1)

#define JZ		(JVS + 1)

#define MOV_RR8		(JZ + 1)
#define MOV_RR16	(MOV_RR8 + 1)
#define MOV_RM8		(MOV_RR16 + 1)
#define MOV_RM16	(MOV_RM8 + 1)
#define MOV_RA8		(MOV_RM16 + 1)
#define MOV_RA16	(MOV_RA8 + 1)
#define MOV_RI8		(MOV_RA16 + 1)
#define MOV_RI16	(MOV_RI8 + 1)
#define MOV_MR8		(MOV_RI16 + 1)
#define MOV_MR16	(MOV_MR8 + 1)
#define MOV_M8I8	(MOV_MR16 + 1)
#define MOV_M16I8	(MOV_M8I8 + 1)
#define MOV_MI16	(MOV_M16I8 + 1)
#define MOV_AR8		(MOV_MI16 + 1)
#define MOV_AR16	(MOV_AR8 + 1)
#define MOV_A8I8	(MOV_AR16 + 1)
#define MOV_A16I8	(MOV_A8I8 + 1)
#define MOV_AI16	(MOV_A16I8 + 1)

#define NOP		(MOV_AI16 + 1)

#define OR_RR8		(NOP + 1)
#define OR_RR16		(OR_RR8 + 1)
#define OR_RM8		(OR_RR16 + 1)
#define OR_RM16		(OR_RM8 + 1)
#define OR_RA8		(OR_RM16 + 1)
#define OR_RA16		(OR_RA8 + 1)
#define OR_RI8		(OR_RA16 + 1)
#define OR_RI16		(OR_RI8 + 1)
#define OR_MR8		(OR_RI16 + 1)
#define OR_MR16		(OR_MR8 + 1)
#define OR_M8I8		(OR_MR16 + 1)
#define OR_M16I8	(OR_M8I8 + 1)
#define OR_MI16		(OR_M16I8 + 1)
#define OR_AR8		(OR_MI16 + 1)
#define OR_AR16		(OR_AR8 + 1)
#define OR_A8I8		(OR_AR16 + 1)
#define OR_A16I8	(OR_A8I8 + 1)
#define OR_AI16		(OR_A16I8 + 1)

#define POP_R8		(OR_AI16 + 1)
#define POP_R16		(POP_R8 + 1)
#define POP_M8		(POP_R16 + 1)
#define POP_M16		(POP_M8 + 1)
#define POP_A8		(POP_M16 + 1)
#define POP_A16		(POP_A8 + 1)

#define POPA		(POP_A16 + 1)

#define POPF		(POPA + 1)

#define PUSH_R8		(POPF + 1)
#define PUSH_R16	(PUSH_R8 + 1)
#define PUSH_M8		(PUSH_R16 + 1)
#define PUSH_M16	(PUSH_M8 + 1)
#define PUSH_A8		(PUSH_M16 + 1)
#define PUSH_A16	(PUSH_A8 + 1)
#define PUSH_I8		(PUSH_A16 + 1)
#define PUSH_I16	(PUSH_I8 + 1)

#define PUSHA		(PUSH_I16 + 1)

#define PUSHF		(PUSHA + 1)

#define RET		(PUSHF + 1)

#define ROL_R8		(RET + 1)
#define ROL_R16		(ROL_R8 + 1)
#define ROL_M8		(ROL_R16 + 1)
#define ROL_M16		(ROL_M8 + 1)
#define ROL_A8		(ROL_M16 + 1)
#define ROL_A16		(ROL_A8 + 1)

#define ROR_R8		(ROL_A16 + 1)
#define ROR_R16		(ROR_R8 + 1)
#define ROR_M8		(ROR_R16 + 1)
#define ROR_M16		(ROR_M8 + 1)
#define ROR_A8		(ROR_M16 + 1)
#define ROR_A16		(ROR_A8 + 1)

#define SBB_RR8		(ROR_A16 + 1)
#define SBB_RR16	(SBB_RR8 + 1)
#define SBB_RM8		(SBB_RR16 + 1)
#define SBB_RM16	(SBB_RM8 + 1)
#define SBB_RA8		(SBB_RM16 + 1)
#define SBB_RA16	(SBB_RA8 + 1)
#define SBB_RI8		(SBB_RA16 + 1)
#define SBB_RI16	(SBB_RI8 + 1)
#define SBB_MR8		(SBB_RI16 + 1)
#define SBB_MR16	(SBB_MR8 + 1)
#define SBB_M8I8	(SBB_MR16 + 1)
#define SBB_M16I8	(SBB_M8I8 + 1)
#define SBB_MI16	(SBB_M16I8 + 1)
#define SBB_AR8		(SBB_MI16 + 1)
#define SBB_AR16	(SBB_AR8 + 1)
#define SBB_A8I8	(SBB_AR16 + 1)
#define SBB_A16I8	(SBB_A8I8 + 1)
#define SBB_AI16	(SBB_A16I8 + 1)

#define SEC		(SBB_AI16 + 1)

#define SEI		(SEC + 1)

#define SHL_R8		(SEI + 1)
#define SHL_R16		(SHL_R8 + 1)
#define SHL_M8		(SHL_R16 + 1)
#define SHL_M16		(SHL_M8 + 1)
#define SHL_A8		(SHL_M16 + 1)
#define SHL_A16		(SHL_A8 + 1)

#define SHR_R8		(SHL_A16 + 1)
#define SHR_R16		(SHR_R8 + 1)
#define SHR_M8		(SHR_R16 + 1)
#define SHR_M16		(SHR_M8 + 1)
#define SHR_A8		(SHR_M16 + 1)
#define SHR_A16		(SHR_A8 + 1)

#define XOR_RR8		(SHR_A16 + 1)
#define XOR_RR16	(XOR_RR8 + 1)
#define XOR_RM8		(XOR_RR16 + 1)
#define XOR_RM16	(XOR_RM8 + 1)
#define XOR_RA8		(XOR_RM16 + 1)
#define XOR_RA16	(XOR_RA8 + 1)
#define XOR_RI8		(XOR_RA16 + 1)
#define XOR_RI16	(XOR_RI8 + 1)
#define XOR_MR8		(XOR_RI16 + 1)
#define XOR_MR16	(XOR_MR8 + 1)
#define XOR_M8I8	(XOR_MR16 + 1)
#define XOR_M16I8	(XOR_M8I8 + 1)
#define XOR_MI16	(XOR_M16I8 + 1)
#define XOR_AR8		(XOR_MI16 + 1)
#define XOR_AR16	(XOR_AR8 + 1)
#define XOR_A8I8	(XOR_AR16 + 1)
#define XOR_A16I8	(XOR_A8I8 + 1)
#define XOR_AI16	(XOR_A16I8 + 1)

#endif /* __OPCODES_H__ */