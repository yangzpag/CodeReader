eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# run_test.pl,v 1.3 2001/07/29 23:27:14 yamuna Exp
# -*- perl -*-

use lib '../../../../../bin';
use PerlACE::Run_Test;

# amount of delay between running the servers

$sleeptime = 6;
$status = 0;

$nsior = PerlACE::LocalFile ("ns.ior");
$testfile = PerlACE::LocalFile ("test");
$makefile = PerlACE::LocalFile ("Makefile");

unlink $nsior;

$NS = new PerlACE::Process ("../../../Naming_Service/Naming_Service", "-o $nsior");
$SV = new PerlACE::Process ("server", "-ORBInitRef NameService=file://$nsior -f $testfile");
$CL = new PerlACE::Process ("ftp", "-ORBInitRef NameService=file://$nsior -f $makefile");

print STDERR "Starting Naming Service\n";

$NS->Spawn ();

if (PerlACE::waitforfile_timed ($nsior, 5) == -1) {
    print STDERR "ERROR: cannot find naming service IOR file\n";
    $NS->Kill (); 
    exit 1;
}

print STDERR "Starting Server\n";

$SV->Spawn ();

sleep $sleeptime;

print STDERR "Starting Client\n";

$client = $CL->SpawnWaitKill (200);

if ($client != 0) {
    print STDERR "ERROR: client returned $client\n";
    $status = 1;
}

$server = $SV->TerminateWaitKill (5);

if ($server != 0) {
    print STDERR "ERROR: server returned $server\n";
    $status = 1;
}

$nserver = $NS->TerminateWaitKill (5);

if ($nserver != 0) {
    print STDERR "ERROR: Naming Service returned $nserver\n";
    $status = 1;
}

unlink $nsior;
unlink $testfile;

exit $status;
