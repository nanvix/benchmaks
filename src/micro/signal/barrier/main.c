/*
 * MIT License
 *
 * Copyright(c) 2011-2020 The Maintainers of Nanvix
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <nanvix/runtime/runtime.h>
#include <nanvix/sys/perf.h>
#include <nanvix/limits.h>
#include <nanvix/ulib.h>

/**
 * @brief Number of iterations for the benchmark.
 */
#ifdef NDEBUG
#define NITERATIONS 30
#else
#define NITERATIONS 1
#endif

/*============================================================================*
 * Benchmark Kernel                                                           *
 *============================================================================*/

/**
 * @brief Forces a platform-independent delay.
 *
 * @param cycles Delay in cycles.
 *
 * @author João Vicente Souto
 */
static void delay(int times, uint64_t cycles)
{
	uint64_t t0, t1;

	for (int i = 0; i < times; ++i)
	{
		kclock(&t0);

		do
			kclock(&t1);
		while ((t1 - t0) < cycles);
	}
}

/*
 * Build a list of the node IDs
 *
 * @param cluster Nodes list buffer
 *
 * @author João Vicente Souto
 */
static void build_node_list(int * clusters, int nclusters)
{
	uassert(clusters != NULL);

	for (int i = 0; i < nclusters; ++i)
		clusters[i] = PROCESSOR_NODENUM_LEADER + i;
}

/**
 * @bbrief Receives data from worker.
 */
static void do_leader(void)
{
	int syncin;
	int syncout;
	int clusters[PROCESSOR_CCLUSTERS_NUM];

	build_node_list(clusters, PROCESSOR_CCLUSTERS_NUM);

	/* Establish connection. */
	uassert((
		syncin = ksync_create(
				clusters,
				PROCESSOR_CCLUSTERS_NUM,
				SYNC_ALL_TO_ONE)
		) >= 0
	);
	uassert((
		syncout = ksync_open(
				clusters,
				PROCESSOR_CCLUSTERS_NUM,
				SYNC_ONE_TO_ALL)
		) >= 0
	);

	delay(5, CLUSTER_FREQ);

	/* Broadcast data. */
	for (int k = 1; k <= NITERATIONS; k++)
	{
		uassert(ksync_wait(syncin) == 0);
		uassert(ksync_signal(syncout) == 0);
	}

	/* House keeping. */
	uassert(ksync_close(syncout) == 0);
	uassert(ksync_unlink(syncin) == 0);
}

/**
 * @brief Sends data to leader.
 */
static void do_worker(void)
{
	int syncin;
	int syncout;
	uint64_t lin0, lin1;
	uint64_t lout0, lout1;
	int clusters[PROCESSOR_CCLUSTERS_NUM];

	build_node_list(clusters, PROCESSOR_CCLUSTERS_NUM);

	/* Establish connection. */
	uassert((
		syncin = ksync_create(
				clusters,
				PROCESSOR_CCLUSTERS_NUM,
				SYNC_ONE_TO_ALL)
		) >= 0
	);
	uassert((
		syncout = ksync_open(
				clusters,
				PROCESSOR_CCLUSTERS_NUM,
				SYNC_ALL_TO_ONE)
		) >= 0
	);

	delay(5, CLUSTER_FREQ);

	uassert(ksync_ioctl(syncin, KSYNC_IOCTL_GET_LATENCY, &lin0) == 0);
	uassert(ksync_ioctl(syncout, KSYNC_IOCTL_GET_LATENCY, &lout0) == 0);

	for (int i = 1; i <= NITERATIONS; i++)
	{
		uassert(ksync_signal(syncout) == 0);
		uassert(ksync_wait(syncin) == 0);

		uassert(ksync_ioctl(syncin, KSYNC_IOCTL_GET_LATENCY, &lin1) == 0);
		uassert(ksync_ioctl(syncout, KSYNC_IOCTL_GET_LATENCY, &lout1) == 0);

		/* Dump statistics. */
#ifndef NDEBUG
		uprintf("[benchmarks][signal-barrier] it=%d latency_in=%l latency_out=%l",
#else
		uprintf("[benchmarks][signal-barrier] %d %l %l",
#endif
			i, (lin1 - lin0), (lout1 - lout0)
		);

		lin0  = lin1;
		lout0 = lout1;
	}

	/* House keeping. */
	uassert(ksync_close(syncout) == 0);
	uassert(ksync_unlink(syncin) == 0);
}

/**
 * @brief Benchmarks barrier communication with syncs.
 */
static void benchmark_signal_barrier(void)
{
	void (*fn)(void);

	fn = (knode_get_num() == PROCESSOR_NODENUM_LEADER) ?
		do_leader : do_worker;

	fn();
}

/*============================================================================*
 * Benchmark Driver                                                           *
 *============================================================================*/

/**
 * @brief Launches a benchmark.
 */
int __main3(int argc, const char *argv[])
{
	((void) argc);
	((void) argv);

	benchmark_signal_barrier();

	return (0);
}
