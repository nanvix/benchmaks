#
# MIT License
#
# Copyright (c) 2011-2018 Pedro Henrique Penna <pedrohenriquepenna@gmail.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.  THE SOFTWARE IS PROVIDED
# "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
# LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
# PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
# WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#

source "scripts/arch/mppa256.sh"

# Default parameters.
NCLUSTERS=16
NITERATIONS=5
BUFSIZE=262144

case "$1" in
	mppa256-async)
		echo "Running BareOS Async Microbenchmarks"
		run2                              \
			"benchmark-mppa256-async.img" \
			"/mppa256-async-master"       \
			"$NCLUSTERS $BUFSIZE"         \
		| grep -v "\[nanvix\]"
	;;
	mppa256-portal)
		echo "Running NodeOs Portal Microbenchmarks"
		for kernelname in "broadcast" "gather" "pingpong";
		do
			run2                                               \
				"benchmark-mppa256-portal.img"                 \
				"/mppa256-portal-master"                       \
				"$NCLUSTERS $NITERATIONS $BUFSIZE $kernelname" \
			| grep -v "\[nanvix\]"
		done
	;;
	mppa256-rqueue)
		echo "Running NodeOS Rqueue Microbenchmarks"
		for kernelname in "broadcast" "gather" "pingpong";
		do
			run2                                      \
				"benchmark-mppa256-rqueue.img"        \
				"/mppa256-rqueue-master"              \
				"$NCLUSTERS $NITERATIONS $kernelname" \
			| grep -v "\[nanvix\]"
		done
	;;
	nanvix-mailbox)
		echo "Running Nanvix Unnamed Mailbox Microbenchmarks"
		for kernelname in "broadcast" "gather" "pingpong";
		do
			run2                                      \
				"benchmark-mailbox.img"               \
				"/mailbox-master"                     \
				"$NCLUSTERS $NITERATIONS $kernelname" \
			| grep -v "\[nanvix\]"
		done
	;;
	nanvix-portal)
		echo "Running Nanvix Unnamed Portal Microbenchmarks"
		for kernelname in "broadcast" "gather" "pingpong";
		do
			run2                                               \
				"benchmark-portal.img"                         \
				"/portal-master"                               \
				"$NCLUSTERS $NITERATIONS $BUFSIZE $kernelname" \
			| grep -v "\[nanvix\]"
		done
	;;
	nanvix-rmem)
		echo "Running Nanvix RMem Microbenchmarks"
		for kernelname in "read" "write";
		do
			run2                                               \
				"benchmark-rmem.img"                           \
				"/rmem-master"                                 \
				"$NCLUSTERS $NITERATIONS $BUFSIZE $kernelname" \
			| grep -v "\[nanvix\]"
		done
	;;
	nanvix-sync)
		echo "Running Nanvix Synchronization Point Microbenchmarks"
		for kernelname in "barrier";
		do
			run2                                      \
				"benchmark-sync.img"                  \
				"/sync-master"                        \
				"$NCLUSTERS $NITERATIONS $kernelname" \
			| grep -v "\[nanvix\]"
		done
	;;
	*)
		echo "Usage: run.sh {nanvix-mailbox | nanvix-portal | nanvix-sync}"
		echo "Usage: run.sh {nanvix-rmem}"
		exit 1
	;;
esac


