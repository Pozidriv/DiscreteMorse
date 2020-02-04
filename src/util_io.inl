#ifndef _BITS
#include <bits/stdc++.h>
#define _BITS
#endif
#ifndef _GLOBAL
#define _GLOBAL
#include "global.h"
#endif

using namespace std;

inline void narrator(void) {
   cout << endl;
}

template<typename First, typename ... Strings>
inline void narrator(First arg, const Strings&... rest) {
   cout << arg << " ";
   narrator(rest...);
}

inline void log(void) {
   g_log_ptr << endl;
}

template<typename First, typename ... Strings>
inline void log(First arg, const Strings&... rest) {
   g_log_ptr << arg << " ";
   log(rest...);
}

template<typename First, typename ... Strings>
inline void debug(First fnct, const Strings&... rest) {
   if(VERBOSE) {
      string token(fnct);
      if(!(token.substr(0, 6) == "Matrix" || MATRIX_VERBOSE)) {
      } else if(!(token.substr(0, 6) == "Matrix" || MATRIX_VERBOSE)) {
      } else {
         cout << "[DEBUG:" << fnct << "] ";
         narrator(rest...);
      }
   }
}
