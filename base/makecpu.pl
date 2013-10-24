#!/bin/perl -w 

# generate pixievm CPU source and header files

use strict qw(vars);
use warnings;

use PixieVM;

my $now = localtime;
my $autogen = "/*\n * this file was automatically generated by\n * $0 on\n * $now.\n */\n\n";

# generate source files
write_modes();			  # generate addressing modes
write_opcodes();		  # generate opcodes
write_instr_h();		  # generate instructions.h
write_instr_cpp();	  # generate instructions.cpp
write_opinfo_h();		  # generate opinfo.h
write_opinfo_cpp();	  # generate opinfo.cpp
write_fetchex_cpp();  # generate fetchex.cpp

# generate modes.h
#
sub write_modes {
	my ($m, $t);
	my $last = 0;

	open FH, ">Modes.h" || die "unable to open file Modes.h";
	print FH $autogen;
	print FH "#ifndef __MODES_H__\n";
	print FH "#define __MODES_H__\n\n";

	foreach $m (@PixieVM::modes) {
		$t = "AM_$m";
		print FH "#define $t\t";
		print FH "\t" if (length $t < 8);
		print FH "(";
		print FH $last ? "$last + 1" : "0";
		print FH ")\n";
		$last = $t;
	}
	print FH "\n#define NMODES\t\t($last + 1)	/* number of addressing modes */\n";
	print FH "\n#endif /* __MODES_H__ */\n";

	close FH;
}

# generate opcodes.h
#
sub write_opcodes {
	my $n = 0; my $last = 0;
	my ($key, $val, $cnt);

	open FH, ">Opcodes.h" || die "unable to open file Opcodes.h";
	print FH $autogen;
	print FH "#ifndef __OPCODES_H__\n";
	print FH "#define __OPCODES_H__\n\n";

	foreach $key (sort keys %PixieVM::instr) {
		$cnt = scalar @{$PixieVM::instr{$key}};
		foreach $val (@{$PixieVM::instr{$key}}) {
			my $op = $cnt == 1 ? "$key" : "$key\_$PixieVM::modes[$val]";
			print FH "#define $op\t";
			print FH "\t" if (length $op < 8);
			print FH "(";
			print FH $last ? "$last + 1" : "0";
			print FH ")\n";
			$last = $op;
		}
		print FH "\n";
	}

	print FH "#endif /* __OPCODES_H__ */\n";
	close FH;
}

# generate instructions.h
#
sub write_instr_h {

	open FH, ">Instructions.h" || die "unable to open file Instructions.h";
	print FH $autogen;
	print FH "#ifndef __INSTRUCTIONS_H__\n";
	print FH "#define __INSTRUCTIONS_H__\n\n";

	print FH "typedef const byte *Instr[NMODES];\n\n";

	my $key;
	foreach $key (sort keys %PixieVM::instr) {
		print FH "extern const Instr INS_$key;\n";
	}

	print FH "\n#endif /* __INSTRUCTIONS_H__ */\n";
	close FH;
}

# generate instructions.cpp
#
sub write_instr_cpp {

	open FH, ">Instructions.cpp" || die "unable to open file Instructions.cpp";

	my $n = 0;
	my ($key, $val, $cnt, $m, $i);

	print FH $autogen;
	print FH "#include \"Common.h\"\n";
	print FH "#include \"Opcodes.h\"\n";
	print FH "#include \"Modes.h\"\n";
	print FH "#include \"Instructions.h\"\n";

	print FH "\nconst byte opcodes[] = {";
	foreach $key (sort keys %PixieVM::instr) {
		$cnt = scalar @{$PixieVM::instr{$key}};
		foreach $val (@{$PixieVM::instr{$key}}) {
			if (($n++ % 6) == 0) { print FH "\n\t"; }
			my $op = $cnt == 1 ? "$key" : "$key\_$PixieVM::modes[$val]";
			print FH "$op, ";
		}
	}
	print FH "\n};\n";

	$n = 0;
	foreach $key (sort keys %PixieVM::instr) {
		print FH "\nconst Instr INS_$key = {\n";
		for ($m = 0; $m < scalar @PixieVM::modes; $m++) {
			my @vals = @{$PixieVM::instr{$key}};
			for ($i = 0; $i < scalar @vals; $i++) {
				if ($vals[$i] == $m) {
					print FH "\t&opcodes[";
					print FH sprintf("0x%.2X", $n++);
					print FH "],\t/* $PixieVM::modes[$m] */\n";			
					last;
				}
			}
			if ($i == scalar @vals) {	# no match
				print FH "\tNULL,\t\t\t/* $PixieVM::modes[$m] */\n";
			}
		}
		print FH "};\n";
	}

	close FH;
}

