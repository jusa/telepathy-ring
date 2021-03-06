/*
 * test-modem.c - A check-based test runner for the modem library
 *
 * Copyright (C) 2008-2010 Nokia Corporation
 *   @author Pekka Pessi <first.surname@nokia.com>
 *
 * This work is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This work is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this work; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "config.h"

#include <test-common.h>

#include "test-modem.h"

#include <glib.h>
#include <stdlib.h>

#include <modem/debug.h>

#include <stdio.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
  struct common_args *args;
  int failed = 0;

  Suite *suite = suite_create("Unit tests for the modem library");
  SRunner *runner;

  modem_debug_set_flags_from_env();
  args = parse_common_args(argc, argv);

  filter_add_tcases(suite, modem_requests_tcases, args->tests);
  /*filter_add_tcases(suite, modem_sms_tcases, args->tests);*/
  filter_add_tcases(suite, modem_sim_tcases, args->tests);
  filter_add_tcases(suite, modem_tones_tcases, args->tests);
  filter_add_tcases(suite, modem_call_service_tcases, args->tests);
  filter_add_tcases(suite, modem_call_tcases, args->tests);

  runner = srunner_create(suite);

  if (args->xml)
    srunner_set_xml(runner, args->xml);
  srunner_run_all(runner, CK_ENV);

  failed = srunner_ntests_failed(runner);
  free_common_args(args);
  srunner_free(runner);

  exit(failed ? EXIT_FAILURE : EXIT_SUCCESS);
}
