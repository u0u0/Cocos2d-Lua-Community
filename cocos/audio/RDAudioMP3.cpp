// Copyright 2021 KeNan Liu
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "RDAudioMP3.h"

#define MINIMP3_IMPLEMENTATION
#define MINIMP3_FLOAT_OUTPUT
#include "minimp3_ex.h"

int decodeMP3(unsigned char *mp3Data,
              int mp3Size,
              unsigned char **pcmData,
              int *pcmChannels,
              int *pcmRate,
              int *pcmSize)
{
    mp3dec_t mp3d;
    mp3dec_file_info_t info;
    memset(&info, 0, sizeof(info));

    int ret = mp3dec_load_buf(&mp3d, mp3Data, mp3Size, &info, 0, 0);
    if(0 != ret) {
        printf("error: mp3dec_load_buf %d\n", ret);
        return -1;
    }

    int size = info.samples * sizeof(int16_t);
    int16_t* buffer = (int16_t *)malloc(size);
    if (!buffer) {
        printf("error: decodeMP3 not enough memory\n");
        return -1;
    }
    mp3dec_f32_to_s16(info.buffer, buffer, info.samples);
    free(info.buffer);

    *pcmData = (unsigned char*)buffer;
    *pcmChannels = info.channels;
    *pcmRate = info.hz;
    *pcmSize = size;
    return 0;
}
