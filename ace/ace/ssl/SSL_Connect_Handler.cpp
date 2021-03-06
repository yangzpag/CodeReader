// -*- C++ -*-

#include "SSL_Connect_Handler.h"
#include "SSL_SOCK_Stream.h"

#include <openssl/err.h>

ACE_RCSID (ACE_SSL,
           SSL_Connect_Handler,
           "SSL_Connect_Handler.cpp,v 1.4 2001/09/29 06:39:58 othman Exp")


ACE_SSL_Connect_Handler::ACE_SSL_Connect_Handler (ACE_SSL_SOCK_Stream &s)
  : ssl_stream_ (s)
{
}

ACE_SSL_Connect_Handler::~ACE_SSL_Connect_Handler (void)
{
}

ACE_HANDLE
ACE_SSL_Connect_Handler::get_handle (void) const
{
  return this->ssl_stream_.get_handle ();
}

int
ACE_SSL_Connect_Handler::handle_input (ACE_HANDLE)
{
  return this->ssl_connect ();
}

int
ACE_SSL_Connect_Handler::handle_output (ACE_HANDLE)
{
  return this->ssl_connect ();
}

int
ACE_SSL_Connect_Handler::handle_close (ACE_HANDLE /* handle */,
                                       ACE_Reactor_Mask /* close_mask */)
{
  return this->ssl_stream_.close ();
}


int
ACE_SSL_Connect_Handler::ssl_connect (void)
{
  // A race condition exists where data may be sent over an SSL
  // session after the SSL active connection is completed but before
  // this event handler is deregistered from the Reactor.
  // Specifically data meant to be handled by SSL_read() could end up
  // being handled by the SSL_connect() call below, resulting in an SSL
  // protocol error (i.e. "SSL_ERROR_SSL" error status).  The
  // following check avoids the race condition.
  if (SSL_is_init_finished (this->ssl_stream_.ssl ()))
    return 0;

  // The SSL_connect() call is wrapped in a do/while(SSL_pending())
  // loop to force the SSL buffer to be flushed read prior to
  // returning to the Reactor.  This is necessary to avoid some subtle
  // problems where data from another record is potentially handled
  // before the current record is fully handled.
  do
    {
      int status = ::SSL_connect (this->ssl_stream_.ssl ());

      switch (::SSL_get_error (this->ssl_stream_.ssl (), status))
        {
        case SSL_ERROR_NONE:
          // Start out with non-blocking disabled on the SSL stream.
          this->ssl_stream_.disable (ACE_NONBLOCK);

          // Active connection completed.
          return 0;

        case SSL_ERROR_WANT_WRITE:
        case SSL_ERROR_WANT_READ:
          break;

        case SSL_ERROR_ZERO_RETURN:
          // The peer has notified us that it is shutting down via
          // the SSL "close_notify" message so we need to
          // shutdown, too.
          //
          // Removing this event handler causes the SSL stream to be
          // shutdown.
          return -1;

        case SSL_ERROR_SYSCALL:
          // On some platforms (e.g. MS Windows) OpenSSL does not
          // store the last error in errno so explicitly do so.
          ACE_OS::set_errno_to_last_error ();

        default:
          ACE_SSL_Context::report_error ();

          return -1;
        }
    }
  while (::SSL_pending (this->ssl_stream_.ssl ()));

  // Completed flushing the SSL buffer, but SSL active connection is
  // still pending completion.

  return 0;
}
