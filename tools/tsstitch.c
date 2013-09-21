/*
 * libtss-1.0 - libtss.c
 * Utility for communicating with Apple's TSS server
 *
 * Copyright (c) 2010 Joshua Hill. All Rights Reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#define _DEBUG

#include <plist/plist.h>
#include <libtss-1.0/libtss.h>
#include <libcrippy-1.0/libcrippy.h>

static struct option longopts[] = {
	{ "help",         no_argument,         NULL,   'h' },
	{ "verbose",      no_argument,         NULL,   'v' },
	{ "ipsw",         required_argument,   NULL,   'i' },
	{ "apple",        no_argument,         NULL,   'a' },
	{ "cydia",        no_argument,         NULL,   'c' },
	{ "nonce",        required_argument,   NULL,   'n' },
	{ "ecid",         required_argument,   NULL,   'e' },
	{ NULL, 0, NULL, 0 }
};

void usage(int argc, char* argv[]) {
	char* name = strrchr(argv[0], '/');
	printf("Usage: %s [OPTIONS]\n", (name ? name + 1 : argv[0]));
	printf("Copyright 2010-2013, Joshua Hill\n");
	printf("Utility for communicating with Apple's TSS server.\n");
	printf("  General\n");
	printf("    -h, --help      \tprints usage information\n");
	printf("    -v, --verbose   \tprint debuging info while running\n");
	printf("    -i, --ipsw FILE \tuse firmware files from this FILE\n");
	printf("    -a, --apple     \tuse Apple's signing servers\n");
	printf("    -c, --cydia     \tuse Cydia's signing servers\n");
	printf("    -n, --nonce     \tNonce to pass to Apple's servers\n");
	printf("    -e, --ecid      \tECID of the device you're trying to sign\n");
	printf("\n");
}



int main(int argc, char* argv[]) {
	int i = 0;
	int err = 0;
	int opt = 0;
	int optindex = 0;

	// General
	int verbose = 0;
	char* ipsw_path = NULL;
	char* ecid_string = NULL;
	char* nonce_string = NULL;
	int use_cydia_server = 0;
	int use_apple_server = 0;

	while ((opt = getopt_long(argc, argv, "hvi:acn:e:", longopts, &optindex)) > 0) {
		switch (opt) {
		/////////////////////////////////////////
		/// General Options
		/// --help
		case 'h':
			usage(argc, argv);
			return 0;

		/// --verbose
		case 'v':
			verbose++;
			break;

		/// --ipsw
		case 'i':
			ipsw_path = strdup(optarg);
			break;

		/// --apple
		case 'a':
			if(use_cydia_server) {
				error("You can only use either -a or -c at once\n");
				return -1;
			} else {
				use_apple_server = 1;
			}
			break;

		/// --cydia
		case 'c':
			if(use_apple_server) {
				error("You can only use either -a or -c at once\n");
				return -1;
			} else {
				use_cydia_server = 1;
			}
			break;

		/// --nonce
		case 'n':
			nonce_string = strdup(optarg);
			break;

		/// --ecid
		case 'e':
			ecid_string = strdup(optarg);
			break;

		/////////////////////////////////////////
		/// Unknown Option
		default:
			usage(argc, argv);
			return -1;
		}
	}

	if ((argc-optind) == 0) {
		argc -= optind;
		argv += optind;

	} else {
		usage(argc, argv);
		return -1;
	}

	// Grab build manifest
	// Get Nonce
	// Send request
	// Receive response
	// Stitch images
	// Rebuild IPSW

	if(ipsw_path) free(ipsw_path);
	return 0;
