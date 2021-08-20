/** @file
  Output debug messages to the debug port.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2016 Intel Corporation.

  The source code contained or described herein and all documents related to the
  source code ("Material") are owned by Intel Corporation or its suppliers or
  licensors. Title to the Material remains with Intel Corporation or its suppliers
  and licensors. The Material may contain trade secrets and proprietary and
  confidential information of Intel Corporation and its suppliers and licensors,
  and is protected by worldwide copyright and trade secret laws and treaty
  provisions. No part of the Material may be used, copied, reproduced, modified,
  published, uploaded, posted, transmitted, distributed, or disclosed in any way
  without Intel's prior express written permission.

  No license under any patent, copyright, trade secret or other intellectual
  property right is granted to or conferred upon you by disclosure or delivery
  of the Materials, either expressly, by implication, inducement, estoppel or
  otherwise. Any license under such intellectual property rights must be
  express and approved by Intel in writing.

  Unless otherwise agreed by Intel in writing, you may not remove or alter
  this notice or any other notice embedded in Materials by Intel or
  Intel's suppliers or licensors in any way.

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/
#ifndef _MrcOemDebugPrint_h_
#define _MrcOemDebugPrint_h_
#pragma pack (push, 1)


#include "MrcTypes.h"
#include "MrcGlobal.h"

typedef char  *MrcVaList;

#ifndef MDEPKG_NDEBUG
#define MRC_DEBUG_PRINT (1)
#endif // MDEPKG_NDEBUG

#define MRC_PRINTS_ON           1
#define MRC_PRINTS_OFF          0

///
/// Algorithm Debug Switches.
///   Controls compiling of Algorithim Debug Printinig.
///
#ifdef MRC_DEBUG_PRINT
#define POWER_TRAINING_DEBUG  UNSUPPORT
#endif // MRC_DEBUG_PRINT

#define TRANSMIT_HOLDING        (0x00)

#define LINE_STATUS             (0x05)
#define TRANS_HOLDING_REG_EMPTY (0x20)
#define BREAK_INTERRUPT         (0x10)
#define DATA_READY              (0x01)
#define RECEIVER_BUFFER         (0x00)
#ifndef EOF
#define EOF                     (0xFF)
#endif
#ifndef DELETE
#define DELETE                  (0x7F)
#endif
#define BACKSPACE               (0x08)

///
/// com port options
///
#define MRC_COM1_BASE (0x3f8)
#define MRC_COM2_BASE (0x2f8)
#define MRC_COM3_BASE (0x3e8)
#define MRC_COM4_BASE (0x2e8)

///
/// select the platform com port address
///
#define GLOBALCOMPORT (MRC_COM1_BASE)                                   ///< 0x3F8-0x3FF
#ifndef MRC_LEFT_JUSTIFY
#define MRC_LEFT_JUSTIFY  (0x01)
#endif
#ifndef MRC_PREFIX_SIGN
#define MRC_PREFIX_SIGN (0x02)
#endif
#ifndef MRC_PREFIX_BLANK
#define MRC_PREFIX_BLANK  (0x04)
#endif
#ifndef MRC_COMMA_TYPE
#define MRC_COMMA_TYPE  (0x08)
#endif
#ifndef MRC_LONG_TYPE
#define MRC_LONG_TYPE (0x10)
#endif
#ifndef MRC_PREFIX_ZERO
#define MRC_PREFIX_ZERO (0x20)
#endif
#ifndef MRC_INT_SIGNED
#define MRC_INT_SIGNED  (0x40)
#endif

#define ASCII_ETX           (3)
#define MRC_CHAR_LF         (0x0A)
#define MRC_CHAR_CR         (0x0D)
#define MRC_CHAR_A          (0x41)
#define MRC_CHAR_B          (0x42)
#define MRC_CHAR_C          (0x43)
#define MRC_CHAR_D          (0x44)
#define MRC_CHAR_LEFT_BRACKET (0x5B)
#define MAX_STRING_LENGTH   256
#define MRC_PUTCC(_str, _c, _CharCount) { \
    _str[_CharCount] = _c; \
    if (_CharCount < (MAX_STRING_LENGTH - 1)) {_CharCount++;}; \
  }
#define MRC_ISDIGIT(_c) (((_c) >= '0') && ((_c) <= '9'))
#define isprint(a)      (((a) >= ' ') && ((a) <= '~') ? (a) : 0)
#define isspace(a)      ((((a) == ' ') || (((a) >= '\t') && ((a) < '\r'))) ? (a) : 0)

#ifndef MRC_INTSIZEOF
#define MRC_INTSIZEOF(n) ((sizeof (n) + sizeof (UINT32) - 1) & ~(sizeof (UINT32) - 1))
#endif
#ifndef VA_START
#define VA_START(ap,v)   (ap = (MrcVaList) &v + MRC_INTSIZEOF (v)) // Macro to set arg_ptr to beginning of list of optional arguments
#endif
#ifndef VA_ARG
#define VA_ARG(ap,t)     (*(t *) ((ap += MRC_INTSIZEOF (t)) - MRC_INTSIZEOF (t))) // Macro to retrieve current argument
#endif
#ifndef VA_END
#define VA_END(ap)       (ap = (MrcVaList) 0)                                     // Macro to reset arg_ptr
#endif

#ifdef MRC_DEBUG_PRINT
#define MRC_DEBUG_MSG_OPEN(MRCDATA, LEVEL, FILE, BUFFER, SIZE) MrcFopen (MRCDATA, LEVEL, FILE, BUFFER, SIZE)
#define MRC_DEBUG_MSG(DEBUG, LEVEL, FORMAT, ...)             MrcPrintf (DEBUG, LEVEL, FORMAT, ##__VA_ARGS__)
#define MRC_DEBUG_TEXT(arg)                                  (arg)
#else
#define MRC_DEBUG_MSG_OPEN(MRCDATA, LEVEL, FILE, BUFFER, SIZE)
#define MRC_DEBUG_MSG(DEBUG, LEVEL, FORMAT, ...)
#define MRC_DEBUG_TEXT(arg)
#endif

#if defined POWER_TRAINING_DEBUG && (POWER_TRAINING_DEBUG == SUPPORT)
#define MRC_POWER_DEBUG_MSG(MRCDATA, LEVEL, FORMAT, ...)  MrcPrintf (MRCDATA, LEVEL, FORMAT, ##__VA_ARGS__)
#else
#define MRC_POWER_DEBUG_MSG(MRCDATA, LEVEL, FORMAT, ...)
#endif

/**
  Convert an unsigned integer to a string.

  @param[in]  MrcCall         - Optional when value is 32-bit, required for 64-bit values.
  @param[in]  Value           - Value to work on.
  @param[in]  ValueSize       - The size of the value in bytes with valid values of 4 and 8.
  @param[out] Str             - The return string to print.
  @param[in]  Width           - The width of string to print
  @param[in]  Flags           - The flag type to print out, like '-' or '+'.
  @param[in]  Base            - Number base to work on, as in 10, or 16.

  @retval Number of characters in the resulting string.
**/
extern
UINT32
UintnToStr (
  IN  const MRC_FUNCTION *const MrcCall,
  IN  const UINT64 Value,
  IN  const UINT32 ValueSize,
  OUT char         *Str,
  IN  const UINT32 Width,
  IN  const UINT32 Flags,
  IN  const UINT32 Base
  );

