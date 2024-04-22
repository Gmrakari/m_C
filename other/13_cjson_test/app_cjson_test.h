#include "cJSON.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    char *appid;
    int appid_len;
} asr_common_param_t;

typedef struct {
    char language[8];
    char domain[24];
    char accent[24];
    int vad_eos;
    char dwa[8];
    char pd[16];
    int ptt;
    char rlang[8];
    int vinfo;
    int nunum;
    int speex_size;
    int nbest;
    int wbest;
} asr_business_param_t;

typedef struct {
    int status;
    char format[24];
    char encode[12];
    char *audio;
    int audio_len;
} asr_data_param_t;

cJSON* asr_generate_common_param(asr_common_param_t *param);

cJSON* asr_generate_business_param(asr_business_param_t *param);

cJSON* asr_generate_data_param(asr_data_param_t *param);

cJSON* asr_generate_root(cJSON *comm, cJSON *business, cJSON *data);
