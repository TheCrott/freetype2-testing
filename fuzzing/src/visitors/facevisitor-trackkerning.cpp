// facevisitor-trackkerning.cpp
//
//   Implementation of FaceVisitorTrackKerning.
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#include "visitors/facevisitor-trackkerning.h"

#include <cassert>

#include "utils/logging.h"


  FaceVisitorTrackKerning::
  FaceVisitorTrackKerning( void )
  {
    // some arbitrary seeds:

    point_sizes.push_back( 0x10000L +  8 );
    point_sizes.push_back( 0x10000L + 16 );
    point_sizes.push_back( 0x10000L + 32 );
    point_sizes.push_back( 0x10000L + 64 );

    degrees.push_back( -100 );
    degrees.push_back(  -10 );
    degrees.push_back(   -1 );
    degrees.push_back(    0 );
    degrees.push_back(    1 );
    degrees.push_back(   10 );
    degrees.push_back(  100 );
  }
  

  void
  FaceVisitorTrackKerning::
  run( Unique_FT_Face  face )
  {
    FT_Error  error;

    FT_Fixed  kerning;


    assert( face != nullptr );

    if ( FT_HAS_KERNING( face ) == 0 )
      return;

    for ( auto  point_size : point_sizes )
    {
      for ( auto  degree : degrees )
      {
        error = FT_Get_Track_Kerning( face.get(),
                                      point_size,
                                      degree,
                                      &kerning );

        LOG_IF( ERROR, error != 0 )
          << "FT_Get_Track_Kerning failed: " << error;
        LOG_IF( INFO, error == 0)
          << "track kerning of "
          << point_size << "/" << degree << ": " << kerning;
      }
    }
  }