# generate opinfo.h
#
sub write_opinfo_h {
	open FH, ">Opinfo.h" || die "unable to open file Opinfo.h";

	print FH $autogen;
	print FH "#ifndef __OPINFO_H__\n";
	print FH "#define __OPINFO_H__\n\n";

	print FH "/* opcode info structure */\n";
	print FH "typedef struct Opinfo {\n";
	print FH "\tconst char *mnemonic;\t/* pointer to mnemonic */\n";
	print FH "\tbyte mode;\t\t\t/* addressing mode */\n";
	print FH "} *LPOPINFO;\n\n";

	printf FH "extern LPOPINFO opinfo[";
	print FH 1 << 8;
	print FH "];\n";

	print FH "\n#endif /* __OPINFO_H__ */\n";

	close FH;
}

# generate opinfo.cpp
#
sub write_opinfo_cpp {
	open FH, ">Opinfo.cpp" || die "unable to open file Opinfo.cpp";

	print FH $autogen;
	print FH "#include \"Common.h\"\n";
	print FH "#include \"Modes.h\"\n";
	print FH "#include \"Opinfo.h\"\n\n";

	print FH "namespace { /* anonymous */\n\nconst char *mnemonics[] = {";
	my ($key, $val, $m, $n);
	foreach $key (sort keys %PixieVM::instr) {
		if (($n++ % 6) == 0) { print FH "\n\t"; }
		print FH "\"";
		print FH lc $key;
		print FH "\"";
		if ($n < scalar keys %PixieVM::instr) { print FH ", "; }
	}
	print FH "\n};\n\n";

	$n = 0;
	foreach $key (sort keys %PixieVM::instr) {
		print FH "#define $key (mnemonics[$n])\n";
		$n++;
	}

	print FH "\n";

	foreach $key (sort keys %PixieVM::instr) {
		foreach $val (@{$PixieVM::instr{$key}}) {
			print FH "Opinfo $key\_$PixieVM::modes[$val]";
			print FH " = { $key, AM_$PixieVM::modes[$val] };\n";
		}
	}

	print FH "\n} /* anonymous */\n\n";

	print FH "LPOPINFO opinfo[";
	print FH 1 << 8;
	print FH "] = {\n";

	$n = 0;
	foreach $key (sort keys %PixieVM::instr) {
		foreach $val (@{$PixieVM::instr{$key}}) {
			print FH "\t&$key\_$PixieVM::modes[$val],";
			print FH "\t /*";
			print FH sprintf("0x%.2X", $n++);
			print FH " */\n";
		}
	}

	for ( ; $n < (1 << 8);$n++) {
		print FH "\tNULL,";
		print FH "\t /*";
		print FH sprintf("0x%.2X", $n);
		print FH " */\n";
	}

	print FH "};\n";

	close FH;
}

# generate fetch / execute switch
#
sub write_fetchex_cpp {
	open FH, ">FetchEx.cpp" || die "unable to open file FetchEx.cpp";
	print FH $autogen;

	my ($key, $val, $cnt);
	foreach $key (sort keys %PixieVM::instr) {
		$cnt = scalar @{$PixieVM::instr{$key}};
		foreach $val (@{$PixieVM::instr{$key}}) {
			my $op = $cnt == 1 ? "$key" : "$key\_$PixieVM::modes[$val]";
			print FH "case $op:\n";
			print FH "\tDO_$op();\n";
			print FH "\tbreak;\n";
		}
	}

	print FH "default:\n";
	print FH "\tbreak;\n";
	close FH;
}

