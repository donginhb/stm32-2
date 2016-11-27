
#ifndef __HTTPD_FSDATA_H__
#define __HTTPD_FSDATA_H__

#include "uip.h"

struct fsdata_file 
{
  const struct fsdata_file *next;
  const char *name;
  const char *data;
  const int len;
#ifdef HTTPD_FS_STATISTICS
#if HTTPD_FS_STATISTICS == 1
  u16_t count;
#endif /* HTTPD_FS_STATISTICS */
#endif /* HTTPD_FS_STATISTICS */
};

struct httpd_fsdata_file_noconst 
{
  struct httpd_fsdata_file *next;
  char *name;
  char *data;
  int len;
#ifdef HTTPD_FS_STATISTICS
#if HTTPD_FS_STATISTICS == 1
  u16_t count;
#endif /* HTTPD_FS_STATISTICS */
#endif /* HTTPD_FS_STATISTICS */
};

#endif /* __HTTPD_FSDATA_H__ */
