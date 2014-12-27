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

#include <stdarg.h>
#include <math.h>

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

double vc_maxval(int count, ...){
	va_list values;
	int i;
	double max;

	va_start(values, count);

	max = 0.0f;
	for(i = 0; i < count; ++i)
	{
		double val = va_arg(values, int);
		max = (max > val) ? max : val;
	}
	
	va_end(values);
	return max;
}

double vc_minval(int count, ...){
	va_list values;
	int i;
	double min;

	va_start(values, count);

	min = 0.0f;
	for(i = 0; i < count; ++i)
	{
		double val = va_arg(values, int);
		min = (min < val) ? min : val;
	}
	
	va_end(values);
	return min;
}

vc_color_data vc_rgb_hsl(vc_color color){
	double minVal = vc_minval(3, color.r, color.g, color.b);
	double maxVal = vc_maxval(3, color.r, color.g, color.b);

	double h, s, l;
	l = (maxVal + minVal) / 2.0;
	if(minVal == maxVal){
		return (vc_color_data){
				.x = 0.0,
				.y = 0.0,
				.z = l};
	}

	double d = maxVal - minVal;

	if( l < 0.5) s = d / (maxVal + minVal);
	else s = d / (2.0 - maxVal - minVal);

	double dr = (maxVal - color.r) / d;
	double dg = (maxVal - color.g) / d;
	double db = (maxVal - color.b) / d;

	if(color.r == maxVal) h = db - dg;
	else if(color.g == maxVal) h = 2.0 + dr - db;
	else h = 4.0 + dg - dr;

	h = fmod((h * 360),360.0);

 	return (vc_color_data){
 			.x = h,
			.y = s,
  			.z = l};
}

double vc_hue_rgb(double n1, double n2, double h){
	
	h = fmod(h, 6.0);
	if(h < 1.0) return n1 + ((n2 - n1) * h);
	if(h < 3.0) return n2;
	if(h < 4.0) return n1 + ((n2 - n1) * (4.0 - h));
	return n1;
}

vc_color_data vc_hsl_rgb(vc_color color){
	if(color.s == 0) return (vc_color_data){
					.x = 1,
					.y = 1,
					.z = 1};
	double r, g, b, n1, n2;
	if(color.l < 0.5) n2 = color.l * (1.0 + color.s);
	else n2 = color.l + color.s - (color.l * color.s);
	
	n1 = (2.0 * color.l) - n2;

	color.h /= 60.0;

	r = vc_hue_rgb(n1, n2, color.h + 2);
	g = vc_hue_rgb(n1, n2, color.h);
	b = vc_hue_rgb(n1, n2, color.h - 2);

	return (vc_color_data){
			.x = r,
			.y = g,
			.z = b};
}

vc_color vc_create_color(
		double x,
		double y,
		double z,
		VC_COLOR_FORMAT fmt,
  		double a){
	vc_color color;
	
	vc_color_data other_fmt;

 	switch(fmt){
		case VC_RGB:
			color.r = x;
			color.g = y;
			color.b = z;

			other_fmt = vc_rgb_hsl(color);

			color.h = other_fmt.x;
			color.s = other_fmt.y;
			color.l = other_fmt.z;
		break;
		case VC_HSL:
			color.h = x;
			color.s = y;
			color.l = z;

			other_fmt = vc_hsl_rgb(color);

			color.r = other_fmt.x;
			color.g = other_fmt.y;
			color.b = other_fmt.z;
		break;
	}

	color.a = a;
}
