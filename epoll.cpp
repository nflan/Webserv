#include <stdio.h>     // for fprintf()
#include <unistd.h>    // for close(), read()
#include <sys/epoll.h> // for epoll_create1(), epoll_ctl(), struct epoll_event
#include <string.h>    // for strncmp
#include <iostream>
#define MAX_EVENTS 5
#define READ_SIZE 10

/*
epoll() is a high-performance I/O completion notification interface that allows an application to monitor multiple file 
descriptors/sockets returning readiness information about them.
In other words, it's a system call that monitors multiple input/output events and provides an efficient way to handle a
large number of file descriptors compared to select or poll system call.

Some resources :	https://kaleid-liner.github.io/blog/2019/06/02/epoll-web-server.html
					https://suchprogramming.com/epoll-in-3-easy-steps/
					
*/

int main()
{
	int running = 1, event_count, i;
	size_t bytes_read;
	char read_buffer[READ_SIZE + 1];
	struct epoll_event event, events[MAX_EVENTS];

	/* on epoll : https://copyconstruct.medium.com/the-method-to-epolls-madness-d9d2d6378642
	*/
	int epoll_fd = epoll_create1(0);
	if (epoll_fd == -1) {
		fprintf(stderr, "Failed to create epoll file descriptor\n");
		return 1;
	}

	/*
	EPOLLIN means that the associated file descriptor (fd) is available for read operations. 
	The file descriptor being set here is 0, which typically refers to standard input (stdin).
	This indicates to the epoll instance that the program wants to be notified whenever there is
	data available to be read from standard input.
	*/
	
	event.events = EPOLLIN; 
	event.data.fd = 0;

	/*	
	epoll_ctl() is the function that manages the epoll instance by adding and removing file descriptors from the list to be watched
	The second parameter EPOLL_CTL_ADD instructs epoll to add a new file descriptor to its watch list.
	The third parameter 0 refers to the file descriptor itself we want to add/remove.
	The fourth parameter &event is a pointer to the struct epoll_event which specifies the event types that we want to monitor for this file descriptor.

	In summary, epoll_ctl(epoll_fd, EPOLL_CTL_ADD, 0, &event) is asking the kernel to add a new file descriptor to epoll's event set, where epoll_fd is the epoll file descriptor.

	epoll_ctl() has three operations that we can use:

	EPOLL_CTL_ADD - Add a file descriptor to the monitored set.
	EPOLL_CTL_MOD - Update and modify the monitored set with new settings data.
	EPOLL_CTL_DEL - Remove a file descriptor from the monitored set.
	*/

	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, 0, &event)) {
		fprintf(stderr, "Failed to add file descriptor to epoll\n");
		close(epoll_fd);
		return 1;
	}

	/*
	epoll_wait(epoll_fd, events, MAX_EVENTS, 30000). This function blocks until at least one event occurs
	or the specified timeout (30 seconds in this case) elapses. It returns the number of events that occurred
	and stores
	*/

	while (1) {
		std::cout << "Polling for input..." << std::endl;
		event_count = epoll_wait(epoll_fd, events, MAX_EVENTS, 30000);
		std::cout << "Polling for input..." << event_count << std::endl;
		printf("%d ready events\n", event_count);
		for (i = 0; i < event_count; i++) {
			printf("Reading file descriptor '%d' -- ", events[i].data.fd);
			bytes_read = read(events[i].data.fd, read_buffer, READ_SIZE);
			printf("%zd bytes read.\n", bytes_read);
			read_buffer[bytes_read] = '\0';
			printf("Read '%s'\n", read_buffer);
			if(!strncmp(read_buffer, "stop\n", 5))
			running = 0;
		}
	}

	if (close(epoll_fd)) {
		fprintf(stderr, "Failed to close epoll file descriptor\n");
		return 1;
	}

	std::cout << "OK" << std::endl;
	return 0;
}