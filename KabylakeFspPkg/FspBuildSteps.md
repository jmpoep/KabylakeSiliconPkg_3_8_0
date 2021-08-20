Intel is a trademark or registered trademark of Intel Corporation or its
subsidiaries in the United States and other countries.
*Other names and brands may be claimed as the property of others.
Copyright (c) 2016 - 2017, Intel Corporation. All rights reserved.

# FSP build steps for building Kabylake FSP binary

In order to build Kabylake FSP binary, following packages needs to be
downloaded along with the FSP SDK open source packages
* KabylakeFspPkg --> contains all the Kabylake FSP Platform code
* KabylakeSiliconPkg --> contains all the Kabylake Silicon initialization code
* ClientSiliconPkg   --> contains common code for Client Silicon

Override folder under KabylakeFspPkg takes precedence over the downloaded
versions of the packages. *build_rule.template* and *tools_def.template* under
*KabylakeFspPkg/Override/BaseTools/Conf* has to be used before calling the
*bld.cmd* under KabylakeFspPkg.

Please refer the usage notes of bld.cmd for more details

## FSP SDK open source packages and hash versions
SDK open source packages needed for building this version of FSP can be
downloaded through GitHub from the links and versions mentioned below

Packages            | Links & Hash Versions
--------------------|-----------------------------------------------------------
BaseTools.Win32     | https://github.com/tianocore/edk2-BaseTools-win32.git f0c97b7716ce92f1fc657f87f29bcc9170e5eb1f
BaseTools, IntelFsp2Pkg, IntelFsp2WrapperPkg, MdePkg, MdeModulePkg, UefiCpuPkg     | https://github.com/tianocore/edk2/tree/UDK2015 3c40d6b0ef43ce57ebc97d1bffa1ee250732de2e
