eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# run_test.pl,v 1.1 2001/03/23 03:38:41 irfan Exp
# -*- perl -*-

use lib '../../../../bin';
use PerlACE::Run_Test;

$T = new PerlACE::Process ("Object_Reactivation");

$test = $T->SpawnWaitKill (60);

if ($test != 0) {
    print STDERR "ERROR: test returned $test\n";
    exit 1;
}

exit 0;
