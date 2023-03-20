// create epoll instance
int epoll_fd = epoll_create1(0);
if (epoll_fd == -1) {
    perror("Failed to create epoll file descriptor");
    exit(EXIT_FAILURE);
}

// add listening socket to epoll instance
struct epoll_event event;
event.events = EPOLLIN | EPOLLET;  // enable edge-triggered mode
event.data.fd = listen_fd;
if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &event) == -1) {
    perror("Failed to add listening socket to epoll");
    exit(EXIT_FAILURE);
}

// wait for events
while (1) {
    struct epoll_event events[MAX_EVENTS];
    int num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
    if (num_events == -1) {
        perror("Failed to wait for events with epoll");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num_events; i++) {
        int fd = events[i].data.fd;
        if (fd == listen_fd) {
            // handle incoming connection
            struct sockaddr_in client_addr;
            socklen_t client_addr_len = sizeof(client_addr);
            int client_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &client_addr_len);
            if (client_fd == -1) {
                perror("Failed to accept incoming connection");
                continue;
            }

            // add client socket to epoll instance
            struct epoll_event client_event;
            client_event.events = EPOLLIN | EPOLLET;  // enable edge-triggered mode
            client_event.data.fd = client_fd;
            if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &client_event) == -1) {
                perror("Failed to add client socket to epoll");
                close(client_fd);
                continue;
            }
        } else {
            // handle incoming data on client socket
            // read data from client socket
            char buffer[BUFFER_SIZE];
            int bytes_read = recv(fd, buffer, BUFFER_SIZE, 0);
            if (bytes_read == -1) {
                perror("Failed to read from client socket");
                continue;
            } else if (bytes_read == 0) {
                // client closed connection
                close(fd);
                epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, NULL);  // remove client socket from epoll instance
            } else {
                // process data from client socket
                // ...
            }
        }
    }
}
