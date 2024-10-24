/* -*-mode: C++; fill-column: 75; -*- */
/* SPDX-License-Identifier: CC-BY-NC-ND-4.0 */

// ===========================================================================
//   CLASP EXENSION RTI CONNEXT DDS MAIN FILE
// ===========================================================================
//   main.cxx
//
//   Copyright 2024 Gönninger B&T GmbH, Germany.
//
//   License: See https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
//   Author:  Frank Gönninger <frank.goenninger@goenninger.net>
//   Support: By Gönninger B&T GmbH <support@goenninger.net>
//
// ===========================================================================

#include <clasp/clasp.h>

// --- RTI CONNEXT DDS ONCLUDESD ---

#include <dds/dds.hpp>

// --- C/ C++ INCLUDES ---

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cstdint>
#include <cstdarg>
#include <unistd.h>
#include <libgen.h>
#include <string>

// -- LOCAL UTILS ---
static void debugprint ( const char * filepath, uint64_t line, const char * fmt, ... )
{
  char            va_buffer [ 32768 ];
  char            msg_buffer [ 32768 ];
  char            time_buffer [ 128 ];
  clockid_t       clock_id = CLOCK_REALTIME;
  int             clock_rc = 0;
  struct timespec timespec;
  static bool     clock_gettime_warned_already = false;

  memset ( &timespec,   0, sizeof ( struct timespec ) );
  memset ( va_buffer,   0, 32768 );
  memset ( msg_buffer,  0, 32768 );
  memset ( time_buffer, 0, 128 );

  clock_rc = clock_gettime ( clock_id, &timespec );
  if ( ( clock_rc != 0 ) && ( clock_gettime_warned_already == false ) )
  {
    clock_gettime_warned_already = true;
    fprintf ( stderr, "CLBIND/RTI-CONNEXT_DDS | **  [WARNING  ] | Could not get timestamp ... (This warning will only be printed once).");

    timespec.tv_sec  = 0;
    timespec.tv_nsec = 0;
  }

  strftime ( time_buffer, 128, "%FT%T", gmtime ( (const long *) &(timespec.tv_sec ) ) );
  size_t cstr_length =  strlen ( time_buffer );
  snprintf ( &time_buffer[ cstr_length ], 128 - cstr_length, ".%09ld+00Z", timespec.tv_nsec );

  va_list arg_ptr;
  va_start ( arg_ptr, fmt );
  vsnprintf ( va_buffer, 32768, fmt, arg_ptr );
  va_end ( arg_ptr );

  if ( snprintf ( msg_buffer, 32768, "%s | %s (%s:%llu) | %s | %s\n",
                  time_buffer,
                  "    [DEBUG    ]",
                  basename ( const_cast< char * >( filepath ) ), line, "CLB",
                  va_buffer ) < 0 )
  {
    fprintf ( stderr, "CLBIND/RTI-CONNEXT-DDS | Process with pid %d ABORTING due to message buffer overrun!\n",
              (int) getpid () );
    abort ();
  }

  fprintf ( stderr, "%s", msg_buffer );

  return;
}

#define DEBUGPRINT(fmt,...) debugprint(  __FILE__ , __LINE__,  fmt, __VA_ARGS__ )
#define TRACE_ENTRY() debugprint( __FILE__ , __LINE__, "ENTRY: %s", __FUNCTION__ )
#define TRACE_EXIT()  debugprint( __FILE__ , __LINE__, "EXIT:  %s", __FUNCTION__ )

// --- PACKAGE ---

PACKAGE_USE("COMMON-LISP");
PACKAGE_NICKNAME("RTI-CONNEXT-DDS");
NAMESPACE_PACKAGE_ASSOCIATION( rti_connext_dds, RTIConnextDDSPkg, "RTI-CONNEXT-DDS" );

// --- CLBINDINGS ---

namespace rti_connext_dds
{
   CL_EXPOSE void rti_connext_dds_start( void )
   {
     TRACE_ENTRY ();
     
     using namespace clbind;

     using namespace dds::all; // This brings all DDS symbols into the rti_connext_dds namespace

     package_ p( RTIConnextDDSPkg );

     class_< DomainParticipant >( p, "domain-participant" )
       .def_constructor( "make-domain-participant", constructor<uint32_t>());

     
     TRACE_EXIT ();
   }
} // namespace rti_connext_dds
