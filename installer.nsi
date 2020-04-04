;NSIS Modern User Interface
;Basic Example Script
;Written by Joost Verburg
;Customized for Xotepad by Felipe Apablaza

;--------------------------------
;Include Modern UI

  !include "MUI2.nsh"

;--------------------------------
;General

  ;Name and file
  Name "Xotepad"
  OutFile "XotepadSetup.exe"
  Unicode True

  ;Default installation folder
  InstallDir "$LOCALAPPDATA\Xotepad"
  
  ;Get installation folder from registry if available
  # InstallDirRegKey HKCU "Software\Modern UI Test" ""

  ;Request application privileges for Windows Vista
  RequestExecutionLevel user

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_LICENSE "${NSISDIR}\Docs\Modern UI\License.txt"
  !insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  
;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Sections
Section "Xotepad Core" SecDummy
  SetOutPath "$INSTDIR"
  
  ;ADD YOUR OWN FILES HERE...
  File ".cmake\component\Xotepad\Release\SciLexer.dll"
  File ".cmake\component\Xotepad\Release\Xotepad.exe"
  
  ;Store installation folder
  # WriteRegStr HKCU "Software\Modern UI Test" "" $INSTDIR
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"
SectionEnd

;--------------------------------
;Descriptions

  ;Language strings
  LangString DESC_SecDummy ${LANG_ENGLISH} "The editor core executable module"

  ;Assign language strings to sections
  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${SecDummy} $(DESC_SecDummy)
  !insertmacro MUI_FUNCTION_DESCRIPTION_END

;--------------------------------
;Uninstaller Section

Section "Uninstall"
  ;ADD YOUR OWN FILES HERE...
  Delete "$INSTDIR\Uninstall.exe"
  Delete "$INSTDIR\SciLexer.dll"
  Delete "$INSTDIR\Xotepad.exe"
  RMDir "$INSTDIR"

  # DeleteRegKey /ifempty HKCU "Software\Modern UI Test"
SectionEnd
