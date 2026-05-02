#define START_H
struct system_general_info {
    char cpu_name[49];
    uint64_t mm_mx;
};
extern struct system_general_info System_info; // 'extern' diz que está em outro lugar
void setup_start(uint32_t magic, struct multiboot_info* mbi);