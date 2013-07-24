//http://www.linuxjournal.com/article/6345?page=0,0

if(fcntl(fd, F_SETSIG, RT_SIGNAL_LEASE) == -1) {
    perror("kernel lease set signal");
    return -1;
}

tmp_buf = mmap(file, len);
write(socket, tmp_buf, len);

/* l_type can be F_RDLCK F_WRLCK */
if(fcntl(fd, F_SETLEASE, l_type)){
    perror("kernel lease set type");
    return -1;
}


//about sendfile()

//On Linux, sendfile() depends on the TCP_CORK socket option to avoid undesirable packet boundaries
//TCP_CORK and TCP_NODELAY option on the socket, which disables the Nagle algorithm.
Set TCP_CORK before sending a series of data that should be considered as a single message and 
set TCP_NODELAY before sending short messages that should be sent immediately.

//http://blog.superpat.com/2010/06/01/zero-copy-in-linux-with-sendfile-and-splice/
ssize_t do_sendfile(int out_fd, int in_fd, off_t offset, size_t count) {
    ssize_t bytes_sent;
    size_t total_bytes_sent = 0;
    while (total_bytes_sent < count) {
        if ((bytes_sent = sendfile(out_fd, in_fd, &offset,
                count - total_bytes_sent)) <= 0) {
            if (errno == EINTR || errno == EAGAIN) {
                // Interrupted system call/try again
                // Just skip to the top of the loop and try again
                continue;
            }
            perror("sendfile");
            return -1;
        }
        total_bytes_sent += bytes_sent;
    }
    return total_bytes_sent;
}

//...

// Send 'len' bytes starting at 'offset' from 'file_fd' to 'socket_fd'
do_sendfile(socket_fd, file_fd, offset, len);


// Our pipe - a pair of file descriptors in an array - see pipe()
static int pipefd[2];

//...

ssize_t do_recvfile(int out_fd, int in_fd, off_t offset, size_t count) {
    ssize_t bytes, bytes_sent, bytes_in_pipe;
    size_t total_bytes_sent = 0;

    // Splice the data from in_fd into the pipe
    while (total_bytes_sent < count) {
        // solve issue:
        //makes the first splice() call hang when you ask for all of the data on the socket. 
        //  simply limiting the data read from the socket to 16k. 
        if ((bytes_sent = splice(in_fd, NULL, pipefd[1], NULL,
            MIN(count - total_bytes_sent, 16384), 
            SPLICE_F_MORE | SPLICE_F_MOVE)) <= 0) {
            if (errno == EINTR || errno == EAGAIN) {
                // Interrupted system call/try again
                // Just skip to the top of the loop and try again
                continue;
            }
            perror("splice");
            return -1;
        }

        // Splice the data from the pipe into out_fd
        bytes_in_pipe = bytes_sent;
        while (bytes_in_pipe > 0) {
            if ((bytes = splice(pipefd[0], NULL, out_fd, &offset, bytes_in_pipe,
                    SPLICE_F_MORE | SPLICE_F_MOVE)) <= 0) {
                if (errno == EINTR || errno == EAGAIN) {
                    // Interrupted system call/try again
                    // Just skip to the top of the loop and try again
                    continue;
                }
                perror("splice");
                return -1;
            }
            bytes_in_pipe -= bytes;
        }
        total_bytes_sent += bytes_sent;
    }
    return total_bytes_sent;
}

//...

// Setup the pipe at initialization time
if ( pipe(pipefd) < 0 ) {
    perror("pipe");
    exit(1);
}

//...

// Send 'len' bytes from 'socket_fd' to 'offset' in 'file_fd'
do_recvfile(file_fd, socket_fd, offset, len);
