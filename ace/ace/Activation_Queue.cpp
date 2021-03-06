// Activation_Queue.cpp
// Activation_Queue.cpp,v 4.17 2001/09/27 22:35:47 schmidt Exp

#include "ace/Activation_Queue.h"

#if !defined (__ACE_INLINE__)
#include "ace/Activation_Queue.i"
#endif /* __ACE_INLINE__ */

ACE_RCSID(ace, Activation_Queue, "Activation_Queue.cpp,v 4.17 2001/09/27 22:35:47 schmidt Exp")

// Dump the state of an object.

void 
ACE_Activation_Queue::dump (void) const
{
  ACE_DEBUG ((LM_DEBUG, ACE_BEGIN_DUMP, this));
  ACE_DEBUG ((LM_DEBUG,
	      ACE_LIB_TEXT ("delete_queue_ = %d\n"),
	      this->delete_queue_));
  ACE_DEBUG ((LM_INFO, ACE_LIB_TEXT ("queue_: \n")));
  if (this->queue_)
    this->queue_->dump();
  else
    ACE_DEBUG ((LM_DEBUG, ACE_LIB_TEXT ("(NULL)\n")));
  ACE_DEBUG ((LM_DEBUG, ACE_END_DUMP));
}

ACE_Activation_Queue::ACE_Activation_Queue (ACE_Message_Queue<ACE_SYNCH> *new_queue) 
  : delete_queue_ (0)
{
  if (new_queue)
    this->queue_ = new_queue;
  else
    {
      ACE_NEW (this->queue_,
               ACE_Message_Queue<ACE_SYNCH>);
      this->delete_queue_ = 1;
    }
}

ACE_Activation_Queue::~ACE_Activation_Queue (void) 
{
  if (this->delete_queue_ != 0)
    delete this->queue_;
}

ACE_Method_Request *
ACE_Activation_Queue::dequeue (ACE_Time_Value *tv)
{
  ACE_Message_Block *mb;

  // Dequeue the message.
  if (this->queue_->dequeue_head (mb, tv) != -1)
    {
      // Get the next <Method_Request>.
      ACE_Method_Request *mr =
        ACE_reinterpret_cast (ACE_Method_Request *,
                              mb->base ());

      // Delete the message block.
      mb->release ();
      return mr;
    }
  else
    return 0;
}

int 
ACE_Activation_Queue::enqueue (ACE_Method_Request *mr,
			       ACE_Time_Value *tv)
{
  ACE_Message_Block *mb;

  // We pass sizeof (*mr) here so that flow control will work
  // correctly.  Since we also pass <mr> note that no unnecessary
  // memory is actually allocated -- just the size field is set.
  ACE_NEW_RETURN (mb,
                  ACE_Message_Block ((char *) mr,
                                     sizeof (*mr),
                                     mr->priority ()),
                  -1);

  // Enqueue in priority order.
  return this->queue_->enqueue_prio (mb, tv);
}

