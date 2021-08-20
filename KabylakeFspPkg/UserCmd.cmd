@echo off

set  PROJDIR=%~p0
set  PROJDIR=%PROJDIR:~1,-1%

if "%1" == "1" goto UserCmd1
if "%1" == "2" goto UserCmd2
if "%1" == "3" goto UserCmd3
if "%1" == "4" goto UserCmd4
goto End

:UserCmd1
echo Copy FSP binaries to CoreBoot ...
call cp.cmd
echo Build OTM ...
(
  echo cd  /work/peifsp/%PROJDIR%
  echo touch  src/mainboard/intel/lavacanyon/FvFsp.bin
  echo make
) > sshcmd.txt
d:\Prog\ssh\plink.exe -i d:\Prog\ssh\id_rsa mxma@192.168.0.80 -m %~dp1\sshcmd.txt
copy T:\peifsp\%PROJDIR%\build\coreboot.rom  d:\coreboot.rom
goto End

:UserCmd2
echo EMPTY
goto End

:UserCmd3
echo Burn BIOS 512 image, please waiting ...
"c:\Program Files (x86)\DediProg\SF100\dpcmd" -g 2 --auto=C:\ItpBurn\Release\LavaCanyon_top512k.bin -a 0x700000 -l 0x100000
goto End

:UserCmd4
echo Burn Coreboot 512 image, please waiting ...
"c:\Program Files (x86)\DediProg\SF100\dpcmd" -g 2 --auto=T:\peifsp\%PROJDIR%\build\coreboot.rom -i -a 0x700000 -l 0x100000
goto End

:End
echo.

