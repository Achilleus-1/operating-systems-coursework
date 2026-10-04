#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
// Project made by   and  


// memory setup
#define PAGE_SIZE 256
#define NUM_PAGES 256
#define NUM_FRAMES 128
#define MEMORY_SIZE (NUM_FRAMES * PAGE_SIZE)

// set up global structures
int page_table[NUM_PAGES];
int frame_usage[NUM_FRAMES];
int lru_counter[NUM_FRAMES];
signed char physical_memory[NUM_FRAMES][PAGE_SIZE];
int time_counter = 0;
int next_frame = 0;
int page_faults = 0;

 
// setup and ititialize the memory structures
void initialize() {
    int i;
    for (i = 0; i < NUM_PAGES; i++) page_table[i] = -1;
    for (i = 0; i < NUM_FRAMES; i++) {
        frame_usage[i] = -1;
        lru_counter[i] = 0;
    }
}
 
// find the Least Recently Used frame (LRU)
int find_lru_frame() {
    int lru = 0;
    int i;
    for (i = 1; i < NUM_FRAMES; i++) {
        if (lru_counter[i] < lru_counter[lru]) lru = i;
    }
    return lru;
}


// pull backingstore into virtual memory
void load_page(FILE* backing_store, int page_number, int frame_number) {
    fseek(backing_store, page_number * PAGE_SIZE, SEEK_SET);
    fread(physical_memory[frame_number], sizeof(signed char), PAGE_SIZE, backing_store);
}


// makes the snapshots for the output report

void write_snapshot(FILE* output, const char* label, int snapshot[NUM_PAGES]) {
    int i;
    fprintf(output, "\n==== Page Table Snapshot %s ====\n", label);
    for (i = 0; i < NUM_PAGES; i++) {
        if (snapshot[i] != -1) {
            fprintf(output, "Page %d -> Frame %d\n", i, snapshot[i]);
        }
    }
}

int main() 
{

    // opens the required files using fopen

    FILE* addr_file = fopen("addresses.txt", "r");
    FILE* backing_store = fopen("BACKING_STORE.bin", "rb");
    FILE* output = fopen("output_report.txt", "w");

    // just in case it cant open any of the files it errors out here

    if (!addr_file || !backing_store || !output) {
        perror("Error opening file");
        return 1;
    }


    // sets up the tables and the counters

    initialize();
    int logical_address;
    int access_count = 0;
    int snapshot_500[NUM_PAGES];
    int snapshot_631[NUM_PAGES];
    // processes the locical addresses
    while (fscanf(addr_file, "%d", &logical_address) != EOF) {
        // pulls the page number and the offset
        int page_number = (logical_address >> 8) & 0xFF;
        int offset = logical_address & 0xFF;
        int frame_number;

        if (page_table[page_number] != -1) {
            frame_number = page_table[page_number];
        } else {
            page_faults++;
            if (next_frame < NUM_FRAMES) {
                frame_number = next_frame++;
            } else {
                frame_number = find_lru_frame();
                int evicted_page = frame_usage[frame_number];
                page_table[evicted_page] = -1;
            }

            // loads a new page and update tables
            load_page(backing_store, page_number, frame_number);
            page_table[page_number] = frame_number;
            frame_usage[frame_number] = page_number;
        }


        // updates the LRU usage
        lru_counter[frame_number] = ++time_counter;


        // computes the physical addresses and values
        int physical_address = (frame_number * PAGE_SIZE) + offset;
        signed char value = physical_memory[frame_number][offset];


        // output traslation
        fprintf(output, "Logical Address: %d Physical Address: %d Value: %d\n",
                logical_address, physical_address, value);


        // snapshot checkpoints
        access_count++;
        if (access_count == 500) {
            int i;
            for (i = 0; i < NUM_PAGES; i++) snapshot_500[i] = page_table[i];
        }
        if (access_count == 631) {
            int i;
            for (i = 0; i < NUM_PAGES; i++) snapshot_631[i] = page_table[i];
        }
    }

 

 
    //just for printing all  stats and fault rate

    fprintf(output, "\n==== Summary Statistics ====\n");
    fprintf(output, "Total Address References: %d\n", access_count);
    fprintf(output, "Total Page Faults: %d\n", page_faults);
    fprintf(output, "Page Fault Rate: %.2f%%\n", (page_faults / (float)access_count) * 100);

    // Snapshot logs

    write_snapshot(output, "After 500th Access", snapshot_500);
    write_snapshot(output, "After 631st Access", snapshot_631);

    // close files with required fclose
    fclose(addr_file);
    fclose(backing_store);
    fclose(output);

    // prints to confirm code finished totally
    printf("Simulation complete.\n");

    return 0;
}