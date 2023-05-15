/*
 * Date:15 May 2023 11:19 PM
 * Filename:_p2p_normal.c
*/

#include "_p2p.h"
#include "_p2p_normal.h"

typedef struct {
    gmrakari_ptr_type_t type;
} gmrakari_ptr_private_t;

static gmrakari_ptr_t *me;


static int _gmrakari_ptr_normal_init(void *param)
{
    int ret = 0;

    gmrakari_ptr_t *gmrakari_ptr = (gmrakari_ptr_t *)me;
    if (gmrakari_ptr->is_init) {
        printf("gmrakari_ptr reinit\r\n");
        ret = -1;
        goto _exit;
    }

    int get_param = (int *)param;

    static gmrakari_ptr_private_t private;
    gmrakari_ptr->private = &private;

    private.type = GMRAKRI_PTR_TYPE_NORMAL;

    printf("gmrakari ptr init ok\r\n");

    if (get_param == 0) {
        printf("get_param err\r\n");
        ret = -2;
        goto _exit;
    }

    gmrakari_ptr->is_init = 1;

_exit:
    return ret;
}

static void _gmrakari_ptr_normal_deinit(void)
{

}

static void _gmrakari_ptr_normal_lock()
{

}

static void _gmrakari_ptr_normal_unlock()
{

}

static void _gmrakari_ptr_normal_control(int cmd, ...)
{

}

static void _gmrakri_ptr_normal_func(void)
{

}

int GMRAKRI_PTR_TYPE_NORMAL_INIT(gmrakari_ptr_t *ptr)
{
    int ret = 0;

    ptr->init = _gmrakari_ptr_normal_init;
    ptr->deinit = _gmrakari_ptr_normal_deinit;

    ptr->lock = _gmrakari_ptr_normal_lock;
    ptr->unlock = _gmrakari_ptr_normal_unlock;

    ptr->control = _gmrakari_ptr_normal_control;
    ptr->func = _gmrakri_ptr_normal_func;

    me = ptr;

    return ret;
}