/**
  Convert a string to a number.

  @param[in, out] String - String to convert.

  @retval Returns the string in number.
**/
extern
UINT32
StrToNumber (
  IN OUT char **String
  );


/**
  This function compares two strings, up to count characters or first null character in either string.

  @param[in] *string1 - First null-terminated string to compare.
  @param[in] *string2 - Second null-terminated string to compare.
  @param[in] count   - Number of characters to compare, starting from beginning.

  @retval 0 on compare or initial Count value == 0.
  @retval < 0, string1 substring less than string2 substring.
  @retval > 0, string2 substring less than string1 substring.

**/
extern
int
Mrcstrncmp (
  const char *string1,
  const char *string2,
  int count
);

/**
  Read char from the uart device.

  @retval Returns the read char.
**/
extern
char
getchar (
  void
  );

/**
  Put char in the uart device.

  @param[in] c - char to put in the uart.

  @retval Returns the ouput char.
**/
extern
int
putchar (
  int c
  );
/**
  This function outputs a string to the default device.

  @param[in] String - The null terminated string to output.

  @retval Returns a nonnegative value if successful.
**/
int
MrcPuts (
  const char *String
  );


/*++
  Format string using specified format specifier. Limited support for sizes other than
  unsigned 32-bit to save code space. Type overrides like {h | I | I64 | L}
  are not supported.

  @param[in] Format     - String containing characters to print and formatting data.
    %[flags][width]type
    [flags] '-' left align
    [flags] '+' prefix with sign (+ or -)
    [flags] '0' zero pad numbers
    [flags] ' ' prefix black in front of postive numbers
    [width] non negative decimal integer that specifies the width to print a value.
    [width] '*' get the width from a int argument on the stack.
    type    'd'|'i' signed decimal integer
    type    'u' unsigned integer
    type    'x'|'X' hexidecimal using "ABCDEF"
    type    'c' print character
    type    'p' print a pointer to void
    type    's' print a null terminated string
  @param[in] Marker     - Variable argument marker.
  @param[in] BufferSize - Size of the buffer, in bytes.
  @param[in] Buffer     - The buffer.

  @retval Number of characters printed.
**/
extern
int
StringFormatter (
  IN const MRC_FUNCTION     *const MrcCall,
  IN const char *const      Format,
  IN MrcVaList              Marker,
  IN UINT32                 BufferSize,
  IN OUT UINT8              *Buffer
  );

