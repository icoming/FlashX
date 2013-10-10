#ifndef __MY_PARAMETERS_H__
#define __MY_PARAMETERS_H__

#include <iostream>
#include <map>
#include <string>

#define USE_GCLOCK

#define PAGE_SIZE 4096
#define LOG_PAGE_SIZE 12

#define MIN_BLOCK_SIZE 512

class sys_parameters
{
	int RAID_block_size;
	int SA_min_cell_size;
	int test_hit_rate;
	int io_depth_per_file;
	int cache_type;
	int cache_size;
	int RAID_mapping_option;
	bool use_virt_aio;
	bool verify_content;
	bool use_flusher;
	bool cache_large_write;
public:
	sys_parameters();

	void init(const std::map<std::string, std::string> &parameters);

	void print();
	void print_help();

	int get_RAID_block_size() const {
		return RAID_block_size;
	}

	int get_SA_min_cell_size() const {
		return SA_min_cell_size;
	}

	int get_test_hit_rate() const {
		return test_hit_rate;
	}

	int get_aio_depth_per_file() const {
		return io_depth_per_file;
	}

	int get_cache_type() const {
		return cache_type;
	}

	int get_cache_size() const {
		return cache_size;
	}

	int get_RAID_mapping_option() const {
		return RAID_mapping_option;
	}

	bool is_use_virt_aio() const {
		return use_virt_aio;
	}

	bool is_verify_content() const {
		return verify_content;
	}

	bool is_use_flusher() const {
		return use_flusher;
	}

	bool is_cache_large_write() const {
		return cache_large_write;
	}
};

extern sys_parameters params;

#define AIO_DEPTH_PER_FILE params.get_aio_depth_per_file()

/**
 * The size of an I/O message sent to an I/O thread.
 * It is in the number of I/O requests.
 */
const int IO_MSG_SIZE = AIO_DEPTH_PER_FILE;
/**
 * The size of a high-priority I/O queue.
 * It's in the number of I/O messages.
 */
const int IO_QUEUE_SIZE = 10;
const int MAX_FETCH_REQS = 3;
const int AIO_COMPLETE_BUF_SIZE = 8;

/**
 * The time interval that I/O threads flush the buffered notifications
 * of IO completion.
 */
const int COMPLETION_FLUSH_INTERVAL = 200 * 1000 * 1000;
/**
 * This number defines the max number of flushes sent to an SSD.
 * The number is set based on the performance result.
 * It varies in different SSDs. It's better that we can estimate at runtime.
 */
const int MAX_NUM_FLUSHES_PER_FILE = 2048;

const int MAX_DISK_CACHED_REQS = 1000;

/**
 * The number of requests issued by user applications
 * in one access.
 */
const int NUM_REQS_BY_USER = 1000;

/**
 * The initial size of the queue for pending IO requests
 * in the global cache.
 */
const int INIT_GCACHE_PENDING_SIZE = NUM_REQS_BY_USER * 100;

/**
 * The min size of IO vector allocated for an IO request..
 */
const int MIN_NUM_ALLOC_IOVECS = 16;
const int NUM_EMBEDDED_IOVECS = 1;

/**
 * The maximal size of IO vector issued by the global cache.
 * The experiment shows AIO with 16 pages in a request can achieve
 * the best performance.
 */
const int MAX_NUM_IOVECS = 16;

const int CELL_SIZE = 16;
const int CELL_MIN_NUM_PAGES = 8;

const int MAX_NUM_DIRTY_CELLS_IN_QUEUE = 1000;
const int DIRTY_PAGES_THRESHOLD = 1;
const int NUM_WRITEBACK_DIRTY_PAGES = 2;
const int MAX_NUM_WRITEBACK = 4;
const int DISCARD_FLUSH_THRESHOLD = 6;

const long MAX_CACHE_SIZE = ((long) 4096) * 1024 * 1024 * 2;

const int NUMA_MSG_SIZE = 4096;
const int NUMA_REQ_QUEUE_SIZE = 2000;
const int NUMA_REPLY_CACHE_SIZE = 50;
const int NUMA_REPLY_QUEUE_SIZE = 1024;
const int NUMA_NUM_PROCESS_THREADS = 8;

const int LOCAL_BUF_SIZE = 100;

struct str2int {
	std::string name;
	int value;
};

class str2int_map {
	str2int *maps;
	int num;
public:
	str2int_map(str2int *maps, int num) {
		this->maps = maps;
		this->num = num;
	}

	int map(const std::string &str) {
		for (int i = 0; i < num; i++) {
			if (maps[i].name.compare(str) == 0)
				return i;
		}
		return -1;
	}

	void print(const std::string &str) {
		std::cout<<str;
		for (int i = 0; i < num; i++) {
			std::cout<<maps[i].name;
			if (i < num - 1)
				std::cout<<", ";
		}
		std::cout<<std::endl;
	}
};

#endif
