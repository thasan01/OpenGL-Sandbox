@echo off
IF NOT DEFINED VCPKG_REPO (
  ECHO ERROR: Variable VCPKG_REPO is not defined.
  GOTO completed
) ELSE (
  ECHO VCPKG_REPO:	%VCPKG_REPO%	
)

ECHO aaa
:completed