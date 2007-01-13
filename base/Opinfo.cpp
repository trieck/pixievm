#include "Common.h"
#include "Modes.h"
#include "Opinfo.h"

namespace { /* anonymous */

const char *mnemonics[] = {
	"adc","and","bit","brk","call","clc",
	"cli","cmp","dec","dex","inc","inx",
	"iret","jcc","jcs","jmi","jmp","jnz",
	"jpl","jvc","jvs","jz","mov","nop",
	"or","pop","popa","popf","push","pusha",
	"pushf","ret","rol","ror","sbb","sec",
	"sei","shl","shr","xor",
};

#define ADC (&mnemonics[0])
#define AND (&mnemonics[1])
#define BIT (&mnemonics[2])
#define BRK (&mnemonics[3])
#define CALL (&mnemonics[4])
#define CLC (&mnemonics[5])
#define CLI (&mnemonics[6])
#define CMP (&mnemonics[7])
#define DEC (&mnemonics[8])
#define DEX (&mnemonics[9])
#define INC (&mnemonics[10])
#define INX (&mnemonics[11])
#define IRET (&mnemonics[12])
#define JCC (&mnemonics[13])
#define JCS (&mnemonics[14])
#define JMI (&mnemonics[15])
#define JMP (&mnemonics[16])
#define JNZ (&mnemonics[17])
#define JPL (&mnemonics[18])
#define JVC (&mnemonics[19])
#define JVS (&mnemonics[20])
#define JZ (&mnemonics[21])
#define MOV (&mnemonics[22])
#define NOP (&mnemonics[23])
#define OR (&mnemonics[24])
#define POP (&mnemonics[25])
#define POPA (&mnemonics[26])
#define POPF (&mnemonics[27])
#define PUSH (&mnemonics[28])
#define PUSHA (&mnemonics[29])
#define PUSHF (&mnemonics[30])
#define RET (&mnemonics[31])
#define ROL (&mnemonics[32])
#define ROR (&mnemonics[33])
#define SBB (&mnemonics[34])
#define SEC (&mnemonics[35])
#define SEI (&mnemonics[36])
#define SHL (&mnemonics[37])
#define SHR (&mnemonics[38])
#define XOR (&mnemonics[39])

Opinfo ADC_RR8 = { ADC, AM_RR8 };
Opinfo ADC_RR16 = { ADC, AM_RR16 };
Opinfo ADC_RM8 = { ADC, AM_RM8 };
Opinfo ADC_RM16 = { ADC, AM_RM16 };
Opinfo ADC_RA8 = { ADC, AM_RA8 };
Opinfo ADC_RA16 = { ADC, AM_RA16 };
Opinfo ADC_RI8 = { ADC, AM_RI8 };
Opinfo ADC_RI16 = { ADC, AM_RI16 };
Opinfo ADC_MR8 = { ADC, AM_MR8 };
Opinfo ADC_MR16 = { ADC, AM_MR16 };
Opinfo ADC_M8I8 = { ADC, AM_M8I8 };
Opinfo ADC_M16I8 = { ADC, AM_M16I8 };
Opinfo ADC_MI16 = { ADC, AM_MI16 };
Opinfo ADC_AR8 = { ADC, AM_AR8 };
Opinfo ADC_AR16 = { ADC, AM_AR16 };
Opinfo ADC_A8I8 = { ADC, AM_A8I8 };
Opinfo ADC_A16I8 = { ADC, AM_A16I8 };
Opinfo ADC_AI16 = { ADC, AM_AI16 };
Opinfo AND_RR8 = { AND, AM_RR8 };
Opinfo AND_RR16 = { AND, AM_RR16 };
Opinfo AND_RM8 = { AND, AM_RM8 };
Opinfo AND_RM16 = { AND, AM_RM16 };
Opinfo AND_RA8 = { AND, AM_RA8 };
Opinfo AND_RA16 = { AND, AM_RA16 };
Opinfo AND_RI8 = { AND, AM_RI8 };
Opinfo AND_RI16 = { AND, AM_RI16 };
Opinfo AND_MR8 = { AND, AM_MR8 };
Opinfo AND_MR16 = { AND, AM_MR16 };
Opinfo AND_M8I8 = { AND, AM_M8I8 };
Opinfo AND_M16I8 = { AND, AM_M16I8 };
Opinfo AND_MI16 = { AND, AM_MI16 };
Opinfo AND_AR8 = { AND, AM_AR8 };
Opinfo AND_AR16 = { AND, AM_AR16 };
Opinfo AND_A8I8 = { AND, AM_A8I8 };
Opinfo AND_A16I8 = { AND, AM_A16I8 };
Opinfo AND_AI16 = { AND, AM_AI16 };
Opinfo BIT_RR8 = { BIT, AM_RR8 };
Opinfo BIT_RR16 = { BIT, AM_RR16 };
Opinfo BIT_RM8 = { BIT, AM_RM8 };
Opinfo BIT_RM16 = { BIT, AM_RM16 };
Opinfo BIT_RA8 = { BIT, AM_RA8 };
Opinfo BIT_RA16 = { BIT, AM_RA16 };
Opinfo BIT_RI8 = { BIT, AM_RI8 };
Opinfo BIT_RI16 = { BIT, AM_RI16 };
Opinfo BIT_MR8 = { BIT, AM_MR8 };
Opinfo BIT_MR16 = { BIT, AM_MR16 };
Opinfo BIT_M8I8 = { BIT, AM_M8I8 };
Opinfo BIT_M16I8 = { BIT, AM_M16I8 };
Opinfo BIT_MI16 = { BIT, AM_MI16 };
Opinfo BIT_AR8 = { BIT, AM_AR8 };
Opinfo BIT_AR16 = { BIT, AM_AR16 };
Opinfo BIT_A8I8 = { BIT, AM_A8I8 };
Opinfo BIT_A16I8 = { BIT, AM_A16I8 };
Opinfo BIT_AI16 = { BIT, AM_AI16 };
Opinfo BRK_IMPLIED = { BRK, AM_IMPLIED };
Opinfo CALL_R16 = { CALL, AM_R16 };
Opinfo CALL_M16 = { CALL, AM_M16 };
Opinfo CALL_A16 = { CALL, AM_A16 };
Opinfo CALL_I16 = { CALL, AM_I16 };
Opinfo CLC_IMPLIED = { CLC, AM_IMPLIED };
Opinfo CLI_IMPLIED = { CLI, AM_IMPLIED };
Opinfo CMP_RR8 = { CMP, AM_RR8 };
Opinfo CMP_RR16 = { CMP, AM_RR16 };
Opinfo CMP_RM8 = { CMP, AM_RM8 };
Opinfo CMP_RM16 = { CMP, AM_RM16 };
Opinfo CMP_RA8 = { CMP, AM_RA8 };
Opinfo CMP_RA16 = { CMP, AM_RA16 };
Opinfo CMP_RI8 = { CMP, AM_RI8 };
Opinfo CMP_RI16 = { CMP, AM_RI16 };
Opinfo CMP_MR8 = { CMP, AM_MR8 };
Opinfo CMP_MR16 = { CMP, AM_MR16 };
Opinfo CMP_M8I8 = { CMP, AM_M8I8 };
Opinfo CMP_M16I8 = { CMP, AM_M16I8 };
Opinfo CMP_MI16 = { CMP, AM_MI16 };
Opinfo CMP_AR8 = { CMP, AM_AR8 };
Opinfo CMP_AR16 = { CMP, AM_AR16 };
Opinfo CMP_A8I8 = { CMP, AM_A8I8 };
Opinfo CMP_A16I8 = { CMP, AM_A16I8 };
Opinfo CMP_AI16 = { CMP, AM_AI16 };
Opinfo DEC_R8 = { DEC, AM_R8 };
Opinfo DEC_R16 = { DEC, AM_R16 };
Opinfo DEC_M8 = { DEC, AM_M8 };
Opinfo DEC_M16 = { DEC, AM_M16 };
Opinfo DEC_A8 = { DEC, AM_A8 };
Opinfo DEC_A16 = { DEC, AM_A16 };
Opinfo DEX_IMPLIED = { DEX, AM_IMPLIED };
Opinfo INC_R8 = { INC, AM_R8 };
Opinfo INC_R16 = { INC, AM_R16 };
Opinfo INC_M8 = { INC, AM_M8 };
Opinfo INC_M16 = { INC, AM_M16 };
Opinfo INC_A8 = { INC, AM_A8 };
Opinfo INC_A16 = { INC, AM_A16 };
Opinfo INX_IMPLIED = { INX, AM_IMPLIED };
Opinfo IRET_IMPLIED = { IRET, AM_IMPLIED };
Opinfo JCC_I8 = { JCC, AM_I8 };
Opinfo JCS_I8 = { JCS, AM_I8 };
Opinfo JMI_I8 = { JMI, AM_I8 };
Opinfo JMP_R16 = { JMP, AM_R16 };
Opinfo JMP_M16 = { JMP, AM_M16 };
Opinfo JMP_A16 = { JMP, AM_A16 };
Opinfo JMP_I16 = { JMP, AM_I16 };
Opinfo JNZ_I8 = { JNZ, AM_I8 };
Opinfo JPL_I8 = { JPL, AM_I8 };
Opinfo JVC_I8 = { JVC, AM_I8 };
Opinfo JVS_I8 = { JVS, AM_I8 };
Opinfo JZ_I8 = { JZ, AM_I8 };
Opinfo MOV_RR8 = { MOV, AM_RR8 };
Opinfo MOV_RR16 = { MOV, AM_RR16 };
Opinfo MOV_RM8 = { MOV, AM_RM8 };
Opinfo MOV_RM16 = { MOV, AM_RM16 };
Opinfo MOV_RA8 = { MOV, AM_RA8 };
Opinfo MOV_RA16 = { MOV, AM_RA16 };
Opinfo MOV_RI8 = { MOV, AM_RI8 };
Opinfo MOV_RI16 = { MOV, AM_RI16 };
Opinfo MOV_MR8 = { MOV, AM_MR8 };
Opinfo MOV_MR16 = { MOV, AM_MR16 };
Opinfo MOV_M8I8 = { MOV, AM_M8I8 };
Opinfo MOV_M16I8 = { MOV, AM_M16I8 };
Opinfo MOV_MI16 = { MOV, AM_MI16 };
Opinfo MOV_AR8 = { MOV, AM_AR8 };
Opinfo MOV_AR16 = { MOV, AM_AR16 };
Opinfo MOV_A8I8 = { MOV, AM_A8I8 };
Opinfo MOV_A16I8 = { MOV, AM_A16I8 };
Opinfo MOV_AI16 = { MOV, AM_AI16 };
Opinfo NOP_IMPLIED = { NOP, AM_IMPLIED };
Opinfo OR_RR8 = { OR, AM_RR8 };
Opinfo OR_RR16 = { OR, AM_RR16 };
Opinfo OR_RM8 = { OR, AM_RM8 };
Opinfo OR_RM16 = { OR, AM_RM16 };
Opinfo OR_RA8 = { OR, AM_RA8 };
Opinfo OR_RA16 = { OR, AM_RA16 };
Opinfo OR_RI8 = { OR, AM_RI8 };
Opinfo OR_RI16 = { OR, AM_RI16 };
Opinfo OR_MR8 = { OR, AM_MR8 };
Opinfo OR_MR16 = { OR, AM_MR16 };
Opinfo OR_M8I8 = { OR, AM_M8I8 };
Opinfo OR_M16I8 = { OR, AM_M16I8 };
Opinfo OR_MI16 = { OR, AM_MI16 };
Opinfo OR_AR8 = { OR, AM_AR8 };
Opinfo OR_AR16 = { OR, AM_AR16 };
Opinfo OR_A8I8 = { OR, AM_A8I8 };
Opinfo OR_A16I8 = { OR, AM_A16I8 };
Opinfo OR_AI16 = { OR, AM_AI16 };
Opinfo POP_R8 = { POP, AM_R8 };
Opinfo POP_R16 = { POP, AM_R16 };
Opinfo POP_M8 = { POP, AM_M8 };
Opinfo POP_M16 = { POP, AM_M16 };
Opinfo POP_A8 = { POP, AM_A8 };
Opinfo POP_A16 = { POP, AM_A16 };
Opinfo POPA_IMPLIED = { POPA, AM_IMPLIED };
Opinfo POPF_IMPLIED = { POPF, AM_IMPLIED };
Opinfo PUSH_R8 = { PUSH, AM_R8 };
Opinfo PUSH_R16 = { PUSH, AM_R16 };
Opinfo PUSH_M8 = { PUSH, AM_M8 };
Opinfo PUSH_M16 = { PUSH, AM_M16 };
Opinfo PUSH_A8 = { PUSH, AM_A8 };
Opinfo PUSH_A16 = { PUSH, AM_A16 };
Opinfo PUSH_I8 = { PUSH, AM_I8 };
Opinfo PUSH_I16 = { PUSH, AM_I16 };
Opinfo PUSHA_IMPLIED = { PUSHA, AM_IMPLIED };
Opinfo PUSHF_IMPLIED = { PUSHF, AM_IMPLIED };
Opinfo RET_IMPLIED = { RET, AM_IMPLIED };
Opinfo ROL_R8 = { ROL, AM_R8 };
Opinfo ROL_R16 = { ROL, AM_R16 };
Opinfo ROL_M8 = { ROL, AM_M8 };
Opinfo ROL_M16 = { ROL, AM_M16 };
Opinfo ROL_A8 = { ROL, AM_A8 };
Opinfo ROL_A16 = { ROL, AM_A16 };
Opinfo ROR_R8 = { ROR, AM_R8 };
Opinfo ROR_R16 = { ROR, AM_R16 };
Opinfo ROR_M8 = { ROR, AM_M8 };
Opinfo ROR_M16 = { ROR, AM_M16 };
Opinfo ROR_A8 = { ROR, AM_A8 };
Opinfo ROR_A16 = { ROR, AM_A16 };
Opinfo SBB_RR8 = { SBB, AM_RR8 };
Opinfo SBB_RR16 = { SBB, AM_RR16 };
Opinfo SBB_RM8 = { SBB, AM_RM8 };
Opinfo SBB_RM16 = { SBB, AM_RM16 };
Opinfo SBB_RA8 = { SBB, AM_RA8 };
Opinfo SBB_RA16 = { SBB, AM_RA16 };
Opinfo SBB_RI8 = { SBB, AM_RI8 };
Opinfo SBB_RI16 = { SBB, AM_RI16 };
Opinfo SBB_MR8 = { SBB, AM_MR8 };
Opinfo SBB_MR16 = { SBB, AM_MR16 };
Opinfo SBB_M8I8 = { SBB, AM_M8I8 };
Opinfo SBB_M16I8 = { SBB, AM_M16I8 };
Opinfo SBB_MI16 = { SBB, AM_MI16 };
Opinfo SBB_AR8 = { SBB, AM_AR8 };
Opinfo SBB_AR16 = { SBB, AM_AR16 };
Opinfo SBB_A8I8 = { SBB, AM_A8I8 };
Opinfo SBB_A16I8 = { SBB, AM_A16I8 };
Opinfo SBB_AI16 = { SBB, AM_AI16 };
Opinfo SEC_IMPLIED = { SEC, AM_IMPLIED };
Opinfo SEI_IMPLIED = { SEI, AM_IMPLIED };
Opinfo SHL_R8 = { SHL, AM_R8 };
Opinfo SHL_R16 = { SHL, AM_R16 };
Opinfo SHL_M8 = { SHL, AM_M8 };
Opinfo SHL_M16 = { SHL, AM_M16 };
Opinfo SHL_A8 = { SHL, AM_A8 };
Opinfo SHL_A16 = { SHL, AM_A16 };
Opinfo SHR_R8 = { SHR, AM_R8 };
Opinfo SHR_R16 = { SHR, AM_R16 };
Opinfo SHR_M8 = { SHR, AM_M8 };
Opinfo SHR_M16 = { SHR, AM_M16 };
Opinfo SHR_A8 = { SHR, AM_A8 };
Opinfo SHR_A16 = { SHR, AM_A16 };
Opinfo XOR_RR8 = { XOR, AM_RR8 };
Opinfo XOR_RR16 = { XOR, AM_RR16 };
Opinfo XOR_RM8 = { XOR, AM_RM8 };
Opinfo XOR_RM16 = { XOR, AM_RM16 };
Opinfo XOR_RA8 = { XOR, AM_RA8 };
Opinfo XOR_RA16 = { XOR, AM_RA16 };
Opinfo XOR_RI8 = { XOR, AM_RI8 };
Opinfo XOR_RI16 = { XOR, AM_RI16 };
Opinfo XOR_MR8 = { XOR, AM_MR8 };
Opinfo XOR_MR16 = { XOR, AM_MR16 };
Opinfo XOR_M8I8 = { XOR, AM_M8I8 };
Opinfo XOR_M16I8 = { XOR, AM_M16I8 };
Opinfo XOR_MI16 = { XOR, AM_MI16 };
Opinfo XOR_AR8 = { XOR, AM_AR8 };
Opinfo XOR_AR16 = { XOR, AM_AR16 };
Opinfo XOR_A8I8 = { XOR, AM_A8I8 };
Opinfo XOR_A16I8 = { XOR, AM_A16I8 };
Opinfo XOR_AI16 = { XOR, AM_AI16 };

} /* anonymous */

