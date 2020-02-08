#ifndef _BITS
#include <bits/stdc++.h>
#define _BITS
#endif
#ifndef _GLOBAL
#define _GLOBAL
#include "global.h"
#endif

// Add verboses as you want functions to shut up
// Don't forget to modify the .inl file accordingly
// Make sure you keep the precedence when you add new verboses
const int VERBOSE = 1;
const int MATRIX_VERBOSE = 0;
const int TWO_GEN_VERBOSE = 0;
const int TWO_GEN_INLINE_VERBOSE = 0;

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
   F_log << endl;
}

template<typename First, typename ... Strings>
inline void log(First arg, const Strings&... rest) {
   F_log << arg << " ";
   log(rest...);
}

template<typename First, typename ... Strings>
inline void debug(First fnct, const Strings&... rest) {
   if(VERBOSE) {
      string token(fnct);
      if(token.substr(0, 6) == "Matrix" && !MATRIX_VERBOSE) {
      } else if(token.substr(0, 7) == "two_gen" && !TWO_GEN_VERBOSE) {
      } else if(token.substr(0, 14) == "two_gen|inList" && !TWO_GEN_INLINE_VERBOSE) {
      } else {
         cout << "[DEBUG:" << fnct << "] ";
         narrator(rest...);
      }
   }
}
