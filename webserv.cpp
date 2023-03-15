#include <sys/socket.h>
#include <errno.h>
#include <stdio.h>

int main(void)
{
	int srv_fd = 0;

	if ((srv_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("error: cannot create socket");
		return (1);
	}
	return (0);
}
