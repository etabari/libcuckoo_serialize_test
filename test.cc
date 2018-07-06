#include <libcuckoo/cuckoohash_map.hh>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <istream>
#include <cstddef>
#include <cstdint>
#include <cstdlib>

using namespace std;

const uint64_t total_inserts = 2000000000ULL;
// const uint64_t total_inserts = 200ULL;
cuckoohash_map<uint64_t, uint32_t> hashmap_1;


int main() {

	// Inseting 2B records in the hashmap
	uint32_t value = 0;
	for (uint64_t key = 0; key < total_inserts; key++) {
		hashmap_1.insert(key, value);
		// Just some values
		value = ++value % 100000;
	}

	cout << "Hash Created: \n";
	cout << "  size: " << hashmap_1.size() << '\n';
	cout << "  bucket_count: " << hashmap_1.bucket_count() << '\n';
	cout << "  load_factor: " << hashmap_1.load_factor() << '\n';
	cout << "  capacity: " << hashmap_1.capacity() << '\n';

	{
		// Saving into a file
		std::ofstream ostrm("libcuckoo_test.bin", std::ios::binary);
		auto lt_1 = hashmap_1.lock_table();
		ostrm << lt_1;
		ostrm.close();
		cout << "Hash written to file\n";
	}

	cuckoohash_map<uint64_t, uint32_t> hashmap_2;

	{
		// Loading the file:
		std::ifstream instrm("libcuckoo_test.bin", std::ios::binary);
		auto lt_2 = hashmap_2.lock_table();
		instrm >> lt_2;
	}

	cout << "Hash Loaded: \n";
	cout << "  size: " << hashmap_2.size() << '\n';
	cout << "  bucket_count: " << hashmap_2.bucket_count() << '\n';
	cout << "  load_factor: " << hashmap_2.load_factor() << '\n';
	cout << "  capacity: " << hashmap_2.capacity() << '\n';

}