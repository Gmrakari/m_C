#ifndef _DB_CFG_H
#define _DB_CFG_H

// 4k
#define DEFAULT_MEM_SIZE (4 * 1024)

#define USE_INIT_MEMORY_SECTOR       (1)

#define USE_ADD_TEST                 (0)

#if USE_ADD_TEST
    #define USE_TEST_ADD_NUM_MIN     (1)
    #define USE_TEST_ADD_NUM_MAX     (97)
#endif 

#define USE_DEL_TEST                 (0)

#define USE_SELECT_TEST              (0)

#endif // _DB_CFG_H