; BsrPlayerCloud.nsi
;
; This script is based on example1.nsi, but it remember the directory, 
; has uninstall support and (optionally) installs start menu shortcuts.
;
; It will install example2.nsi into a directory that the user selects,

;--------------------------------

;XPStyle on

SetCompressor /SOLID lzma

; MUI 1.67 compatible ------
!include "MUI.nsh"

; MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"


!insertmacro MUI_PAGE_INSTFILES

; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES


; Language files
!insertmacro MUI_LANGUAGE "SimpChinese"



; The name of the installer
Name "SipGatewayServer"

; The file to write
OutFile "SipGatewayServer.exe"

; The default installation directory
InstallDir $PROGRAMFILES\SipGatewayServer

; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
InstallDirRegKey HKLM "Software\SipGatewayServer" "Install_Dir"

; Request application privileges for Windows Vista
RequestExecutionLevel admin

;--------------------------------

; Pages
;Page components
;Page directory
;Page instfiles
;UninstPage uninstConfirm
;UninstPage instfiles

;--------------------------------

; The stuff to install
Section "SipGatewayServer (required)"

  SectionIn RO
  
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
 
  ; Put file there
	File /r bin\*.*
	
	CreateDirectory "$SMPROGRAMS\SipGatewayServer"
  CreateShortCut  "$SMPROGRAMS\SipGatewayServer\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  CreateShortCut "$SMPROGRAMS\SipGatewayServer\SipGatewayServer (MakeNSISW).lnk" "$INSTDIR\SipAgent.exe"
  
  
  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\SipGatewayServer "Install_Dir" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\SipGatewayServer" "DisplayName" "NSIS SipGatewayServer"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\SipGatewayServer" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\SipGatewayServer" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\SipGatewayServer" "NoRepair" 1
  WriteUninstaller "uninstall.exe"
  
SectionEnd


;--------------------------------

; Uninstaller

Section "Uninstall"
	
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\SipGatewayServer"
  DeleteRegKey HKLM SOFTWARE\SipGatewayServer

  ; Remove files and uninstaller
  ;Delete $INSTDIR\BsrPlayerCloud.nsi
  ;Delete $INSTDIR\uninstall.exe
	Delete "$INSTDIR\*.*"
	RMDir /r "$INSTDIR"

  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\SipGatewayServer\*.*"

  ; Remove directories used
  RMDir "$SMPROGRAMS\SipGatewayServer"
  RMDir "$INSTDIR"

SectionEnd
