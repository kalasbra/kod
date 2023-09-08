/********************************************************************************
 * @brief Library containing functionality for using semaphores.
 ********************************************************************************/
#pragma once

/********************************************************************************
 * @brief Everything between extern "C" { and } is compiled as C code. 
 ********************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/********************************************************************************
 * @brief Semaphore attributes. Valid semaphore ID:s are in the range 0 - 31.
 * 
 * @param SEM_ID_MIN
 *        The lowest permitted semaphore ID.
 * @param SEM_ID_MAX
 *        The highest permitted semaphore ID.
 ********************************************************************************/
#define SEM_ID_MIN 0
#define SEM_ID_MAX 31

/********************************************************************************
 * @brief Reserves semaphore with specified ID. The calling thread is blocked
 *        until the semaphore is available.
 * 
 * @param sem_id
 *        The ID of semaphore to reserve.
 * @return 
 *        True upon reserved semaphore, else false if an invalid semaphore ID
 *        was specified.
 ********************************************************************************/
bool semaphore_reserve(const uint8_t sem_id);

/********************************************************************************
 * @brief Releases semaphore with specified ID. 
 * 
 * @param sem_id
 *        The ID of semaphore to release.
 * @return 
 *        True upon released semaphore, else false if an invalid semaphore ID
 *        was specified.
 ********************************************************************************/
bool semaphore_release(const uint8_t sem_id);

#ifdef __cplusplus
} /* extern C */
#endif 