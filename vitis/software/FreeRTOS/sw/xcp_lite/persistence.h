#pragma once
#define __PERSISTENCE_H__

/*----------------------------------------------------------------------------
| File:
|   persistence.h
|
| Description:
|   XCPlite internal header file for persistence.c
|
| Copyright (c) Vector Informatik GmbH. All rights reserved.
| See LICENSE file in the project root for details.
|
 ----------------------------------------------------------------------------*/

#include "xcplib_cfg.h" // for OPTION_xxx

#ifdef OPTION_ENABLE_PERSISTENCE

#include <assert.h>  // for assert
#include <stdbool.h> // for bool
#include <stdint.h>  // for uintxx_t

#include "xcplite.h" // for tXcpCalSegIndex

#ifdef __cplusplus
extern "C" {
#endif

// Create the binary file with the current default pages
bool XcpBinWrite(const char *epk);

// Load the binary file and create calibration segment marked as preloaded
bool XcpBinLoad(void);

// Delete the binary file
void XcpBinDelete(void);

#ifdef OPTION_CAL_SEGMENTS
// Freeze current working page data of the specified calibration segment in the binary file
bool XcpBinFreezeCalSeg(tXcpCalSegIndex calseg);
#endif

/// Get the filename of the binary persistence file
/// Buffer valid until the next call of this function
const char *XcpBinGetFilename(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // OPTION_ENABLE_PERSISTENCE
