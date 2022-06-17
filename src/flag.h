#ifndef FLAG_H
#define FLAG_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DEFAULT_PORT_NUMBER 8081
#define DEFAULT_WEBROOT "./www"

static int get_port_number(char *arg_port)
{
    int port_number = strtol(arg_port, &arg_port, 10);
    if (port_number <= 0 || port_number > 65535) {
        port_number = DEFAULT_PORT_NUMBER;
    }
    return port_number;
}

struct cmd_config {
    unsigned short int port;
};

static struct cmd_config *get_config_by_cmd(int argc, char **argv)
{
    int cmdopt = 0;
    struct cmd_config *cfg =
        (struct cmd_config *) malloc(sizeof(struct cmd_config));

    while ((cmdopt = getopt(argc, argv, "p:r:")) != -1) {
        switch (cmdopt) {
        case 'p':
            cfg->port = get_port_number(optarg);
            break;
        case '?':
            fprintf(stderr, "Illeggal option: -%c\n",
                    isprint(optopt) ? optopt : '#');
            exit(EXIT_FAILURE);
            break;
        default:
            fprintf(stderr, "Not supported option\n");
            break;
        }
    }
    return cfg;
}

#endif