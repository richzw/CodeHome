Source: http://ithare.com/once-again-on-tcp-vs-udp/?utm_source=twitterfeed&utm_medium=twitter

------------------------------

IP: just packets, nothing more
-------------

Within the IP stack, it is the job of the hosts to provide delivery guarantees. Nothing is done in this regard en route.

UDP: datagrams ~= packets
-------------

UDP is a very basic protocol which runs on top of IP. Actually, it is that basic, that when UDP datagrams run on top of IP packets, 
there is always 1-to-1 correspondence between the two.

As UDP datagrams simply run on top of IP packets, and IP packets can be lost, UDP datagrams can be lost too.


TCP: stream != packets
-------------

- TCP interprets all the data to be communicated between two hosts as two streams (one stream going from host A to host B, and another going in the opposite direction)
- whenever the host calls the TCP function send(), the data is pushed into the stream
- the TCP stack keeps a buffer (usually 2K–16K in size) on the sending side; all the data pushed to the stream goes to this buffer. If the buffer is full, send() won’t return until there is enough space in the buffer
- Data from the buffer is sent over the IP as TCP packets; each TCP packet consists of an IP packet, a TCP header, and TCP data. TCP data within a TCP packet is data from the sending TCP buffer; data is not removed from the TCP buffer on the sending side at the moment when TCP packet is sent (!)
- After the receiving side gets the TCP packet, it sends a TCP packet in the opposite direction, with a TCP header with the ACK bit set – an indication that a certain portion of the data has been received. On receiving this ACK packet, the sender may remove the corresponding piece from its TCP sending buffer.3
- Data received goes to another buffer on the receiving side; again, its size is usually of the order of 2K–16K. This receiving buffer is where the data for the recv() function comes from.
- If the sending side doesn’t receive an ACK in a predefined time – it will re-send the TCP packet. This is the primary mechanism by which TCP guarantees delivery in case of the packet being lost


