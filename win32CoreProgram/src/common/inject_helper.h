#pragma once

#include <Windows.h>

#include "noncopyable.h"


class InjectHelper : public XIBAO::NonCopyable
{
public:
  InjectHelper(DWORD dwProcessID, PCWSTR pszLibFile);
  ~InjectHelper();

private:
  bool _inject();
  bool _eject();

private:
  DWORD _dwProcessId;
  PCWSTR _pszLibFile;
};

