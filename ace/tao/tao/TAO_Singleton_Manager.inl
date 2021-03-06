// -*- C++ -*-
//
// TAO_Singleton_Manager.inl,v 1.1 2000/08/06 20:49:55 othman Exp

ACE_INLINE
int
TAO_Singleton_Manager::at_exit (ACE_Cleanup *object,
                             void *param)
{
  return TAO_Singleton_Manager::instance ()->at_exit_i (
    object,
    (ACE_CLEANUP_FUNC) ace_cleanup_destroyer,
    param);
}

ACE_INLINE
int
TAO_Singleton_Manager::at_exit (void *object,
                             ACE_CLEANUP_FUNC cleanup_hook,
                             void *param)
{
  return TAO_Singleton_Manager::instance ()->at_exit_i (
    object,
    cleanup_hook,
    param);
}
