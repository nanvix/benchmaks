#
# MIT License
#
# Copyright(c) 2011-2020 The Maintainers of Nanvix
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

# Builds everything.
all: all-heartbeat all-barrier all-lookup all-pgfetch all-msync

# Cleans up build objects.
clean: clean-heartbeat clean-barrier clean-lookup clean-pgfetch clean-msync

# Cleans up everything.
distclean: distclean-heartbeat distclean-barrier distclean-lookup \
	distclean-pgfetch distclean-msync

#===============================================================================
# Heart Beat
#===============================================================================

# Builds benchmark.
all-heartbeat:
	$(MAKE) -C heartbeat all

# Cleans up build object.
clean-heartbeat:
	$(MAKE) -C heartbeat clean

# Cleans up everything.
distclean-heartbeat:
	$(MAKE) -C heartbeat distclean

#===============================================================================
# Barrier
#===============================================================================

# Builds benchmark.
all-barrier:
	$(MAKE) -C barrier all

# Cleans up build object.
clean-barrier:
	$(MAKE) -C barrier clean

# Cleans up everything.
distclean-barrier:
	$(MAKE) -C barrier distclean

#===============================================================================
# Lookup
#===============================================================================

# Builds benchmark.
all-lookup:
	$(MAKE) -C lookup all

# Cleans up build object.
clean-lookup:
	$(MAKE) -C lookup clean

# Cleans up everything.
distclean-lookup:
	$(MAKE) -C lookup distclean

#===============================================================================
# Page Fetch
#===============================================================================

# Builds benchmark.
all-pgfetch:
	$(MAKE) -C pgfetch all

# Cleans up build object.
clean-pgfetch:
	$(MAKE) -C pgfetch clean

# Cleans up everything.
distclean-pgfetch:
	$(MAKE) -C pgfetch distclean

#===============================================================================
# Memory Sync
#===============================================================================

# Builds benchmark.
all-msync:
	$(MAKE) -C msync all

# Cleans up build object.
clean-msync:
	$(MAKE) -C msync clean

# Cleans up everything.
distclean-msync:
	$(MAKE) -C msync distclean
