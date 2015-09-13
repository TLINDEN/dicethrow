#
#    This file is part of dicethrow
#
#    Copyright (C) 2015 T.v.Dein.
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#    You can contact me by mail: <tom AT vondein DOT org>.

CFLAGS   = -Wall -Wextra -Werror -O1 -g
LDFLAGS  =
OBJS     = dicethrow.o randfile.o tossing.o debug.o
DST      = dicethrow
PREFIX   = /usr/local
UID      = root
GID      = 0
MAN      = dicethrow.1
POD      = dicethrow.pod


all: $(DST)

$(DST): $(OBJS)
	gcc $(OBJS) -o $(DST)

%.o: %.c
	gcc -c $(CFLAGS) $*.c -o $*.o

clean:
	rm -f *.o $(DST)

man:
	pod2man $(POD) > $(MAN)

install: $(DST)
	install -d -o $(UID) -g $(GID) $(PREFIX)
	install -d -o $(UID) -g $(GID) $(PREFIX)/sbin
	install -d -o $(UID) -g $(GID) $(PREFIX)/man/man1
	install -o $(UID) -g $(GID) -m 555 $(DST) $(PREFIX)/sbin/
	install -o $(UID) -g $(GID) -m 444 $(MAN) $(PREFIX)/man/man1/
