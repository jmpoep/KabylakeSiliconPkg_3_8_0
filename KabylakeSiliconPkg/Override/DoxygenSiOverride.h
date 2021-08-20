/** @file
This file contains doxygen commands definitions for creating
ClientSiliconPkg override documentation

@copyright
Copyright (c) 2016 - 2018 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent off
Intel Corporation.
This file contains an 'Sample Driver' and is
licensed for Intel CPUs and chipsets under the terms of your
license agreement with Intel or your vendor.  This file may
be modified by the user, subject to additional terms of the
license agreement
**/

/**
 @page siliconpkgoverride

Silicon Override tags (SICO-xxxx) document issues that Silicon team has resolved with an override of Royal Park.

The Active SICO table lists every issue which is currently resolved with an override. It is a catalog of all such existing overrides.

The Retired SICO table lists issues which previously required such overrides. It is purely historical as these overrides have all been deleted (are no longer needed).
<BR>
<CENTER>
<STRONG>Active SICOs</STRONG>
<BR>in KabylakeSiliconPkg/Override
</CENTER>

<table border="1" style="width:1200px">
<tr>
  <th>Tag</th>
  <th>Client HSD</th>
  <th>BP HSD</th>
  <th>Status / Planned EOL</th>
  <th>Description</th>
</tr>
  <tr> <td>SICO-KBL-0001</td> <td></td>    <td></td>        <td></td>           <td>1504005677:Enabling Performance measurement for FSP Binary - Moving PeiFpdtPerformanceLib from ClientCommonPkg to ClientSiliconPkg (as needed by FSP binary) by renaming the library as PerformanceLibFpdt to follow the standard naming</td> </tr>
  <tr> <td>SICO-KBL-0003</td> <td></td>    <td></td>        <td></td>           <td>1208436659:[BP|KBL|CNL] Using wrong variable when checking return value of function in DxeHstiLib/HstiDxe.c</td> </tr>
  <tr> <td>SICO-KBL-0004</td> <td></td>    <td></td>        <td></td>           <td>1209517630:Merge in UDK2015 fix to provide BSP BIST to CpuMpPei</td> </tr>
  <tr> <td>SICO-KBL-0005</td> <td></td>    <td></td>        <td></td>           <td>1604300189:For FSP, place AP Wakeup buffer in fixed place, so Bootloader knows not update this.</td> </tr>
  <tr> <td>SICO-KBL-0006</td> <td></td>    <td></td>        <td></td>           <td>22064840:Copy GDT to memory if in flash. System hangs on reboot cycle at checkpoint 0x36.</td></tr>
  <tr> <td>SICO-KBL-0007</td> <td></td>    <td></td>        <td></td>           <td>1604360610:CPU_CHECK_AP_INTERVAL is reduced to meet performance budget.</td></tr>
  <tr> <td>SICO-KBL-0009</td> <td></td>    <td></td>        <td></td>           <td>2201839018:[KBL] Potential TianoCompress overflow issues</td></tr>
  </table>

<BR>
<CENTER>
<STRONG>Retired SICOs</STRONG>
<BR>formerly in KabylakeSiliconPkg/Override
</CENTER>

<table border="1" style="width:1200px">
<tr>
  <th>Tag</th>
  <th>Client HSD</th>
  <th>BP HSD</th>
  <th>Actual EOL</th>
  <th>Description</th>
</tr>
  <tr> <td>SICO-KBL-0002</td> <td></td>    <td></td>        <td></td>           <td>Improve Responsiveness Performance of microcode patch load in CpuMpPei driver, and adjust verification check to work for KBL</td> </tr>
</table>

**/

