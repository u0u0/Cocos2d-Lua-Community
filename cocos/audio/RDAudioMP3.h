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

#ifndef __RDAudioMP3_H__
#define __RDAudioMP3_H__

#ifdef __cplusplus
extern "C" {
#endif

int decodeMP3(unsigned char *mp3Data,
              int mp3Size,
              unsigned char **pcmData,
              int *pcmChannels,
              int *pcmRate,
              int *pcmSize);

#ifdef __cplusplus
}
#endif

#endif // __RDAudioMP3_H__
