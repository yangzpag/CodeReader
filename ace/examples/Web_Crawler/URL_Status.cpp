/* -*- C++ -*- */
// URL_Status.cpp,v 1.2 1999/05/03 21:10:16 kirthika Exp

#include "URL_Status.h"

ACE_RCSID(Web_Crawler, URL_Status, "URL_Status.cpp,v 1.2 1999/05/03 21:10:16 kirthika Exp")

URL_Status::URL_Status (STATUS_CODE code)
  : status_ (code)
{
}

URL_Status::URL_Status (const URL_Status &s)
  : status_ (s.status_)
{
}

URL_Status::STATUS_CODE
URL_Status::status (void) const
{
  return this->status_;
}

void
URL_Status::status (int s)
{
  this->status_ = URL_Status::STATUS_CODE (s);
}

void
URL_Status::status (URL_Status::STATUS_CODE s)
{
  this->status_ = s;
}

int URL_Status::destroy (void)
{
  delete this;
  return 0;
}
