add this to main.cpp, to activate console on windows

#ifdef USE_WIN32_CONSOLE
AllocConsole();
freopen("CONIN$", "r", stdin);
  freopen("CONOUT$", "w", stdout);
freopen("CONOUT$", "w", stderr);
#endif