/*++

  Print to output stream/device. Limited support for sizes other than
  unsigned 32-bit to save code space. Type overrides like {h | I | I64 | L}
  are not supported.

  @param[in] Debug  - Location to store debug message print information for future use.
  @param[in] Level  - The debug level.
  @param[in] Format - String containing characters to print and formatting data.
    %[flags][width]type
    [flags] '-' left align
    [flags] '+' prefix with sign (+ or -)
    [flags] '0' zero pad numbers
    [flags] ' ' prefix black in front of postive numbers
    [width] non negative decimal integer that specifies the width to print a value.
    [width] '*' get the width from a int argument on the stack.
    type    'd'|'i' signed decimal integer
    type    'u' unsigned integer
    type    'x'|'X' hexidecimal using "ABCDEF"
    type    'c' print character
    type    'p' print a pointer to void
    type    's' print a null terminated string
  @param[in] Marker - Variable argument marker

  @retval Number of characters printed.
**/
extern
int
MrcPrintfVaList (
  IN MrcDebug *const    Debug,
  IN MrcDebugMsgLevel   Level,
  IN const char *const  Format,
  IN MrcVaList          Marker
  );

/**
  Function used to get a serial debug print buffer

  @param[in, out] MrcData - The MRC global data area.
**/
extern
void
MrcSerialBufferMalloc (
  MrcParameters *const MrcData
  );

/**
  put char in the uart device.

  @param[in] Debug  - Location to store debug message print information for future use.
  @param[in] Level  - The debug level.
  @param[in] Format - String containing characters to print and formatting data.
    %[flags][width]type
    [flags] '-' left align
    [flags] '+' prefix with sign (+ or -)
    [flags] '0' zero pad numbers
    [flags] ' ' prefix black in front of postive numbers
    [width] non negative decimal integer that specifies the width to print a value.
    [width] '*' get the width from a int argument on the stack.
    type    'd'|'i' signed decimal integer
    type    'u' unsigned integer
    type    'x'|'X' hexidecimal using "ABCDEF"
    type    'c' print character
    type    'p' print a pointer to void
    type    's' print a null terminated string

  @retval Returns the puted char.
**/
extern
int
MrcPrintf (
  IN MrcDebug *const    Debug,
  IN MrcDebugMsgLevel   Level,
  IN const char *const  Format,
  ...
  );

/**
  Save the output stream/device. This function must be called prior to debug
  string output.

  @param[in,out] MrcData - Pointer to the MRC global data structure.
  @param[in]     Level   - The debug level to set. Messages at or above this level are printed.
  @param[in]     Stream  - Pointer to the stream/device to use.
  @param[in]     Buffer  - Pointer to the buffer that will be used to 'tee' the data to.
  @param[in]     Size    - Size of the 'tee' buffer.

  @retval Nothing.
**/
extern
void
MrcFopen (
  IN OUT void *const    MrcData,
  IN  MrcDebugMsgLevel  Level,
  IN  UINT32            Stream,
  IN  UINT32            Buffer,
  IN  UINT32            Size
  );

#pragma pack (pop)
#endif //_MrcOemDebugPrint_h_
