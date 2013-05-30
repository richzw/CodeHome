
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
