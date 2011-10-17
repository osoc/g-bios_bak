// fix the wolrd!
#include <sysconf.h>
#include <getopt.h>

static void usage(void)
{
	printf("Usage:\n"
		"\t-r <all|net|boot>: reset system configuration.\n");
}

int main(int argc, char *argv[])
{
	int ret, opt;
	BOOL reset_all = FALSE;
	char *arg;

	while ((opt = getopt(argc, argv, "r:h", &arg)) != -1)
	{
		switch (opt)
		{
		case 'r':
			if (!strcmp(arg, "all"))
			{
				reset_all = TRUE;
				printf("reseting all configuration to default!");
			}
			else if (!strcmp(arg, "net"))
			{
				printf("reseting network configuration to default!");
			}
			else if (!strcmp(arg, "boot"))
			{
				printf("reseting Linux configuration to default!");
			}
			else
			{
				usage();
				return -EINVAL;
			}
			break;

		default:
			usage();
			return -EINVAL;
		}
	}

	ret = sysconf_save();

	return ret;
}
