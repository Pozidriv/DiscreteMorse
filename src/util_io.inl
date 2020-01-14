#ifndef BITS
#include <bits/stdc++.h>
#define BITS
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

template<typename First, typename ... Strings>
inline void debug(First fnct, const Strings&... rest) {
   if(VERBOSE) {
      string token(fnct);
      if(!(token.substr(0, 6) == "Matrix" && MATRIX_VERBOSE)) {
      } else if(!(token.substr(0, 6) == "Matrix" && MATRIX_VERBOSE)) {
      } else {
         cout << "[DEBUG:" << fnct << "] ";
         narrator(rest...);
      }
   }
}
