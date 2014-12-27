/*
# Copyright (c) 2014, Liam Middlebrook
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
*/

#ifndef _VC_VITAMINC_H_
#define _VC_VITAMINC_H_

#define VC_COLOR_FORMAT char
#define VC_RGB 0
#define VC_HSL 1

typedef struct {
        double r, g, b, h, s, l, a;
} vc_color;

typedef struct {
        double x, y, z;
} vc_color_data;

int _RybWheel = {
    0,  26,  52,
   83, 120, 130,
  141, 151, 162,
  177, 190, 204,
  218, 232, 246,
  261, 275, 288,
  303, 317, 330,
  338, 345, 352,
  360};

int _RgbWheel = {
    0,   8,  17,
   26,  34,  41,
   48,  54,  60,
   81, 103, 123,
  138, 155, 171,
  187, 204, 219,
  234, 251, 267,
  282, 298, 329,
  360};

vc_color_data vc_rgb_hsl(vc_color color);

double vc_hue_rgb(double n1, double n2, double h);

double vc_hue_rgb(double n1, double n2, double h);

vc_color vc_create_color(
                double x,
                double y,
                double z,
                VC_COLOR_FORMAT fmt,
                double a);
#endif
