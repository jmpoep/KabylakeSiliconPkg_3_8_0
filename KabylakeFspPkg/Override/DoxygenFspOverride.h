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
 @page FSP Package override

  FSP Override tags (FSPO-xxxx) document issues that Royal Park team has resolved with an override of Royal Park.
  
  The Active FSPO table lists every issue which is currently resolved with an override. It is a catalog of all such existing overrides.

  The Retired FSPO table lists issues which previously required such overrides. It is purely historical as these overrides have all been deleted (are no longer needed).
<BR>
<CENTER>
<STRONG>Active FSPOs</STRONG>
<BR>in KabylakeFspPkg/Override
</CENTER>

<table border="1" style="width:1200px">
<tr>
  <th>Tag</th>
  <th>Client HSD</th>
  <th>BP HSD</th>
  <th>Status / Planned EOL</th>
  <th>Description</th>
</tr>
  <tr> <td>FSPO-0001</td> <td></td>    <td></td>        <td></td>           <td>1604143872:During POST if system BIOS pass NULL of UPD region pointer to FspMemoryInit & FspSiliconInit then System will hang.</td> </tr>
  <tr> <td>FSPO-0002</td> <td></td>    <td></td>        <td></td>           <td>[1604116217] [KBL FSP] Enable MTRR Programming from FSP wrapper</td> </tr>
  <tr> <td>FSPO-0003</td> <td></td>    <td></td>        <td></td>           <td>1604155579: [Kabylake.other] Need to change the FSP UPD signature to align with FSP2.0 spec</td> </tr>
  <tr> <td>FSPO-0004</td> <td></td>    <td></td>        <td></td>           <td>1604155579: [Kabylake.other] Add SpecVersion in FSP_INFO_HEADER</td> </tr>
  <tr> <td>FSPO-0005</td> <td></td>    <td></td>        <td></td>           <td>1504388079: [KBL FSP] Fail to open bsf file by BCT due to invalid string found in BSE OPTION field</td> </tr>
  <tr> <td>FSPO-0006</td> <td></td>    <td></td>        <td></td>           <td>2201882860: [KBL] FV Alignment in EDK2 Chain-of-Trust Bypass</td> </tr>
</table>

<BR>
<CENTER>
<STRONG>Retired FSPOs</STRONG>
<BR>formerly in KabylakeFspPkg/Override
</CENTER>

<table border="1" style="width:1200px">
<tr>
  <th>Tag</th>
  <th>Client HSD</th>
  <th>BP HSD</th>
  <th>Actual EOL</th>
  <th>Description</th>
</tr>
  <tr> <td>FSCO-0001</td> <td></td>    <td></td>        <td></td>           <td>1504005677:Enabling Performance measurement for FSP Binary - Publish FSP performance records through FPDT. Other tags used SICO-KBL-0001, RPPO-KBL-0045</td> </tr>
  <tr> <td>FSCO-0002</td> <td></td>    <td></td>        <td></td>           <td>1604100118:Rename KBL FSP UPD Structure to match version 2.0 Draft 5</td> </tr>
  </table>

**/

