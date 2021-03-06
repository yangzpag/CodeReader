//
// Stock_i.cpp,v 1.1 2001/03/07 01:14:54 doccvs Exp
//

#include "Stock_i.h"

Quoter_Stock_i::Quoter_Stock_i (const char *symbol,
                                const char *full_name,
                                CORBA::Double price)
  :  symbol_ (symbol),
     full_name_ (full_name),
     price_ (price)
{
}

char *
Quoter_Stock_i::symbol () throw (CORBA::SystemException)
{
  return CORBA::string_dup (this->symbol_.c_str ());
}

char *
Quoter_Stock_i::full_name () throw (CORBA::SystemException)
{
  return CORBA::string_dup (this->full_name_.c_str ());
}

CORBA::Double
Quoter_Stock_i::price () throw (CORBA::SystemException)
{
  return this->price_;
}
