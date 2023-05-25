#include <stdio.h>
#include <stdlib.h>
#include <sys/timex.h>
#include <time.h>

int main (void)
{
  struct timespec rtime;
  struct ntptimeval ntime;
  double runixtime, nunixtime;
  double ntp_divisor = 1e9; 
  struct timex ftimexbuf;
  ftimexbuf.modes = 0 | ADJ_NANO; //https://stackoverflow.com/questions/16063408/does-ntp-gettime-actually-return-nanosecond-precision
  adjtimex(&ftimexbuf);

  // printf ("%d\n", ftimexbuf.status);
  // printf ("%d\n", STA_NANO);
  printf ("STA_NANO status is %d\n", (ftimexbuf.status & STA_NANO));
  if ((STA_NANO & ftimexbuf.status)==0)
  {
    printf ("Nano flag not set ?\n");
    ntp_divisor = 1e6;
    printf ("Setting ntp divisor to %lf\n", ntp_divisor);
  }

  clock_gettime (CLOCK_REALTIME, &rtime);
  ntp_gettime (&ntime);

  runixtime = (double) rtime.tv_sec + (((double) rtime.tv_nsec) / 1e9);
  nunixtime = (double) ntime.time.tv_sec + (((double) ntime.time.tv_usec) / ntp_divisor);

  printf ("Realtime timestamp (s) %ld\n", (long)rtime.tv_sec);
  printf ("NTP timestamp      (s) %ld\n", (long)ntime.time.tv_sec);

  printf ("Realtime timestamp (us or ns ?) %ld\n", (long)rtime.tv_nsec);
  printf ("NTP timestamp      (us or ns ?) %ld\n", (long)ntime.time.tv_usec);

  // printf ("timex time (s)      %ld\n", (long)ftimexbuf.time.tv_sec);
  // printf ("timex time (ns or us) %ld\n", (long)ftimexbuf.time.tv_usec);

  printf ("Full realtime UNIX timestamp is %lf\n", runixtime);
  printf ("Full NTP UNIX timestamp is      %lf\n", nunixtime);

  return 0;
}
