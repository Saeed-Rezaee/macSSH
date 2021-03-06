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

#ifndef BUFFER_H
#define BUFFER_H

#include "ssh-packet.h"
#include "includes.h"

/* Buffer to hold in- and outgoing data */
struct buffer {
	
	void (*buf_add)(struct buffer *, struct packet *pck);
        
	int (*buf_isempty)(struct buffer *buf);
	int (*buf_len)(struct buffer *buf);
	
	struct packet* (*buf_get)(struct buffer *buf);
        struct packet* (*buf_peak)(struct buffer *buf);
        
        struct packet *packets;

};

struct buffer* buf_new();
void buf_free(struct buffer *buf);

#endif /* BUFFER_H */

