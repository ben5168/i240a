#include <cctype>

#include "digit-sum.hh"

int
digitSum(const char* str)
{
      int acc = 0;
      bool wantDigit = true;
      for(const char* p = str; p; ++p) {
            int c = *p;
            if(isdigit(c)) {
                  if(wantDigit) {
                        acc += c - '0';
                        wantDigit = false;
                  }
            else {
                  break;
                  }
            }
            else if(c == '+') {
                  if(wantDigit) break;
                  wantDigit = true;
            }
            else if(isspace(c)) {
                  continue;
            }
            else {
                  break;
            }    
      }
      return acc;
}
