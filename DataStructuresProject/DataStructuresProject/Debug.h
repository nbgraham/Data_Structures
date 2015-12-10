#ifndef DEBUG
#endif

#ifndef dbg
#ifdef DEBUG
#define dbg  cout<<
#else
#define dbg   if(0)
#endif
#endif
