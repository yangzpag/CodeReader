eval '(exit $?0)' && eval 'exec perl -pi -S $0 ${1+"$@"}'
    & eval 'exec perl -pi -S $0 $argv:q'
    if 0;

# ecdata_patch.pl,v 1.1 2000/05/24 16:45:19 cdgill Exp
#
# This script patches the event data definition by removing the IDL typedef,
# for java idl compilers that do not handle typedefs correctly.  Repeated
# applications of this patch to an already patched file should be idempotent.
# This script reads from stdin and writes to stdout.

while (<>) {
s%^(\s*)(typedef RtecEventData EventData;)%$1// $2%;
s%^(\s*)(EventData data;)%$1Rtec$2%;
print;
}
