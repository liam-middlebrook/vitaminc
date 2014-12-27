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

#include <math.h>

#include "vitaminc.h"
#include "util.h"

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
