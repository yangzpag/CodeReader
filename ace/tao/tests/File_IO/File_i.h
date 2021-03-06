// File_i.h,v 1.2 2001/08/25 04:18:27 bala Exp

//===================================================================
//
// = FILENAME
//     File_i.h
//
// = DESCRIPTION
//      Defines the implementation classes for the File IDL
//     module
//
// = AUTHOR
//     Irfan Pyarali
//
//====================================================================

#include "FileS.h"

class FileImpl
{
  // = TITLE
  //   FileImpl class provides the namespace for the File IDL module .
public:
  class Descriptor : public POA_File::Descriptor
  {
    // = TITLE
    //   Descriptor implements the Descriptor interface in the File
    //   Module A single Descriptor servant can serve multiple object
    //   references
  public:
    Descriptor (PortableServer::POA_ptr poa);
    // Constructor

    ~Descriptor (void);
    // Destructor

    PortableServer::POA_ptr _default_POA (CORBA::Environment &env);
    // Returns the default POA of this object

    virtual CORBA::Long write (const File::Descriptor::DataBuffer &buffer,
                               CORBA::Environment &env)
      ACE_THROW_SPEC ((CORBA::SystemException,
                       File::IOError));
    // write buffer to File corresponding to this Descriptor

    virtual File::Descriptor::DataBuffer *read (CORBA::Long num_bytes,
                                                CORBA::Environment &env)
      ACE_THROW_SPEC ((CORBA::SystemException,
    // Reads num_bytes from the file and returns it
                       File::IOError));

    virtual CORBA::ULong lseek (CORBA::ULong offset,
                                CORBA::Long whence,
                                CORBA::Environment &env)
      ACE_THROW_SPEC ((CORBA::SystemException,
                       File::IOError));
    // seek to the offset in file from whence

    virtual void destroy (CORBA::Environment &env)
      ACE_THROW_SPEC ((CORBA::SystemException));
    // closes the file corresponding to the requested ObjectID

  private:

    ACE_HANDLE fd (CORBA::Environment &env);
    // Extracts the ACE_HANDLE from the objectID

    PortableServer::POA_var poa_;
  };

  class System : public POA_File::System
  {
    // = TITLE
    //   File System implementation class.
  public:
    System (PortableServer::POA_ptr poa);
    // Constructor, Creates a single File Descriptor Servant and
    // registers it with the POA as the Default Servant

    ~System (void);
    //Destructor

    PortableServer::POA_ptr _default_POA (CORBA::Environment &env);
    //Returns the default POA of this object

    File::Descriptor_ptr open (const char *file_name,
                               CORBA::Long flags,
                               CORBA::Environment &env)
      ACE_THROW_SPEC ((CORBA::SystemException,
                       File::IOError));
    // Opens a file ,creates a Descriptor reference with the
    // ACE_HANDLE and returns that reference

  private:
    PortableServer::POA_var poa_;

    Descriptor fd_servant_;
    // The single File Descriptor servant which serves requests for
    // any Descriptor object under poa_.
  };
};