LPOPINFO opinfo[256] = {
	&ADC_RR8,	 /*0x00 */
	&ADC_RR16,	 /*0x01 */
	&ADC_RM8,	 /*0x02 */
	&ADC_RM16,	 /*0x03 */
	&ADC_RA8,	 /*0x04 */
	&ADC_RA16,	 /*0x05 */
	&ADC_RI8,	 /*0x06 */
	&ADC_RI16,	 /*0x07 */
	&ADC_MR8,	 /*0x08 */
	&ADC_MR16,	 /*0x09 */
	&ADC_M8I8,	 /*0x0A */
	&ADC_M16I8,	 /*0x0B */
	&ADC_MI16,	 /*0x0C */
	&ADC_AR8,	 /*0x0D */
	&ADC_AR16,	 /*0x0E */
	&ADC_A8I8,	 /*0x0F */
	&ADC_A16I8,	 /*0x10 */
	&ADC_AI16,	 /*0x11 */
	&AND_RR8,	 /*0x12 */
	&AND_RR16,	 /*0x13 */
	&AND_RM8,	 /*0x14 */
	&AND_RM16,	 /*0x15 */
	&AND_RA8,	 /*0x16 */
	&AND_RA16,	 /*0x17 */
	&AND_RI8,	 /*0x18 */
	&AND_RI16,	 /*0x19 */
	&AND_MR8,	 /*0x1A */
	&AND_MR16,	 /*0x1B */
	&AND_M8I8,	 /*0x1C */
	&AND_M16I8,	 /*0x1D */
	&AND_MI16,	 /*0x1E */
	&AND_AR8,	 /*0x1F */
	&AND_AR16,	 /*0x20 */
	&AND_A8I8,	 /*0x21 */
	&AND_A16I8,	 /*0x22 */
	&AND_AI16,	 /*0x23 */
	&BIT_RR8,	 /*0x24 */
	&BIT_RR16,	 /*0x25 */
	&BIT_RM8,	 /*0x26 */
	&BIT_RM16,	 /*0x27 */
	&BIT_RA8,	 /*0x28 */
	&BIT_RA16,	 /*0x29 */
	&BIT_RI8,	 /*0x2A */
	&BIT_RI16,	 /*0x2B */
	&BIT_MR8,	 /*0x2C */
	&BIT_MR16,	 /*0x2D */
	&BIT_M8I8,	 /*0x2E */
	&BIT_M16I8,	 /*0x2F */
	&BIT_MI16,	 /*0x30 */
	&BIT_AR8,	 /*0x31 */
	&BIT_AR16,	 /*0x32 */
	&BIT_A8I8,	 /*0x33 */
	&BIT_A16I8,	 /*0x34 */
	&BIT_AI16,	 /*0x35 */
	&BRK_IMPLIED,	 /*0x36 */
	&CALL_R16,	 /*0x37 */
	&CALL_M16,	 /*0x38 */
	&CALL_A16,	 /*0x39 */
	&CALL_I16,	 /*0x3A */
	&CLC_IMPLIED,	 /*0x3B */
	&CLI_IMPLIED,	 /*0x3C */
	&CMP_RR8,	 /*0x3D */
	&CMP_RR16,	 /*0x3E */
	&CMP_RM8,	 /*0x3F */
	&CMP_RM16,	 /*0x40 */
	&CMP_RA8,	 /*0x41 */
	&CMP_RA16,	 /*0x42 */
	&CMP_RI8,	 /*0x43 */
	&CMP_RI16,	 /*0x44 */
	&CMP_MR8,	 /*0x45 */
	&CMP_MR16,	 /*0x46 */
	&CMP_M8I8,	 /*0x47 */
	&CMP_M16I8,	 /*0x48 */
	&CMP_MI16,	 /*0x49 */
	&CMP_AR8,	 /*0x4A */
	&CMP_AR16,	 /*0x4B */
	&CMP_A8I8,	 /*0x4C */
	&CMP_A16I8,	 /*0x4D */
	&CMP_AI16,	 /*0x4E */
	&DEC_R8,	 /*0x4F */
	&DEC_R16,	 /*0x50 */
	&DEC_M8,	 /*0x51 */
	&DEC_M16,	 /*0x52 */
	&DEC_A8,	 /*0x53 */
	&DEC_A16,	 /*0x54 */
	&DEX_IMPLIED,	 /*0x55 */
	&INC_R8,	 /*0x56 */
	&INC_R16,	 /*0x57 */
	&INC_M8,	 /*0x58 */
	&INC_M16,	 /*0x59 */
	&INC_A8,	 /*0x5A */
	&INC_A16,	 /*0x5B */
	&INX_IMPLIED,	 /*0x5C */
	&IRET_IMPLIED,	 /*0x5D */
	&JCC_I8,	 /*0x5E */
	&JCS_I8,	 /*0x5F */
	&JMI_I8,	 /*0x60 */
	&JMP_R16,	 /*0x61 */
	&JMP_M16,	 /*0x62 */
	&JMP_A16,	 /*0x63 */
	&JMP_I16,	 /*0x64 */
	&JNZ_I8,	 /*0x65 */
	&JPL_I8,	 /*0x66 */
	&JVC_I8,	 /*0x67 */
	&JVS_I8,	 /*0x68 */
	&JZ_I8,	 /*0x69 */
	&MOV_RR8,	 /*0x6A */
	&MOV_RR16,	 /*0x6B */
	&MOV_RM8,	 /*0x6C */
	&MOV_RM16,	 /*0x6D */
	&MOV_RA8,	 /*0x6E */
	&MOV_RA16,	 /*0x6F */
	&MOV_RI8,	 /*0x70 */
	&MOV_RI16,	 /*0x71 */
	&MOV_MR8,	 /*0x72 */
	&MOV_MR16,	 /*0x73 */
	&MOV_M8I8,	 /*0x74 */
	&MOV_M16I8,	 /*0x75 */
	&MOV_MI16,	 /*0x76 */
	&MOV_AR8,	 /*0x77 */
	&MOV_AR16,	 /*0x78 */
	&MOV_A8I8,	 /*0x79 */
	&MOV_A16I8,	 /*0x7A */
	&MOV_AI16,	 /*0x7B */
	&NOP_IMPLIED,	 /*0x7C */
	&OR_RR8,	 /*0x7D */
	&OR_RR16,	 /*0x7E */
	&OR_RM8,	 /*0x7F */
	&OR_RM16,	 /*0x80 */
	&OR_RA8,	 /*0x81 */
	&OR_RA16,	 /*0x82 */
	&OR_RI8,	 /*0x83 */
	&OR_RI16,	 /*0x84 */
	&OR_MR8,	 /*0x85 */
	&OR_MR16,	 /*0x86 */
	&OR_M8I8,	 /*0x87 */
	&OR_M16I8,	 /*0x88 */
	&OR_MI16,	 /*0x89 */
	&OR_AR8,	 /*0x8A */
	&OR_AR16,	 /*0x8B */
	&OR_A8I8,	 /*0x8C */
	&OR_A16I8,	 /*0x8D */
	&OR_AI16,	 /*0x8E */
	&POP_R8,	 /*0x8F */
	&POP_R16,	 /*0x90 */
	&POP_M8,	 /*0x91 */
	&POP_M16,	 /*0x92 */
	&POP_A8,	 /*0x93 */
	&POP_A16,	 /*0x94 */
	&POPA_IMPLIED,	 /*0x95 */
	&POPF_IMPLIED,	 /*0x96 */
	&PUSH_R8,	 /*0x97 */
	&PUSH_R16,	 /*0x98 */
	&PUSH_M8,	 /*0x99 */
	&PUSH_M16,	 /*0x9A */
	&PUSH_A8,	 /*0x9B */
	&PUSH_A16,	 /*0x9C */
	&PUSH_I8,	 /*0x9D */
	&PUSH_I16,	 /*0x9E */
	&PUSHA_IMPLIED,	 /*0x9F */
	&PUSHF_IMPLIED,	 /*0xA0 */
	&RET_IMPLIED,	 /*0xA1 */
	&ROL_R8,	 /*0xA2 */
	&ROL_R16,	 /*0xA3 */
	&ROL_M8,	 /*0xA4 */
	&ROL_M16,	 /*0xA5 */
	&ROL_A8,	 /*0xA6 */
	&ROL_A16,	 /*0xA7 */
	&ROR_R8,	 /*0xA8 */
	&ROR_R16,	 /*0xA9 */
	&ROR_M8,	 /*0xAA */
	&ROR_M16,	 /*0xAB */
	&ROR_A8,	 /*0xAC */
	&ROR_A16,	 /*0xAD */
	&SBB_RR8,	 /*0xAE */
	&SBB_RR16,	 /*0xAF */
	&SBB_RM8,	 /*0xB0 */
	&SBB_RM16,	 /*0xB1 */
	&SBB_RA8,	 /*0xB2 */
	&SBB_RA16,	 /*0xB3 */
	&SBB_RI8,	 /*0xB4 */
	&SBB_RI16,	 /*0xB5 */
	&SBB_MR8,	 /*0xB6 */
	&SBB_MR16,	 /*0xB7 */
	&SBB_M8I8,	 /*0xB8 */
	&SBB_M16I8,	 /*0xB9 */
	&SBB_MI16,	 /*0xBA */
	&SBB_AR8,	 /*0xBB */
	&SBB_AR16,	 /*0xBC */
	&SBB_A8I8,	 /*0xBD */
	&SBB_A16I8,	 /*0xBE */
	&SBB_AI16,	 /*0xBF */
	&SEC_IMPLIED,	 /*0xC0 */
	&SEI_IMPLIED,	 /*0xC1 */
	&SHL_R8,	 /*0xC2 */
	&SHL_R16,	 /*0xC3 */
	&SHL_M8,	 /*0xC4 */
	&SHL_M16,	 /*0xC5 */
	&SHL_A8,	 /*0xC6 */
	&SHL_A16,	 /*0xC7 */
	&SHR_R8,	 /*0xC8 */
	&SHR_R16,	 /*0xC9 */
	&SHR_M8,	 /*0xCA */
	&SHR_M16,	 /*0xCB */
	&SHR_A8,	 /*0xCC */
	&SHR_A16,	 /*0xCD */
	&XOR_RR8,	 /*0xCE */
	&XOR_RR16,	 /*0xCF */
	&XOR_RM8,	 /*0xD0 */
	&XOR_RM16,	 /*0xD1 */
	&XOR_RA8,	 /*0xD2 */
	&XOR_RA16,	 /*0xD3 */
	&XOR_RI8,	 /*0xD4 */
	&XOR_RI16,	 /*0xD5 */
	&XOR_MR8,	 /*0xD6 */
	&XOR_MR16,	 /*0xD7 */
	&XOR_M8I8,	 /*0xD8 */
	&XOR_M16I8,	 /*0xD9 */
	&XOR_MI16,	 /*0xDA */
	&XOR_AR8,	 /*0xDB */
	&XOR_AR16,	 /*0xDC */
	&XOR_A8I8,	 /*0xDD */
	&XOR_A16I8,	 /*0xDE */
	&XOR_AI16,	 /*0xDF */
	NULL,	 /*0xE0 */
	NULL,	 /*0xE1 */
	NULL,	 /*0xE2 */
	NULL,	 /*0xE3 */
	NULL,	 /*0xE4 */
	NULL,	 /*0xE5 */
	NULL,	 /*0xE6 */
	NULL,	 /*0xE7 */
	NULL,	 /*0xE8 */
	NULL,	 /*0xE9 */
	NULL,	 /*0xEA */
	NULL,	 /*0xEB */
	NULL,	 /*0xEC */
	NULL,	 /*0xED */
	NULL,	 /*0xEE */
	NULL,	 /*0xEF */
	NULL,	 /*0xF0 */
	NULL,	 /*0xF1 */
	NULL,	 /*0xF2 */
	NULL,	 /*0xF3 */
	NULL,	 /*0xF4 */
	NULL,	 /*0xF5 */
	NULL,	 /*0xF6 */
	NULL,	 /*0xF7 */
	NULL,	 /*0xF8 */
	NULL,	 /*0xF9 */
	NULL,	 /*0xFA */
	NULL,	 /*0xFB */
	NULL,	 /*0xFC */
	NULL,	 /*0xFD */
	NULL,	 /*0xFE */
	NULL,	 /*0xFF */
};
