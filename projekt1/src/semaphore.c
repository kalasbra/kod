#include <semaphore.h>

static uint32_t semaphores = 0;

bool semaphore_reserve(const uint8_t sem_id) {
    if (sem_id > SEM_ID_MAX) return false;
    while (semaphores & (1ULL << sem_id));
    semaphores |= (1ULL << sem_id);
    return true;
}

bool semaphore_release(const uint8_t sem_id) {
    if (sem_id > SEM_ID_MAX) return false;
    semaphores &= ~(1ULL << sem_id);
    return true;
}