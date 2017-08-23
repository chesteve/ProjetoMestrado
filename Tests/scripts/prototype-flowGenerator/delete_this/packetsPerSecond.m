## Copyright (C) 2017 anderson
## 
## This program is free software; you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 3 of the License, or
## (at your option) any later version.
## 
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.

## -*- texinfo -*- 
## @deftypefn {Function File} {@var{retval} =} pps (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: anderson <anderson@duvel-ThinkCentre-M93p>
## Created: 2017-05-03

function [pps] = packetsPerSecond (arrival_time, fig_name)
	max = ceil(max(arrival_time));
	pps = zeros(max - 1, 1);
	
	for i = 1:(max - 1)
		pps(i) = length(arrival_time( (arrival_time>i) & (arrival_time< (i+1))));
	endfor
	
	fig = plot((1:(max - 1)), pps);
	plot_name = ['figures/' fig_name];
	saveas(fig, plot_name, 'pdf');

endfunction