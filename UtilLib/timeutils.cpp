#include "timeutils.h"


std::string getcurrentDateTime(char* Format)
{
     //possible Elements in Format (can be combined arbitrarily:
     // '%' has to be added before the Letter
     // The string can be filled with other elements like "." or "-" to differentiate Time, Date, Year etc.
     // YEAR:
     //%Y : Year as decimal number
     //%y : last two digits of year [0; 99]
     //%C: First two digits of year [0; 99]
     // MONTH:
     //%b : abbreviated Month (example: Dec)
     //%B : Full Month name
     //%m : Month as a decimal number [01; 12]
     // WEEK:
     //%U : week of the Year as a decimal number [00, 53]
     // DAY:
     //%d : day of the month [01; 31]
     //%j : day of the year [001; 366]
     //%a : abbreviated weekday eg. Fri
     //%A : full weekday
     //%w : weekday as decimal number [0; 6] (sun is 0)
     // HOUR, MINUTE, SECOND
     //%H : hour as decimal number [0; 23]
     //%M : minute as decimal number [00; 59]
     //%S : second as decimal number [00, 60]


      time_t now = time(0);
      struct tm tstruct;
      char buf[80];
      tstruct = *localtime(&now);
      now += 1*0*0;
	

      strftime(buf, sizeof(buf), Format , &tstruct);
      return buf;
}
 
