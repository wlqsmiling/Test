#include <stdio.h>
#include <time.h>
#include <sys/time.h>

int main() {
   time_t t;
   struct tm *tm_info;
   time(&t);
   tm_info = localtime(&t);

   printf("Current timezone:%s\n",tm_info->tm_isdst ? tzname[1]:tzname[0]);

    return 0;
}
