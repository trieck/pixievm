#!/bin/perl -w 

# generate pixievm tests

use strict qw(vars);
use warnings;
use feature qw(switch);

use PixieVM;

write_tests();

sub hash_val {
	my %hash = %{ $_[0] };
	my $key = $_[1];
	if (exists($hash{$key})) {
		return $hash{$key};
	}

	return 0;
}

sub make_regs {
	my %h = %{ $_[0] };

	my $a = hash_val(\%h, 'A');
	my $b = hash_val(\%h, 'B');
	my $c = hash_val(\%h, 'C');
	my $d = hash_val(\%h, 'D');
	my $x = hash_val(\%h, 'X');
	my $s = hash_val(\%h, 'S');
	my $i = hash_val(\%h, 'I');
	my $f = hash_val(\%h, 'F');

	return sprintf("%04x%04x%04x%04x%04x%04x%04x%04x", 
		$a, $b, $c, $d, $x, $s, $i, $f);
}

sub write_instr {
	my ($instr, $flags) = @_[0..1];
	print "$instr\t". make_regs($flags) . "\n";
}

sub write_rr8 {
	my $mnem = shift;

	write_instr("$mnem al, al", { I => 2 });

	print "$mnem al, bl\n";
	print "$mnem al, cl\n";
	print "$mnem al, dl\n";

	print "$mnem al, ah\n";
	print "$mnem al, bh\n";
	print "$mnem al, ch\n";
	print "$mnem al, dh\n";

	print "$mnem ah, al\n";
	print "$mnem ah, bl\n";
	print "$mnem ah, cl\n";
	print "$mnem ah, dl\n";

	print "$mnem ah, ah\n";
	print "$mnem ah, bh\n";
	print "$mnem ah, ch\n";
	print "$mnem ah, dh\n";

	print "$mnem bl, al\n";
	print "$mnem bl, bl\n";
	print "$mnem bl, cl\n";
	print "$mnem bl, dl\n";

	print "$mnem bl, ah\n";
	print "$mnem bl, bh\n";
	print "$mnem bl, ch\n";
	print "$mnem bl, dh\n";

	print "$mnem bh, al\n";
	print "$mnem bh, bl\n";
	print "$mnem bh, cl\n";
	print "$mnem bh, dl\n";

	print "$mnem bh, ah\n";
	print "$mnem bh, bh\n";
	print "$mnem bh, ch\n";
	print "$mnem bh, dh\n";
}

sub write_rr16 {
	my $mnem = shift;
	print "$mnem a, a\n";
	print "$mnem a, b\n";
	print "$mnem a, c\n";
	print "$mnem a, d\n";

	print "$mnem b, a\n";
	print "$mnem b, b\n";
	print "$mnem b, c\n";
	print "$mnem b, d\n";

	print "$mnem c, a\n";
	print "$mnem c, b\n";
	print "$mnem c, c\n";
	print "$mnem c, d\n";

	print "$mnem d, a\n";
	print "$mnem d, b\n";
	print "$mnem d, c\n";
	print "$mnem d, d\n";
}

sub write_rm8 {
	my $mnem = shift;
	print "$mnem al, [a+x]\n";
	print "$mnem al, [b+x]\n";
	print "$mnem al, [c+x]\n";
	print "$mnem al, [d+x]\n";

	print "$mnem ah, [a+x]\n";
	print "$mnem ah, [b+x]\n";
	print "$mnem ah, [c+x]\n";
	print "$mnem ah, [d+x]\n";

	print "$mnem bl, [a+x]\n";
	print "$mnem bl, [b+x]\n";
	print "$mnem bl, [c+x]\n";
	print "$mnem bl, [d+x]\n";

	print "$mnem bh, [a+x]\n";
	print "$mnem bh, [b+x]\n";
	print "$mnem bh, [c+x]\n";
	print "$mnem bh, [d+x]\n";

	print "$mnem cl, [a+x]\n";
	print "$mnem cl, [b+x]\n";
	print "$mnem cl, [c+x]\n";
	print "$mnem cl, [d+x]\n";

	print "$mnem ch, [a+x]\n";
	print "$mnem ch, [b+x]\n";
	print "$mnem ch, [c+x]\n";
	print "$mnem ch, [d+x]\n";

	print "$mnem dl, [a+x]\n";
	print "$mnem dl, [b+x]\n";
	print "$mnem dl, [c+x]\n";
	print "$mnem dl, [d+x]\n";

	print "$mnem dh, [a+x]\n";
	print "$mnem dh, [b+x]\n";
	print "$mnem dh, [c+x]\n";
	print "$mnem dh, [d+x]\n";
}

sub write_test {
	my ($mnem, $mode) = @_[0..1];

	given($mode) {
		when(RR8) 	{ write_rr8 $mnem; }
		when(RR16) 	{ write_rr16 $mnem; }
		when(RM8) 	{ write_rm8 $mnem; }
		default 		{ exit 1; }
	}

}

sub write_tests {
	my ($key, $val, $cnt);

	foreach $key (sort keys %PixieVM::instr) {
		$cnt = scalar @{$PixieVM::instr{$key}};
		foreach $val (@{$PixieVM::instr{$key}}) {
			write_test lc $key, $PixieVM::modes[$val];
		}
	}
}


