#ifndef _DB_H_
#define _DB_H_

/**
 *  Global View
 * 
 *  Sector size         = BLOCK_SIZE
 *  Head size           = sizeof(db_header_t)
 *  None size           = BLOCK_SIZE - sizeof(db_header_t)
 *  All face info size  = DB_NUM * DB_ITEM_SIZE    (Valid size is sizeof(db_item_t))
 *  ___________________________________________________________________________
 * |      Sector0      |      Sector1      |      ...      |      SectorN      |
 * |___________________|___________________|_______________|___________________|
 * | Head |    None    |                      All face info                    |
 * |______|____________|_______________________________________________________|
*/


#define DB_HEAD_SIGN    (0xAB5555AB)
#define DB_HEAD_VERSION (0x00000001)

#endif // _DB_H_