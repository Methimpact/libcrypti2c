/* -*- mode: c; c-file-style: "gnu" -*-
 * Copyright (C) 2014 Cryptotronix, LLC.
 *
 * This file is part of libcrypti2c.
 *
 * libcrypti2c is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * libcrypti2c is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libcrypti2c.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "log.h"

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <assert.h>
#include <syslog.h>

static enum CI2C_LOG_LEVEL CURRENT_LOG_LEVEL = INFO;

int ci2c_log_level_to_syslog (enum CI2C_LOG_LEVEL lvl)
{
  int rsp = LOG_DEBUG;

  switch (lvl)
    {
    case EMERG:
      rsp = LOG_EMERG;
      break;
    case ALERT:
      rsp = LOG_ALERT;
      break;
    case CRIT:
      rsp = LOG_CRIT;
      break;
    case ERR:
      rsp = LOG_ERR;
      break;
    case WARNING:
      rsp = LOG_WARNING;
      break;
    case NOTICE:
      rsp = LOG_NOTICE;
      break;
    case INFO:
      rsp = LOG_INFO;
      break;
    case DEBUG:
    default:
      rsp = LOG_DEBUG;
      break;
    }

  return rsp;
}


void
CI2C_LOG(enum CI2C_LOG_LEVEL lvl, const char *format, ...)
{
  if (lvl <= CURRENT_LOG_LEVEL)
    {
      va_list args;
      va_start(args, format);

      vsyslog (ci2c_log_level_to_syslog (lvl), format, args);

      va_end(args);

    }
}

void
ci2c_set_log_level(enum CI2C_LOG_LEVEL lvl)
{
  CURRENT_LOG_LEVEL = lvl;

  openlog ("libcrypti2c", 0, LOG_USER);

}

void
ci2c_print_hex_string(const char *str, const uint8_t *hex, unsigned int len)
{

  if (CURRENT_LOG_LEVEL < DEBUG)
    return;

  unsigned int i;
  const int MAX_USER_STR_LEN = 100;

  const int TOTAL_LEN = strnlen (str, MAX_USER_STR_LEN) + 3 + (len * 5) + 1;

  assert(NULL != str);
  assert(NULL != hex);

  char *msg = (char *) ci2c_malloc_wipe (TOTAL_LEN);

  int offset = sprintf (msg, "%s : ", str);

  for (i = 0; i < len; i++)
    {
      offset = offset + sprintf (msg + offset, "0x%02X ", hex[i]);
    }

  sprintf (msg + offset, "%s", "\n");

  CI2C_LOG(DEBUG, "%s", msg);

  ci2c_free_wipe (msg, TOTAL_LEN);

}

bool
ci2c_is_debug (void)
{
  return (DEBUG == CURRENT_LOG_LEVEL) ? true : false;
}
