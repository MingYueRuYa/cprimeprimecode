/*
 * 向linux 系统中截断信号处理, 处理片段
 * */
#ifdef Q_OS_LINUX
#include "signal.h"
void TermHandler(int sig)
{
  Q_UNUSED(sig);
  QCoreApplication::quit();
}

void IntHandler(int sig)
{
  Q_UNUSED(sig);
  QCoreApplication::quit();
}

/*!
  Linux系统下，初始化Term信号捕获函数，使程序正确处理kill指令。
 */
static bool SetupSignalHandlers()
{
  struct sigaction term;
  term.sa_handler = TermHandler;
  sigemptyset(&term.sa_mask);
  term.sa_flags = SA_RESTART;
  if (sigaction(SIGTERM, &term, 0) > 0) {
	return false;
  }
  term.sa_handler = IntHandler;
  sigemptyset(&term.sa_mask);
  term.sa_flags = SA_RESTART;
  if (sigaction(SIGINT, &term, 0) > 0) {
	return false;
  }
  return true;
}
#endif
