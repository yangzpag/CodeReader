// Progress_i.cpp,v 1.5 2001/03/30 19:23:52 coryan Exp

#include "Progress_i.h"

#if defined(ACE_HAS_FL)

#include <FL/Fl_Slider.h>
#include <FL/Fl_Button.h>

#if !defined(__ACE_INLINE__)
#include "Progress_i.i"
#endif /* __ACE_INLINE__ */

ACE_RCSID(FL_Cube, test_i, "Progress_i.cpp,v 1.5 2001/03/30 19:23:52 coryan Exp")

Progress_i::Progress_i (Progress_Window *window)
  :  window_ (window)
{
}

void
Progress_i::sent_request (CORBA::Long id,
                     CORBA::Environment &)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  //ACE_DEBUG ((LM_DEBUG, "Progress (%t) - sent request %d\n", id));
  this->window_->sent_request (id);
}

void
Progress_i::recv_reply (CORBA::Long id,
                        CORBA::Environment &)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  this->window_->recv_reply (id);
}

CORBA::Long
Progress_i::bind (Peer_ptr a_peer,
                  CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  ACE_DEBUG ((LM_DEBUG, "Progress (%t) - peer bound\n"));
  return this->window_->bind (a_peer, ACE_TRY_ENV);
}

// ****************************************************************

Progress_Window::Progress_Window (int n_peers,
                                  int n_iterations,
                                  int x, int y,
                                  int w, int h,
                                  const char* l)
  :  Fl_Box (x, y, w, h, l),
     n_peers_ (n_peers),
     peers_ (n_peers),
     n_iterations_ (n_iterations)
{
  ACE_NEW (this->request_progress_, Fl_Widget*[this->n_peers_]);
  ACE_NEW (this->reply_progress_, Fl_Widget*[this->n_peers_]);

  // @@ leak...
  Fl_Widget *button = new Fl_Button (x + 5, y + 5,
                                     50, h - 10,
                                     "Start");
  button->callback (Progress_Window::start_callback, this);

  // Compute the slider height, leaving a little margin...
  int sh = h / ( 2 * this->n_peers_);
  sh = sh - 5;

  // The initial position, with margin...
  int sy = y + 5;

  // Set the width of the sliders...
  int sx = x + 60;
  int sw = w - 65;
  int max = this->n_peers_ * this->n_iterations_;
  for (int i = 0; i < this->n_peers_; ++i)
    {
      Fl_Slider *obj;

      this->request_progress_[i] = obj =
        new Fl_Slider (FL_HOR_FILL_SLIDER, sx, sy, sw, sh, "");
      obj->color (FL_BLACK);
      obj->selection_color (FL_RED);
      obj->bounds (0, max);
      obj->precision (0);
      obj->value (0);
      sy += sh + 5;

      this->reply_progress_[i] = obj =
        new Fl_Slider (FL_HOR_FILL_SLIDER, sx, sy, sw, sh, "");
      obj->color (FL_BLACK);
      obj->selection_color (FL_GREEN);
      obj->bounds (0, max);
      obj->precision (0);
      obj->value (0);
      sy += sh + 5;
    }
}

void
Progress_Window::sent_request (CORBA::Long id)
{
  if (id < 0 || id >= this->n_peers_)
    return;
  Fl_Slider *obj =
    ACE_dynamic_cast (Fl_Slider*,this->request_progress_[id]);
  obj->value (obj->value () + 1);
  obj->redraw ();

  int i = ACE_static_cast(int,obj->value ());
  if (i % 100 == 0)
    ACE_DEBUG ((LM_DEBUG, "Progress (%t) - recv reply %d\n", i));
}

void
Progress_Window::recv_reply (CORBA::Long id)
{
  if (id < 0 || id >= this->n_peers_)
    return;
  Fl_Slider *obj =
    ACE_dynamic_cast (Fl_Slider*,this->reply_progress_[id]);
  obj->value (obj->value () + 1);
  obj->redraw ();

  int i = ACE_static_cast(int,obj->value ());
  if (i % 100 == 0)
    ACE_DEBUG ((LM_DEBUG, "Progress (%t) - recv reply %d\n", i));
}

CORBA::Long
Progress_Window::bind (Peer_ptr a_peer,
                       CORBA::Environment &)
{
  CORBA::ULong l = this->peers_.length ();
  this->peers_.length (l + 1);
  this->peers_[l] = Peer::_duplicate (a_peer);

  return l;
}

void
Progress_Window::start_callback (Fl_Widget* /* widget */,
                                 void *data)
{
  Progress_Window *self = ACE_static_cast (Progress_Window*, data);
  self->start ();
}

void
Progress_Window::start ()
{
  if (this->peers_.length () < CORBA::ULong (this->n_peers_))
    return;

  ACE_DECLARE_NEW_CORBA_ENV;
  for (CORBA::ULong i = 0; i != this->peers_.length (); ++i)
    {
      ACE_TRY
        {
          this->peers_[i]->start (this->peers_,
                                  this->n_iterations_,
                                  ACE_TRY_ENV);
          ACE_TRY_CHECK;
        }
      ACE_CATCHANY
        {
          // Ignore exceptions
        }
      ACE_ENDTRY;
    }
}


#endif /* ACE_HAS_FL */
