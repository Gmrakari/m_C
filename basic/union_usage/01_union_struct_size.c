#include <stdio.h>
#include <stdint.h>
#include <stdlib.h> // malloc / free
#include <string.h> // memcpy

typedef unsigned char gm_dp_prop_type_t;

typedef union {
    int32_t dp_value;   
    uint32_t dp_enum;   
    char *dp_str;       
    char *dp_raw;       
    int32_t dp_bool;    
    uint32_t dp_bitmap; 
} gm_dp_value_type_t;

typedef enum {
    GM_DP_VALUE = 0,
    GM_DP_ENUM,
    GM_DP_STR,
    GM_DP_RAW,
    GM_DP_BOOL,
    GM_DP_BITMAP,
    GM_DP_DEFAULT
} dp_type_enum_t;

typedef struct {
    char *name;                    // Data point name
    uint8_t dpid;                  // Data point ID
    gm_dp_prop_type_t type;        // Data point type
    gm_dp_value_type_t value;      // Data point value
    uint32_t time_stamp;           // Timestamp of the data point event, 0 means now
} gm_dp_obj_t;

static size_t _get_union_struct_size()
{
    gm_dp_value_type_t type;
    size_t type_size = sizeof(type);
    return type_size;
}

static void _test_union_size()
{
    size_t type_size = _get_union_struct_size();
    printf("len: %ld\r\n", type_size);
}

static int _read_union_member(gm_dp_value_type_t *type, int read_count, dp_type_enum_t type_info)
{
    if (!type)
        return -1;

    size_t max_member_size = sizeof(int32_t);
    if (sizeof(uint32_t) > max_member_size)
        max_member_size = sizeof(uint32_t);
    
    if (sizeof(char *) > max_member_size)
        max_member_size = sizeof(char *);

    if (sizeof(int32_t) > max_member_size)
        max_member_size = sizeof(int32_t);

    size_t type_member_num = sizeof(gm_dp_value_type_t) / max_member_size;

    // if (read_count == 0) {
    //     printf("type_member_num:%ld\r\n", type_member_num);
    //     printf("dp_value: %d\r\n", type->dp_value);
    //     printf("dp_enum: %d\r\n", type->dp_enum);
    //     printf("dp_str: %s\r\n", type->dp_str);
    //     printf("dp_raw: %s\r\n", type->dp_raw);
    //     printf("dp_bool: %d\r\n", type->dp_bool);
    //     printf("dp_bitmap: %d\r\n", type->dp_bitmap);
    //     return 0;
    // }

    if (read_count == 1) {
        switch(type_info) {
            case GM_DP_VALUE: {
                printf("dp_value: %d\r\n", type->dp_value);
                break;
            }
            case GM_DP_ENUM: {
                printf("dp_enum: %d\r\n", type->dp_enum);
                break;
            }
            case GM_DP_STR: {
                printf("dp_str: %s\r\n", type->dp_str);
                break;
            }
            case GM_DP_RAW: {
                printf("dp_raw: %s\r\n", type->dp_raw);
                break;
            }
            case GM_DP_BOOL: {
                printf("dp_bool: %d\r\n", type->dp_bool);
                break;
            }
            case GM_DP_BITMAP: {
                printf("dp_bitmap: %d\r\n", type->dp_bitmap);
                break;
            }
            default :
                break;
        }

    }

    return 0;
}

static int _write_union_member(gm_dp_value_type_t *type, dp_type_enum_t type_info, void *param)
{
    if (!type) return -1;

    switch(type_info) {
        case GM_DP_VALUE: {
            int32_t *value = (int32_t *)param;
            type->dp_value = *value;
            break;
        }
        case GM_DP_ENUM: {
            uint32_t *c_enum = (int32_t *)param;
            type->dp_enum = *c_enum;
            break;
        }
        case GM_DP_STR: {
            char *str = (char *)param;
            type->dp_str = str;
            break;
        }
        case GM_DP_RAW: {
            char *raw = (char *)param;
            type->dp_raw = raw;
            break;
        }
        case GM_DP_BOOL: {
            int32_t *c_bool = (int32_t *)param;
            type->dp_bool = *c_bool;
            break;
        }
        case GM_DP_BITMAP: {
            uint32_t *bitmap = (int32_t *)param;
            type->dp_bitmap = *bitmap;
            break;
        }
        default :
            break;
    }

    return 0;
}

static int _write_union_member_test_case(gm_dp_value_type_t *type) 
{
    int ret = 0;
    int32_t value = 11;printf("[%s][%d]\r\n", __func__, __LINE__);
    ret = _write_union_member(type, GM_DP_VALUE, &value);printf("[%s][%d]\r\n", __func__, __LINE__);
    if (ret == 0) {
        _read_union_member(type, 1, GM_DP_VALUE);
    }

    uint32_t m_enum = 22;
    ret = _write_union_member(type, GM_DP_ENUM, &m_enum);
    if (ret == 0) {
        _read_union_member(type, 1, GM_DP_ENUM);
    }

    char str2[] = "33 dp_str info";
    ret = _write_union_member(type, GM_DP_STR, &str2);
    if (ret == 0) {
        _read_union_member(type, 1, GM_DP_STR);
    }

    char raw2[] = "44 dp_raw info";
    ret = _write_union_member(type, GM_DP_RAW, &raw2);
    if (ret == 0) {
        _read_union_member(type, 1, GM_DP_RAW);
    }

    int32_t c_bool = 55;
    ret = _write_union_member(type, GM_DP_BOOL, &c_bool);
    if (ret == 0) {
        _read_union_member(type, 1, GM_DP_BOOL);
    }

    uint32_t bitmap = 66;
    ret = _write_union_member(type, GM_DP_BITMAP, &bitmap);
    if (ret == 0) {
        _read_union_member(type, 1, GM_DP_BITMAP);
    }

    return ret;
}

static int _test_read_write_union_member()
{
    int ret = 0;

    gm_dp_value_type_t type;

    char m_string[] = "3 dp_str info";
    char m_raw[] = "4 dp_raw info";
    size_t str_len = 20;
    size_t raw_len = 20;
    char *str = malloc(sizeof(char) * str_len);
    memset(str, 0x00, str_len);
    memcpy(str, m_string, sizeof(m_string));

    char *raw = malloc(sizeof(char) * raw_len);
    memset(raw, 0x00, raw_len);
    memcpy(raw, m_raw, sizeof(m_raw));

    type.dp_value = 1;
    type.dp_enum = 2;
    type.dp_str = str;
    type.dp_raw = raw;
    type.dp_bool = 5;
    type.dp_bitmap = 6;
    _read_union_member(&type, 0, GM_DP_DEFAULT);

    if (type.dp_str) {
        free(type.dp_str);
        type.dp_str = NULL;
    }

    if (type.dp_raw) {
        free(type.dp_raw);
        type.dp_raw = NULL;
    }

    // test pass
    // ret = _write_union_member_test_case(&type);
    // if (ret != 0) 
    //     return ret;

    return ret;
}

static void _test_01()
{
    // _test_union_size();
    _test_read_write_union_member();
}

int main() 
{
    _test_01();

    return 0;
}
