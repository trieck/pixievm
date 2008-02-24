#ifndef __INSTRUCTIONS_H__
#define __INSTRUCTIONS_H__

typedef const byte *Instr[NMODES];

extern const Instr INS_ADC;
extern const Instr INS_AND;
extern const Instr INS_BIT;
extern const Instr INS_BRK;
extern const Instr INS_CALL;
extern const Instr INS_CLC;
extern const Instr INS_CLI;
extern const Instr INS_CMP;
extern const Instr INS_DEC;
extern const Instr INS_DEX;
extern const Instr INS_INC;
extern const Instr INS_INX;
extern const Instr INS_IRET;
extern const Instr INS_JCC;
extern const Instr INS_JCS;
extern const Instr INS_JMI;
extern const Instr INS_JMP;
extern const Instr INS_JNZ;
extern const Instr INS_JPL;
extern const Instr INS_JVC;
extern const Instr INS_JVS;
extern const Instr INS_JZ;
extern const Instr INS_MOV;
extern const Instr INS_NOP;
extern const Instr INS_OR;
extern const Instr INS_POP;
extern const Instr INS_POPA;
extern const Instr INS_POPF;
extern const Instr INS_PUSH;
extern const Instr INS_PUSHA;
extern const Instr INS_PUSHF;
extern const Instr INS_RET;
extern const Instr INS_ROL;
extern const Instr INS_ROR;
extern const Instr INS_SBB;
extern const Instr INS_SEC;
extern const Instr INS_SEI;
extern const Instr INS_SHL;
extern const Instr INS_SHR;
extern const Instr INS_XOR;

#endif /* __INSTRUCTIONS_H__ */
