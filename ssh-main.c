/*
    This file is part of macSSH
    
    Copyright 2016 Daniel Machon

    SSH program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "includes.h"
#include "build.h"
#include "misc.h"
#include "ssh-session.h"
#include "util.h"
#include "ssh-options.h"
#include "kex.h"
#include "dbg.h"
#include "keys.h"

void ssh_version()
{
	printf("SSH version: %s\n", SSH_VERSION);
	printf("Build defs: %s\n", SSH_DEFS);
}

void ssh_help()
{
	printf("SSH [OPTIONS...] {COMMAND} ...\n\n"
		"Query or send control commands to SSH.\n\n"
		"  -h --help			Show this help\n"
		"     --version			Show version and CPP definitions\n"
		"  -v --verbose			Be more verbose\n"
		"     --debug			Print extra debug information during runtime\n"
		"\n"
		"  -p --port			Specify remote port\n"
		"  -k --key			Create PK key (rsa or dss)\n"
		);
}

int ssh_parse_argv(int argc, char **argv)
{

	enum {
		ARG_FAIL = 0x100,
		ARG_VERSION,
		ARG_VERBOSE,
		ARG_DEBUG,
		ARG_HELP,
		ARG_PORT,
		ARG_KEY,
	};

	static const struct option options[] = {
		{ "help", no_argument, NULL, 'h'},
		{ "version", no_argument, NULL, ARG_VERSION},
		{ "verbose", no_argument, NULL, ARG_VERBOSE},
		{ "debug", no_argument, NULL, ARG_DEBUG},
		{ "port", required_argument, NULL, ARG_PORT},
		{ "key", required_argument, NULL, ARG_KEY},
		{}
	};


	int c;
	while ((c = getopt_long(argc, argv, "hv:p:k:", options, NULL)) >= 0) {
		switch (c) {
		case 'h':
			ssh_help();
			return 0;
		case 'v':
			return 0;
		case 'p':
			argv_options.server_port = 22;
		case 'k':
			ssh_generate_rsa_key();
			return 0;
		case ARG_HELP:
			ssh_help();
			return 0;
		case ARG_VERSION:
			ssh_version();
			return 0;
		case ARG_VERBOSE:
			argv_options.verbose = 1;
			break;
		case ARG_DEBUG:
			argv_options.debug = 1;
			break;
		case ARG_KEY:
			ssh_generate_rsa_key();
			return 0;
		default:
			ssh_help();
			return 0;
		}
	}

	return 1;
}

/*
 * Client main
 */
int main(int argc, char **argv)
{
	if (!ssh_parse_argv(argc, argv))
		return EXIT_SUCCESS;

	/* Setup session state */
	session_init(&ses);
        
        client_session_loop();

	session_free(&ses);

	return(EXIT_SUCCESS);
}

