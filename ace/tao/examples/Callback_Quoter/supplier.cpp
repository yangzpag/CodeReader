// supplier.cpp,v 1.4 1998/11/04 03:01:10 kirthika Exp

#include "Supplier_i.h"

// This function runs the Callback Quoter Supplier daemon.

int
main (int argc, char **argv)
{
 Supplier supplier;

  ACE_DEBUG ((LM_DEBUG,
              "\n\tMarket Status Supplier Daemon\n\n"));

  if (supplier.init (argc, argv) == -1)
    return -1;
  else
    return supplier.run ();
}
