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

#include "RDAudioAAC.h"
#include "faad.h"

static int id3v2_tag(unsigned char *buffer)
{
    unsigned long tagsize = 0;
    if (strncmp((const char *)buffer, "ID3", 3) == 0) {
        /* high bit is not used */
        tagsize = (buffer[6] << 21) | (buffer[7] << 14) | (buffer[8] << 7) | (buffer[9] << 0);
        tagsize += 10;
    }
    return tagsize;
}

int decodeAAC(unsigned char *aacData,
              int aacSize,
              unsigned char **pcmData,
              int *pcmChannels,
              int *pcmRate,
              int *pcmSize)
{
    int size = id3v2_tag(aacData);
    int consumed = size;

    NeAACDecHandle hDecoder = NeAACDecOpen();
    NeAACDecConfigurationPtr config = NeAACDecGetCurrentConfiguration(hDecoder);
    config->dontUpSampleImplicitSBR = 1;
    
    unsigned long sampleRate;
    unsigned char channels;
    size = NeAACDecInit(hDecoder, aacData + consumed, aacSize - consumed, &sampleRate, &channels);
    if (size < 0) {
        NeAACDecClose(hDecoder);
        return -1;
    }
    consumed += size;
    
    NeAACDecFrameInfo frameInfo;
    int outSize = 0;
    void *output = NULL;
    void *sample = NULL;
    do {
        sample = NeAACDecDecode(hDecoder, &frameInfo, aacData + consumed, aacSize - consumed);
        consumed += frameInfo.bytesconsumed;
        if (frameInfo.error > 0) {
            printf("Error: %s\n", NeAACDecGetErrorMessage(frameInfo.error));
            if (output) free(output);
            NeAACDecClose(hDecoder);
            return -1;
        }
        if (frameInfo.samples > 0) {
            size = frameInfo.channels * frameInfo.samples;
            output = realloc(output, outSize + size);
            memcpy((char *)output + outSize, sample, size);
            outSize += size;
        }
        if (consumed >= aacSize) {
            break;
        }
    } while (sample != NULL);
    
    NeAACDecClose(hDecoder);
    
    *pcmData = (unsigned char *)output;
    *pcmChannels = channels;
    *pcmRate = sampleRate;
    *pcmSize = outSize;
    return 0;
}
